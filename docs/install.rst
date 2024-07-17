============
Installation
============


Windows executable
------------------

For Windows, we offer an `executable <https://github.com/tudelft3d/val3dity/releases>`_, but you can always compile the project yourself with CMake.

It's also possible to compile val3dity yourself with the CMake file we offer, but it's slightly more complex with the dependencies.
We suggest you look at `how we build it on GitHub Actions <https://github.com/tudelft3d/val3dity/blob/main/.github/workflows/build_exe.yml>`_ to get some inspirate (and help).


macOS & Linux: you need to compile
----------------------------------

The details to compile and use val3dity are on `GitHub <https://github.com/tudelft3d/val3dity#installation-of-the-command-line-tool>`_.


Web-application
---------------

If you don't want to go through the troubles of compiling and/or installing val3dity, we suggest you use the `web application <http://geovalidation.bk.tudelft.nl/val3dity>`_. 
Simply upload your file to our server and get a validation report back.
We delete the file as soon as it has been validated.
However, a file is limited to 50MB.


Using val3dity as a library
---------------------------

val3dity can be compiled and used as a library, see `the instructions <https://github.com/tudelft3d/val3dity#using-val3dity-as-a-library>`_.

Also, there is a simple example of how to use it in `./demo_lib` with instructions to compile it.

