# Testing val3dity

This README is solely concerned with the integration tests for val3dity. These tests are implemented in python, with the `pytest` library. The tests call val3dity using the `subprocess` library and feed it with various files. Every file materializes a specific error case, or one of its corner cases. Thus validating a test file should result in a single error, unless there is good reason to do otherwise.

Run basic set of tests:
```
pytest path/to/val3dityexe
```
<!-- TODO: how to pass pytest and arbitrary argument that the tests can take -->

Run full set of tests:
```
pytest --runfull path/to/val3dityexe
```

Run a single test case, eg *test_101* that is part of the *test_geometry_generic* test suite:
```
pytest test_geometry_generic.py::test_101
```

The tests are organised in the hierarchy:

+ test suite
    + test case
        + test

In these integration tests a **test suite** is a collection of *test cases* that test a conceptually related set of errors. For example the geometry errors of 3D primitives that are relevant for each accepted file format. Each test suite has its own module, named as `test_<test suite>.py` (eg `test_geometry_generic.py`). Every test suite has a description in form of a docstring that briefly clarifies its goal.

In the module of the test suite, the **test cases** are living. Every test case tests a particular error, bug. For example the error *101_TOO_FEW_POINTS* has its own test case. Technically, every test case consists of:

+ A test function named as `test_<test case>()`, eg `test_101()`.
+ A collection of data files that are used by the *tests* of the test case. Each file is named as `<test case>_<corner case>.<format>`, and stored at `data/test_<test suite>/`.

A good way to think about the organisation is that within a test case, every **test** is expected to return the same error. In other words, a test case checks that a certain path in the software reliably returns the same output for different inputs. In *val3dity* the different inputs are most often corner cases of the geometric primitives with certain errors (eg 101).
Ideally every test has its own data file, where the data file contains *only* the error that the test is testing. The data files are stored separately from the test modules.

This hierarchy gives space to the following file structure:

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

## A few details

Test configuration parameters are in `conftest.py`.

To mark a test as part of the *full* superset, mark it as `full`. In this case the test is only run when the `--runfull` command line argument is passed to pytest. For example:

```python
@pytest.mark.full
def test_102():
    assert 0
```

If you add a new marker, make sure you register it in `pytest.ini`.

<!-- TODO: write custom assertion based on validate -->

*The main purpose of structuring the tests in the described way is to provide clarity for the developers and help with systematic testing. Certainly there are other possible approaches.*

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
use a session-fixture for VAL3DITYEXE and DATAFOLDER