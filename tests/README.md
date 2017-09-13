# Testing val3dity

This README is solely concerned with the integration tests for val3dity. These tests are implemented in python, with the `pytest` library. The tests call val3dity using the `subprocess` library and feed it with various files. Every file materializes a specific error case, or one of its corner cases. Thus validating a test file should result in a single error, unless there is good reason to do otherwise.

Run basic set of tests:
```
pytest
```

Run full set of tests:
```
pytest --runfull
```

Run in verbose mode to see which tests are executed or skipped:
```
pytest -v
```

Run a single test case, eg *test_101* that is part of the *test_geometry_generic* test suite:
```
pytest test_geometry_generic.py::test_101
```

For more info see [pytest docs on markers](https://docs.pytest.org/en/latest/example/markers.html#marking-test-functions-and-selecting-them-for-a-run).

The tests are organised in the hierarchy:

+ test case
    + test

In these integration tests a **test case** is a collection of *tests* that test a conceptually related set of errors. For example the geometry errors of 3D primitives that are relevant for each accepted file format. Each test case has its own module, named as `test_<test case>.py` (eg `test_geometry_generic.py`). Every test case has a description in form of a docstring that briefly clarifies its goal.

Every **test** tests a particular error, bug. For example the error *101_TOO_FEW_POINTS* has its own test `test_101`. Technically, every test case consists of:

+ A collection of test function named as `test_<test>()`, eg `test_101()`.
+ A collection of data files that are used by the *tests* of the test case. Each file is named as `<test case>_<corner case>.<format>`, and stored at `data/test_<test case>/`, `data/test_geometry_generic/101.poly`.

A good way to think about the organisation is that within a test case, every **test** is expected to return the same error. In other words, a test case checks that a certain path in the software reliably returns the same output for different inputs. In *val3dity* the different inputs are most often corner cases of the geometric primitives with certain errors (eg 101).
Ideally every test has its own data file, where the data file contains *only* the error that the test is testing. The data files are stored separately from the test modules.

Most spatial data, or geometry data needs some metadata, because they are too complex to be self-explanatory. Therefore every test data file *needs* a description in `test_data.yml`. Note that this is enforced by `test_metadata.py` when running the *full test set*. 

The test hierarchy yields the following file structure:

```
data/
|–– test_geometry_generic/
    |–– 101.poly
    |–– 101_1.poly
    |–– 101_<corner case>.poly
    |–– <test case>.poly
    |–– <test case>_<corner case>.poly
|–– test_geometry_specific/
|–– test_file_format/
|–– test_empty_files/
|–– test_valid/
|–– test_<test suite>/
|-- test_data.yml
|–– ...
...
tests/
|-- conftest.py
|–– test_geometry_generic.py
|–– test_geometry_specific.py
|–– test_file_format.py
|–– test_empty_files.py
|–– test_valid.py
|–– test_<test suite>.py
|–– ...
```

*The main purpose of structuring the tests in the described way is to provide clarity for the developers and help with systematic testing. Certainly there are other possible approaches.*

## A few details

Test configuration parameters are in `conftest.py`.

To mark a test as part of the *full* superset, mark it as `full`. In this case the test is only run when the `--runfull` command line argument is passed to pytest. For example:

```python
@pytest.mark.full
def test_102():
    assert 0
```

If you add a new marker, make sure you register it in `pytest.ini`.

In `test_data.yml` the quoting of the nodes is important, particularly if there are no letters in the filename:

```yaml
# test case
test_geometry_generic:
  # test file: description
  "101": cube top face a line (with only 2 vertices)
  "101_1": cube with top face having only 2 points
```

------

possibly define tests in a yaml file, sth like

```
geometry_generic:
    101:
        basic: 101.poly
        case1: 101_1.poly
        case2: 101_2.poly
...
```