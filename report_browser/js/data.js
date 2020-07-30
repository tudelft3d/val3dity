var errors = {

    "101": {
      "name": "TOO_FEW_POINTS",
      "link": "https://val3dity.readthedocs.io/en/latest/errors/#too-few-points"
    },
    "102": {
      "name": "CONSECUTIVE_POINTS_SAME",
      "link": "https://val3dity.readthedocs.io/en/latest/errors/#consecutive-points-same"
    },
    "103": {
      "name": "RING_NOT_CLOSED",
      "link": "https://val3dity.readthedocs.io/en/latest/errors/#ring-not-closed"
    },
    "104": {
      "name": "RING_SELF_INTERSECTION",
      "link": "https://val3dity.readthedocs.io/en/latest/errors/#ring-self-intersection"
    },
    "201": {
      "name": "INTERSECTION_RINGS",
      "link": "https://val3dity.readthedocs.io/en/latest/errors/#intersection-rings"
    },
    "202": {
      "name": "DUPLICATED_RINGS",
      "link": "https://val3dity.readthedocs.io/en/latest/errors/#duplicated-rings"
    },
    "203": {
      "name": "NON_PLANAR_POLYGON_DISTANCE_PLANE",
      "link": "https://val3dity.readthedocs.io/en/latest/errors/#non-planar-polygon-distance-plane"
    },
    "204": {
      "name": "NON_PLANAR_POLYGON_NORMALS_DEVIATION",
      "link": "https://val3dity.readthedocs.io/en/latest/errors/#non-planar-polygon-normals-deviation"
    },
    "205": {
      "name": "POLYGON_INTERIOR_DISCONNECTED",
      "link": "https://val3dity.readthedocs.io/en/latest/errors/#polygon-interior-disconnected"
    },
    "206": {
      "name": "INNER_RING_OUTSIDE",
      "link": "https://val3dity.readthedocs.io/en/latest/errors/#inner-ring-outside"
    },
    "207": {
      "name": "INNER_RINGS_NESTED",
      "link": "https://val3dity.readthedocs.io/en/latest/errors/#inner-rings-nested"
    },
    "208": {
      "name": "ORIENTATION_RINGS_SAME",
      "link": "https://val3dity.readthedocs.io/en/latest/errors/#orientation-rings-same"
    },
    "300": {
      "name": "NOT_VALID_2_MANIFOLD",
      "link": "https://val3dity.readthedocs.io/en/latest/errors/#not-valid-2-manifold"
    },
    "301": {
      "name": "TOO_FEW_POLYGONS",
      "link": "https://val3dity.readthedocs.io/en/latest/errors/#too-few-polygons"
    },
    "302": {
      "name": "SHELL_NOT_CLOSED",
      "link": "https://val3dity.readthedocs.io/en/latest/errors/#shell-not-closed"
    },
    "303": {
      "name": "NON_MANIFOLD_CASE",
      "link": "https://val3dity.readthedocs.io/en/latest/errors/#non-manifold-case"
    },
    "305": {
      "name": "MULTIPLE_CONNECTED_COMPONENTS",
      "link": "https://val3dity.readthedocs.io/en/latest/errors/#multiple-connected-components"
    },
    "306": {
      "name": "SHELL_SELF_INTERSECTION",
      "link": "https://val3dity.readthedocs.io/en/latest/errors/#shell-self-intersection"
    },
    "307": {
      "name": "POLYGON_WRONG_ORIENTATION",
      "link": "https://val3dity.readthedocs.io/en/latest/errors/#polygon-wrong-orientation"
    },
    "309": {
      "name": "VERTICES_NOT_USED",
      "link": "https://val3dity.readthedocs.io/en/latest/errors/#vertices-not-used"
    },
    "401": {
      "name": "INTERSECTION_SHELLS",
      "link": "https://val3dity.readthedocs.io/en/latest/errors/#intersection-shells"
    },
    "402": {
      "name": "DUPLICATED_SHELLS",
      "link": "https://val3dity.readthedocs.io/en/latest/errors/#duplicated-shells"
    },
    "403": {
      "name": "INNER_SHELL_OUTSIDE",
      "link": "https://val3dity.readthedocs.io/en/latest/errors/#inner-shell-outside"
    },
    "404": {
      "name": "SOLID_INTERIOR_DISCONNECTED",
      "link": "https://val3dity.readthedocs.io/en/latest/errors/#solid-interior-disconnected"
    },
    "405": {
      "name": "WRONG_ORIENTATION_SHELL",
      "link": "https://val3dity.readthedocs.io/en/latest/errors/#wrong-orientation-shell"
    },
    "501": {
      "name": "INTERSECTION_SOLIDS",
      "link": "https://val3dity.readthedocs.io/en/latest/errors/#intersection-solids"
    },
    "502": {
      "name": "DUPLICATED_SOLIDS",
      "link": "https://val3dity.readthedocs.io/en/latest/errors/#duplicated-solids"
    },
    "503": {
      "name": "DISCONNECTED_SOLIDS",
      "link": "https://val3dity.readthedocs.io/en/latest/errors/#disconnected-solids"
    },
    "601": {
      "name": "BUILDINGPARTS_OVERLAP",
      "link": "https://val3dity.readthedocs.io/en/latest/errors/#buildingparts-overlap"
    },
    "609": {
      "name": "CITYOBJECT_HAS_NO_GEOMETRY",
      "link": "https://val3dity.readthedocs.io/en/latest/errors/#cityobject-has-no-geometry"
    },
    "701": {
      "name": "CELLS_OVERLAP",
      "link": "https://val3dity.readthedocs.io/en/latest/errors/#cells-overlap"
    },
    "702": {
      "name": "DUAL_VERTEX_OUTSIDE_CELL",
      "link": "https://val3dity.readthedocs.io/en/latest/errors/#dual-vertex-outside-cell"
    },
    "703": {
      "name": "PRIMAL_DUAL_XLINKS_ERROR",
      "link": "https://val3dity.readthedocs.io/en/latest/errors/#primal-dual-xlinks-error"
    },
    "704": {
      "name": "PRIMAL_DUAL_ADJACENCIES_INCONSISTENT",
      "link": "https://val3dity.readthedocs.io/en/latest/errors/#primal-dual-adjacencies-inconsistent"
    },
    "901": {
      "name": "INVALID_INPUT_FILE",
      "link": "https://val3dity.readthedocs.io/en/latest/errors/#invalid-input-file"
    },
    "902": {
      "name": "EMPTY_PRIMITIVE",
      "link": "https://val3dity.readthedocs.io/en/latest/errors/#empty-primitive"
    },
    "903": {
      "name": "WRONG_INPUT_PARAMETERS",
      "link": "https://val3dity.readthedocs.io/en/latest/errors/#wrong-input-parameters"
    },
    "904": {
      "name": "FORMAT_NOT_SUPPORTED",
      "link": "https://val3dity.readthedocs.io/en/latest/errors/#format-not-supported"
    },
    "999": {
      "name": "UNKNOWN_ERROR",
      "link": "https://val3dity.readthedocs.io/en/latest/errors/#unknown-error"
    }


}

