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

# from conftest import validate

# def test_101(validate, val3dity, data_geometry_generic, options_solid):
#     error = validate(
#         val3dity,
#         data_geometry_generic,
#         "cube28.poly",
#         options_solid) 
#     assert(error == [101])

# should work as simple as this:
# import val3dity_test as v3t
# assert(v3t.validate("cube28.poly") == [101])
# assert(v3t.validate("multierror.poly") == [101, 104])
# assert(v3t.validate("cube28.poly") == [])

# parametrized fixture
@pytest.fixture(scope="module")
def data_geometry_generic():
    """path to the data for test_geometry_generic"""
    root = os.getcwd()
    dir_path = os.path.join(root, "data/test_geometry_generic")
    return(dir_path)

@pytest.fixture(scope="module",
                params=["cube28.poly",
                        "toofewpts.poly"])
def data_101(request, data_geometry_generic):
    file_path = os.path.abspath(os.path.join(data_geometry_generic, request.param))
    return(file_path)

# @pytest.mark.usefixtures("validate", "options_solid")
# class GeometryGeneric:
    
def test_101(validate, data_101, options_solid):
    print(data_101)
    error = validate(data_101, options_solid)
    print(error)
    assert(error == [101])
    

@pytest.mark.full
def test_102(self):
    print("not implemented")