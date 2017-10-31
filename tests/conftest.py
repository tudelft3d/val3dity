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

@pytest.fixture(scope="session")
def val3dity():
    """path to val3dity executable"""
    root = os.getcwd()
    p = os.path.join(root, "build/val3dity")
    return(os.path.abspath(p))

#-------------------------------------------------------------- data & folders
@pytest.fixture(scope="session")
def dir_file_format():
    """path to the data for test_file_format"""
    root = os.getcwd()
    dir_path = os.path.join(root, "data/test_file_format")
    return(dir_path)


@pytest.fixture(scope="session")
def dir_valid():
    """path to the data for test_valid"""
    root = os.getcwd()
    dir_path = os.path.join(root, "data/test_valid")
    return(dir_path)


@pytest.fixture(scope="session")
def dir_empty():
    """path to the data for test_empty"""
    root = os.getcwd()
    dir_path = os.path.join(root, "data/test_empty")
    return(dir_path)


@pytest.fixture(scope="session")
def dir_geometry_generic():
    """path to the data for test_geometry_generic"""
    root = os.getcwd()
    dir_path = os.path.join(root, "data/test_geometry_generic")
    return(dir_path)


@pytest.fixture(scope="session")
def dir_geometry_specific():
    """path to the data for test_geometry_specific"""
    root = os.getcwd()
    dir_path = os.path.join(root, "data/test_geometry_specific")
    return(dir_path)


@pytest.fixture(scope="session")
def data_basecube():
    """unit cube that is used in combination with inner-shell testing"""
    root = os.getcwd()
    file_path = os.path.abspath(
        os.path.join(root, "data/test_valid/basecube.poly")
        )
    return([file_path])

@pytest.fixture(scope="session")
def data_composite_solid():
    """two unit cubes as a composite solid"""
    root = os.getcwd()
    file_path = os.path.abspath(
        os.path.join(root, "data/test_valid/composite_solid.json")
        )
    return([file_path])


#------------------------------------------------------------- va3dity options
@pytest.fixture(scope="session")
def solid():
    """val3dity options for validating a Solid"""
    return(["--unittests", "-p Solid"])

@pytest.fixture(scope="session")
def compositesurface():
    """val3dity options for validating a CompositeSurface"""
    return(["--unittests", "-p CompositeSurface"])

@pytest.fixture(scope="session")
def multisurface():
    """val3dity options for validating a MultiSurface"""
    return(["--unittests", "-p MultiSurface"])

@pytest.fixture(scope="session")
def citymodel():
    """val3dity options for validating a CityModel"""
    return(["--unittests"])

#-------------------------------------------------------- validation functions
@pytest.fixture(scope="session")
def validate():
    def _validate(file_path, options=solid(), val3dity=val3dity()):
        """Validate a file

        :return: The error numbers. Empty list if the file is valid.
        :rtype: list
        """
        try:
            assert isinstance(file_path, str)
            file_path = [file_path]
        except AssertionError:
            assert isinstance(file_path, list)
        except Exception:
            return(["Something went really wrong. Validate the file separately with val3dity."])
        assert isinstance(options, list)

        command = [val3dity] + options + file_path
        
        try:
            proc = subprocess.run(command,
                                  stdout=subprocess.PIPE,
                                  stderr=subprocess.PIPE,
                                  universal_newlines=True,
                                  timeout=15)
        except subprocess.TimeoutExpired:
            return([" ".join(["Something went really wrong.",
                             "Validate the file separately with val3dity.",
                             "Or set a higher timeout in conftest.py."])])
        
        out = proc.stdout
        err = proc.stderr
        rcode = proc.returncode
        
        if rcode < 0:
            # For example Segmentation fault
            return(["Something went really wrong. Validate the file separately with val3dity."])
        else:
            output = []
            if (out != ''):
                if (out.find('@VALID') != -1):
                    return(output)
                elif (out.find('@INVALID') != -1):
                    i = out.find('@INVALID')
                    s = out[i + 9:]
                    tmp = s.split(" ")
                    codes = map(int, tmp[:-1])
                    for each in codes:
                        if output.count(each) == 0:
                            output.append(each)
                    return(output)
                else:
                    return([out.replace('\n', ' ')])
            else:
                return(output)
    
    return(_validate)


@pytest.fixture(scope="session")
def validate_full():
    """Validate a file and return the full stdout, stderr
    
    :rtype: list of strings
    """
    def _validate(command):
        try:
            proc = subprocess.run(command,
                                  stdout=subprocess.PIPE,
                                  stderr=subprocess.PIPE,
                                  universal_newlines=True,
                                  timeout=6)
        except subprocess.TimeoutExpired:
            return([" ".join(["Something went really wrong.",
                             "Validate the file separately with val3dity.",
                             "Or set a higher timeout in conftest.py."])])
        out = proc.stdout
        err = proc.stderr
        rcode = proc.returncode
        if rcode < 0:
            # For example Segmentation fault
            return(["Something went really wrong. Validate the file separately with val3dity."])
        else:
            return([out, err])
        
    return(_validate)