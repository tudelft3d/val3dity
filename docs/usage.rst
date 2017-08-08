
==============
Using val3dity
==============

How are 3D primitives validated?
--------------------------------

All primitives are validated hierarchically, for instance:

  1. the lower-dimensionality primitives (the polygons) are validated by first embedding every polygon in 3D and then by projecting it to a 2D plane and using `GEOS <http://trac.osgeo.org/geos/>`_;
  1. then these are assembled into shells/surfaces and their validity is analysed (must be watertight, no self-intersections, orientation of the normals must be consistent and pointing outwards, etc);
  1. then the ``Solids`` are validated
  1. finally, for ``CompositeSolids`` the interactions between the ``Solids`` are analysed.

This means that if one polygon of a Solid is not valid, the validator will report that error but will *not* continue the validation (to avoid "cascading" errors). 

For a ``MultiSolid``, each of the ``Solid`` is validated individually, but the topological relationships between the ``Solids`` are not verified, since a ``Multi*`` is a simple collection of primitives that does not enforce any.

For a ``CompositeSurface``, the surface formed by the individual surfaces must be a 2-manifold, and the same hierarchical validation applies.

For ``MultiSurfaces``, only the validation of the individual polygons is performed, ie are they valid according to the 2D rules, and are they planar (we use a tolerance that can be defined)?


Input files
-----------

val3dity accepts as input any `GML files <https://en.wikipedia.org/wiki/Geography_Markup_Language>`_ (or one of the formats built upon it, such as `CityGML <http://www.citygml.org>`_), `OBJ <https://en.wikipedia.org/wiki/Wavefront_.obj_file>`_, `OFF <https://en.wikipedia.org/wiki/OFF_(file_format)>`_, and `POLY <http://wias-berlin.de/software/tetgen/1.5/doc/manual/manual006.html#ff_poly>`_.
It simply scans the file looking for the 3D primitives and validates these according to the rules in ISO19107, all the rest is ignored. 

In OBJ, OFF, and POLY files, each primitive will be validated according to the ISO19107 rules, as if they were either a Solid or a CompositeSurface.


