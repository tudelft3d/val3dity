

var app = new Vue({
    el: '#app',
    data: {
      file_loaded: false,
      report: {},
    },
    methods: {
      reset() {
        this.report = {};
        this.file_loaded = false;
      },
      selectedFile() {
        console.log("Selected a val3dity report JSON file...");
        console.log(this.$refs.reportFile.files[0]);

        let file = this.$refs.reportFile.files[0];
        if (!file || file.type != "application/json")
        {
          console.log("This is not a val3dity report JSON file. Abort.");
          return;
        }

        let reader = new FileReader();
        reader.readAsText(file, "UTF-8");
        reader.onload = evt => {
          jre = JSON.parse(evt.target.result);
          this.report = jre;
          this.file_loaded = true;
        }
      }
    }
})

Vue.config.devtools = true

var errors = {
    "101": {
        "name": "TOO_FEW_POINTS",
        "link": "http://geovalidation.bk.tudelft.nl/val3dity/docs/errors/#too-few-points"
    },
    "102": {
        "name": "CONSECUTIVE_POINTS_SAME",
        "link": "http://geovalidation.bk.tudelft.nl/val3dity/docs/errors/#consecutive-points-same"
    },
    "103": {
        "name": "NOT_CLOSED",
        "link": "http://geovalidation.bk.tudelft.nl/val3dity/docs/errors/#not-closed"
    },
    "104": {
        "name": "SELF_INTERSECTION",
        "link": "http://geovalidation.bk.tudelft.nl/val3dity/docs/errors/#self-intersection"
    },
    "201": {
        "name": "INTERSECTION_RINGS",
        "link": "http://geovalidation.bk.tudelft.nl/val3dity/docs/errors/#intersection-rings"
    },
    "202": {
        "name": "DUPLICATED_RINGS",
        "link": "http://geovalidation.bk.tudelft.nl/val3dity/docs/errors/#duplicated-rings"
    },
    "203": {
        "name": "NON_PLANAR_POLYGON_DISTANCE_PLANE",
        "link": "http://geovalidation.bk.tudelft.nl/val3dity/docs/errors/#non-planar-polygon-distance-plane"
    },
    "204": {
        "name": "NON_PLANAR_POLYGON_NORMALS_DEVIATION",
        "link": "http://geovalidation.bk.tudelft.nl/val3dity/docs/errors/#non-planar-polygon-normals-deviation"
    },
    "205": {
        "name": "INTERIOR_DISCONNECTED",
        "link": "http://geovalidation.bk.tudelft.nl/val3dity/docs/errors/#interior-disconnected"
    },
    "206": {
        "name": "INNER_RING_OUTSIDE",
        "link": "http://geovalidation.bk.tudelft.nl/val3dity/docs/errors/#inner-ring-outside"
    },
    "207": {
        "name": "INNER_RINGS_NESTED",
        "link": "http://geovalidation.bk.tudelft.nl/val3dity/docs/errors/#inner-rings-nested"
    },
    "208": {
        "name": "ORIENTATION_RINGS_SAME",
        "link": "http://geovalidation.bk.tudelft.nl/val3dity/docs/errors/#orientation-rings-same"
    },
    "301": {
        "name": "TOO_FEW_POLYGONS",
        "link": "http://geovalidation.bk.tudelft.nl/val3dity/docs/errors/#too-few-polygons"
    },
    "302": {
        "name": "NOT_CLOSED",
        "link": "http://geovalidation.bk.tudelft.nl/val3dity/docs/errors/#error-302"
    },
    "303": {
        "name": "NON_MANIFOLD_CASE",
        "link": "http://geovalidation.bk.tudelft.nl/val3dity/docs/errors/#non-manifold-case"
    },
    "305": {
        "name": "MULTIPLE_CONNECTED_COMPONENTS",
        "link": "http://geovalidation.bk.tudelft.nl/val3dity/docs/errors/#multiple-connected-components"
    },
    "306": {
        "name": "SELF_INTERSECTION",
        "link": "http://geovalidation.bk.tudelft.nl/val3dity/docs/errors/#error-306"
    },
    "307": {
        "name": "POLYGON_WRONG_ORIENTATION",
        "link": "http://geovalidation.bk.tudelft.nl/val3dity/docs/errors/#polygon-wrong-orientation"
    },
    "401": {
        "name": "INTERSECTION_SHELLS",
        "link": "http://geovalidation.bk.tudelft.nl/val3dity/docs/errors/#intersection-shells"
    },
    "402": {
        "name": "DUPLICATED_SHELLS",
        "link": "http://geovalidation.bk.tudelft.nl/val3dity/docs/errors/#duplicated-shells"
    },
    "403": {
        "name": "INNER_SHELL_OUTSIDE",
        "link": "http://geovalidation.bk.tudelft.nl/val3dity/docs/errors/#inner-shell-outside"
    },
    "404": {
        "name": "INTERIOR_DISCONNECTED",
        "link": "http://geovalidation.bk.tudelft.nl/val3dity/docs/errors/#error-404"
    },
    "405": {
        "name": "WRONG_ORIENTATION_SHELL",
        "link": "http://geovalidation.bk.tudelft.nl/val3dity/docs/errors/#wrong-orientation-shell"
    },
    "501": {
        "name": "INTERSECTION_SOLIDS",
        "link": "http://geovalidation.bk.tudelft.nl/val3dity/docs/errors/#intersection-solids"
    },
    "502": {
        "name": "DUPLICATED_SOLIDS",
        "link": "http://geovalidation.bk.tudelft.nl/val3dity/docs/errors/#duplicated-solids"
    },
    "503": {
        "name": "DISCONNECTED_SOLIDS",
        "link": "http://geovalidation.bk.tudelft.nl/val3dity/docs/errors/#disconnected-solids"
    },
    "601": {
        "name": "BUILDINGPARTS_OVERLAP",
        "link": "http://geovalidation.bk.tudelft.nl/val3dity/docs/errors/#buildingparts-overlap"
    },
    "609": {
        "name": "CITYOBJECT_HAS_NO_GEOMETRY",
        "link": "http://geovalidation.bk.tudelft.nl/val3dity/docs/errors/#cityobject-has-no-geometry"
    },
    "901": {
        "name": "INVALID_INPUT_FILE",
        "link": "http://geovalidation.bk.tudelft.nl/val3dity/docs/errors/#invalid-input-file"
    },
    "902": {
        "name": "EMPTY_PRIMITIVE",
        "link": "http://geovalidation.bk.tudelft.nl/val3dity/docs/errors/#empty-primitive"
    },
    "903": {
        "name": "WRONG_INPUT_PARAMETERS",
        "link": "http://geovalidation.bk.tudelft.nl/val3dity/docs/errors/#wrong-input-parameters"
    },
    "999": {
        "name": "UNKNOWN_ERROR",
        "link": "http://geovalidation.bk.tudelft.nl/val3dity/docs/errors/#unknown-error"
    }
}
