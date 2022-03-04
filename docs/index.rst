
========
val3dity
========


(version |release|)

val3dity---pronounced 'val-three-dity'---allows us to validate 3D primitives according to the international standard ISO19107.
Think of it as `PostGIS ST_IsValid  <http://postgis.net/docs/ST_IsValid.html>`_, but for 3D primitives (PostGIS is only for 2D ones).

In short, it verifies whether a 3D primitive respects the definition as given in `ISO19107 <http://www.iso.org/iso/catalogue_detail.htm?csnumber=26012>`_ and GML/CityGML.
The validation of the following 3D primitives is fully supported:

  - ``MultiSurface``
  - ``CompositeSurface`` 
  - ``Solid``
  - ``MultiSolid``
  - ``CompositeSolid``

Unlike many other validation tools in 3D GIS, inner rings in polygons/surfaces are supported and so are cavities in solids (also called voids or inner shells).
However, as is the case for many formats used in practice, only planar and linear primitives are allowed: no curves or spheres or other parametrically-modelled primitives are supported. 
There is no plan to support these geometries.

val3dity accepts as input:

  - `CityJSON <http://www.cityjson.org>`_
  - `tu3djson <https://github.com/tudelft3d/tu3djson>`_
  - `OBJ <https://en.wikipedia.org/wiki/Wavefront_.obj_file>`_ 
  - `OFF <https://en.wikipedia.org/wiki/OFF_(file_format)>`_
  - `IndoorGML <http://indoorgml.net/>`_

For the CityJSON and IndoorGML formats, extra validations (specific to the format) are performed, eg the overlap between different parts of a building, or the validation of the navigation graph in IndoorGML.

.. note::  
  If you use val3dity in a scientific context, please cite these articles:

  Ledoux, Hugo (2019). val3dity: validation of 3D GIS primitives according to the international standards. *Open Geospatial Data, Software and Standards*, 3(1), 2018, pp.1 `[DOI] <http://dx.doi.org/10.1186/s40965-018-0043-x>`_

  Ledoux, Hugo (2013). On the validation of solids represented with the international standards for geographic information. *Computer-Aided Civil and Infrastructure Engineering*, 28(9):693-706. `[PDF] <https://3d.bk.tudelft.nl/hledoux/pdfs/13_cacaie.pdf>`_ `[DOI] <http://dx.doi.org/10.1111/mice.12043>`_

.. rubric:: Content

.. toctree::
  :maxdepth: 2

  install
  usage
  errors
  definitions
  faq
  contact

