"""Testing generic error cases on geometry primitives.

The intention is to isolate the geometry from the file format.
The POLY format is simple, supports inner rings and the parser is reliable.
Therefore each geometry error case (http://val3dity.readthedocs.io/en/v2/errors/#)
is tested with the POLY format *only*. Don't replicate these geometry error cases
in different file formats, because test maintenance will become very error prone
(ie update one file but forget the other...).
"""

import pytest
import os.path


@pytest.fixture(scope="module")
def data_geometry_generic():
    """path to the data for test_geometry_generic"""
    root = os.getcwd()
    dir_path = os.path.join(root, "data/test_geometry_generic")
    return(dir_path)

@pytest.fixture(scope="module",
                params=["101.poly",
                        "101_1.poly"])
def data_101(request, data_geometry_generic):
    file_path = os.path.abspath(os.path.join(data_geometry_generic, request.param))
    return(file_path)

#----------------------------------------------------------------------- Tests
def test_101(validate, data_101):
    error = validate(data_101)
    assert(error == [101])

@pytest.mark.full
def test_102():
    print("not implemented")
        
        