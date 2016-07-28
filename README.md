# val3dity

Validation of 3D primitives according to the international standard ISO 19107.

The 3D primitives of GML (`<gml:Solid>`, `<gml:CompositeSurface>`, or `<gml:MultiSurface>`) are what it was built for, but it can be used to validate any 3D primitive, also in other formats. 
It accepts as input any GML files (or one of the formats built upon it, such as CityGML), OBJ, OFF, and [POLY](http://wias-berlin.de/software/tetgen/1.5/doc/manual/manual006.html#ff_poly).
It simply scans the file looking for the 3D primitives and validates these according to the rules in ISO19107 (all the rest is ignored). 
In a OBJ/OFF/STL file, each primitive will be validated according to the ISO 19107 rules. 

For `Solids`, the validation is performed hierarchically, ie first every polygon (embedded in 3D) is validated (by projecting it to a 2D plane and using [GEOS](http://trac.osgeo.org/geos/)), then every shell is validated (must be watertight, no self-intersections, orientation of the normals must be consistent and pointing outwards, etc), and finally the interactions between the shells are analysed. 
This means that if a polygon of your solid is not valid, the validator will report that error but will *not* continue the validation (to avoid "cascading" errors). 

For `CompositeSurfaces`, the surface formed by the polygons must be a 2-manifold.

For `MultiSurfaces`, only the validation of the individual polygons is performed, ie are they valid according to the 2D rules, and are they planar?

Most of the details are available in this scientific article:

> Ledoux, Hugo (2013). On the validation of solids represented with the
international standards for geographic information. *Computer-Aided Civil and Infrastructure Engineering*, 28(9):693-706. [ [PDF] ](https://3d.bk.tudelft.nl/hledoux/pdfs/13_cacaie.pdf) [ [DOI] ](http://dx.doi.org/10.1111/mice.12043)


## Web application

If you're you don't want to go through the troubles of compiling and/or installing val3dity, we suggest you use the [web application](http://geovalidation.bk.tudelft.nl/val3dity). 
You upload your file to our server and get a validation report back.
We delete the file as soon as it has been validated.
However, a file is limited to 50MB.


## How do I compile and use val3dity?

It is a command-line program, which we provide as source code, with CMake.
It's trivial to compile under Mac and Linux.
[For Windows, we do offer an executable](https://github.com/tudelft3d/val3dity/releases).

To compile val3dity yourself, you first need to install the following free libraries:

  1. [CGAL](http://www.cgal.org)
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
Observe that OBJ/OFF/STL files have no mechanism to define inner shells, and thus a solid will be formed by only its exterior shell.
Validating one primitive in OBJ as a MultiSurface (`-p MS` option) will validate individually each surface according to the ISO 19107 rules, without ensuring that they form a 2-manifold.
If your OBJ contains only be triangles (often the case), then using the option `-p MS` is rather meaningless since most likely all your triangles are valid; validation could however catch cases where vertices are not referenced by faces (error `309: VERTICES_NOT_USED`) and collapsed triangles.
Validating it as a solid with verify whether the primitive is a 2-manifold, whether it is closed/watertight and whether all normals are pointing outwards.

See the [FAQ for the web application](http://geovalidation.bk.tudelft.nl/val3dity/faq) for more details.


## Options for validating

It is possible to define 2 tolerances for the planarity of surfaces with the flags: 

  1. `--planarity_d2s` the distance between every point forming a surface and a plane is less than a given tolerance (eg 1cm, which is the default).
  1. `--planarity_n` the surface is triangulated and the normal of each triangle must not deviate more than than a certain usef-defined tolerance (eg 1 degree, which is the default).

Similarly, the input points in a GML files are snapped together using a tolerance, which can be changed with `--snap_tolerance` (default is 1mm).

## Error reported 

![](https://dl.dropboxusercontent.com/u/8129172/errorcodes.png)

(a description of each error is available [here](https://github.com/tudelft3d/val3dity/blob/master/errors_description/errors_description.md))

