"""Testing error cases related to CityJSONSeq input"""

import os.path

import pytest


# ------------------------------------------------------------------------ Data
@pytest.fixture(scope="module", params=["denhaag_random_5.city.jsonl"])
def data_1(request, dir_cjseq):
    file_path = os.path.abspath(os.path.join(dir_cjseq, request.param))
    return [file_path]


@pytest.fixture(scope="module", params=["notransform.city.jsonl"])
def data_2(request, dir_cjseq):
    file_path = os.path.abspath(os.path.join(dir_cjseq, request.param))
    return [file_path]


@pytest.fixture(scope="module", params=["unclosedbracket.city.jsonl"])
def data_3(request, dir_cjseq):
    file_path = os.path.abspath(os.path.join(dir_cjseq, request.param))
    return [file_path]


@pytest.fixture(scope="module", params=["3dbag_b2.city.json", "3dbag_b2.city.jsonl"])
def data_3dbag_b2(request, dir_cjseq):
    file_path = os.path.abspath(os.path.join(dir_cjseq, request.param))
    return [file_path]


# ----------------------------------------------------------------------- Tests
def test_data_1_cjseq(validate, data_1, unittests):
    error = validate(data_1, options=unittests)
    assert error == [203, 601]


def test_data_2_cjseq(validate, data_2, unittests):
    error = validate(data_2, options=unittests)
    assert error == [901]


def test_data_3_cjseq(validate, data_3, unittests):
    error = validate(data_3, options=unittests)
    assert error == [901]


def test_3dbag_b2_same_errors(validate, data_3dbag_b2, unittests):
    """Test that both .json and .jsonl versions of 3dbag_b2 produce the same errors"""
    error = validate(data_3dbag_b2, options=unittests)
    # Both files should have error 102 (CONSECUTIVE_POINTS_SAME)
    assert error == [102]
