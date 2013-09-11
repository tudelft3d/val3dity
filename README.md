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
    
To run it:

  $ ./val3dity outershell.poly innershell1.poly innershell2.poly
    
Each shell of the solid must be modelled with a [POLY](http://tetgen.berlios.de/fformats.poly.html) file, the first argument is always the outer shell, and the others are inner shells.
There can be 0 or an infinity of inner shells, their order is not important.
For instance to validate a solid having only outer shell (it's a unit cube):
  $ ./val3dity data/poly/cube.poly

