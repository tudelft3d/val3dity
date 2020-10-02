"""Testing error cases related to IndoorGML input
"""


import pytest
import os.path

#------------------------------------------------------------------------ Data
@pytest.fixture(scope="module",
                params=["igml.gml"])
def data_valid_indoorgml(request, dir_indoorgml):
    file_path = os.path.abspath(
        os.path.join(
            dir_indoorgml,
            request.param))
    return([file_path])


#----------------------------------------------------------------------- Tests
def test_valid_indoorgml(validate, data_valid_indoorgml, unittests):
    error = validate(data_valid_indoorgml, options=unittests)
    assert(error == [])
