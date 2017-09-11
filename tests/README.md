The entry point for testing *val3dity* is `test.py`.

Run basic set of tests:
```
python test.py
```
<!-- TODO: how to define the basic set of tests --> 

Run full set of tests:
```
python test.py --full
```

The tests are organised in the hierarchy of 

+ test suite
    + test case
        + test

In these integration tests a **test suite** is a collection of *test cases* that test a conceptually related set of errors. For example the geometry errors of 3D primitives that are relevant for each accepted file format. Each test suite has its own folder, named as `test_<test suite>` (eg `test_geometry_generic`). Every test suite has a `DESCRIPTION` that briefly outlines its goal.

Within the folder of its test suite, the subordinate **test cases** are living. Every test case tests a particular error, bug. For example the error *101_TOO_FEW_POINTS* has its own test case. Technically, every test case consists of:

+ A single python script named as `test_<test case>.py`.
+ A collection of data files that are used by the *tests* of the test case. Each file is named as `<test case>_<corner case>.<format>`.

Every test case must have at least one basic **test** and arbitrary many *corner cases*. Ideally every test has its own data file, where the data file contains *only* the error that the test is testing.

This hierarchy gives space to the following file structure:

```
tests/
|–– test_geometry_generic/
    |–– 101.poly
    |–– 101_1.poly
    |–– 101_<corner case>.poly
    |–– <test case>.poly
    |–– <test case>_<corner case>.poly
    |–– ...
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
|-- test.py
|–– fail.png
|–– success.png
```

The script `test.py` collects and runs all test cases and prepares a structured report `test_report.json`. Only those files and folders are considered that are prepended with `test_`.

*The main purpose of structuring the tests in the described way is to provide clarity for the developers and help with systematic testing. Certainly there are other possible approaches.*