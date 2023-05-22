"""Testing error cases related to JSON-FG
"""


import pytest
import os.path

#------------------------------------------------------------------------ Data
@pytest.fixture(scope="module",
                params=["building.fg.json",
                        "cubes.fg.json"])
def data_jsonfg_valid(request, dir_jsonfg):
    file_path = os.path.abspath(
        os.path.join(
            dir_jsonfg,
            request.param))
    return([file_path])

@pytest.fixture(scope="module",
                params=["e103.fg.json"])
def data_jsonfg_invalid(request, dir_jsonfg):
    file_path = os.path.abspath(
        os.path.join(
            dir_jsonfg,
            request.param))
    return([file_path])

@pytest.fixture(scope="module",
                params=["geojson.json"])
def data_vanilla_geojson(request, dir_jsonfg):
    file_path = os.path.abspath(
        os.path.join(
            dir_jsonfg,
            request.param))
    return([file_path])



#----------------------------------------------------------------------- Tests
def test_data_jsonfg_valid(validate, data_jsonfg_valid, unittests):
    error = validate(data_jsonfg_valid, options=unittests)
    assert(error == [])

def test_data_jsonfg_invalid(validate, data_jsonfg_invalid, unittests):
    error = validate(data_jsonfg_invalid, options=unittests)
    assert(error == [103])

def test_vanilla_geojson(validate, data_vanilla_geojson, unittests):
    error = validate(data_vanilla_geojson, options=unittests)
    assert(error == [906])
