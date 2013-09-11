# val3dity

Validation of solids according to the international standard ISO 19107.

## I'm interested in the details of how the validation is performed ##

The validation is performed hierarchically, ie first every surface are validated in 2D (with [GEOS](http://trac.osgeo.org/geos/)), then every shell is validated (must be watertight, no self-intersections, orientation of the normals must be consistent and pointing outwards, etc.), and finally the interactions between the shells are analysed.

Most details about the implementation are available in this [scientific article](http://homepage.tudelft.nl/23t4p/pdfs/_13cacaie.pdf).

## How do I use val3dity?

It is a command-line program, which we provide as source code, together with makefiles for Mac and Linux. We plan on offering binaries (including for Windows) in the future.

To compile val3dity, you first need to install the free libraries [CGAL](http://www.cgal.org), [GEOS](http://trac.osgeo.org/geos/) and [CMake](http://www.cmake.org). Afterwards run:

    $ cmake .
    $ make
    
To execute val3dity:

    $ ./val3dity outershell.poly innershell1.poly innershell2.poly
    
Each shell of the solid must be modelled with a [POLY](http://tetgen.berlios.de/fformats.poly.html) file, the first argument is always the outer shell, and the others are inner shells.
There can be 0 or an infinity of inner shells, their order is not important.
For instance, to validate a solid having only outer shell (it's a unit cube):

```  
$ ./val3dity data/poly/cube.poly
Reading 1 file(s).
Reading outer shell:	data/poly/cube.poly

Validating surface in 2D with GEOS (their projection)
-----all valid

Triangulating outer shell
-----done

Validating shell #0
-----Planarity
	yes
-----Combinatorial consistency
	yes
-----Geometrical consistency
	yes
-----Orientation of normals
	yes
Shell #0 valid

Valid solid. Hourrraaa!
```

And to validate a solid with one outer shell and 2 inner shells:

```
$ ./val3dity data/poly/cube.poly data/poly/py1.poly data/poly/py7.poly
Reading 3 file(s).
Reading outer shell:	data/poly/cube.poly
Reading inner shell #0:	data/poly/py1.poly
Reading inner shell #1:	data/poly/py7.poly

Validating surface in 2D with GEOS (their projection)
-----all valid

Triangulating outer shell
Triangulating inner shell #0
Triangulating inner shell #1
-----done

Validating shell #0
-----Planarity
	yes
-----Combinatorial consistency
	yes
-----Geometrical consistency
	yes
-----Orientation of normals
	yes
Shell #0 valid

Validating shell #1
-----Planarity
	yes
-----Combinatorial consistency
	yes
-----Geometrical consistency
	yes
-----Orientation of normals
	yes
Shell #1 valid

Validating shell #2
-----Planarity
	yes
-----Combinatorial consistency
	yes
-----Geometrical consistency
	yes
-----Orientation of normals
	yes
Shell #2 valid

Inspecting interactions between the 3 shells
Error 400: shells are face adjacent
	[shell: #1; face: #2]

Invalid solid :(
```

# Error reported 

## Surface level

  * 200   : exterior ring and interior rings have same orientation
  * 210   : surface is not planar
  * 220   : surface is not valid in 2D (its projection)
    * 221 : interior ring intersect exterior ring
    * 222 : interior ring outside exterior ring
    * 223 : interior rings intersect
    * 224 : interior not connected

## Shell level

  * 300   : is not a 2-manifold
    * 301 : surface is not closed
    * 302 : dangling faces 
    * 303 : one(several) face(s) not connected to the 2-manifold 
    * 304 : orientation of one/several face(s) not correct 
    * 305 : surface self-intersect
  * 310   : normals not pointing in correct direction (all of them)

## Solid level

  * 400   : shells are face adjacent
  * 410   : interior of shells intersect
  * 420   : interior shell completely outside the exterior shell
  * 430   : interior not connected
