"""Testing error cases related to file formats.

1. Here each file contains the same, valid geometry. Thus the various formatting 
options and errors are tested. 

2. Invalid schema or geometry definitions, eg invalid definition of a hole
in a .poly file.
"""

## 901

import pytest
import os.path

#----------------------------------------------------------------- Data folder
@pytest.fixture(scope="module")
def data_file_format():
    """path to the data for test_file_format"""
    root = os.getcwd()
    dir_path = os.path.join(root, "data/test_file_format")
    return(dir_path)

#------------------------------------------------------------------------ Data
@pytest.fixture(scope="module",
                params=["invalid_json_1.json",
                        "invalid_json_2.json"])
def data_invalid_json(request, data_file_format):
    file_path = os.path.abspath(
        os.path.join(
            data_file_format,
            request.param))
    return(file_path)


@pytest.fixture(scope="module",
                params=["invalid_citygml_1.gml",
                        "invalid_citygml_2.gml",
                        "invalid_citygml_3.gml"])
def data_invalid_citygml(request, data_file_format):
    file_path = os.path.abspath(
        os.path.join(
            data_file_format,
            request.param))
    return(file_path)
#----------------------------------------------------------------------- Tests
def test_invalid_json(validate, data_invalid_json, citymodel):
    error = validate(data_invalid_json, options=citymodel)
    assert(error == [901])

def test_invalid_citygml(validate, data_invalid_citygml, citymodel):
    error = validate(data_invalid_citygml, options=citymodel)
    assert(error == [901])
