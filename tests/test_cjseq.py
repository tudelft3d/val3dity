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
