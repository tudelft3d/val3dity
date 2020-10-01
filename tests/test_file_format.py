"""Testing error cases related to file formats.

- Each file contains the same, valid geometry. Thus the various formatting 
options and errors are tested. 

- Invalid schema or geometry definitions, eg invalid CityGML
"""

## 901

import pytest
import os.path

#------------------------------------------------------------------------ Data
@pytest.fixture(scope="module",
                params=["invalid_citygml_1.gml",
                        "invalid_citygml_2.gml"])
def data_invalid_citygml(request, dir_file_format):
    file_path = os.path.abspath(
        os.path.join(
            dir_file_format,
            request.param))
    return([file_path])


@pytest.fixture(scope="module",
                params=["invalid_json_cityjson.json",
                        "invalid_schema_cityjson_1.json"])
def data_invalid_cityjson(request, dir_file_format):
    file_path = os.path.abspath(
        os.path.join(
            dir_file_format,
            request.param))
    return([file_path])


@pytest.fixture(scope="module",
                params=["invalid_schema_cityjson_2.json"])
def data_cityjson_wrong_vindex(request, dir_file_format):
    file_path = os.path.abspath(
        os.path.join(
            dir_file_format,
            request.param))
    return([file_path])


@pytest.fixture(scope="module",
                params=["invalid_indoorgml_1.gml",
                        "invalid_indoorgml_2.gml"])
def data_invalid_indoorgml(request, dir_file_format):
    file_path = os.path.abspath(
        os.path.join(
            dir_file_format,
            request.param))
    return([file_path])


#----------------------------------------------------------------------- Tests
def test_invalid_citygml(validate, data_invalid_citygml, unittests):
    error = validate(data_invalid_citygml, options=unittests)
    assert(error == [901])


def test_invalid_cityjson(validate, data_invalid_cityjson, unittests):
    error = validate(data_invalid_cityjson, options=unittests)
    assert(error == [901])   

def test_invalid_cityjson_vindex(validate, data_cityjson_wrong_vindex, unittests):
    error = validate(data_cityjson_wrong_vindex, options=unittests)
    assert(error == ["CRASH"])       

def test_invalid_indoorgml(validate, data_invalid_indoorgml, unittests):
    error = validate(data_invalid_indoorgml, options=unittests)
    assert(error == [901])     