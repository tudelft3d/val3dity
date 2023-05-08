.. _errors:

======
Errors
======

.. image:: _static/errorcodes.png
   :width: 100%

.. contents:: :local:

.. _e101:

101 -- TOO_FEW_POINTS
---------------------

A ring should have at least 3 points. For GML rings, this error ignores the fact that the first and the last point of a ring are the same (see :ref:`e103`), ie a GML ring should have at least 4 points.

This ring is for instance invalid:

.. code-block:: xml

  <gml:LinearRing>
    <gml:pos>0.0 0.0 0.0</gml:pos>
    <gml:pos>1.0 0.0 0.0</gml:pos>
    <gml:pos>0.0 0.0 0.0</gml:pos>
  </gml:LinearRing>

.. _e102:

102 -- CONSECUTIVE_POINTS_SAME 
------------------------------
Points in a ring should not be repeated (except first-last in case of GML, see :ref:`e103`). This error is for the common error where 2 *consecutive* points are at the same location. Error 104 is for points in a ring that are repeated, but not consecutive. 

This ring is for instance invalid:

.. code-block:: xml

  <gml:LinearRing>
    <gml:pos>0.0 0.0 0.0</gml:pos>
    <gml:pos>1.0 0.0 0.0</gml:pos>
    <gml:pos>1.0 0.0 0.0</gml:pos>
    <gml:pos>1.0 1.0 0.0</gml:pos>
    <gml:pos>0.0 1.0 0.0</gml:pos>
    <gml:pos>0.0 0.0 0.0</gml:pos>
  </gml:LinearRing>

.. _e103:

103 -- RING_NOT_CLOSED 
----------------------

*This applies only to GML rings, in CityJSON/OBJ/OFF it is ignored.* 
The first and last points have to be identical (at the same location). 
This is verified after the points have been merged with the :ref:`snap_tol` option.

This ring is for instance invalid:

.. code-block:: xml

  <gml:LinearRing>
    <gml:pos>0.0 0.0 0.0</gml:pos>
    <gml:pos>1.0 0.0 0.0</gml:pos>
    <gml:pos>1.0 1.0 0.0</gml:pos>
    <gml:pos>0.0 1.0 0.0</gml:pos>
  </gml:LinearRing>

.. _e104:

104 -- RING_SELF_INTERSECTION 
-----------------------------
A ring should be *simple*, ie it should not self-intersect. The self-intersection can be at the location of an explicit point, or not. This case includes rings that are (partly) collapsed to a line for instance.

Observe that self-intersection in 3D and 2D is different, ie a bowtie (the first polygon below) has a self-intersection "in the middle" in 2D, but in 3D if the 4 vertices are not on a plane then there is no intersection.

.. image:: _static/104.png
   :width: 80%

A ring is self-intersecting if its projection to the best-fitted plane (done with least-square) through the vertices of the polygon containing the ring has a self-intersection.
This rule is there because if it is not possible to project the rings/polygons to a plane, then it is not possible to triangulate it (which is necessary, at least by val3dity, to validate 3D primitives).
In the figure below, the left example shows one polygon (the top one) where a projection (let say to the xy-plane) would not cause any self-intersection.
However, the right example does cause a self-intersection.
It is the same is the vertices *b* and *c* are projected to the same location: a self-intersection is also returned.

.. image:: _static/104b.png


.. _e201:

201 -- INTERSECTION_RINGS
-------------------------
Two or more rings intersect, these can be either the exterior ring with an interior ring or only interior rings. 

.. image:: _static/201.png
   :width: 50%

.. _e202:

202 -- DUPLICATED_RINGS
-----------------------
Two or more rings are identical.

.. _e203:

203 -- NON_PLANAR_POLYGON_DISTANCE_PLANE
----------------------------------------

A polygon must be planar, ie all its points (used for both the exterior and interior rings) must lie on a plane. 
To verify this, we must ensure that the the distance between every point and a plane is less than a given *tolerance* (eg 1cm). 
In the validator, this plane is fitted with least-square adjustment, and the distance between each of the point to the plane is calculated. 
If the distance is larger than the given threshold then an error is reported. 
The distance to the plane, if larger than the threshold, is also reported in the report.

.. _e204:

204 -- NON_PLANAR_POLYGON_NORMALS_DEVIATION
-------------------------------------------

