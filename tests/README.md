Run basic set of tests:
```
pytest
```
<!-- TODO: how to define the basic set of tests --> 

Run full set of tests:
```
pytest
```

The tests are organised in the hierarchy:

+ test suite
    + test case
        + test

In these integration tests a **test suite** is a collection of *test cases* that test a conceptually related set of errors. For example the geometry errors of 3D primitives that are relevant for each accepted file format. Each test suite has its own folder, named as `test_<test suite>` (eg `test_geometry_generic`). Every test suite has a `DESCRIPTION` that briefly clarifies its goal.

Within the folder of its test suite, the subordinate **test cases** are living. Every test case tests a particular error, bug. For example the error *101_TOO_FEW_POINTS* has its own test case. Technically, every test case consists of:

+ A single python script named as `test_<test case>.py`.
+ A collection of data files that are used by the *tests* of the test case. Each file is named as `<test case>_<corner case>.<format>`, and stored at `data/test_<test suite>/`.

Every test case must have at least one basic **test** and arbitrary many *corner cases*. Ideally every test has its own data file, where the data file contains *only* the error that the test is testing.

<!-- TODO: it would actually make more  sense to have all test suite in a single script. 
In this case, fixtures can be separately invoked just for the module that requires them. No
need to keep all of them across the whole session. -->

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
|–– test_geometry_generic/
    |–– DESCRIPTION.txt
    |–– test_101.py
    |–– test_<test case>.py
    |–– ...
|–– test_geometry_specific/
|–– test_file_format/
|–– test_empty_files/
|–– test_valid/
|–– test_<test suite>/
|–– ...
```

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