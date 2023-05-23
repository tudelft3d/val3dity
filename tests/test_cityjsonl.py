"""Testing error cases related to CityJSONL input
"""
import pytest
import os.path

#------------------------------------------------------------------------ Data
@pytest.fixture(scope="module",
                params=["denhaag_random_5.jsonl"])
def data_1(request, dir_cityjsonl):
    file_path = os.path.abspath(
        os.path.join(
            dir_cityjsonl,
            request.param))
    return([file_path])

@pytest.fixture(scope="module",
                params=["a.jsonl"])
def data_2(request, dir_cityjsonl):
    file_path = os.path.abspath(
        os.path.join(
            dir_cityjsonl,
            request.param))
    return([file_path])



#----------------------------------------------------------------------- Tests
def test_data_1_cityjsonl(validate, data_1, unittests):
    error = validate(data_1, options=unittests)
    assert(error == [203, 601])

def test_data_2_cityjsonl(validate, data_2, unittests):
    error = validate(data_2, options=unittests)
    assert(error == [901])

