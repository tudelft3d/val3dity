
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
    

To validate all the 3D primitives in a CityJSON file and see a summary output:

.. code-block:: bash

  $ val3dity my3dcity.city.json 


To validate each 3D primitive in ``input.city.json``, and use a tolerance for testing the planarity of the surface of 20cm (0.2):

.. code-block:: bash

  $ val3dity --planarity_d2p_tol 0.2 input.city.json


To validate an OBJ file and verify whether the 3D primitives from a Solid (this is the default):

.. code-block:: bash

  $ val3dity input.obj 

The same file could be validated as a MultiSurface, ie each of its surface are validated independently

.. code-block:: bash

  $ val3dity -p MultiSurface input.obj


Using CityJSONSeq
-----------------

To validate a `CityJSONSeq stream <https://www.cityjson.org/cityjsonseq/>`_, you need to pipe the stream into val3dity and use ``--stdin`` for the input. 

If you have a CityJSONSeq serialised in a file, then you can cat it:

.. code-block:: bash

  $ cat myfile.city.jsonl | val3dity stdin

The output shows, line by line, what are the errors. If the list of error is empty (``[]``) this means the feature is geometrically valid.

  

Accepted input
--------------

val3dity accepts as input:

  - `CityJSON <http://www.cityjson.org>`_
  - `CityJSON Sequences (CityJSONSeq) <https://www.cityjson.org/cityjsonseq/>`_
  - `tu3djson <https://github.com/tudelft3d/tu3djson>`_
  - `JSON-FG (OGC Features and Geometries JSON) <https://github.com/opengeospatial/ogc-feat-geo-json>`_
  - `OBJ <https://en.wikipedia.org/wiki/Wavefront_.obj_file>`_ 
  - `OFF <https://en.wikipedia.org/wiki/OFF_(file_format)>`_
  - `IndoorGML <http://indoorgml.net/>`_

For **CityJSON** files, all the City Objects (eg ``Building`` or ``Bridge``) are processed and their 3D primitives are validated.
The 3D primitives are bundled under their City Objects in the report.
If your CityJSON contains ``Buildings`` with one or more ``BuildingParts``, val3dity will perform an extra validation: it will ensure that the 3D primitives do not overlap (technically that the interior of each ``BuildingPart`` does not intersect with the interior of any other part of the ``Building``).
If there is one or more intersections, then :ref:`e601` will be reported.

For **CityJSONSeq** streams, the validation is performed line-by-line and the errors are returned for each line. 
If you want to generate a global report, you can serialise the stream into a .jsonl file and then validate this file as you would with any other input files.

For **IndoorGML** files, all the cells (in the primal subdivisions, the rooms) are validated individually, and then some extra validation tests are run on the dual navigation network. All errors 7xx are related specifically to IndoorGML.

For **JSON-FG** files, only ``Polyhedron`` and ``MultiPolyhedron`` are processed, the other possible types are ignored (``Prism``, ``MultiPrism``, and all the 2D types inherited from `GeoJSON <https://geojson.org/>`_). 
It should be noticed that the JSON-FG nomenclature is different: a ``Polyhedron`` is a ``Solid``, and a ``MultiPolyhedron`` is a ``MultiSolid`` (an arbitrary aggregation of several solids and there is no assumption regarding their topological relationships).

For **OBJ** and **OFF** files, each primitive will be validated according to the ISO19107 rules. One must specify how the primitives should be validated (``MultiSurface``, ``CompositeSurface``, or ``Solid``).
In an OBJ file, if there is more than one object (lines starting with "o", eg `o myobject`), each will be validated individually.
Observe that OBJ files have no mechanism to define inner shells, and thus a solid will be formed by only its exterior shell.
Validating one primitive in an OBJ as a MultiSurface (``-p MultiSurface`` option) will individually validate each surface according to the ISO19107 rules, without ensuring that they form a 2-manifold.
If your OBJ contains triangles only (often the case), then using the option `-p MultiSurface` is rather meaningless since most likely all your triangles are valid. Validation could however catch cases where triangles are collapsed to a line/point.
Validating it as a solid verifies whether the primitive is a 2-manifold, ie whether it is closed/watertight and whether all normals are pointing outwards.


How are 3D primitives validated?
--------------------------------

