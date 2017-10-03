"""Testing empty files and geometries.

Try to break val3dity by giving it (partially) empty files in each format.
"""

import pytest
import os.path

#----------------------------------------------------------------- Data folder
@pytest.fixture(scope="module")
def data_empty():
    """path to the data for test_empty"""
    root = os.getcwd()
    dir_path = os.path.join(root, "data/test_empty")
    return(dir_path)

#------------------------------------------------------------------------ Data
@pytest.fixture(scope="module",
                params=["completely_empty.gml",
                        "completely_empty.xml",
                        "completely_empty.obj",
                        "completely_empty.off",
                        "completely_empty.json",])
def data_completely_empty(request, data_empty):
    file_path = os.path.abspath(
        os.path.join(
            data_empty,
            request.param))
    return(file_path)

#----------------------------------------------------------------------- Tests
def test_completely_empty(validate, data_completely_empty, citymodel):
    error = validate(data_completely_empty, options=citymodel)
    assert(error == [901])
## 902