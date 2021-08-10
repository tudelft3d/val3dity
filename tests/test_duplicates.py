"""Testing duplicates vertices in different formats

All formats should use tolerance to merge "duplicates" a duplicate is 
defined as a vertex closer than 'snap_tol' to another one.
"""

import pytest
import os.path


#------------------------------------------------------------------------ Data
@pytest.fixture(scope="module",
                params=["cube_tol_1.json",
                        "cube_tol_1.off",
                        "cube_tol_1.obj"])
def data_duplicates(request, dir_duplicates):
    file_path = os.path.abspath(
        os.path.join(
            dir_duplicates,
            request.param))
    return(file_path)

@pytest.fixture(scope="module",
                params=[
                    ["--unittests", "--snap_tol 0.1"],
                    ["--unittests", "--snap_tol 0.01"],
                    ["--unittests", "--snap_tol 0.001"]
                    ])
def options_snap_tol(request):
    return(request.param)


@pytest.fixture(scope="module",
                params=[
                    ["--unittests", "--snap_tol 0.00001"],
                    ["--unittests", "--snap_tol 1e-12"]
                    ])
def options_snap_tol_invalid(request):
    return(request.param)

#----------------------------------------------------------------------- Tests
def test_duplicates(validate, data_duplicates, options_snap_tol):
    error = validate(data_duplicates, options=options_snap_tol)
    assert(error == [])

def test_duplicates(validate, data_duplicates, options_snap_tol_invalid):
    error = validate(data_duplicates, options=options_snap_tol_invalid)
    assert(error == [302])
