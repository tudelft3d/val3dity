val3dity
========

Validation of solids according to the international standard ISO 19107.

## I'm interested in the details of how the validation is performed ##

Most details about the implementation are available in this [scientific article](http://homepage.tudelft.nl/23t4p/pdfs/_13cacaie.pdf).

## How do I use val3dity?

It is a command-line program, which we provide as source code, together with makefiles for Mac and Linux. We plan on offering binaries (including for Windows) in the future.

To compile val3dity, you first need to install the free libraries [CGAL](http://www.cgal.org) and [GEOS](http://trac.osgeo.org/geos/). [CMake](http://www.cmake.org) is highly recommended. Afterwards run:

    $ cmake .
    $ make
    $ ./val3dity inputfile.poly

