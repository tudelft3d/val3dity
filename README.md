# val3dity

Validation of 3D primitives according to the international standard ISO 19107.

Its main aim is the 3D primitives of GML (`Solids`, `CompositeSurfaces`, or `MultiSurfaces`), but it can be used to validate any 3D primitive. 
It accepts as input any GML files (or one of the formats built upon it, such as CityGML), OBJ, OFF, and [POLY](http://wias-berlin.de/software/tetgen/1.5/doc/manual/manual006.html#ff_poly).
It simply scans the file looking for the 3D primitives and validates these according to the rules in ISO19107 (all the rest is ignored). 

For `Solids`, the validation is performed hierarchically, ie first every polygon (embedded in 3D) is validated (by projecting it to a 2D plane and using [GEOS](http://trac.osgeo.org/geos/)), then every shell is validated (must be watertight, no self-intersections, orientation of the normals must be consistent and pointing outwards, etc), and finally the interactions between the shells are analysed. 
This means that if a polygon of your solid is not valid, the validator will report that error but will *not* continue the validation (to avoid "cascading" errors). 

For `CompositeSurfaces`, the surface formed by the polygons must be a 2-manifold.

For `MultiSurfaces`, only the validation of the individual polygons is performed, ie are they valid according to the 2D rules, and are they planar?

Most of the details are available in this scientific article:

> Ledoux, Hugo (2013). On the validation of solids represented with the
international standards for geographic information. *Computer-Aided Civil and Infrastructure Engineering*, 28(9):693-706. [ [PDF] ](https://3d.bk.tudelft.nl/hledoux/pdfs/13_cacaie.pdf) [ [DOI] ](http://dx.doi.org/10.1111/mice.12043)

## Web application

If you're running Windows and/or you don't want to go through the troubles of compiling, we suggest you use the [web application](http://geovalidation.bk.tudelft.nl/val3dity). 
You upload your file to our server and get a validation report back.
We delete the file as soon as it has been validated; files are limited to 50MB.


## How do I compile and use val3dity?

It is a command-line program, which we provide as source code, with CMake.
It's trivial to compile under Mac and Linux.
For Windows, we do not offer binaries at this moment, but compiling it is easily possible with the CMake.

To compile val3dity yourself, you first need to install the following free libraries:

  1. [CGAL](http://www.cgal.org), 
  1. [GEOS](http://trac.osgeo.org/geos/) 
  1. [Assimp](http://www.assimp.org)
  1. [CMake](http://www.cmake.org)

Under Mac we suggest using [Homebrew](http://brew.sh/):

    $ homebrew install cmake 
    $ homebrew install cgal
    $ homebrew install geos
    $ homebrew install assimp

Afterwards run:

    $ cmake .
    $ make
    
To execute val3dity and see its options:

    $ ./val3dity --help
    
To validate all the solids in a GML or CityGML file:

    $ ./val3dity myfile.gml

Each `<gml:Solid>` in the file will be individually validated and a summary report will be output. 

To validate all the MultiSurfaces in a GML or CityGML file:

    $ ./val3dity myfile.gml -p MS

For a full report in XML format:

    $ ./val3dity myfile.gml --oxml myreport.xml

Other formats can also be used as input, the 3D primitives will then validated according to the ISO19107 definitions:

  1. OBJ (a file can contain more than 1 object, each will be validated individually)
  1. OFF
  1. [POLY](http://wias-berlin.de/software/tetgen/1.5/doc/manual/manual006.html#ff_poly), there are several examples of test datasets in the folder `data/poly/`, see the `README.txt`
  1. [all the formats supported by Assimp](http://www.assimp.org/main_features_formats.html) can in theory be used, although I haven't tested them all. OBJ and OFF surely work.

In a OBJ/OFF/STL file, each primitive will be validated according to the ISO 19107 rules. 
Observe that OBJ/OFF/STL have no mechanism to define inner shells, and thus a solid will be formed by only its exterior shell.
Validating one primitive in OBJ as a MultiSurface (`-p MS` option) will validate individually each surface according to the ISO 19107 rules, without ensuring that they form a 2-manifold.

See the [FAQ for the web application](http://geovalidation.bk.tudelft.nl/val3dity/faq) for more details.


## Options for validating

It is possible to define some tolerances for the planarity of surfaces with the flag `--planarity_n 0.1` which would mean that the points representing a surface should be at a maximum distance of 0.1m (or units, val3dity doesn't reproject the input coordinates) to a plane fitted with least-square adjustment to the points.

Similarly, the input points in a GML files are snapped together using a tolerance, which can be changed with `--snap_tolerance XX`.

## Error reported 

(a description of each error is available [here](https://github.com/tudelft3d/val3dity/blob/master/errors_description/errors_description.md))

### Ring level

  * 101: TOO_FEW_POINTS
  * 102: CONSECUTIVE_POINTS_SAME
  * 103: NOT_CLOSED
  * 104: SELF_INTERSECTION 
  * 105: COLLAPSED_TO_LINE


### POLYGON level

  * 201: INTERSECTION_RINGS
  * 202: DUPLICATED_RINGS
  * 203: NON_PLANAR_POLYGON_DISTANCE_PLANE 
  * 204: NON_PLANAR_POLYGON_NORMALS_DEVIATION 
  * 205: INTERIOR_DISCONNECTED
  * 206: HOLE_OUTSIDE
  * 207: INNER_RINGS_NESTED
  * 208: ORIENTATION_RINGS_SAME


### SHELL level

  * 301: TOO_FEW_POLYGONS
  * 302: NOT_CLOSED
  * 303: NON_MANIFOLD_VERTEX
  * 304: NON_MANIFOLD_EDGE 
  * 305: SEPARATE_PARTS
  * 306: SELF_INTERSECTION
  * 307: POLYGON_WRONG_ORIENTATION
  * 308: ALL_POLYGONS_WRONG_ORIENTATION
  * 309: VERTICES_NOT_USED 


### SOLID level

  * 401: SHELLS_FACE_ADJACENT
  * 402: SHELL_INTERIOR_INTERSECT
  * 403: INNER_SHELL_OUTSIDE_OUTER
  * 404: INTERIOR_OF_SHELL_NOT_CONNECTED

### OTHERS

  * 901: INVALID_INPUT_FILE
  * 902: EMPTY_PRIMITIVE
  * 999: UNKNOWN_ERROR
