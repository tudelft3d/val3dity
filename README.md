# val3dity

Validation of solids according to the international standard ISO 19107.

The validation of a solid is performed hierarchically, ie first every surface is validated in 2D (with [GEOS](http://trac.osgeo.org/geos/)), then every shell is validated (must be watertight, no self-intersections, orientation of the normals must be consistent and pointing outwards, etc), and finally the interactions between the shells are analysed.

Most of the details of the implementation are available in this scientific article:

> Ledoux, Hugo (2013). On the validation of solids represented with the
international standards for geographic information. *Computer-Aided Civil and Infrastructure Engineering*, 28(9):693-706. [ [PDF] ](http://3dgeoinfo.bk.tudelft.nl/hledoux/pdfs/13_cacaie.pdf) [ [DOI] ](http://dx.doi.org/10.1111/mice.12043)


## How do I use val3dity?

It is a command-line program, which we provide as source code, together with makefiles for Mac and Linux. 

For Windows, we do not have binaries at this moment, but you can use the [web interface](http://geovalidation.bk.tudelft.nl/val3dity). 

To compile val3dity yourself, you first need to install the free libraries [CGAL](http://www.cgal.org), [GEOS](http://trac.osgeo.org/geos/) and [CMake](http://www.cmake.org)--under Mac we suggest using [Homebrew](http://brew.sh/). Afterwards run:

    $ cmake .
    $ make
    
To execute val3dity:

    $ ./val3dity outershell.poly innershell1.poly innershell2.poly
    
Each shell of the solid must be represented with a [POLY](http://tetgen.berlios.de/fformats.poly.html) file; the first argument is always the outer shell, and the others are inner shells. 

There can be 0 or an infinity of inner shells, their order is not important.
For instance, to validate a solid having only one outer shell (it's a unit cube):

```  
$ ./val3dity data/poly/cube.poly
Reading 1 file(s).
Reading outer shell:  data/poly/cube.poly

Validating surface in 2D (their projection)
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

Valid solid :)
```

An example where an error is found is as follows (`cube3.poly` is a unit cube with hole in the top polygon):

```
$ ./val3dity data/poly/cube3.poly 
Reading 1 file(s).
Reading outer shell:  data/poly/cube3.poly

Validating surface in 2D (their projection)
-----all valid

Triangulating outer shell
-----done

Validating shell #0
-----Planarity
  yes
-----Combinatorial consistency
Error #302 SHELL_NOT_CLOSED
  [shell: #1; face: #-1]
  Location hole: 0.2 0.8 1

Invalid solid :(
```

And to validate a solid with one outer shell and 2 inner shells:

```
$ ./val3dity data/poly/cube.poly data/poly/py1.poly data/poly/py7
.poly
Reading 3 file(s).
Reading outer shell:  data/poly/cube.poly
Reading inner shell #0: data/poly/py1.poly
Reading inner shell #1: data/poly/py7.poly

Validating surface in 2D (their projection)
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
Error #402 INTERSECTION_SHELLS
  [shell: #2; face: #3]

Invalid solid :(
```


# GML/CityGML input?

Yes it's possible: the script `ressources/python/gml2poly/val3dity.py` allows you to read a GML file and validate it. Not all bells and whistles of GML have been implemented, but `xlinks` are supported for the most common use (no resolving of URLs though).


# Web-application

If you're running Windows and/or you don't want to go through the troubles of compiling, we suggest you use the [web application](http://geovalidation.bk.tudelft.nl/val3dity). It takes as input a GML file (of any flavour, including CityGML for instance) containing one or more `gml:Solids`.


# Error reported 

(a description of each error is available [here](https://github.com/tudelft3d/val3dity/blob/master/errors_description/errors_description.md))

## Ring level

  * 101: TOO_FEW_POINTS
  * 102: CONSECUTIVE_POINTS_SAME
  * 103: NOT_CLOSED
  * 104: SELF_INTERSECTION 
  * 105: COLLAPSED_TO_LINE


## POLYGON level

  * 201: INTERSECTION_RINGS
  * 202: DUPLICATED_RINGS
  * 203: NON_PLANAR_POLYGON_DISTANCE_PLANE 
  * 204: NON_PLANAR_POLYGON_NORMALS_DEVIATION 
  * 205: INTERIOR_DISCONNECTED
  * 206: HOLE_OUTSIDE
  * 207: INNER_RINGS_NESTED
  * 208: ORIENTATION_RINGS_SAME


## SHELL level

  * 301: TOO_FEW_POLYGONS
  * 302: NOT_CLOSED
  * 303: NON_MANIFOLD_VERTEX
  * 304: NON_MANIFOLD_EDGE 
  * 305: MULTIPLE_CONNECTED_COMPONENTS
  * 306: SELF_INTERSECTION
  * 307: POLYGON_WRONG_ORIENTATION
  * 308: ALL_POLYGONS_WRONG_ORIENTATION
  * 309: VERTICES_NOT_USED 


## SOLID level

  * 401:  SHELLS_FACE_ADJACENT
  * 402:  SHELL_INTERIOR_INTERSECT
  * 403:  INNER_SHELL_OUTSIDE_OUTER
  * 404:  INTERIOR_OF_SHELL_NOT_CONNECTED
