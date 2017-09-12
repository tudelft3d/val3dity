import pytest

def test_101(validate, val3dity, data_geometry_generic, options_solid):
    error = validate(
        val3dity,
        data_geometry_generic,
        "cube28.poly",
        options_solid)
    assert(len(error) == 1) 
    assert(error[0] == 101)
