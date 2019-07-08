import pytest
import yaml
import os.path
from os import walk

@pytest.mark.full
def test_metadata():
    """Check that every test file in /data/test_*/ is documented in test_metadata.yml"""
    root = os.getcwd()
    data_dir = os.path.join(root, "data")
    file = os.path.abspath(os.path.join(root, data_dir, "test_metadata.yml"))
    
    with open(file, "r") as stream:
        ds = yaml.load(stream, Loader=yaml.FullLoader)
    
    cases = ds.keys()
    for case in cases:
        case_dir = os.path.join(data_dir, case)
        for root, dir, filenames in walk(case_dir, topdown=True):
            files_exist = set([os.path.splitext(f)[0] for f in filenames])
        tests = ds[case].keys()
        files_documented = set(tests)
        assert files_exist == files_documented, \
         "There is a discrepancy between the existing and documented test files \
for the test case {case}. Compare test_data.yml with the contents of \
the {case} folder.".format(case=case)
        for test in tests:
            if not ds[case][test]:
                raise AssertionError('test %s must have a description in test_metadata.yml' % test)
            else:
                assert len(ds[case][test]) > 0, \
                'test %s must have a description in test_metadata.yml' % test
