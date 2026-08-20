"""Testing error cases related to CityJSONSeq input"""

import json
import os.path
import re
import subprocess

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

@pytest.fixture(scope="module", params=["shifted_302.city.jsonl"])
def data_4(request, dir_cjseq):
    file_path = os.path.abspath(os.path.join(dir_cjseq, request.param))
    return file_path


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
    
def test_302_location_uses_feature_shift(val3dity, data_4, tmp_path):
    report_path = tmp_path / "report.json"
    command = [val3dity, "--unittests", "--report", str(report_path), data_4]
    subprocess.run(
        command,
        stdout=subprocess.PIPE,
        stderr=subprocess.PIPE,
        universal_newlines=True,
        timeout=15,
        check=True,
    )

    report = json.loads(report_path.read_text())
    errors = [
        e
        for f in report["features"]
        for e in f["errors"]
        if e["code"] == 302 and e["id"].startswith("coid=open-0|")
    ]
    assert len(errors) == 1

    x, y, z = map(float, re.findall(r"[-+]?\d+(?:\.\d+)?", errors[0]["info"]))
    top_vertices = {
        (121000.123, 491000.456, 1.0),
        (121001.123, 491000.456, 1.0),
        (121001.123, 491001.456, 1.0),
        (121000.123, 491001.456, 1.0),
    }
    assert any(
        abs(x - vx) < 1e-9 and abs(y - vy) < 1e-9 and abs(z - vz) < 1e-9
        for vx, vy, vz in top_vertices
    )
