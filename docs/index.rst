.. CityJSON documentation master file, created by
   sphinx-quickstart on Thu Jun 22 17:47:16 2017.
   You can adapt this file completely to your liking, but it should at least
   contain the root `toctree` directive.

========
val3dity
========

(version |release|)

Validation of 3D primitives according to the international standard ISO19107.
Think of it as `PostGIS ST_IsValid  <http://postgis.net/docs/ST_IsValid.html>`_, but for 3D primitives (PostGIS is only for 2D ones).

It allows us to validate a 3D primitive, ie to verify whether it respects the definition as given in `ISO19107 <http://www.iso.org/iso/catalogue_detail.htm?csnumber=26012>`_ and GML/CityGML.
The 3D primitives of GML are all supported:

  - ``<gml:MultiSurface>``
  - ``<gml:CompositeSurface>`` 
  - ``<gml:Solid>``
  - ``<gml:MultiSolid>``
  - ``<gml:CompositeSolid>``

However, as is the case for CityGML, only planar and linear primitives are allowed: no curves or spheres or other parametrically-modelled primitives are supported (and there is no plan to do so!).


.. note::  
  Most of the details are available in this scientific article, (if you use val3dity for scientific purposes please cite this article):

  Ledoux, Hugo (2013). On the validation of solids represented with the international standards for geographic information. *Computer-Aided Civil and Infrastructure Engineering*, 28(9):693-706. `[PDF] <https://3d.bk.tudelft.nl/hledoux/pdfs/13_cacaie.pdf>`_ `[DOI] <http://dx.doi.org/10.1111/mice.12043>`_


.. rubric:: Content

.. toctree::
   :maxdepth: 2

   usage
   faq
   errors
   changelog
   contact