All primitives are validated hierarchically, for instance:

  1. the lower-dimensionality primitives (the polygons) are validated by projecting them to a 2D plane (obtained with least-square adjustment) and using `GEOS <http://trac.osgeo.org/geos/>`_;
  2. then these are assembled into shells/surfaces and their validity is analysed, as they must be watertight, no self-intersections, orientation of the normals must be consistent and pointing outwards, etc;
  3. then the ``Solids`` are validated
  4. finally, for ``CompositeSolids`` the interactions between the ``Solids`` are analysed.

This means that if one polygon of a Solid is not valid, the validator will report that error but will *not* continue the validation (to avoid "cascading" errors). 

The formal definitions of the 3D primitives, along with explanations, are given in :doc:`definitions`.

.. image:: _static/workflow.svg
   :width: 60%



Options for the validation
--------------------------

``-h, --help``
*****************
|  Display usage information and exit.

----

``--ignore204``
***************
|  Ignore the error :ref:`e204`.

----

.. _option_overlap_tol:

``--overlap_tol``
*****************
|  Tolerance for testing the overlap between primitives in ``CompositeSolids`` and ``BuildingParts``
|  default = -1 (disabled)

The maximum allowed distance for overlaps. Helps to validate the topological relationship between ``Solids`` forming a ``CompositeSolid``, the ``BuildingParts`` of a building in CityJSON, or the cells in IndoorGML.
The tolerance ``--overlap_tol 0.05`` means that each of the solids is given a 0.05unit *fuzzy* boundary (thus 5cm if meters are the unit of the input), and thus this is considered when validating. ``0.0unit`` means that the original boundaries are used.
Using an overlap tolerance significantly reduces the speed of the validator, because rather complex geometric operations are performed.

.. image:: _static/vcsol_2.png
   :width: 100%

----

``--planarity_d2p_tol``
***********************
|  Tolerance for planarity based on a distance to a plane 
|  default = 0.01

The distance between every point forming a surface and a plane must be less than ``--planarity_d2p_tol`` (eg 1cm, which is the default).
This plane is fitted with least-square adjustment, and the distance between each of the point to the plane is calculated.
If this distance is larger than the defined value, then :ref:`e203` is reported. Read more at :ref:`e203`.

.. note::  
  Planarity is defined with two tolerances: ``--planarity_d2p_tol`` and ``--planarity_n_tol``.

----

``--planarity_n_tol``
*********************
|  Tolerance for planarity based on normals deviation 
|  default = 20 (degree)

Helps to detect small folds in a surface. ``--planarity_n_tol`` refers to the normal of each triangle after the surface has been triangulated. If the triangle normals deviate from each other more than the given tolerance, then error :ref:`e204` is reported. Read more at :ref:`e204`.

.. note::  
  Planarity is defined with two tolerances: ``--planarity_d2p_tol`` and ``--planarity_n_tol``.

----


``-p, --primitive``
*******************
|  Which geometric primitive to validate. Only relevant for OBJ/OFF, because for CityJSON all primitives are validated. Read more geometric primitives at :ref:`def`.
|  One of ``Solid``, ``CompositeSurface``, ``MultiSurface``.

----

.. _report:

``-r, --report``
****************
|  Outputs the validation report to the file given. The report is in JSON file format, and can be used to produce nice reports automatically or to extract statistics. Use `val3dity report browser <http://geovalidation.bk.tudelft.nl/val3dity/browser/>`_ with your report.

----

.. _listerrors:

``--listerrors``
****************
|  Outputs a list of the val3dity errors.

----

.. _snap_tol:

``--snap_tol``
**************
|  Tolerance for snapping vertices that are close to each others
|  default = 0.001

Geometries modelled in GML store amazingly very little topological relationships. 
A cube is for instance represented with 6 surfaces, all stored independently. 
This means that the coordinates xyz of a single vertex (where 3 surfaces "meet") is stored 3 times. 
It is possible that these 3 vertices are not exactly at the same location (eg (0.01, 0.5, 1.0), (0.011, 0.49999, 1.00004) and (0.01002, 0.5002, 1.0007)), and that would create problems when validating since there would be holes in the cube for example. 
The snap tolerance basically gives a threshold that says: "if 2 points are closer then *X*, then we assume that they are the same". 
It's setup by default to be 1mm. 

----

``--verbose``
*************
|  The validation outputs to the console the status of each step of the validation. If this option is not set, then this goes to a file `val3dity.log` in the same folder as the executable.

----

``--version``
*****************
|  Display version information and exit.

