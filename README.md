# val3dity 

val3dity---pronounced 'val-three-dity'---allows us to validate 3D primitives according to the international standard ISO19107.
Think of it as [PostGIS ST_IsValid](http://postgis.net/docs/ST_IsValid.html), but for 3D primitives (PostGIS only validates 2D primitives).

In short, it verifies whether a 3D primitive respects the definition as given in [ISO19107](http://www.iso.org/iso/catalogue_detail.htm?csnumber=26012) and GML/CityGML.
All the 3D primitives of GML are supported:

  - `<gml:MultiSurface>`
  - `<gml:CompositeSurface>` 
  - `<gml:Solid>`
  - `<gml:MultiSolid>`
  - `<gml:CompositeSolid>`

Unlike many other validation tools in 3D GIS, inner rings in polygons/surfaces are supported and so are cavities in solids (also called voids or inner shells).
However, as is the case for CityGML, only planar and linear primitives are allowed: no curves or spheres or other parametrically-modelled primitives are supported. There is no plan to support these geometries, because val3dity is developed with 3D city models in focus.

val3dity accepts as input:

  - [CityGML](https://www.citygml.org)) 
  - [CityJSON](http://www.cityjson.org))
  - any [GML files](https://en.wikipedia.org/wiki/Geography_Markup_Language) 
  - [OBJ](https://en.wikipedia.org/wiki/Wavefront_.obj_file), 
  - [OFF](https://en.wikipedia.org/wiki/OFF_(file_format))


## Installation of the command-line tool

We provide the source code that you need to compile with CMake. 
This is straightforward under Mac and Linux.

[For Windows, we offer an executable](https://github.com/tudelft3d/val3dity/releases), although it's also possible to compile val3dity yourself.

To compile val3dity yourself, you first need to install the following free libraries:

  1. [CGAL](http://www.cgal.org)
  1. [GEOS](http://trac.osgeo.org/geos/) 
  1. [CMake](http://www.cmake.org)

Under Mac we suggest using [Homebrew](http://brew.sh/):

    $ brew install cmake 
    $ brew install cgal
    $ brew install geos

Afterwards navigate to the folder with val3dity and run:

    $ mkdir build
    $ cd build
    $ cmake ..
    $ make
    $ ./val3dity ../data/cityjson/cube.json

The summary of the validation is reported, and you should see that `cube.json` contains one valid primitive.

To see all the options:

    $ ./val3dity --help

## Web application

If you don't want to go through the troubles of compiling and/or installing val3dity, we suggest you use the [web application](http://geovalidation.bk.tudelft.nl/val3dity). 
Simply upload your file to our server and get a validation report back.
We delete the file as soon as it has been validated.
However, a file is limited to 50MB.
    
## Documentation and help

Read the full documentation at [http://val3dity.rtfd.io](http://val3dity.rtfd.io). 
The primary channel to communicate with the developers is the Issues section. 
If you have a question or came across a bug, please submit an issue there. 
However we ask you check first whether your problem has already been solved by someone else.