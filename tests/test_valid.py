"""Testing valid files and geometries.

One per format should be enough.
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


#----------------------------------------------------------------------- Tests
def test_poly(validate, data_poly):
    error = validate(data_poly)
    assert(error == [])