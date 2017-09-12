import pytest
import subprocess
import os.path
import re
import pprint

@pytest.fixture(scope="session")
def val3dity():
    # or just ../build/val3dity
    # or find the executable in the val3dity folder
    # TODO: find out how can the path to the val3dity exec. passed as an argument to pytest
    return("path to val3dity executable as argument")

@pytest.fixture(scope="session")
def data_geometry_generic():
    return("../data/test_geometry_generic")


@pytest.fixture(scope="module")
def options_solid():
    return(["--unittests", "-p Solid"])

@pytest.fixture(scope="module")
def options_citymodel():
    return(["--unittests"])


VAL3DITYEXE = "/home/bdukai/Development/val3dity/build/val3dity"
# VAL3DITYEXE = os.path.abspath(VAL3DITYEXE)
SOLIDFOLDER = "/home/bdukai/Development/val3dity/tests/test_geometry_generic"
# SOLIDFOLDER = os.path.abspath(SOLIDFOLDER)

options_solid = ["--unittests", "-p Solid"]
options_citymodel = ["--unittests"]
val3dity_exe = VAL3DITYEXE

def validate(val3dity, data_path, file, options_solid):
    file_path = os.path.join(data_path, file)
    command = [val3dity] + options_solid + [file_path]
    
    cp = subprocess.run(command, stdout=subprocess.PIPE,
                        universal_newlines=True)
    re = cp.stdout
    
    output = []
    if (re != ''):
        if (re.find('@VALID') != -1):
            return(output)
        i = re.find('@INVALID')
        s = re[i+9:]
        tmp = s.split(" ")
        codes = map(int, tmp[:-1])
        for each in codes:
            if output.count(each) == 0:
                output.append(each)
    return(output)


r = validate("cube28.poly", options_solid)
r = validate("cube.poly", options_solid)
r = validate("DenHaag_1BwBP.gml", options_citymodel)

