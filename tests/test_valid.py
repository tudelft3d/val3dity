"""Testing valid files and geometries.

These are rather general tests on valid geometry. To test whether val3dity
returns VALID in a boundary condition of a specific error, better include
those validity checks in the relevant test case.
"""

import pytest
import os.path

#----------------------------------------------------------------- Data folder
@pytest.fixture(scope="module")
def data_valid():
    """path to the data for test_valid"""
    root = os.getcwd()
    dir_path = os.path.join(root, "data/test_valid")
    return(dir_path)

#------------------------------------------------------------------------ Data
@pytest.fixture(scope="module",
                params=["valid_1.poly",
                        "valid_2.poly",
                        "valid_3.poly"])
def data_poly(request, data_valid):
    file_path = os.path.abspath(
        os.path.join(
            data_valid,
            request.param))
    return(file_path)


@pytest.fixture(scope="module",
                params=["planar.poly"])
def data_planar(request, data_valid):
    file_path = os.path.abspath(
        os.path.join(
            data_valid,
            request.param))
    return(file_path)


@pytest.fixture(scope="module",
                params=["self_fold.obj"])
def data_self_fold(request, data_valid):
    file_path = os.path.abspath(
        os.path.join(
            data_valid,
            request.param))
    return(file_path)

#----------------------------------------------------------------------- Tests
@pytest.mark.skip(reason="POLY files are not intended for citymodels, just for geometry testing")
def test_valid_poly(validate, data_poly):
    error = validate(data_poly)
    assert(error == [])

def test_valid_planar(validate, data_planar):
    error = validate(data_planar)
    assert(error == [])

def test_valid_self_fold(validate, data_self_fold):
    error = validate(data_self_fold)
    assert(error == [])