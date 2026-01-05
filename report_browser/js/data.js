// Configuration
const DOC_VERSION = "2.5.1";
const DOC_BASE_URL = `https://val3dity.readthedocs.io/${DOC_VERSION}`;

var errors = {
  101: {
    name: "TOO_FEW_POINTS",
    link: `${DOC_BASE_URL}/errors/#too-few-points`,
  },
  102: {
    name: "CONSECUTIVE_POINTS_SAME",
    link: `${DOC_BASE_URL}/errors/#consecutive-points-same`,
  },
  103: {
    name: "RING_NOT_CLOSED",
    link: `${DOC_BASE_URL}/errors/#ring-not-closed`,
  },
  104: {
    name: "RING_SELF_INTERSECTION",
    link: `${DOC_BASE_URL}/errors/#ring-self-intersection`,
  },
  201: {
    name: "INTERSECTION_RINGS",
    link: `${DOC_BASE_URL}/errors/#intersection-rings`,
  },
  202: {
    name: "DUPLICATED_RINGS",
    link: `${DOC_BASE_URL}/errors/#duplicated-rings`,
  },
  203: {
    name: "NON_PLANAR_POLYGON_DISTANCE_PLANE",
    link: `${DOC_BASE_URL}/errors/#non-planar-polygon-distance-plane`,
  },
  204: {
    name: "NON_PLANAR_POLYGON_NORMALS_DEVIATION",
    link: `${DOC_BASE_URL}/errors/#non-planar-polygon-normals-deviation`,
  },
  205: {
    name: "POLYGON_INTERIOR_DISCONNECTED",
    link: `${DOC_BASE_URL}/errors/#polygon-interior-disconnected`,
  },
  206: {
    name: "INNER_RING_OUTSIDE",
    link: `${DOC_BASE_URL}/errors/#inner-ring-outside`,
  },
  207: {
    name: "INNER_RINGS_NESTED",
    link: `${DOC_BASE_URL}/errors/#inner-rings-nested`,
  },
  208: {
    name: "ORIENTATION_RINGS_SAME",
    link: `${DOC_BASE_URL}/errors/#orientation-rings-same`,
  },
  300: {
    name: "NOT_VALID_2_MANIFOLD",
    link: `${DOC_BASE_URL}/errors/#not-valid-2-manifold`,
  },
  301: {
    name: "TOO_FEW_POLYGONS",
    link: `${DOC_BASE_URL}/errors/#too-few-polygons`,
  },
  302: {
    name: "SHELL_NOT_CLOSED",
    link: `${DOC_BASE_URL}/errors/#shell-not-closed`,
  },
  303: {
    name: "NON_MANIFOLD_CASE",
    link: `${DOC_BASE_URL}/errors/#non-manifold-case`,
  },
  305: {
    name: "MULTIPLE_CONNECTED_COMPONENTS",
    link: `${DOC_BASE_URL}/errors/#multiple-connected-components`,
  },
  306: {
    name: "SHELL_SELF_INTERSECTION",
    link: `${DOC_BASE_URL}/errors/#shell-self-intersection`,
  },
  307: {
    name: "POLYGON_WRONG_ORIENTATION",
    link: `${DOC_BASE_URL}/errors/#polygon-wrong-orientation`,
  },
  309: {
    name: "VERTICES_NOT_USED",
    link: `${DOC_BASE_URL}/errors/#vertices-not-used`,
  },
  401: {
    name: "INTERSECTION_SHELLS",
    link: `${DOC_BASE_URL}/errors/#intersection-shells`,
  },
  402: {
    name: "DUPLICATED_SHELLS",
    link: `${DOC_BASE_URL}/errors/#duplicated-shells`,
  },
  403: {
    name: "INNER_SHELL_OUTSIDE",
    link: `${DOC_BASE_URL}/errors/#inner-shell-outside`,
  },
  404: {
    name: "SOLID_INTERIOR_DISCONNECTED",
    link: `${DOC_BASE_URL}/errors/#solid-interior-disconnected`,
  },
  405: {
    name: "WRONG_ORIENTATION_SHELL",
    link: `${DOC_BASE_URL}/errors/#wrong-orientation-shell`,
  },
  501: {
    name: "INTERSECTION_SOLIDS",
    link: `${DOC_BASE_URL}/errors/#intersection-solids`,
  },
  502: {
    name: "DUPLICATED_SOLIDS",
    link: `${DOC_BASE_URL}/errors/#duplicated-solids`,
  },
  503: {
    name: "DISCONNECTED_SOLIDS",
    link: `${DOC_BASE_URL}/errors/#disconnected-solids`,
  },
  601: {
    name: "BUILDINGPARTS_OVERLAP",
    link: `${DOC_BASE_URL}/errors/#buildingparts-overlap`,
  },
  609: {
    name: "CITYOBJECT_HAS_NO_GEOMETRY",
    link: `${DOC_BASE_URL}/errors/#cityobject-has-no-geometry`,
  },
  701: {
    name: "CELLS_OVERLAP",
    link: `${DOC_BASE_URL}/errors/#cells-overlap`,
  },
  702: {
    name: "DUAL_VERTEX_OUTSIDE_CELL",
    link: `${DOC_BASE_URL}/errors/#dual-vertex-outside-cell`,
  },
  703: {
    name: "PRIMAL_DUAL_XLINKS_ERROR",
    link: `${DOC_BASE_URL}/errors/#primal-dual-xlinks-error`,
  },
  704: {
    name: "PRIMAL_DUAL_ADJACENCIES_INCONSISTENT",
    link: `${DOC_BASE_URL}/errors/#primal-dual-adjacencies-inconsistent`,
  },
  901: {
    name: "INVALID_INPUT_FILE",
    link: `${DOC_BASE_URL}/errors/#invalid-input-file`,
  },
  902: {
    name: "EMPTY_PRIMITIVE",
    link: `${DOC_BASE_URL}/errors/#empty-primitive`,
  },
  903: {
    name: "WRONG_INPUT_PARAMETERS",
    link: `${DOC_BASE_URL}/errors/#wrong-input-parameters`,
  },
  904: {
    name: "FORMAT_NOT_SUPPORTED",
    link: `${DOC_BASE_URL}/errors/#format-not-supported`,
  },
  905: {
    name: "INVALID_JSON",
    link: `${DOC_BASE_URL}/errors/#invalid-json`,
  },
  906: {
    name: "PRIMITIVE_NO_GEOMETRY",
    link: `${DOC_BASE_URL}/errors/#primitive-no-geometry`,
  },
  999: {
    name: "UNKNOWN_ERROR",
    link: `${DOC_BASE_URL}/errors/#unknown-error`,
  },
};
