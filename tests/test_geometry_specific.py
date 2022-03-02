"""Testing format specific error cases on geometry primitives.

Error cases that are only relevant for a particular format and 
cannot be modelled by each format, thus don't belong to *Geometry errors*
(eg 601).
"""
import pytest
import os.path


#------------------------------------------------------------------------ Data

@pytest.fixture(scope="module",
                params=["501.json",
                        "501_1.json"])
def data_501(request, dir_geometry_specific):
    file_path = os.path.abspath(
        os.path.join(
            dir_geometry_specific,
            request.param))
    return(file_path)


@pytest.fixture(scope="module",
                params=["501.json"])
def data_501_overlap(request, dir_geometry_specific):
    file_path = os.path.abspath(
        os.path.join(
            dir_geometry_specific,
            request.param))
    return(file_path)


@pytest.fixture(scope="module",
                params=["502.json"])
def data_502(request, dir_geometry_specific):
    file_path = os.path.abspath(
        os.path.join(
            dir_geometry_specific,
            request.param))
    return(file_path)


@pytest.fixture(scope="module",
                params=["503.json"])
def data_503(request, dir_geometry_specific):
    file_path = os.path.abspath(
        os.path.join(
            dir_geometry_specific,
            request.param))
    return(file_path)


@pytest.fixture(scope="module",
                params=["601.json",
                        "601_1.json"])
def data_601(request, dir_geometry_specific):
    file_path = os.path.abspath(
        os.path.join(
            dir_geometry_specific,
            request.param))
    return(file_path)


@pytest.fixture(scope="module",
                params=["601_1.json"])
def data_601_overlap(request, dir_geometry_specific):
    file_path = os.path.abspath(
        os.path.join(
            dir_geometry_specific,
            request.param))
    return(file_path)



@pytest.fixture(scope="module",
                params=[
                    ["--unittests", "--overlap_tol 0.01"],
                    ["--unittests", "--overlap_tol 0.1"],
                    ["--unittests", "--overlap_tol 1.0"]
                    ])
def options_overlap(request):
    return(request.param)


#----------------------------------------------------------------------- Tests

def test_501(validate, data_501, unittests):
    error = validate(data_501, options=unittests)
    assert(error == [501])

def test_501_overlap(validate, data_501_overlap, options_overlap):
    error = validate(data_501_overlap, options=options_overlap)
    assert(error == [])

def test_502(validate, data_502, unittests):
    error = validate(data_502, options=unittests)
    assert(error == [502])

def test_503(validate, data_503, unittests):
    error = validate(data_503, options=unittests)
    assert(error == [503])

def test_601(validate, data_601, unittests):
    error = validate(data_601, options=unittests)
    assert(error == [601])

def test_601_overlap(validate, data_601_overlap, options_overlap):
    error = validate(data_601_overlap, options=options_overlap)
    assert(error == [])