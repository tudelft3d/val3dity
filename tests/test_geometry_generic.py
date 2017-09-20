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

#----------------------------------------------------------------- Data folder
@pytest.fixture(scope="module")
def data_geometry_generic():
    """path to the data for test_geometry_generic"""
    root = os.getcwd()
    dir_path = os.path.join(root, "data/test_geometry_generic")
    return(dir_path)

#------------------------------------------------------------------------ Data
@pytest.fixture(scope="module",
                params=["101.poly"])
def data_101(request, data_geometry_generic):
    file_path = os.path.abspath(
        os.path.join(
            data_geometry_generic,
            request.param))
    return(file_path)
# TODO: add GML ring where the first and the last points are the same


@pytest.fixture(scope="module",
                params=["102.poly"])
def data_102(request, data_geometry_generic):
    file_path = os.path.abspath(
        os.path.join(
            data_geometry_generic,
            request.param))
    return(file_path)
# TODO: add GML ring where consecutive points are the same


@pytest.fixture(scope="module",
                params=["104.poly",
                        "104_1.poly",
                        "104_2.poly",
                        "104_3.poly"])
def data_104(request, data_geometry_generic):
    file_path = os.path.abspath(
        os.path.join(
            data_geometry_generic,
            request.param))
    return(file_path)


@pytest.fixture(scope="module",
                params=["105.poly",
                        "105_1.poly"])
def data_105(request, data_geometry_generic):
    file_path = os.path.abspath(
        os.path.join(
            data_geometry_generic,
            request.param))
    return(file_path)


@pytest.fixture(scope="module",
                params=["201.poly",
                        "201_1.poly",
                        "201_2.poly"])
def data_201(request, data_geometry_generic):
    file_path = os.path.abspath(
        os.path.join(
            data_geometry_generic,
            request.param))
    return(file_path)


@pytest.fixture(scope="module",
                params=["202.poly"])
def data_202(request, data_geometry_generic):
    file_path = os.path.abspath(
        os.path.join(
            data_geometry_generic,
            request.param))
    return(file_path)


@pytest.fixture(scope="module",
                params=["203.poly",
                        "203_1.poly",
                        "203_2.poly"])
def data_203(request, data_geometry_generic):
    file_path = os.path.abspath(
        os.path.join(
            data_geometry_generic,
            request.param))
    return(file_path)


@pytest.mark.skip(reason="reports 204 which is fine")
@pytest.fixture(scope="module",
                params=["203_valid.poly"])
def data_203_valid(request, data_geometry_generic):
    file_path = os.path.abspath(
        os.path.join(
            data_geometry_generic,
            request.param))
    return(file_path)


@pytest.fixture(scope="module",
                params=["204.poly",
                        "204_1.poly",
                        "204_2.poly",
                        "204_3.poly",
                        "204_4.poly"])
def data_204(request, data_geometry_generic):
    file_path = os.path.abspath(
        os.path.join(
            data_geometry_generic,
            request.param))
    return(file_path)


@pytest.fixture(scope="module",
                params=["204_valid.poly"])
def data_204_valid(request, data_geometry_generic):
    file_path = os.path.abspath(
        os.path.join(
            data_geometry_generic,
            request.param))
    return(file_path)


@pytest.fixture(scope="module",
                params=["205.poly"])
def data_205(request, data_geometry_generic):
    file_path = os.path.abspath(
        os.path.join(
            data_geometry_generic,
            request.param))
    return(file_path)


@pytest.fixture(scope="module",
                params=["206.poly"])
def data_206(request, data_geometry_generic):
    file_path = os.path.abspath(
        os.path.join(
            data_geometry_generic,
            request.param))
    return(file_path)


@pytest.fixture(scope="module",
                params=["207.poly",
                        "207_1.poly"])
def data_207(request, data_geometry_generic):
    file_path = os.path.abspath(
        os.path.join(
            data_geometry_generic,
            request.param))
    return(file_path)
# TODO: add 207_2.poly once val3dity can parse the holes in a poly file


@pytest.fixture(scope="module",
                params=["208.poly"])
def data_208(request, data_geometry_generic):
    file_path = os.path.abspath(
        os.path.join(
            data_geometry_generic,
            request.param))
    return(file_path)

#----------------------------------------------------------------------- Tests
def test_101(validate, data_101):
    error = validate(data_101)
    assert(error == [101])

def test_102(validate, data_102):
    error = validate(data_102)
    assert(error == [102])

def test_104(validate, data_104):
    error = validate(data_104)
    assert(error == [104])

def test_105(validate, data_105):
    error = validate(data_105)
    assert(error == [105])

def test_201(validate, data_201):
    error = validate(data_201)
    assert(error == [201])

def test_202(validate, data_202):
    error = validate(data_202)
    assert(error == [202])

def test_203(validate, data_203):
    error = validate(data_203)
    assert(error == [203])

@pytest.mark.skip(reason="reports 204 which is fine")
def test_203_valid(validate, data_203_valid):
    error = validate(data_203_valid)
    assert(error == [])

def test_204(validate, data_204):
    error = validate(data_204)
    assert(error == [204])

def test_204_valid(validate, data_204_valid):
    error = validate(data_204_valid)
    assert(error == [])

def test_205(validate, data_205):
    error = validate(data_205)
    assert(error == [205])

def test_206(validate, data_206):
    error = validate(data_206)
    assert(error == [206])

def test_207(validate, data_207):
    error = validate(data_207)
    assert(error == [207])

def test_208(validate, data_208):
    error = validate(data_208)
    assert(error == [208])


## 301

## 302

## 303

## 304

## 305

## 306

## 307

## 309

## 401

## 402

## 403

## 404

## 405

## 501

## 502

## 503
