"""Testing error cases related to IndoorGML input
"""


import pytest
import os.path

#------------------------------------------------------------------------ Data
@pytest.fixture(scope="module",
                params=["cube.json",
                        "cube2.json"])
def data_tu3djson_valid(request, dir_tu3djson):
    file_path = os.path.abspath(
        os.path.join(
            dir_tu3djson,
            request.param))
    return([file_path])

@pytest.fixture(scope="module",
                params=["cube3.json"])
def data_tu3djson_invalid(request, dir_tu3djson):
    file_path = os.path.abspath(
        os.path.join(
            dir_tu3djson,
            request.param))
    return([file_path])

@pytest.fixture(scope="module",
                params=["geojson.json"])
def data_other_json(request, dir_tu3djson):
    file_path = os.path.abspath(
        os.path.join(
            dir_tu3djson,
            request.param))
    return([file_path])


#----------------------------------------------------------------------- Tests
def test_data_tu3djson_valid(validate, data_tu3djson_valid, unittests):
    error = validate(data_tu3djson_valid, options=unittests)
    assert(error == [])

def test_data_tu3djson_invalid(validate, data_tu3djson_invalid, unittests):
    error = validate(data_tu3djson_invalid, options=unittests)
    assert(error == [104])

def test_other_json(validate, data_other_json, unittests):
    error = validate(data_other_json, options=unittests)
    assert(error == [904])
