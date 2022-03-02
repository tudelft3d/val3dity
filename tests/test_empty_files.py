"""Testing empty files and geometries.

Try to break val3dity by giving it (partially) empty files in each format.
"""

import pytest
import os.path


#------------------------------------------------------------------------ Data
@pytest.fixture(scope="module",
                params=["completely_empty.obj",
                        "completely_empty.off",
                        "completely_empty.json",])
def data_completely_empty(request, dir_empty):
    file_path = os.path.abspath(
        os.path.join(
            dir_empty,
            request.param))
    return(file_path)



@pytest.fixture(scope="module",
                params=["empty_primitive.json",
                        "empty_primitive_1.json",
                        "empty_primitive.obj",
                        "empty_primitive.poly",
                        "empty_primitive.off"])
def dir_empty_primitive(request, dir_empty):
    file_path = os.path.abspath(
        os.path.join(
            dir_empty,
            request.param))
    return(file_path)

#----------------------------------------------------------------------- Tests
def test_completely_empty(validate, data_completely_empty, unittests):
    error = validate(data_completely_empty, options=unittests)
    assert(error == [901] or error == [902])

def test_empty_primitive(validate, dir_empty_primitive, unittests):
    error = validate(dir_empty_primitive, options=unittests)
    assert(error == [902])

