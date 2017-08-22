
==============
Using val3dity
==============

.. note::

  val3dity is a command-line program only, there is not graphical interface.

How to run val3dity?
--------------------

To execute val3dity and see its options:

.. code-block:: bash

  $ val3dity --help
    

To validate all the 3D primitives in a CityGML file and see a summary output:

.. code-block:: bash

  $ val3dity citygmlinput.gml 


To validate all the 3D primitives in a GML file and get a report ``report.xml``:

.. code-block:: bash

  $ val3dity input.gml -r report.xml


To validates each 3D primitive in input.gml, and to merge/snap the vertices closer than 0.1unit:

.. code-block:: bash

  $ val3dity input.gml --snap_tolerance 0.1


To validate an OBJ file and verify whether the 3D primitives from a ``Solid``:

.. code-block:: bash

  $ val3dity input.obj -p Solid
    

How are 3D primitives validated?
--------------------------------

All primitives are validated hierarchically, for instance:

  1. the lower-dimensionality primitives (the polygons) are validated by first embedding every polygon in 3D and then by projecting it to a 2D plane and using `GEOS <http://trac.osgeo.org/geos/>`_;
  2. then these are assembled into shells/surfaces and their validity is analysed (must be watertight, no self-intersections, orientation of the normals must be consistent and pointing outwards, etc);
  3. then the ``Solids`` are validated
  4. finally, for ``CompositeSolids`` the interactions between the ``Solids`` are analysed.

This means that if one polygon of a Solid is not valid, the validator will report that error but will *not* continue the validation (to avoid "cascading" errors). 

For a ``MultiSolid``, each of the ``Solid`` is validated individually, but the topological relationships between the ``Solids`` are not verified, since a ``Multi*`` is a simple collection of primitives that does not enforce any.

For a ``CompositeSurface``, the surface formed by the individual surfaces must be a 2-manifold, and the same hierarchical validation applies.

For ``MultiSurfaces``, only the validation of the individual polygons is performed, ie are they valid according to the 2D rules, and are they planar (we use a tolerance that can be defined)?


Input files
-----------

val3dity accepts as input:

  - `CityGML <https://www.citygml.org>`_ 
  - `CityJSON <http://www.cityjson.org>`_
  - any `GML file <https://en.wikipedia.org/wiki/Geography_Markup_Language>`_
  - `OBJ <https://en.wikipedia.org/wiki/Wavefront_.obj_file>`_ 
  - `OFF <https://en.wikipedia.org/wiki/OFF_(file_format)>`_
  - `POLY <http://wias-berlin.de/software/tetgen/1.5/doc/manual/manual006.html#ff_poly>`_

For CityGML/CityJSON files, all the City Objects (eg ``Building`` or ``Bridge``) are processed and their 3D primitives are validated.
The 3D primitives are bundled under their City Objects in the report.

For GML files, the file is simply scanned for the 3D primitives and validates these according to the rules in ISO19107, all the rest is ignored. 

For OBJ, OFF, and POLY files, each primitive will be validated according to the ISO19107 rules, one must specify how the primitives should be validated (``MultiSurface``, ``CompositeSurface``, or ``Solid``).
In an OBJ file, if there is more than one object (lines starting with "o", eg `o myobject`), each will be validated individually.
Observe that OBJ files have no mechanism to define inner shells, and thus a solid will be formed by only its exterior shell.
Validating one primitive in an OBJ as a MultiSurface (``-p MultiSurface`` option) will validate individually each surface according to the ISO19107 rules, without ensuring that they form a 2-manifold.
If your OBJ contains only triangles (often the case), then using the option `-p MultiSurface` is rather meaningless since most likely all your triangles are valid; validation could however catch cases where vertices are not referenced by faces (error ``309: VERTICES_NOT_USED``), cases where triangles are collapsed to a line/point.
Validating it as a solid verify whether the primitive is a 2-manifold, ie whether it is closed/watertight and whether all normals are pointing outwards.


Options for the validation
--------------------------

Validation of CityGML/CityJSON Buildings
****************************************

If your CityGML/CityJSON contains ``Buildings`` having one or more ``BuildingParts``, val3dity will perform an extra validation: it will ensure that the 3D primitives do not overlap (technically that the interior of each ``BuildingPart`` does not intersect with the interior of any other part of the ``Building``).

Snapping tolerance
******************
Geometries modelled in GML store amazingly very little topological relationships. 
A cube is for instance represented with 6 surfaces, all stored independently. 
This means that the coordinates xyz of a single vertex (where 3 surfaces "meet") is stored 3 times. 
It is possible that these 3 vertices are not exactly at the same location (eg (0.01, 0.5, 1.0), (0.011, 0.49999, 1.00004) and (0.01002, 0.5002, 1.0007)), and that would create problems when validating since there would for example be holes in the cube. 
The snap tolerance basically gives a threshold that says: "if 2 points are closer then *X*, then we assume that they are the same". 
It's setup by default to be 1mm. 

It can be changed with ``--snap_tolerance 0.08`` (which would mean to use 0.08unit; default is 1mm).
If no snapping is wanted, use ``--snap_tolerance 0``

Planarity tolerances
********************
It is possible to define 2 tolerances for the planarity of surfaces with the flags: 

  1. ``--planarity_d2s`` the distance between every point forming a surface and a plane is less than a given tolerance (eg 1cm, which is the default).
  2. ``--planarity_n`` the surface is triangulated and the normal of each triangle must not deviate more than than a certain usef-defined tolerance (eg 1 degree, which is the default).

Tolerance for 3D distance between Solids and/or BuildingParts
*************************************************************

.. image:: _static/vcsol_2.png
   :width: 100%

For the validation of the topological relationships between Solids forming a CompositeSolid, or the different `BuildingParts` of a building, one can define a tolerance.
This is used to prevent the validator reporting that 2 parts of a building overlap, while they are simply overlapping by 0.1mm for instance.
The tolerance ``--overlap_tolerance 0.05`` means that each of the solids is given a 0.05unit *fuzzy* boundary (thus 5cm if meters are the unit of the input), and thus this is considered when validating.
Its default is 0.0unit.
Observe that using an overlap tolerance significantly reduces the speed of the validator, as rather complex geometric operations are performed.

To validate only the buildings in a CityGML file (and ignore all the rest) with a tolerance for the overlap of 1cm (0.01unit), and to obtain a report for each building:

.. code-block:: bash

  $ ./val3dity input.gml -b --overlap-tolerance 0.01 -r myreport.xml


