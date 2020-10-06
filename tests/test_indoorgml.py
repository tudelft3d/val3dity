"""Testing error cases related to IndoorGML input
"""


import pytest
import os.path

#------------------------------------------------------------------------ Data
@pytest.fixture(scope="module",
                params=["igml_v1.gml",
                        "igml_v2.gml"])
def data_igml_valid(request, dir_indoorgml):
    file_path = os.path.abspath(
        os.path.join(
            dir_indoorgml,
            request.param))
    return([file_path])

@pytest.fixture(scope="module",
                params=["igml_701.gml"])
def data_igml_701(request, dir_indoorgml):
    file_path = os.path.abspath(
        os.path.join(
            dir_indoorgml,
            request.param))
    return([file_path])


@pytest.fixture(scope="module",
                params=["igml_702.gml"])
def data_igml_702(request, dir_indoorgml):
    file_path = os.path.abspath(
        os.path.join(
            dir_indoorgml,
            request.param))
    return([file_path])


@pytest.fixture(scope="module",
                params=["igml_703_1.gml",
                        "igml_703_2.gml"])
def data_igml_703(request, dir_indoorgml):
    file_path = os.path.abspath(
        os.path.join(
            dir_indoorgml,
            request.param))
    return([file_path])

@pytest.fixture(scope="module",
                params=["igml_704_1.gml"])
def data_igml_704_valid(request, dir_indoorgml):
    file_path = os.path.abspath(
        os.path.join(
            dir_indoorgml,
            request.param))
    return([file_path])

@pytest.fixture(scope="module",
                params=["igml_704_2.gml"])
def data_igml_704(request, dir_indoorgml):
    file_path = os.path.abspath(
        os.path.join(
            dir_indoorgml,
            request.param))
    return([file_path])


#----------------------------------------------------------------------- Tests
def test_valid_indoorgml(validate, data_igml_valid, unittests):
    error = validate(data_igml_valid, options=unittests)
    assert(error == [])

def test_igml_701(validate, data_igml_701, unittests):
    error = validate(data_igml_701, options=unittests)
    assert(error == [701])

def test_igml_702(validate, data_igml_702, unittests):
    error = validate(data_igml_702, options=unittests)
    assert(error == [702])

def test_igml_703(validate, data_igml_703, unittests):
    error = validate(data_igml_703, options=unittests)
    assert(error == [703])  
      
def test_igml_704(validate, data_igml_704, unittests):
    error = validate(data_igml_704, options=unittests)
    assert(error == [704])  

def test_igml_704(validate, data_igml_704_valid, unittests):
    error = validate(data_igml_704_valid, options=unittests)
    assert(error == [])      