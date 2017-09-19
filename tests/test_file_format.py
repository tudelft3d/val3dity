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
                params=["poly_hole.poly"])
def data_poly_hole(request, data_file_format):
    file_path = os.path.abspath(
        os.path.join(
            data_file_format,
            request.param))
    return(file_path)


#----------------------------------------------------------------------- Tests
def test_poly_hole(validate, data_poly_hole):
    error = validate(data_poly_hole)
    assert(error == [901])
