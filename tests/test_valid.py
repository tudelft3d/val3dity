"""Testing valid files and geometries.

These are rather general tests on valid geometry. To test whether val3dity
returns VALID in a boundary condition of a specific error, better include
those validity checks in the relevant test case.
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
                params=["planar.poly"])
def data_planar(request, data_valid):
    file_path = os.path.abspath(
        os.path.join(
            data_valid,
            request.param))
    return(file_path)


@pytest.fixture(scope="module",
                params=["self_fold.obj"])
def data_self_fold(request, data_valid):
    file_path = os.path.abspath(
        os.path.join(
            data_valid,
            request.param))
    return(file_path)


@pytest.fixture(scope="module",
                params=["closed_top.poly"])
def data_closed_top(request, data_valid):
    file_path = os.path.abspath(
        os.path.join(
            data_valid,
            request.param))
    return(file_path)


@pytest.fixture(scope="module",
                params=["inner_pyramid.poly",
                        "inner_pyramid_1.poly",
                        "inner_pyramid_2.poly",
                        "inner_pyramid_3.poly",
                        "inner_pyramid_4.poly"])
def data_inner_pyramid(request, data_valid):
    file_path = os.path.abspath(
        os.path.join(
            data_valid,
            request.param))
    return(file_path)


@pytest.fixture(scope="module",
                params=["inner_shell.poly",
                        "inner_shell_1.poly",
                        ["inner_shell_2.poly", "inner_shell.poly"],
                        ["inner_shell_3.poly", "inner_shell.poly"],
                        ["inner_shell_4.poly", "inner_shell.poly"]
                        ])
def data_inner_shell(request, data_valid, data_basecube):
    ishell = request.param
    ishell_path = []
    if isinstance(ishell, list):
        for i in ishell:
            i_path = os.path.abspath(
                        os.path.join(data_valid, i)
                        )
            ishell_path = ishell_path + ["--ishell", i_path]
    else:
        ishell_path = ["--ishell",
                       os.path.abspath(
                           os.path.join(data_valid, ishell)
                           )
                       ]
    inner_outer_path = ishell_path + data_basecube
    return(inner_outer_path)

#----------------------------------------------------------------------- Tests
def test_planar(validate, data_planar):
    error = validate(data_planar)
    assert(error == [])

def test_self_fold(validate, data_self_fold):
    error = validate(data_self_fold)
    assert(error == [])

def test_closed_top(validate, data_closed_top):
    error = validate(data_closed_top)
    assert(error == [])

@pytest.mark.skip(reason="inner_pyramid_2 and _3 break val3dity")
def test_valid_inner_shell(validate, data_inner_pyramid):
    error = validate(data_inner_pyramid)
    assert(error == [])

def test_inner_shell(validate, data_inner_shell):
    error = validate(data_inner_shell)
    assert(error == [])
