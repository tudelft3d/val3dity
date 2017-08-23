============
Installation
============


macOS & Linux
-------------

We offer CMake and it's trivial to compile val3dity.

To compile val3dity yourself, you first need to install the following free libraries:

  1. `CGAL <http://www.cgal.org>`_
  1. `GEOS <http://trac.osgeo.org/geos/)>`_
  1. `CMake <http://www.cmake.org>`_

Under Mac we suggest using `Homebrew <http://brew.sh/>`_:

.. code-block:: bash

  $ brew install cmake 
  $ brew install cgal
  $ brew install geos

Afterwards run:

.. code-block:: bash
  
  $ mkdir build
  $ cd build
  $ cmake ..
  $ make
  $ ./val3dity ../data/cityjson/cube.json


Windows
-------

For Windows, we do offer an `executable <https://github.com/tudelft3d/val3dity/releases>`_, and there's a Visual Studio project code in the folder ``vs_build``, although installating the dependencies is slightly more complex than for macOS/Linux.


Web-application
---------------

If you don't want to go through the troubles of compiling and/or installing val3dity, we suggest you use the `web application <http://geovalidation.bk.tudelft.nl/val3dity>`_. 
You upload your file to our server and get a validation report back.
We delete the file as soon as it has been validated.
However, a file is limited to 50MB.
