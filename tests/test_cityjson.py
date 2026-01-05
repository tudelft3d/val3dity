"""Testing error cases related to CityJSON input"""

import os.path

import pytest


# ------------------------------------------------------------------------ Data
@pytest.fixture(scope="module", params=["geomtemplate_1.json"])
def data_cj_v_gt(request, dir_cityjson):
    file_path = os.path.abspath(os.path.join(dir_cityjson, request.param))
    return [file_path]


@pytest.fixture(scope="module", params=["geomtemplate_2.json"])
def data_cj_iv_gt(request, dir_cityjson):
    file_path = os.path.abspath(os.path.join(dir_cityjson, request.param))
    return [file_path]


@pytest.fixture(scope="module", params=["torus.city.json"])
def data_cj_v11(request, dir_cityjson):
    file_path = os.path.abspath(os.path.join(dir_cityjson, request.param))
    return [file_path]


@pytest.fixture(scope="module", params=["several_lods_valid.json"])
def data_several_lods_valid(request, dir_cityjson):
    file_path = os.path.abspath(os.path.join(dir_cityjson, request.param))
    return [file_path]


@pytest.fixture(scope="module", params=["several_lods_invalid.json"])
def data_several_lods_invalid(request, dir_cityjson):
    file_path = os.path.abspath(os.path.join(dir_cityjson, request.param))
    return [file_path]


@pytest.fixture(scope="module", params=["emptygeom.json"])
def data_empty_geom(request, dir_cityjson):
    file_path = os.path.abspath(os.path.join(dir_cityjson, request.param))
    return [file_path]


@pytest.fixture(scope="module", params=["cube_v10.city.json", "cube_v11.city.json"])
def data_versions(request, dir_cityjson):
    file_path = os.path.abspath(os.path.join(dir_cityjson, request.param))
    return [file_path]


# ----------------------------------------------------------------------- Tests
def test_valid_geomtemplates(validate, data_cj_v_gt, unittests):
    error = validate(data_cj_v_gt, options=unittests)
    assert error == []


def test_invalid_geomtemplates(validate, data_cj_iv_gt, unittests):
    error = validate(data_cj_iv_gt, options=unittests)
    assert error == [203]


def test_cityjson_v11(validate, data_cj_v11, unittests):
    error = validate(data_cj_v11, options=unittests)
    assert error == []


def test_several_lods_valid(validate, data_several_lods_valid, unittests):
    error = validate(data_several_lods_valid, options=unittests)
    assert error == []


def test_empty_geom(validate, data_empty_geom, unittests):
    error = validate(data_empty_geom, options=unittests)
    assert error == []


def test_versions(validate, data_versions, unittests):
    error = validate(data_versions, options=unittests)
    assert error == []