To ensure that small folds on a surface are detected. Consider the Solid below, the top surface containing 8 vertices (*abcdefgh*) is clearly non-planar since there is a vertical "fold" in the middle. 
The normal of the sub-surface *abgh* points upwards, while that of *bcfg* points in a different angle. 
But this surface would not be detected by the :ref:`e203` test (with a tolerance of 1cm for instance) since all the vertices are within that threshold. 
Thus, another requirement is necessary: the distance between every point forming a polygon and *all* the planes defined by all possible combinations of 3 non-collinear points is less than a given tolerance. 
In practice it can be implemented with a triangulation of the polygon (any triangulation): the orientation of the normal of each triangle must not deviate more than than a certain user-defined tolerance. 

A surface is first checked for :ref:`e203`, if it’s valid then :ref:`e204` is checked. 
However, it is only checked if there are no :ref:`e104` in the polygon, since otherwise it's not possible to triangulate the polygon.
In the figure below, the Solid on the left could be tested for 204, while the right one couldn't (but an :ref:`e104` would be returned).

By definition, if :ref:`e204` is reported then all the vertices are within 1cm (or the tolerance you gave as input), thus you wouldn’t be able to visualise them.
Also, 204 usually means that the vertices in the polygon are *very* close to each other (say 0.1mm), and thus it’s easy to get a large deviation (say 80 degree; the report contains the actual deviation).

.. image:: _static/104b.png


.. _e205:

205 -- POLYGON_INTERIOR_DISCONNECTED
------------------------------------
The interior of a polygon must be connected. The combination of different valid rings can create such an error, for example:

.. image:: _static/205.png
   :width: 25%

.. _e206:

206 -- INNER_RING_OUTSIDE
-------------------------
One or more interior rings are located *completely* outside the exterior ring. If the interior ring intersects the exterior ring (even at only one point), then error :ref:`e201` should be returned.

.. image:: _static/206.png
   :width: 25%

.. _e207:

207 -- INNER_RINGS_NESTED
-------------------------
One or more interior ring(s) is(are) located completely inside another interior ring.

.. image:: _static/207.png
   :width: 25%

.. _e208:

208 -- ORIENTATION_RINGS_SAME 
-----------------------------
The interior rings must have the opposite direction (clockwise vs counterclockwise) when viewed from a given point-of-view. 
When the polygon is used as a bounding surface of a shell, then the rings have to have a specified orientation (see 307/308).

.. image:: _static/208.png
   :width: 25%


.. _e300:

300 -- NOT_VALID_2_MANIFOLD
---------------------------
The shell is not valid, but the exact error (errors 3xx) is not known. This error happens when the construction of the shell failed for unknown reason. Hopefully you don't get that error.


.. _e301:

301 -- TOO_FEW_POLYGONS
-----------------------
A shell should have at least 4 polygons---the simplest volumetric shape in 3D is a tetrahedron.

.. _e302:

302 -- SHELL_NOT_CLOSED
-----------------------
The shell must not have 'holes', ie it must be 'watertight'. This refers only to the topology of the shell, not to its geometry (see :ref:`e306`).

The left solid is invalid, while the right one is valid (since the hole is filled with other polygons):

.. image:: _static/302.png

.. _e303:

303 -- NON_MANIFOLD_CASE
------------------------
Each shell must be simple, ie it must be a 2-manifold. Two cases are possible:

  1. An edge of a shell is non-manifold when there are more than 2 incident polygons to it.
  2. A vertex is non-manifold when its incident polygons do not form one 'umbrella'

Notice that this error might be returned for shells having their surfaces that are not consistently oriented (while they are 2-manifold).
Imagine you have a cube with 6 surfaces, if some surfaces have their normal pointing outwards, and some inwards, then this error might be returned (or :ref:`e307`, depending on the configuration).

.. image:: _static/303.png

.. image:: _static/304.png


.. _e305:

305 -- MULTIPLE_CONNECTED_COMPONENTS
------------------------------------
Polygons that are not connected to the shell should be reported as an error. 

.. image:: _static/305.png

.. _e306:

306 -- SHELL_SELF_INTERSECTION
------------------------------
If topology of the shell is correct and the shell is closed (thus no error 301/302/303/304/305), it is possible that the geometry introduces errors, eg intersections. 
For instance, the topology of both these shells is identical, but the geometry differs. 
The left shell is valid while the right one is invalid.

.. image:: _static/306.png

.. _e307:

307 -- POLYGON_WRONG_ORIENTATION
--------------------------------
If one polygon is used to construct a shell, its exterior ring must be oriented in such as way that when viewed from outside the shell the points are ordered counterclockwise.


.. _e401:

401 -- INTERSECTION_SHELLS
--------------------------
The interior of two or more shells intersect, these can be either the exterior shells with an interior shells or two or more interior shells. 
Two shells sharing (part of) a face is also not allowed.

