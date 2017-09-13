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
                     default=False, help="run all tests")
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
    # or just ../build/val3dity
    # or find the executable in the val3dity folder
    # TODO: find out how can the path to the val3dity exec. passed as an argument to pytest
    return("path to val3dity executable as argument")

@pytest.fixture(scope="session")
def options_solid():
    return(["--unittests", "-p Solid"])

@pytest.fixture(scope="session")
def options_citymodel():
    return(["--unittests"])


VAL3DITYEXE = "/home/bdukai/Development/val3dity/build/val3dity"
# VAL3DITYEXE = os.path.abspath(VAL3DITYEXE)
SOLIDFOLDER = "/home/bdukai/Development/val3dity/tests/test_geometry_generic"
# SOLIDFOLDER = os.path.abspath(SOLIDFOLDER)

options_solid = ["--unittests", "-p Solid"]
options_citymodel = ["--unittests"]
val3dity_exe = VAL3DITYEXE
data_path = "../data/test_geometry_generic"

def validate(val3dity, data_path, file, options_solid):
    file_path = os.path.join(data_path, file)
    command = [val3dity] + options_solid + [file_path]
    
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


