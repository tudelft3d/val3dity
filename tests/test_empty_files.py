"""Testing empty files and geometries.

Try to break val3dity by giving it (partially) empty files in each format.
"""

import pytest
import os.path


#------------------------------------------------------------------------ Data
@pytest.fixture(scope="module",
                params=["completely_empty.gml",
                        "completely_empty.xml",
                        "completely_empty.obj",
                        "completely_empty.off",
                        "completely_empty.json",])
def data_completely_empty(request, dir_empty):
    file_path = os.path.abspath(
        os.path.join(
            dir_empty,
            request.param))
    return(file_path)


@pytest.fixture(scope="module",
                params=["cityobject_no_geom.gml"])
def data_cityobject_no_geom(request, dir_empty):
    file_path = os.path.abspath(
        os.path.join(
            dir_empty,
            request.param))
    return(file_path)


@pytest.fixture(scope="module",
                params=["empty_primitive.gml",
                        "empty_primitive.xml",
                        "empty_primitive.json",
                        "empty_primitive_1.json",
                        "empty_primitive.obj",
                        "empty_primitive.off"])
def dir_empty_primitive(request, dir_empty):
    file_path = os.path.abspath(
        os.path.join(
            dir_empty,
            request.param))
    return(file_path)

#----------------------------------------------------------------------- Tests
def test_completely_empty(validate, data_completely_empty, citymodel):
    error = validate(data_completely_empty, options=citymodel)
    assert(error == [901] or error == [902])

def test_empty_primitive(validate, dir_empty_primitive, citymodel):
    error = validate(dir_empty_primitive, options=citymodel)
    assert(error == [902])

def test_no_geom(validate, data_cityobject_no_geom, citymodel):
    error = validate(data_cityobject_no_geom, options=citymodel)
    assert(error == [609])    