Conceptually the same as :ref:`e201`.

.. _e402:

402 -- DUPLICATED_SHELLS
------------------------
Two or more shells are identical in *one* Solid. Note that for example a MultiSolid is a collection of Solids, but the topological relationships between them are not prescribed at all, they can be duplicated.

Conceptually the same as :ref:`e202`.

.. _e403:

403 -- INNER_SHELL_OUTSIDE
--------------------------
One or more interior shells are located *completely* outside the exterior shell. If the interior shell intersects the exterior shell (even at only one point), then error :ref:`e401` should be returned.

Conceptually the same as :ref:`e206`.

.. _e404:

404 -- SOLID_INTERIOR_DISCONNECTED
----------------------------------
Conceptually the same as :ref:`e205` the configuration of the interior shells makes the interior of the solid disconnected. 

.. _e405:

405 -- WRONG_ORIENTATION_SHELL
------------------------------
The polygon/surfaces forming an outer shell should have their normals pointing outwards, and for an interior shell inwards. 

'Outwards' is as follows: if a right-hand system is used, ie when the ordering of the points on the surface follows the direction of rotation of the curled fingers of the right hand, then the thumb points towards the outside. 
The torus below shows the correct orientation for some rings of some faces.

Conceptually the same as :ref:`e208`.

.. image:: _static/orientation.png
   :width: 50%


.. _e501:

501 -- INTERSECTION_SOLIDS
--------------------------
The interior of 2 ``Solids`` part of a ``CompositeSolid`` intersects.

.. image:: _static/501.png
   :width: 50%

.. _e502:

502 -- DUPLICATED_SOLIDS
------------------------
Two ``Solids`` in a ``CompositeSolid`` are identical.

.. _e503:

503 -- DISCONNECTED_SOLIDS
--------------------------
Two ``Solids`` in a ``CompositeSolid`` are disconnected.

.. image:: _static/503.png
   :width: 50%


.. _e601:

601 -- BUILDINGPARTS_OVERLAP
----------------------------
Some primitives in a Building and/or BuildingPart have their interior overlapping.



.. _e701: 

701 -- CELLS_OVERLAP
--------------------
Two IndoorGML cells overlap with each other. Similar to :ref:`e601` but for IndoorGML.
The overlap allowed can be controlled with the validation option :ref:`option_overlap_tol`.


.. _e702: 

702 -- DUAL_VERTEX_OUTSIDE_CELL
-------------------------------
The dual vertex of an IndoorGML cell is located outside the cell.


.. _e703: 

703 -- PRIMAL_DUAL_XLINKS_ERROR
-------------------------------
The XLinks in an IndoorGML file are wrong, the primal and the dual are not correctly linked. The schema validation (.xsd) of IndoorGML does not validate this.

.. _e704: 

704 -- PRIMAL_DUAL_ADJACENCIES_INCONSISTENT
-------------------------------------------
The adjacency of IndoorGML cells in the primal and the dual are no consistent. Basically, if two 3-cells are adjacent in the primal, are they also in the dual (do they have a dual edge)? The :ref:`option_overlap_tol` influences this.


.. _e901:

901 -- INVALID_INPUT_FILE
-------------------------
Input file is not valid or corrupted. If a CityGML file, you can `check it against the schema <http://geovalidation.bk.tudelft.nl/schemacitygml/>`_.

.. _e902:

902 -- EMPTY_PRIMITIVE
----------------------
The input file contains empty primitives, eg an OBJ where to surfaces are defined, or a ``CompositeSolid`` in a CityJSON file containing one empty Solid.

.. _e903:

903 -- WRONG_INPUT_PARAMETERS
-----------------------------
The parameters used for the validation are not valid.


.. _e904:

904 -- FORMAT_NOT_SUPPORTED
---------------------------
It can be that certain versions of a supported format are not supported, eg v3.0 of CityGML is not.


.. _e906:

906 -- PRIMITIVE_NO_GEOMETRY
----------------------------
The primitive has no geometry that val3dity recognises.
It could be that the primitive has a geometry, but that it is a 2D geometry or a format that is not processed by val3dity.
In CityJSON, it is possible to have for instance a ``Building`` without geometry, so this error would be reported.
In JSON-FG, the 2D geometries in ``"geometry"`` are not processed, and neither as the 3D geometries of type ``"Prism"``.

.. _e999:

999 -- UNKNOWN_ERROR
--------------------
If none of the above is suitable, which means something  went (really) bad. If you see this error, `please report it <https://github.com/tudelft3d/val3dity/issues>`_.
