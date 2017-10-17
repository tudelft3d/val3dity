
==============
Using val3dity
==============

.. note::

  val3dity is a command-line program only, there is no graphical interface. Alternatively, you can use the `web application <http://geovalidation.bk.tudelft.nl/val3dity>`_.

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


To validate each 3D primitive in input.gml, and to merge/snap the vertices closer than 0.1unit:

.. code-block:: bash

  $ val3dity input.gml --snap_tol 0.1


To validate an OBJ file and verify whether the 3D primitives from a ``Solid`` (this is the default):

.. code-block:: bash

  $ val3dity input.obj 

The same file could be validated as a ``MultiSurface``, ie each of its surface are validated independently

.. code-block:: bash

  $ val3dity input.obj -p MultiSurface
    

Accepted input
--------------

val3dity accepts as input:

  - `CityGML <https://www.citygml.org>`_ 
  - `CityJSON <http://www.cityjson.org>`_
  - any `GML file <https://en.wikipedia.org/wiki/Geography_Markup_Language>`_
  - `OBJ <https://en.wikipedia.org/wiki/Wavefront_.obj_file>`_ 
  - `OFF <https://en.wikipedia.org/wiki/OFF_(file_format)>`_

For **CityGML/CityJSON** files, all the City Objects (eg ``Building`` or ``Bridge``) are processed and their 3D primitives are validated.
The 3D primitives are bundled under their City Objects in the report.

If your CityGML/CityJSON contains ``Buildings`` with one or more ``BuildingParts``, val3dity will perform an extra validation: it will ensure that the 3D primitives do not overlap (technically that the interior of each ``BuildingPart`` does not intersect with the interior of any other part of the ``Building``).
If there is one or more intersections, then :ref:`error_601` will be reported.

For **GML** files, the file is simply scanned for the 3D primitives and validates these according to the rules in ISO19107, all the rest is ignored. 

For **OBJ** and **OFF** files, each primitive will be validated according to the ISO19107 rules. One must specify how the primitives should be validated (``MultiSurface``, ``CompositeSurface``, or ``Solid``).
In an OBJ file, if there is more than one object (lines starting with "o", eg `o myobject`), each will be validated individually.
Observe that OBJ files have no mechanism to define inner shells, and thus a solid will be formed by only its exterior shell.
Validating one primitive in an OBJ as a MultiSurface (``-p MultiSurface`` option) will individually validate each surface according to the ISO19107 rules, without ensuring that they form a 2-manifold.
If your OBJ contains triangles only (often the case), then using the option `-p MultiSurface` is rather meaningless since most likely all your triangles are valid. Validation could however catch cases where triangles are collapsed to a line/point.
Validating it as a solid verifies whether the primitive is a 2-manifold, ie whether it is closed/watertight and whether all normals are pointing outwards.

Options for the validation
--------------------------

.. _snap_tol:

``--snap_tol``
**************
|  Tolerance for snapping vertices that are close to each others
|  default = 0.001
|  to disable snapping = -1 

Geometries modelled in GML store amazingly very little topological relationships. 
A cube is for instance represented with 6 surfaces, all stored independently. 
This means that the coordinates xyz of a single vertex (where 3 surfaces "meet") is stored 3 times. 
It is possible that these 3 vertices are not exactly at the same location (eg (0.01, 0.5, 1.0), (0.011, 0.49999, 1.00004) and (0.01002, 0.5002, 1.0007)), and that would create problems when validating since there would be holes in the cube for example. 
The snap tolerance basically gives a threshold that says: "if 2 points are closer then *X*, then we assume that they are the same". 
It's setup by default to be 1mm. 

----

``--planarity_d2p_tol``
***********************
|  Tolerance for planarity based on a distance to a plane 
|  default = 0.01

The distance between every point forming a surface and a plane must be less than ``--planarity_d2p_tol`` (eg 1cm, which is the default).
This plane is fitted with least-square adjustment, and the distance between each of the point to the plane is calculated.
If this distance is larger than the defined value, then :ref:`error_203` is reported. Read more at :ref:`error_203`.

.. note::  
  Planarity is defined with two tolerances: ``--planarity_d2p_tol`` and ``--planarity_n_tol``.

----

``--planarity_n_tol``
*********************
|  Tolerance for planarity based on normals deviation 
|  default = 1 (degree)

Helps to detect small folds in a surface. ``--planarity_n_tol`` refers to the normal of each triangle after the surface has been triangulated. If the triangle normals deviate from each other more than the given tolerance, then error :ref:`error_204` is reported. Read more at :ref:`error_204`.

.. note::  
  Planarity is defined with two tolerances: ``--planarity_d2p_tol`` and ``--planarity_n_tol``.

----

.. _option_overlap_tol:

``--overlap_tol``
*****************
|  Tolerance for testing the overlap between primitives in ``CompositeSolids`` and ``BuildingParts``
|  default = 0.0

The maximum allowed distance for overlaps. Helps to validate the topological relationship between ``Solids`` forming a ``CompositeSolid`` or the ``BuildingParts`` of a building.
The tolerance ``--overlap_tol 0.05`` means that each of the solids is given a 0.05unit *fuzzy* boundary (thus 5cm if meters are the unit of the input), and thus this is considered when validating. ``0.0unit`` means that the original boundaries are used.
Using an overlap tolerance significantly reduces the speed of the validator, because rather complex geometric operations are performed.

.. image:: _static/vcsol_2.png
   :width: 100%

----

``--verbose``
*************
|  The validation outputs to the console the status of each step of the validation. If this option is not set, then this goes to a file `val3dity.log` in the same folder as the executable.

----

``-r, --report``
****************
|  Outputs the validation report to the file given. The report is in JSON file_format.


----

``--onlyinvalid``
****************
|  Only the invalid primitives are reported in the validation report.


----

``--notranslate``
*****************
|  By default, all coordinates are translated by the (minx, miny) of the input file. This is to avoid precision error with floating-point numbers. This option skips the translation; we advise not to use this though.

----

``--ignore204``
*****************
|  Ignore the error `204 – NON_PLANAR_POLYGON_NORMALS_DEVIATION <http://val3dity.readthedocs.io/en/v2/errors/#non-planar-polygon-normals-deviation>`_.

----

``-p, --primitive``
*****************
|  Which geometric primitive to validate. Only relevant for OBJ/OFF, because for CityGML/CityJSON all primitives are validated. Read more geometric primitives at :ref:`def`.
|  One of ``Solid``, ``CompositeSurface``, ``MultiSurface``.

----

``--version``
*****************
|  Display version information and exit.

----

``-h, --help``
*****************
|  Display usage information and exit.


How are 3D primitives validated?
--------------------------------

All primitives are validated hierarchically, for instance:

  1. the lower-dimensionality primitives (the polygons) are validated by projecting them to a 2D plane (obtained with least-square adjustment) and using `GEOS <http://trac.osgeo.org/geos/>`_;
  2. then these are assembled into shells/surfaces and their validity is analysed, as they must be watertight, no self-intersections, orientation of the normals must be consistent and pointing outwards, etc;
  3. then the ``Solids`` are validated
  4. finally, for ``CompositeSolids`` the interactions between the ``Solids`` are analysed.

This means that if one polygon of a Solid is not valid, the validator will report that error but will *not* continue the validation (to avoid "cascading" errors). 

The formal definitions of the 3D primitives, along with explanations, are given in 