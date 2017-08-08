======
Errors
======


Ring level
----------

  * 101: TOO_FEW_POINTS
  * 102: CONSECUTIVE_POINTS_SAME
  * 103: NOT_CLOSED
  * 104: SELF_INTERSECTION 
  * 105: COLLAPSED_TO_LINE


POLYGON level
-------------

  * 201: INTERSECTION_RINGS
  * 202: DUPLICATED_RINGS
  * 203: NON_PLANAR_POLYGON_DISTANCE_PLANE 
  * 204: NON_PLANAR_POLYGON_NORMALS_DEVIATION 
  * 205: INTERIOR_DISCONNECTED
  * 206: INNER_RING_OUTSIDE
  * 207: INNER_RINGS_NESTED
  * 208: ORIENTATION_RINGS_SAME


SHELL level
-----------

  * 301: TOO_FEW_POLYGONS
  * 302: NOT_CLOSED
  * 303: NON_MANIFOLD_VERTEX
  * 304: NON_MANIFOLD_EDGE 
  * 305: SEPARATE_PARTS
  * 306: SELF_INTERSECTION
  * 307: POLYGON_WRONG_ORIENTATION
  * 309: VERTICES_NOT_USED 


SOLID level
-----------

  * 401: INTERSECTION_SHELLS
  * 402: DUPLICATED_SHELLS
  * 403: INNER_SHELL_OUTSIDE
  * 404: INTERIOR_DISCONNECTED
  * 405: WRONG_ORIENTATION_SHELL


COMPOSITESOLID level
--------------------

  * 501: INTERSECTION_SOLIDS
  * 502: DUPLICATED_SOLIDS
  * 503: DISCONNECTED_SOLIDS

BUILDING 
--------
  
  * 601: BUILDINGPARTS_OVERLAP

OTHERS
------

  * 901: INVALID_INPUT_FILE
  * 902: EMPTY_PRIMITIVE
  * 999: UNKNOWN_ERROR