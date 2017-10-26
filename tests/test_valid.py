"""Testing valid files and geometries.

These are rather general tests on valid geometry. To test whether val3dity
returns VALID in a boundary condition of a specific error, better include
those validity checks in the relevant test case.
"""

import pytest
import os.path


#------------------------------------------------------------------------ Data
@pytest.fixture(scope="module",
                params=["planar.poly"])
def data_planar(request, dir_valid):
    file_path = os.path.abspath(
        os.path.join(
            dir_valid,
            request.param))
    return(file_path)


@pytest.fixture(scope="module",
                params=["self_fold.obj"])
def data_self_fold(request, dir_valid):
    file_path = os.path.abspath(
        os.path.join(
            dir_valid,
            request.param))
    return(file_path)


@pytest.fixture(scope="module",
                params=["closed_top.poly"])
def data_closed_top(request, dir_valid):
    file_path = os.path.abspath(
        os.path.join(
            dir_valid,
            request.param))
    return(file_path)


@pytest.fixture(scope="module",
                params=["v405.off"])
def data_v_405(request, dir_valid):
    file_path = os.path.abspath(
        os.path.join(
            dir_valid,
            request.param))
    return(file_path)



@pytest.fixture(scope="module",
                params=["basecube_large_coords.poly"])
def data_large_coords(request, dir_valid):
    file_path = os.path.abspath(
        os.path.join(
            dir_valid,
            request.param))
    return(file_path)


@pytest.fixture(scope="module",
                params=["inner_shell.poly",
                        "inner_shell_1.poly",
                        ["inner_shell_2.poly", "inner_shell.poly"],
                        ["inner_shell_3.poly", "inner_shell.poly"],
                        ["inner_shell_4.poly", "inner_shell.poly"]
                        ])
def data_inner_shell(request, dir_valid, data_basecube):
    ishell = request.param
    ishell_path = []
    if isinstance(ishell, list):
        for i in ishell:
            i_path = os.path.abspath(
                        os.path.join(dir_valid, i)
                        )
            ishell_path = ishell_path + ["--ishell", i_path]
    else:
        ishell_path = ["--ishell",
                       os.path.abspath(
                           os.path.join(dir_valid, ishell)
                           )
                       ]
    inner_outer_path = ishell_path + data_basecube
    return(inner_outer_path)


#----------------------------------------------------------------------- Tests

def test_large_coords(validate, data_large_coords):
    error = validate(data_large_coords)
    assert(error == [])

def test_v_405(validate, data_v_405):
    error = validate(data_v_405)
    assert(error == [])

def test_planar(validate, data_planar):
    error = validate(data_planar)
    assert(error == [])

def test_self_fold(validate, data_self_fold):
    error = validate(data_self_fold)
    assert(error == [])

def test_closed_top(validate, data_closed_top):
    error = validate(data_closed_top)
    assert(error == [])

@pytest.mark.full
def test_inner_shell(validate, data_inner_shell):
    error = validate(data_inner_shell)
    assert(error == [])

# data_composite_solid is in conftest.py
def test_composite_solid(validate, data_composite_solid, citymodel):
    error = validate(data_composite_solid, options=citymodel)
    assert(error == [])
