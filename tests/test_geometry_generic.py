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




## 105

## 201

## 202

## 203

## 204

## 205

## 206

## 207

## 208

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
