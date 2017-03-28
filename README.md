# val3dity

Validation of 3D primitives according to the international standard ISO19107.
Think of it as the [PostGIS ST_IsValid](http://postgis.net/docs/ST_IsValid.html), but for 3D primitives (PostGIS is only for 2D ones).

Allows us to validate a 3D primitive, ie to verify whether the 3D primitive respects the definition as given in [ISO19107](http://www.iso.org/iso/catalogue_detail.htm?csnumber=26012) and GML/CityGML.
The 3D primitives of GML are all supported:

  - `<gml:Solid>`
  - `<gml:MultiSolid>`
  - `<gml:CompositeSolid>`
  - `<gml:CompositeSurface>` 
  - `<gml:MultiSurface>`

However, as is the case for CityGML, only planar and linear primitives are allowed: no curves or spheres or other parametrically-modelled primitives.

val3dity accepts as input any [GML files](https://en.wikipedia.org/wiki/Geography_Markup_Language) (or one of the formats built upon it, such as [CityGML](http://www.citygml.org)), [OBJ](https://en.wikipedia.org/wiki/Wavefront_.obj_file), and [POLY](http://wias-berlin.de/software/tetgen/1.5/doc/manual/manual006.html#ff_poly).
It simply scans the file looking for the 3D primitives and validates these according to the rules in ISO19107, all the rest is ignored. 
In a OBJ file, each primitive will be validated according to the ISO19107 rules, as if they were a Solid.

All primitives are validated hierarchically, for instance:

  1. the lower-dimensionality primitives (the polygons) are validated by first embedding every polygon in 3D and then by projecting it to a 2D plane and using [GEOS](http://trac.osgeo.org/geos/);
  1. then these are assembled into shells/surfaces and their validity analysed (must be watertight, no self-intersections, orientation of the normals must be consistent and pointing outwards, etc);
  1. then the Solids are validated
  1. finally, for CompositeSolids the interactions between the Solids are analysed.

This means that if one polygon of a Solid is not valid, the validator will report that error but will *not* continue the validation (to avoid "cascading" errors). 

For `CompositeSurfaces`, the surface formed by the polygons must be a 2-manifold, and the same hierarchical validation applies.

For `MultiSurfaces`, only the validation of the individual polygons is performed, ie are they valid according to the 2D rules, and are they planar (we use a tolerance that can be defined)?

Most of the details are available in this scientific article, (if you use val3dity for scientific purposes please cite this article):

> Ledoux, Hugo (2013). On the validation of solids represented with the
international standards for geographic information. *Computer-Aided Civil and Infrastructure Engineering*, 28(9):693-706. [ [PDF] ](https://3d.bk.tudelft.nl/hledoux/pdfs/13_cacaie.pdf) [ [DOI] ](http://dx.doi.org/10.1111/mice.12043)


## Validation of CityGML Buildings

By using the `--buildings` option, the validator will--instead of search for specific 3D primitives--validate each CityGML `Building`, and produce a report per building.
Every 3D primitive of a building will be validated (be it a `Solid`, `CompositeSolid`, or `MultiSurface`) and included in the report.
Furthermore, if a building is composed of `BuildingPart`, then the topological relationships between all the parts are analysed to ensure that they do not overlap (technically that the interior of each part does not intersect with the interior of any other part).


<!-- ## Web application

If you don't want to go through the troubles of compiling and/or installing val3dity, we suggest you use the [web application](http://geovalidation.bk.tudelft.nl/val3dity). 
You upload your file to our server and get a validation report back.
We delete the file as soon as it has been validated.
However, a file is limited to 50MB.
 -->

## How do I compile and use val3dity?

It is a command-line program, which we provide as source code, with CMake.
It's trivial to compile under Mac and Linux.
[For Windows, we do offer an executable](https://github.com/tudelft3d/val3dity/releases).

To compile val3dity yourself, you first need to install the following free libraries:

  1. [CGAL](http://www.cgal.org)
  1. [GEOS](http://trac.osgeo.org/geos/) 
  1. [CMake](http://www.cmake.org)

Under Mac we suggest using [Homebrew](http://brew.sh/):

    $ homebrew install cmake 
    $ homebrew install cgal
    $ homebrew install geos

Afterwards run:

    $ cmake .
    $ make
    
To execute val3dity and see its options:

    $ ./val3dity --help
    
To validate all the `<gml:Solid>` in a GML or CityGML file and see a summary output:

    $ ./val3dity input.gml -p Solid

Each `<gml:Solid>` in the file will be individually validated and a summary report will be output. 

For a full report in XML format:

    $ ./val3dity input.gml -p Solid -r myreport.xml

To validate other 3D primitives use the `-p` option:

  - `-p MultiSurface`
  - `-p CompositeSurface`
  - `-p MultiSolid`
  - `-p CompositeSolid`

eg:

    $ ./val3dity ./data/gml/csol2.gml -p CompositeSolid


Other formats can also be used as input, the 3D primitives will then be validated according to the ISO19107 definitions:

  1. OBJ: a file can contain more than 1 object (lines starting with "o", eg `o myobject`), each will be validated individually
  1. [POLY](http://wias-berlin.de/software/tetgen/1.5/doc/manual/manual006.html#ff_poly), there are several examples of test datasets in the folder `data/poly/`, see the `README.txt`

In an OBJ file, each primitive will be validated according to the ISO19107 rules. 
Observe that OBJ files have no mechanism to define inner shells, and thus a solid will be formed by only its exterior shell.
Validating one primitive in an OBJ as a MultiSurface (`-p MultiSurface` option) will validate individually each surface according to the ISO19107 rules, without ensuring that they form a 2-manifold.
If your OBJ contains only triangles (often the case), then using the option `-p MultiSurface` is rather meaningless since most likely all your triangles are valid; validation could however catch cases where vertices are not referenced by faces (error `309: VERTICES_NOT_USED`), cases where triangles are collapsed to a line/point.
Validating it as a solid verify whether the primitive is a 2-manifold, ie whether it is closed/watertight and whether all normals are pointing outwards.

See the [FAQ for the web application](http://geovalidation.bk.tudelft.nl/val3dity/faq) for more details.


## Options for validating

It is possible to define 2 tolerances for the planarity of surfaces with the flags: 

  1. `--planarity_d2s` the distance between every point forming a surface and a plane is less than a given tolerance (eg 1cm, which is the default).
  1. `--planarity_n` the surface is triangulated and the normal of each triangle must not deviate more than than a certain usef-defined tolerance (eg 1 degree, which is the default).

Similarly, the input points in a GML files are snapped together using a tolerance, which can be changed with `--snap_tolerance` (default is 1mm).

For the validation of the topological relationships between Solids forming a CompositeSolid, or the different `BuildingParts` of a building, one can define a tolerance.
This is used to prevent the validator reporting that 2 parts of a building overlap, while they are simply overlapping by 0.1mm for instance.
The tolerance `--overlap_tolerance 0.05` means that each of the solids is given a 0.05unit *fuzzy* boundary (thus 5cm if meters are the unit of the input), and thus this is considered when validating.
Its default is 0.0unit.
Observe that using an overlap tolerance significantly reduces the speed of the validator, as rather complex geometric operations are performed.

To validate only the buildings in a CityGML file (and ignore all the rest), and to obtain a report where each building has its ID and its error:

    $ ./val3dity input.gml -b --overlap-tolerance 0.01 -r myreport.xml


## Error reported 

![](/ressources/help/errorcodes.png)

(a description of each error is available [here](https://github.com/tudelft3d/val3dity/blob/master/errors_description/errors_description.md))

