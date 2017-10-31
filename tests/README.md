# Testing val3dity

This README is solely concerned with the integration tests for val3dity. These tests are implemented in **python 3**, with the `pytest` library. The tests call val3dity using the `subprocess` library and feed it with various files. Every file materializes a specific error case, or one of its boundary conditions. Thus validating a test file should result in a single error, unless there is good reason to do otherwise.

Due to the current setup of file referencing in the tests, `pytest` need to be run from the `/val3dity` root directory, thus `somepath/val3dity $ pytest`

Run basic set of tests:
```
$ pytest
```

Run full set of tests:
```
$ pytest --runfull
```

Run in verbose mode to see which tests are executed or skipped:
```
$ pytest -v
```

Run a single test case, eg *test_101*:
```
$ pytest -k "test_101"
```

Run a single test case, eg *test_104* with only one of its inputs:
```
$ pytest -k "test_104[104_2.poly]"
```

Run test on the test metadata:
```
$ pytest --runfull -k "metadata"
```


For more info see [pytest docs on markers](https://docs.pytest.org/en/latest/example/markers.html#marking-test-functions-and-selecting-them-for-a-run).

The tests are organised in the hierarchy:

+ test case
    + test

In these integration tests a **test case** is a collection of *tests* that test a conceptually related set of errors. For example the geometry errors of 3D primitives that are relevant for each accepted file format. Each test case has its own module, named as `test_<test case>.py` (eg `test_geometry_generic.py`). Every test case has a description in form of a docstring that briefly clarifies its goal.

Every **test** tests a particular error, bug. For example the error *101_TOO_FEW_POINTS* has its own test `test_101`. Technically, every test case consists of:

+ A collection of test functions named as `test_<test>()`, eg `test_101()`.
+ A collection of data files that are used by the *tests* of the test case. Each file is named as `<test case>_<boundary condition>.<format>`, and stored at `data/test_<test case>/`, `data/test_geometry_generic/101.poly`.

A good way to think about the organisation is that within a test case, every **test** is expected to return the same error. In other words, a test case checks that a certain path in the software reliably returns the same output for different inputs. In *val3dity* the different inputs are most often boundary conditions of the geometric primitives with certain errors (eg 101). The data files are stored separately from the test modules.

Most spatial data, or geometry data needs some metadata, because they are too complex to be self-explanatory. Therefore every test data file *needs* a description in `test_metadata.yml`. Note that this is enforced by `test_metadata.py` when running the *full test set*. 

In `test_metadata.yml` the quoting of the nodes is important, particularly if there are no letters in the filename:

```yaml
test_geometry_generic:                                  # test case
  "101": cube top face a line (with only 2 vertices)    # test file: description
  "101_1": cube with top face having only 2 points
```

The test hierarchy yields the following file structure:

```
data/
|–– test_geometry_generic/
    |–– 101.poly
    |–– 101_1.poly
    |–– 101_<boundary condition>.poly
    |–– <test case>.poly
    |–– <test case>_<boundary condition>.poly
|–– test_geometry_specific/
|–– test_file_format/
|–– test_empty_files/
|–– test_valid/
|–– test_<test case>/
|-- test_metadata.yml
|–– ...
...
tests/
|-- conftest.py
|–– test_geometry_generic.py
|–– test_geometry_specific.py
|–– test_file_format.py
|–– test_empty_files.py
|–– test_valid.py
|–– test_user_input.py
|–– test_<test case>.py
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

If you add a new marker, make sure to register it in `pytest.ini`.

### How test with multiple input parameters?

For example you want to test a geometry with `--snap_tol` `0.1, 0.01, 0.001`. To do that, create a fixture with these arguments. For example:

```python
@pytest.fixture(scope="module",
                params=[
                    ["--unittests", "--snap_tol 0.1"],
                    ["--unittests", "--snap_tol 0.01"],
                    ["--unittests", "--snap_tol 0.001"]
                    ])
def options_valid(request):
    return(request.param)


def test_options_valid(validate, data_composite_solid, options_valid):
    """Valid input options and tolerance arguments"""
    error = validate(data_composite_solid, options=options_valid)
    assert(error == [])
```

### How to add inner shells to a geometry?

For testing errors that are related to inner shells, these need to be passed separately from the exterior in the POLY files. It needs a bit more lines of code, but use test_geometry_generic::401 as an example. You can add multiple inner shells as a list: `[interor1, interor2, ...]`. The normals of the interor have to point "inwards". The fixture `data_401` below uses the `data_basecube` as the exterior shell.

```python
@pytest.fixture(scope="session")
def data_basecube():
    """unit cube that is used in combination with inner-shell testing"""
    root = os.getcwd()
    file_path = os.path.abspath(
        os.path.join(root, "data/test_valid/basecube.poly")
        )
    return([file_path])


@pytest.fixture(scope="module",
                params=["401.poly",
                        "401_1.poly",
                        ["401_2.poly", "inner_shell.poly"],
                        ["401_3.poly", "inner_shell.poly"],
                        "401_4.poly"])
def data_401(request, dir_geometry_generic, data_basecube):
    ishell = request.param
    ishell_path = []
    if isinstance(ishell, list):
        for i in ishell:
            i_path = os.path.abspath(
                        os.path.join(dir_geometry_generic, i)
                        )
            ishell_path = ishell_path + ["--ishell", i_path]
    else:
        ishell_path = ["--ishell",
                       os.path.abspath(
                           os.path.join(dir_geometry_generic, ishell)
                           )
                       ]
    inner_outer_path = ishell_path + data_basecube
    return(inner_outer_path)


def test_401(validate, data_401):
    error = validate(data_401)
    assert(error == [401])
```

### How to get the whole stdout from val3dity instead of just the error code?

Use the `validate_full()` fixture validation function instead of `validate()`.



