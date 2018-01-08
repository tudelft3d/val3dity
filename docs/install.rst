============
Installation
============


macOS & Linux
-------------

We provide the source code that you need to compile with CMake.


To compile val3dity yourself, you first need to install the following free libraries:

  1. `CGAL v4.10+ <http://www.cgal.org>`_ (<v4.10 will compile and run, but wrong results for one test (error 405))
  2. *watch out*: CGAL needs to be compiled with the `Eigen library <http://eigen.tuxfamily.org>`_
  3. `GEOS <http://trac.osgeo.org/geos/>`_
  4. `CMake <http://www.cmake.org>`_

Under macOS, it's super easy, we suggest using `Homebrew <http://brew.sh/>`_:

.. code-block:: bash

    $ brew install cgal --with-eigen
    $ brew install cmake 
    $ brew install geos

Under Linux (at least Ubuntu), CGAL has to be compiled because apt-get doesn't give you a version with Eigen.
Thus, in a nutshell,

  1. download `latest CGAL code <https://github.com/CGAL/cgal/releases>`_
  2. install Eigen library: ``$ sudo apt-get install libeigen3-dev``
  3. compile CGAL by first activating the Eigen option in the CMake (``$ cmake . -DWITH_Eigen3=ON``), or use `cmake-gui <https://cmake.org/runningcmake/>`_ and activate it (option is called ``WITH_Eigen3``)
  4. ``export CGAL_DIR=/path/to/CGAL-4.1x`` which will tell your shell to use that version of CGAL (thus more version of CGAL can be installed on the same computer; see that `handy manual <https://github.com/CGAL/cgal/wiki/Branch-Build>`_)

To compile and run val3dity (from the val3dity folder):

.. code-block:: bash
  
  $ mkdir build
  $ cd build
  $ cmake ..
  $ make
  $ ./val3dity ../data/cityjson/cube.json

The summary of the validation is reported, and you should see that `cube.json` contains one valid primitive.

To verify that everything went fine during the compilation, run the unit tests (from the root folder of val3dity; must use Python3):

.. code-block:: bash

    $ python3 -m pytest --runfull

You shouldn't get any errors


Finally, to see all the options possible:

.. code-block:: bash

  $ ./val3dity --help


Windows
-------

For Windows, we offer an `executable <https://github.com/tudelft3d/val3dity/releases>`_, and there's a Visual Studio project code in the folder ``vs_build``, although installing the dependencies is slightly more complex than for macOS/Linux.


Web-application
---------------

If you don't want to go through the troubles of compiling and/or installing val3dity, we suggest you use the `web application <http://geovalidation.bk.tudelft.nl/val3dity>`_. 
Simply upload your file to our server and get a validation report back.
We delete the file as soon as it has been validated.
However, a file is limited to 50MB.
