import pytest
import subprocess
import os.path
import sys

#------------------------- use concurrent test execution if xdist is installed
# def pytest_cmdline_preparse(args):
#     if 'xdist' in sys.modules:  # pytest-xdist plugin
#         print("using xdist")
#         import multiprocessing
#         num = int(max(multiprocessing.cpu_count() / 2, 1))
#         args[:] = ["-n", str(num)] + args
#     else:
#         print("xdist not installed")


#------------------------------------ add option for running the full test set
def pytest_addoption(parser):
    parser.addoption("--runfull", action="store_true",
                     default=False, help="run full set of tests")
def pytest_collection_modifyitems(config, items):
    if config.getoption("--runfull"):
        # --runslow given in cli: do not skip slow tests
        return
    skip_full = pytest.mark.skip(reason="need --runfull option to run")
    for item in items:
        if "full" in item.keywords:
            item.add_marker(skip_full)

#------------------------------------------------------------ session fixtures
@pytest.fixture(scope="session")
def val3dity():
    """path to val3dity executable"""
    root = os.getcwd()
    p = os.path.join(root, "build/val3dity")
    return(os.path.abspath(p))

@pytest.fixture(scope="session")
def solid():
    """val3dity options for validating a solid"""
    return(["--unittests", "-p Solid"])

@pytest.fixture(scope="session")
def citymodel():
    """val3dity options for validating a solid"""
    return(["--unittests"])

@pytest.fixture(scope="session")
def validate():
    def _validate(file_path, options=solid(), val3dity=val3dity()):
        """Validate a file
        
        :return: The error numbers. Empty list if the file is valid.
        :rtype: list
        """
        
        command = [val3dity] + options + [file_path]
        
        cp = subprocess.run(command, stdout=subprocess.PIPE,
                            universal_newlines=True)
        summary = cp.stdout
        
        output = []
        if (summary != ''):
            if (summary.find('@VALID') != -1):
                return(output)
            i = summary.find('@INVALID')
            s = summary[i+9:]
            tmp = s.split(" ")
            codes = map(int, tmp[:-1])
            for each in codes:
                if output.count(each) == 0:
                    output.append(each)
        return(output)
    
    return(_validate)

