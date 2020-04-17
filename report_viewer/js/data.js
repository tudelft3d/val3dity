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
    "701": {
        "name": "CELLS_OVERLAP",
        "link": "http://geovalidation.bk.tudelft.nl/val3dity/docs/errors/"
    },
    "702": {
        "name": "DUAL_VERTEX_OUTSIDE_CELL",
        "link": "http://geovalidation.bk.tudelft.nl/val3dity/docs/errors/"
    },
    "703": {
        "name": "PRIMAL_DUAL_XLINKS_ERROR",
        "link": "http://geovalidation.bk.tudelft.nl/val3dity/docs/errors/"
    },
    "704": {
        "name": "PRIMAL_DUAL_ADJACENCIES_INCONSISTENT",
        "link": "http://geovalidation.bk.tudelft.nl/val3dity/docs/errors/"
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
    "904": {
        "name": "FORMAT_NOT_SUPPORTED",
        "link": "http://geovalidation.bk.tudelft.nl/val3dity/docs/errors/#wrong-input-parameters"
    },    
    "999": {
        "name": "UNKNOWN_ERROR",
        "link": "http://geovalidation.bk.tudelft.nl/val3dity/docs/errors/#unknown-error"
    }
}

var test_report = {
    "all_errors": [
        102,
        104,
        302
    ],
    "dataset_errors": null,
    "features": [
        {
            "errors_feature": null,
            "id": "b0a8da4cc-2d2a-11e6-9a38-393caa90be70",
            "primitives": [{
                "id": "b0a8da4cc-2d2a-11e6-9a38-393caa90be70(0)",
                "numberfaces": 51,
                "numbervertices": 40,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "Bridge",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "b1105d28c-00ba-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "errors": [{
                    "code": 302,
                    "description": "SHELL_NOT_CLOSED",
                    "id": "",
                    "info": "Location hole: (85022.4, 447477, -0.1)",
                    "type": "Error"
                }],
                "id": "b1105d28c-00ba-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 229,
                "numbershells": 1,
                "numbervertices": 154,
                "type": "Solid",
                "validity": false
            }],
            "type": "Building",
            "validity": false
        },
        {
            "errors_feature": null,
            "id": "b11267a1d-00ba-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "errors": [{
                    "code": 302,
                    "description": "SHELL_NOT_CLOSED",
                    "id": "",
                    "info": "Location hole: (84855.6, 447550, -0.02)",
                    "type": "Error"
                }],
                "id": "b11267a1d-00ba-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 36,
                "numbershells": 1,
                "numbervertices": 23,
                "type": "Solid",
                "validity": false
            }],
            "type": "Building",
            "validity": false
        },
        {
            "errors_feature": null,
            "id": "b1126a169-00ba-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "errors": [{
                    "code": 302,
                    "description": "SHELL_NOT_CLOSED",
                    "id": "",
                    "info": "Location hole: (84844.2, 447550, 0)",
                    "type": "Error"
                }],
                "id": "b1126a169-00ba-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 55,
                "numbershells": 1,
                "numbervertices": 36,
                "type": "Solid",
                "validity": false
            }],
            "type": "Building",
            "validity": false
        },
        {
            "errors_feature": null,
            "id": "b1126c87e-00ba-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "errors": [{
                    "code": 302,
                    "description": "SHELL_NOT_CLOSED",
                    "id": "",
                    "info": "Location hole: (84842.2, 447553, 0.03)",
                    "type": "Error"
                }],
                "id": "b1126c87e-00ba-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 39,
                "numbershells": 1,
                "numbervertices": 26,
                "type": "Solid",
                "validity": false
            }],
            "type": "Building",
            "validity": false
        },
        {
            "errors_feature": null,
            "id": "b1126c883-00ba-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "errors": [{
                    "code": 302,
                    "description": "SHELL_NOT_CLOSED",
                    "id": "",
                    "info": "Location hole: (84851.2, 447560, 0.06)",
                    "type": "Error"
                }],
                "id": "b1126c883-00ba-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 20,
                "numbershells": 1,
                "numbervertices": 14,
                "type": "Solid",
                "validity": false
            }],
            "type": "Building",
            "validity": false
        },
        {
            "errors_feature": null,
            "id": "b112715ef-00ba-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "errors": [{
                    "code": 302,
                    "description": "SHELL_NOT_CLOSED",
                    "id": "",
                    "info": "Location hole: (84860, 447544, -0.01)",
                    "type": "Error"
                }],
                "id": "b112715ef-00ba-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 36,
                "numbershells": 1,
                "numbervertices": 24,
                "type": "Solid",
                "validity": false
            }],
            "type": "Building",
            "validity": false
        },
        {
            "errors_feature": null,
            "id": "b112715f4-00ba-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "errors": [{
                    "code": 302,
                    "description": "SHELL_NOT_CLOSED",
                    "id": "",
                    "info": "Location hole: (84847.2, 447537, -0.01)",
                    "type": "Error"
                }],
                "id": "b112715f4-00ba-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 50,
                "numbershells": 1,
                "numbervertices": 31,
                "type": "Solid",
                "validity": false
            }],
            "type": "Building",
            "validity": false
        },
        {
            "errors_feature": null,
            "id": "b112715fe-00ba-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "errors": [{
                    "code": 302,
                    "description": "SHELL_NOT_CLOSED",
                    "id": "",
                    "info": "Location hole: (84880.7, 447558, 0.44)",
                    "type": "Error"
                }],
                "id": "b112715fe-00ba-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 50,
                "numbershells": 1,
                "numbervertices": 33,
                "type": "Solid",
                "validity": false
            }],
            "type": "Building",
            "validity": false
        },
        {
            "errors_feature": null,
            "id": "b11271601-00ba-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "errors": [{
                    "code": 302,
                    "description": "SHELL_NOT_CLOSED",
                    "id": "",
                    "info": "Location hole: (84892.6, 447552, 0.49)",
                    "type": "Error"
                }],
                "id": "b11271601-00ba-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 38,
                "numbershells": 1,
                "numbervertices": 25,
                "type": "Solid",
                "validity": false
            }],
            "type": "Building",
            "validity": false
        },
        {
            "errors_feature": null,
            "id": "b1127160e-00ba-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "errors": [{
                    "code": 302,
                    "description": "SHELL_NOT_CLOSED",
                    "id": "",
                    "info": "Location hole: (84856.1, 447562, 0.08)",
                    "type": "Error"
                }],
                "id": "b1127160e-00ba-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 37,
                "numbershells": 1,
                "numbervertices": 24,
                "type": "Solid",
                "validity": false
            }],
            "type": "Building",
            "validity": false
        },
        {
            "errors_feature": null,
            "id": "b1127b2f3-00ba-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "errors": [{
                    "code": 302,
                    "description": "SHELL_NOT_CLOSED",
                    "id": "",
                    "info": "Location hole: (84953.1, 447490, -0.08)",
                    "type": "Error"
                }],
                "id": "b1127b2f3-00ba-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 49,
                "numbershells": 1,
                "numbervertices": 30,
                "type": "Solid",
                "validity": false
            }],
            "type": "Building",
            "validity": false
        },
        {
            "errors_feature": null,
            "id": "b1128005c-00ba-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "errors": [{
                    "code": 302,
                    "description": "SHELL_NOT_CLOSED",
                    "id": "",
                    "info": "Location hole: (84959.3, 447488, -0.1)",
                    "type": "Error"
                }],
                "id": "b1128005c-00ba-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 41,
                "numbershells": 1,
                "numbervertices": 26,
                "type": "Solid",
                "validity": false
            }],
            "type": "Building",
            "validity": false
        },
        {
            "errors_feature": null,
            "id": "b11280066-00ba-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "errors": [{
                    "code": 302,
                    "description": "SHELL_NOT_CLOSED",
                    "id": "",
                    "info": "Location hole: (84917.2, 447547, 0.14)",
                    "type": "Error"
                }],
                "id": "b11280066-00ba-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 50,
                "numbershells": 1,
                "numbervertices": 32,
                "type": "Solid",
                "validity": false
            }],
            "type": "Building",
            "validity": false
        },
        {
            "errors_feature": null,
            "id": "b1128006b-00ba-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "errors": [{
                    "code": 302,
                    "description": "SHELL_NOT_CLOSED",
                    "id": "",
                    "info": "Location hole: (84927.4, 447541, 0.15)",
                    "type": "Error"
                }],
                "id": "b1128006b-00ba-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 37,
                "numbershells": 1,
                "numbervertices": 26,
                "type": "Solid",
                "validity": false
            }],
            "type": "Building",
            "validity": false
        },
        {
            "errors_feature": null,
            "id": "b11280070-00ba-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "errors": [{
                    "code": 302,
                    "description": "SHELL_NOT_CLOSED",
                    "id": "",
                    "info": "Location hole: (84950.1, 447534, 0.02)",
                    "type": "Error"
                }],
                "id": "b11280070-00ba-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 41,
                "numbershells": 1,
                "numbervertices": 26,
                "type": "Solid",
                "validity": false
            }],
            "type": "Building",
            "validity": false
        },
        {
            "errors_feature": null,
            "id": "b11280075-00ba-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "errors": [{
                    "code": 302,
                    "description": "SHELL_NOT_CLOSED",
                    "id": "",
                    "info": "Location hole: (84956, 447535, 0.08)",
                    "type": "Error"
                }],
                "id": "b11280075-00ba-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 32,
                "numbershells": 1,
                "numbervertices": 22,
                "type": "Solid",
                "validity": false
            }],
            "type": "Building",
            "validity": false
        },
        {
            "errors_feature": null,
            "id": "b1128007a-00ba-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "errors": [{
                    "code": 302,
                    "description": "SHELL_NOT_CLOSED",
                    "id": "",
                    "info": "Location hole: (84946.7, 447588, 0.16)",
                    "type": "Error"
                }],
                "id": "b1128007a-00ba-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 41,
                "numbershells": 1,
                "numbervertices": 28,
                "type": "Solid",
                "validity": false
            }],
            "type": "Building",
            "validity": false
        },
        {
            "errors_feature": null,
            "id": "b1128007f-00ba-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "errors": [{
                    "code": 302,
                    "description": "SHELL_NOT_CLOSED",
                    "id": "",
                    "info": "Location hole: (84928.1, 447541, 0.2)",
                    "type": "Error"
                }],
                "id": "b1128007f-00ba-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 16,
                "numbershells": 1,
                "numbervertices": 12,
                "type": "Solid",
                "validity": false
            }],
            "type": "Building",
            "validity": false
        },
        {
            "errors_feature": null,
            "id": "b11282794-00ba-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "errors": [{
                    "code": 302,
                    "description": "SHELL_NOT_CLOSED",
                    "id": "",
                    "info": "Location hole: (84991.8, 447542, 0.21)",
                    "type": "Error"
                }],
                "id": "b11282794-00ba-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 42,
                "numbershells": 1,
                "numbervertices": 28,
                "type": "Solid",
                "validity": false
            }],
            "type": "Building",
            "validity": false
        },
        {
            "errors_feature": null,
            "id": "b11282799-00ba-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "errors": [{
                    "code": 302,
                    "description": "SHELL_NOT_CLOSED",
                    "id": "",
                    "info": "Location hole: (85000, 447542, 0.22)",
                    "type": "Error"
                }],
                "id": "b11282799-00ba-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 47,
                "numbershells": 1,
                "numbervertices": 30,
                "type": "Solid",
                "validity": false
            }],
            "type": "Building",
            "validity": false
        },
        {
            "errors_feature": null,
            "id": "b1128279e-00ba-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "errors": [{
                    "code": 302,
                    "description": "SHELL_NOT_CLOSED",
                    "id": "",
                    "info": "Location hole: (84958.4, 447540, 0.07)",
                    "type": "Error"
                }],
                "id": "b1128279e-00ba-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 30,
                "numbershells": 1,
                "numbervertices": 20,
                "type": "Solid",
                "validity": false
            }],
            "type": "Building",
            "validity": false
        },
        {
            "errors_feature": null,
            "id": "b112827a3-00ba-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "errors": [{
                    "code": 302,
                    "description": "SHELL_NOT_CLOSED",
                    "id": "",
                    "info": "Location hole: (84962.3, 447543, 0.08)",
                    "type": "Error"
                }],
                "id": "b112827a3-00ba-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 38,
                "numbershells": 1,
                "numbervertices": 26,
                "type": "Solid",
                "validity": false
            }],
            "type": "Building",
            "validity": false
        },
        {
            "errors_feature": null,
            "id": "b112827a8-00ba-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "errors": [{
                    "code": 302,
                    "description": "SHELL_NOT_CLOSED",
                    "id": "",
                    "info": "Location hole: (84983.2, 447551, 0.16)",
                    "type": "Error"
                }],
                "id": "b112827a8-00ba-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 46,
                "numbershells": 1,
                "numbervertices": 31,
                "type": "Solid",
                "validity": false
            }],
            "type": "Building",
            "validity": false
        },
        {
            "errors_feature": null,
            "id": "b112827ad-00ba-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "errors": [{
                    "code": 302,
                    "description": "SHELL_NOT_CLOSED",
                    "id": "",
                    "info": "Location hole: (84987.4, 447547, 0.17)",
                    "type": "Error"
                }],
                "id": "b112827ad-00ba-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 53,
                "numbershells": 1,
                "numbervertices": 35,
                "type": "Solid",
                "validity": false
            }],
            "type": "Building",
            "validity": false
        },
        {
            "errors_feature": null,
            "id": "b112827b2-00ba-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "errors": [{
                    "code": 302,
                    "description": "SHELL_NOT_CLOSED",
                    "id": "",
                    "info": "Location hole: (84956, 447579, 0.13)",
                    "type": "Error"
                }],
                "id": "b112827b2-00ba-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 113,
                "numbershells": 1,
                "numbervertices": 75,
                "type": "Solid",
                "validity": false
            }],
            "type": "Building",
            "validity": false
        },
        {
            "errors_feature": null,
            "id": "b112827b7-00ba-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "errors": [{
                    "code": 302,
                    "description": "SHELL_NOT_CLOSED",
                    "id": "",
                    "info": "Location hole: (84948.9, 447581, 0.14)",
                    "type": "Error"
                }],
                "id": "b112827b7-00ba-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 107,
                "numbershells": 1,
                "numbervertices": 72,
                "type": "Solid",
                "validity": false
            }],
            "type": "Building",
            "validity": false
        },
        {
            "errors_feature": null,
            "id": "b22139d30-00b5-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "b22139d30-00b5-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 262,
                "numbervertices": 151,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "LandUse",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "b2214d56a-00b5-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "b2214d56a-00b5-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 4,
                "numbervertices": 5,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "LandUse",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "b22183104-00b5-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "b22183104-00b5-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 8,
                "numbervertices": 10,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "LandUse",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "b221a544c-00b5-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "b221a544c-00b5-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 26,
                "numbervertices": 20,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "LandUse",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "b221b16fc-00b5-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "b221b16fc-00b5-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 42,
                "numbervertices": 37,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "LandUse",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "b221b8c65-00b5-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "b221b8c65-00b5-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 30,
                "numbervertices": 32,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "LandUse",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "b221d3a47-00b5-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "b221d3a47-00b5-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 16,
                "numbervertices": 12,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "LandUse",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "b221dafb6-00b5-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "b221dafb6-00b5-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 358,
                "numbervertices": 214,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "LandUse",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "b221e7287-00b5-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "b221e7287-00b5-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 860,
                "numbervertices": 463,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "LandUse",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "b22204791-00b5-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "b22204791-00b5-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 81,
                "numbervertices": 65,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "LandUse",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "b22206eb6-00b5-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "b22206eb6-00b5-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 45,
                "numbervertices": 31,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "LandUse",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "b222095f0-00b5-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "b222095f0-00b5-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 24,
                "numbervertices": 19,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "LandUse",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "b2221a6f3-00b5-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "b2221a6f3-00b5-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 2,
                "numbervertices": 4,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "LandUse",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "b2221ce24-00b5-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "b2221ce24-00b5-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 2,
                "numbervertices": 4,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "LandUse",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "b2222df3c-00b5-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "b2222df3c-00b5-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 53,
                "numbervertices": 47,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "LandUse",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "b2223065e-00b5-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "b2223065e-00b5-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 622,
                "numbervertices": 336,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "LandUse",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "b222354ba-00b5-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "b222354ba-00b5-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 6,
                "numbervertices": 7,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "LandUse",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "b222465d8-00b5-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "b222465d8-00b5-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 4,
                "numbervertices": 6,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "LandUse",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "b22250278-00b5-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "b22250278-00b5-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 855,
                "numbervertices": 498,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "LandUse",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "b222836f6-00b5-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "b222836f6-00b5-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 75,
                "numbervertices": 48,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "LandUse",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "b2228f9ca-00b5-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "b2228f9ca-00b5-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 26,
                "numbervertices": 22,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "LandUse",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "b222920fb-00b5-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "b222920fb-00b5-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 12,
                "numbervertices": 9,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "LandUse",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "b222b6a92-00b5-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "b222b6a92-00b5-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 20,
                "numbervertices": 14,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "LandUse",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "b222c557f-00b5-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "b222c557f-00b5-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 18,
                "numbervertices": 20,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "LandUse",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "b222ddc12-00b5-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "b222ddc12-00b5-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 283,
                "numbervertices": 157,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "LandUse",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "b222e2a53-00b5-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "b222e2a53-00b5-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 5,
                "numbervertices": 7,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "LandUse",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "b222ec5e4-00b5-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "b222ec5e4-00b5-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 2,
                "numbervertices": 4,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "LandUse",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "b2230c204-00b5-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "b2230c204-00b5-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 11,
                "numbervertices": 13,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "LandUse",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "b2231105d-00b5-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "b2231105d-00b5-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 5,
                "numbervertices": 7,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "LandUse",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "b2231d343-00b5-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "b2231d343-00b5-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 2,
                "numbervertices": 4,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "LandUse",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "b2232218d-00b5-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "b2232218d-00b5-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 195,
                "numbervertices": 190,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "LandUse",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "b2c15e416-2d29-11e6-9a38-393caa90be70",
            "primitives": [{
                "id": "b2c15e416-2d29-11e6-9a38-393caa90be70(0)",
                "numberfaces": 340,
                "numbervertices": 212,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "PlantCover",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "b2c160b4a-2d29-11e6-9a38-393caa90be70",
            "primitives": [{
                "id": "b2c160b4a-2d29-11e6-9a38-393caa90be70(0)",
                "numberfaces": 1008,
                "numbervertices": 522,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "PlantCover",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "b2c160b4d-2d29-11e6-9a38-393caa90be70",
            "primitives": [{
                "id": "b2c160b4d-2d29-11e6-9a38-393caa90be70(0)",
                "numberfaces": 640,
                "numbervertices": 390,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "PlantCover",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "b2c1659af-2d29-11e6-9a38-393caa90be70",
            "primitives": [{
                "id": "b2c1659af-2d29-11e6-9a38-393caa90be70(0)",
                "numberfaces": 895,
                "numbervertices": 463,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "PlantCover",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "b2c16cf36-2d29-11e6-9a38-393caa90be70",
            "primitives": [{
                "id": "b2c16cf36-2d29-11e6-9a38-393caa90be70(0)",
                "numberfaces": 1174,
                "numbervertices": 634,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "PlantCover",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "b2c1743cc-2d29-11e6-9a38-393caa90be70",
            "primitives": [{
                "id": "b2c1743cc-2d29-11e6-9a38-393caa90be70(0)",
                "numberfaces": 927,
                "numbervertices": 555,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "PlantCover",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "b2c176ae8-2d29-11e6-9a38-393caa90be70",
            "primitives": [{
                "id": "b2c176ae8-2d29-11e6-9a38-393caa90be70(0)",
                "numberfaces": 724,
                "numbervertices": 387,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "PlantCover",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "b2c179213-2d29-11e6-9a38-393caa90be70",
            "primitives": [{
                "id": "b2c179213-2d29-11e6-9a38-393caa90be70(0)",
                "numberfaces": 688,
                "numbervertices": 348,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "PlantCover",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "b31bb8aab-00ba-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "errors": [{
                    "code": 302,
                    "description": "SHELL_NOT_CLOSED",
                    "id": "",
                    "info": "Location hole: (84938, 447524, 0.03)",
                    "type": "Error"
                }],
                "id": "b31bb8aab-00ba-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 26,
                "numbershells": 1,
                "numbervertices": 18,
                "type": "Solid",
                "validity": false
            }],
            "type": "Building",
            "validity": false
        },
        {
            "errors_feature": null,
            "id": "b31bb8ab0-00ba-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "errors": [{
                    "code": 302,
                    "description": "SHELL_NOT_CLOSED",
                    "id": "",
                    "info": "Location hole: (84943.2, 447527, 0.03)",
                    "type": "Error"
                }],
                "id": "b31bb8ab0-00ba-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 29,
                "numbershells": 1,
                "numbervertices": 20,
                "type": "Solid",
                "validity": false
            }],
            "type": "Building",
            "validity": false
        },
        {
            "errors_feature": null,
            "id": "b31bb8ab5-00ba-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "errors": [{
                    "code": 302,
                    "description": "SHELL_NOT_CLOSED",
                    "id": "",
                    "info": "Location hole: (84946.1, 447531, 0.02)",
                    "type": "Error"
                }],
                "id": "b31bb8ab5-00ba-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 23,
                "numbershells": 1,
                "numbervertices": 16,
                "type": "Solid",
                "validity": false
            }],
            "type": "Building",
            "validity": false
        },
        {
            "errors_feature": null,
            "id": "b31bbb1ca-00ba-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "errors": [{
                    "code": 302,
                    "description": "SHELL_NOT_CLOSED",
                    "id": "",
                    "info": "Location hole: (84946.9, 447492, -0.06)",
                    "type": "Error"
                }],
                "id": "b31bbb1ca-00ba-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 33,
                "numbershells": 1,
                "numbervertices": 22,
                "type": "Solid",
                "validity": false
            }],
            "type": "Building",
            "validity": false
        },
        {
            "errors_feature": null,
            "id": "b31bbd90d-00ba-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "errors": [{
                    "code": 302,
                    "description": "SHELL_NOT_CLOSED",
                    "id": "",
                    "info": "Location hole: (84859.1, 447530, -0.03)",
                    "type": "Error"
                }],
                "id": "b31bbd90d-00ba-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 20,
                "numbershells": 1,
                "numbervertices": 14,
                "type": "Solid",
                "validity": false
            }],
            "type": "Building",
            "validity": false
        },
        {
            "errors_feature": null,
            "id": "b31bbd912-00ba-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "errors": [{
                    "code": 302,
                    "description": "SHELL_NOT_CLOSED",
                    "id": "",
                    "info": "Location hole: (84855.9, 447532, -0.03)",
                    "type": "Error"
                }],
                "id": "b31bbd912-00ba-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 27,
                "numbershells": 1,
                "numbervertices": 18,
                "type": "Solid",
                "validity": false
            }],
            "type": "Building",
            "validity": false
        },
        {
            "errors_feature": null,
            "id": "b31bbd917-00ba-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "errors": [{
                    "code": 302,
                    "description": "SHELL_NOT_CLOSED",
                    "id": "",
                    "info": "Location hole: (84920.4, 447535, 0.13)",
                    "type": "Error"
                }],
                "id": "b31bbd917-00ba-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 30,
                "numbershells": 1,
                "numbervertices": 20,
                "type": "Solid",
                "validity": false
            }],
            "type": "Building",
            "validity": false
        },
        {
            "errors_feature": null,
            "id": "b31bbd91c-00ba-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "errors": [{
                    "code": 302,
                    "description": "SHELL_NOT_CLOSED",
                    "id": "",
                    "info": "Location hole: (84930.6, 447518, 0.08)",
                    "type": "Error"
                }],
                "id": "b31bbd91c-00ba-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 37,
                "numbershells": 1,
                "numbervertices": 26,
                "type": "Solid",
                "validity": false
            }],
            "type": "Building",
            "validity": false
        },
        {
            "errors_feature": null,
            "id": "b31bbd921-00ba-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "errors": [{
                    "code": 302,
                    "description": "SHELL_NOT_CLOSED",
                    "id": "",
                    "info": "Location hole: (84892, 447519, 0)",
                    "type": "Error"
                }],
                "id": "b31bbd921-00ba-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 89,
                "numbershells": 1,
                "numbervertices": 57,
                "type": "Solid",
                "validity": false
            }],
            "type": "Building",
            "validity": false
        },
        {
            "errors_feature": null,
            "id": "b31bbd926-00ba-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "errors": [{
                    "code": 302,
                    "description": "SHELL_NOT_CLOSED",
                    "id": "",
                    "info": "Location hole: (84879.9, 447515, -0.02)",
                    "type": "Error"
                }],
                "id": "b31bbd926-00ba-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 56,
                "numbershells": 1,
                "numbervertices": 36,
                "type": "Solid",
                "validity": false
            }],
            "type": "Building",
            "validity": false
        },
        {
            "errors_feature": null,
            "id": "b31bbd92b-00ba-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "errors": [{
                    "code": 302,
                    "description": "SHELL_NOT_CLOSED",
                    "id": "",
                    "info": "Location hole: (84933.9, 447522, 0.03)",
                    "type": "Error"
                }],
                "id": "b31bbd92b-00ba-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 28,
                "numbershells": 1,
                "numbervertices": 18,
                "type": "Solid",
                "validity": false
            }],
            "type": "Building",
            "validity": false
        },
        {
            "errors_feature": null,
            "id": "b31bbff40-00ba-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "errors": [{
                    "code": 302,
                    "description": "SHELL_NOT_CLOSED",
                    "id": "",
                    "info": "Location hole: (84877.8, 447519, -0.03)",
                    "type": "Error"
                }],
                "id": "b31bbff40-00ba-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 49,
                "numbershells": 1,
                "numbervertices": 32,
                "type": "Solid",
                "validity": false
            }],
            "type": "Building",
            "validity": false
        },
        {
            "errors_feature": null,
            "id": "b31bbff45-00ba-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "errors": [{
                    "code": 302,
                    "description": "SHELL_NOT_CLOSED",
                    "id": "",
                    "info": "Location hole: (84901.1, 447521, 0.17)",
                    "type": "Error"
                }],
                "id": "b31bbff45-00ba-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 77,
                "numbershells": 1,
                "numbervertices": 50,
                "type": "Solid",
                "validity": false
            }],
            "type": "Building",
            "validity": false
        },
        {
            "errors_feature": null,
            "id": "b31bbff4a-00ba-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "errors": [{
                    "code": 302,
                    "description": "SHELL_NOT_CLOSED",
                    "id": "",
                    "info": "Location hole: (84904.8, 447524, 0.14)",
                    "type": "Error"
                }],
                "id": "b31bbff4a-00ba-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 38,
                "numbershells": 1,
                "numbervertices": 24,
                "type": "Solid",
                "validity": false
            }],
            "type": "Building",
            "validity": false
        },
        {
            "errors_feature": null,
            "id": "b31bbff4f-00ba-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "errors": [{
                    "code": 302,
                    "description": "SHELL_NOT_CLOSED",
                    "id": "",
                    "info": "Location hole: (84870.3, 447522, -0.04)",
                    "type": "Error"
                }],
                "id": "b31bbff4f-00ba-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 50,
                "numbershells": 1,
                "numbervertices": 34,
                "type": "Solid",
                "validity": false
            }],
            "type": "Building",
            "validity": false
        },
        {
            "errors_feature": null,
            "id": "b31bbff54-00ba-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "errors": [{
                    "code": 302,
                    "description": "SHELL_NOT_CLOSED",
                    "id": "",
                    "info": "Location hole: (84908.7, 447526, 0.19)",
                    "type": "Error"
                }],
                "id": "b31bbff54-00ba-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 19,
                "numbershells": 1,
                "numbervertices": 14,
                "type": "Solid",
                "validity": false
            }],
            "type": "Building",
            "validity": false
        },
        {
            "errors_feature": null,
            "id": "b31bbff59-00ba-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "errors": [{
                    "code": 302,
                    "description": "SHELL_NOT_CLOSED",
                    "id": "",
                    "info": "Location hole: (84912.7, 447529, 0.15)",
                    "type": "Error"
                }],
                "id": "b31bbff59-00ba-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 24,
                "numbershells": 1,
                "numbervertices": 16,
                "type": "Solid",
                "validity": false
            }],
            "type": "Building",
            "validity": false
        },
        {
            "errors_feature": null,
            "id": "b31bbff5e-00ba-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "errors": [{
                    "code": 302,
                    "description": "SHELL_NOT_CLOSED",
                    "id": "",
                    "info": "Location hole: (84863.8, 447526, -0.03)",
                    "type": "Error"
                }],
                "id": "b31bbff5e-00ba-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 26,
                "numbershells": 1,
                "numbervertices": 18,
                "type": "Solid",
                "validity": false
            }],
            "type": "Building",
            "validity": false
        },
        {
            "errors_feature": null,
            "id": "b31bbff63-00ba-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "errors": [{
                    "code": 302,
                    "description": "SHELL_NOT_CLOSED",
                    "id": "",
                    "info": "Location hole: (84916.5, 447532, 0.12)",
                    "type": "Error"
                }],
                "id": "b31bbff63-00ba-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 30,
                "numbershells": 1,
                "numbervertices": 20,
                "type": "Solid",
                "validity": false
            }],
            "type": "Building",
            "validity": false
        },
        {
            "errors_feature": null,
            "id": "b31bbff68-00ba-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "errors": [{
                    "code": 302,
                    "description": "SHELL_NOT_CLOSED",
                    "id": "",
                    "info": "Location hole: (84895.3, 447516, 0.01)",
                    "type": "Error"
                }],
                "id": "b31bbff68-00ba-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 83,
                "numbershells": 1,
                "numbervertices": 55,
                "type": "Solid",
                "validity": false
            }],
            "type": "Building",
            "validity": false
        },
        {
            "errors_feature": null,
            "id": "b31bc267b-00ba-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "errors": [{
                    "code": 302,
                    "description": "SHELL_NOT_CLOSED",
                    "id": "",
                    "info": "Location hole: (84892.2, 447525, 0.21)",
                    "type": "Error"
                }],
                "id": "b31bc267b-00ba-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 25,
                "numbershells": 1,
                "numbervertices": 18,
                "type": "Solid",
                "validity": false
            }],
            "type": "Building",
            "validity": false
        },
        {
            "errors_feature": null,
            "id": "b31bc2680-00ba-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "errors": [{
                    "code": 302,
                    "description": "SHELL_NOT_CLOSED",
                    "id": "",
                    "info": "Location hole: (84901.7, 447502, -0.01)",
                    "type": "Error"
                }],
                "id": "b31bc2680-00ba-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 90,
                "numbershells": 1,
                "numbervertices": 60,
                "type": "Solid",
                "validity": false
            }],
            "type": "Building",
            "validity": false
        },
        {
            "errors_feature": null,
            "id": "b31bc2685-00ba-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "errors": [{
                    "code": 302,
                    "description": "SHELL_NOT_CLOSED",
                    "id": "",
                    "info": "Location hole: (84905.9, 447500, -0.03)",
                    "type": "Error"
                }],
                "id": "b31bc2685-00ba-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 45,
                "numbershells": 1,
                "numbervertices": 28,
                "type": "Solid",
                "validity": false
            }],
            "type": "Building",
            "validity": false
        },
        {
            "errors_feature": null,
            "id": "b31bc268a-00ba-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "errors": [{
                    "code": 302,
                    "description": "SHELL_NOT_CLOSED",
                    "id": "",
                    "info": "Location hole: (84916.2, 447509, 0.07)",
                    "type": "Error"
                }],
                "id": "b31bc268a-00ba-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 50,
                "numbershells": 1,
                "numbervertices": 34,
                "type": "Solid",
                "validity": false
            }],
            "type": "Building",
            "validity": false
        },
        {
            "errors_feature": null,
            "id": "b31bc2699-00ba-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "errors": [{
                    "code": 302,
                    "description": "SHELL_NOT_CLOSED",
                    "id": "",
                    "info": "Location hole: (84909.5, 447498, -0.02)",
                    "type": "Error"
                }],
                "id": "b31bc2699-00ba-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 66,
                "numbershells": 1,
                "numbervertices": 44,
                "type": "Solid",
                "validity": false
            }],
            "type": "Building",
            "validity": false
        },
        {
            "errors_feature": null,
            "id": "b31bc269e-00ba-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "errors": [{
                    "code": 302,
                    "description": "SHELL_NOT_CLOSED",
                    "id": "",
                    "info": "Location hole: (84913.9, 447495, -0.02)",
                    "type": "Error"
                }],
                "id": "b31bc269e-00ba-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 36,
                "numbershells": 1,
                "numbervertices": 24,
                "type": "Solid",
                "validity": false
            }],
            "type": "Building",
            "validity": false
        },
        {
            "errors_feature": null,
            "id": "b31bc26a3-00ba-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "errors": [{
                    "code": 302,
                    "description": "SHELL_NOT_CLOSED",
                    "id": "",
                    "info": "Location hole: (84915.8, 447512, 0.06)",
                    "type": "Error"
                }],
                "id": "b31bc26a3-00ba-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 48,
                "numbershells": 1,
                "numbervertices": 32,
                "type": "Solid",
                "validity": false
            }],
            "type": "Building",
            "validity": false
        },
        {
            "errors_feature": null,
            "id": "b31bc26a8-00ba-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "errors": [{
                    "code": 302,
                    "description": "SHELL_NOT_CLOSED",
                    "id": "",
                    "info": "Location hole: (84926.1, 447498, -0.03)",
                    "type": "Error"
                }],
                "id": "b31bc26a8-00ba-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 56,
                "numbershells": 1,
                "numbervertices": 38,
                "type": "Solid",
                "validity": false
            }],
            "type": "Building",
            "validity": false
        },
        {
            "errors_feature": null,
            "id": "b31bc4dbd-00ba-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "errors": [{
                    "code": 302,
                    "description": "SHELL_NOT_CLOSED",
                    "id": "",
                    "info": "Location hole: (84928.4, 447512, 0.07)",
                    "type": "Error"
                }],
                "id": "b31bc4dbd-00ba-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 37,
                "numbershells": 1,
                "numbervertices": 24,
                "type": "Solid",
                "validity": false
            }],
            "type": "Building",
            "validity": false
        },
        {
            "errors_feature": null,
            "id": "b31bc4dc2-00ba-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "errors": [{
                    "code": 302,
                    "description": "SHELL_NOT_CLOSED",
                    "id": "",
                    "info": "Location hole: (84940.7, 447494, -0.03)",
                    "type": "Error"
                }],
                "id": "b31bc4dc2-00ba-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 30,
                "numbershells": 1,
                "numbervertices": 20,
                "type": "Solid",
                "validity": false
            }],
            "type": "Building",
            "validity": false
        },
        {
            "errors_feature": null,
            "id": "b31bc4dc7-00ba-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "errors": [{
                    "code": 302,
                    "description": "SHELL_NOT_CLOSED",
                    "id": "",
                    "info": "Location hole: (84942.1, 447592, 0.14)",
                    "type": "Error"
                }],
                "id": "b31bc4dc7-00ba-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 38,
                "numbershells": 1,
                "numbervertices": 24,
                "type": "Solid",
                "validity": false
            }],
            "type": "Building",
            "validity": false
        },
        {
            "errors_feature": null,
            "id": "b31bc4dcc-00ba-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "errors": [{
                    "code": 302,
                    "description": "SHELL_NOT_CLOSED",
                    "id": "",
                    "info": "Location hole: (84937.6, 447597, 0.15)",
                    "type": "Error"
                }],
                "id": "b31bc4dcc-00ba-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 42,
                "numbershells": 1,
                "numbervertices": 28,
                "type": "Solid",
                "validity": false
            }],
            "type": "Building",
            "validity": false
        },
        {
            "errors_feature": null,
            "id": "b31bc751d-00ba-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "errors": [{
                    "code": 302,
                    "description": "SHELL_NOT_CLOSED",
                    "id": "",
                    "info": "Location hole: (84905.4, 447571, 0.4)",
                    "type": "Error"
                }],
                "id": "b31bc751d-00ba-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 37,
                "numbershells": 1,
                "numbervertices": 23,
                "type": "Solid",
                "validity": false
            }],
            "type": "Building",
            "validity": false
        },
        {
            "errors_feature": null,
            "id": "b31bc7522-00ba-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "errors": [{
                    "code": 302,
                    "description": "SHELL_NOT_CLOSED",
                    "id": "",
                    "info": "Location hole: (84905.4, 447575, 0.42)",
                    "type": "Error"
                }],
                "id": "b31bc7522-00ba-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 39,
                "numbershells": 1,
                "numbervertices": 25,
                "type": "Solid",
                "validity": false
            }],
            "type": "Building",
            "validity": false
        },
        {
            "errors_feature": null,
            "id": "b31bc9c37-00ba-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "errors": [{
                    "code": 302,
                    "description": "SHELL_NOT_CLOSED",
                    "id": "",
                    "info": "Location hole: (84909.2, 447598, 0.3)",
                    "type": "Error"
                }],
                "id": "b31bc9c37-00ba-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 16,
                "numbershells": 1,
                "numbervertices": 12,
                "type": "Solid",
                "validity": false
            }],
            "type": "Building",
            "validity": false
        },
        {
            "errors_feature": null,
            "id": "b31bc9c3c-00ba-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "errors": [{
                    "code": 302,
                    "description": "SHELL_NOT_CLOSED",
                    "id": "",
                    "info": "Location hole: (84905.6, 447584, 0.48)",
                    "type": "Error"
                }],
                "id": "b31bc9c3c-00ba-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 19,
                "numbershells": 1,
                "numbervertices": 14,
                "type": "Solid",
                "validity": false
            }],
            "type": "Building",
            "validity": false
        },
        {
            "errors_feature": null,
            "id": "b31bc9c41-00ba-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "errors": [{
                    "code": 302,
                    "description": "SHELL_NOT_CLOSED",
                    "id": "",
                    "info": "Location hole: (84910.6, 447603, 0.3)",
                    "type": "Error"
                }],
                "id": "b31bc9c41-00ba-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 36,
                "numbershells": 1,
                "numbervertices": 24,
                "type": "Solid",
                "validity": false
            }],
            "type": "Building",
            "validity": false
        },
        {
            "errors_feature": null,
            "id": "b31bc9c46-00ba-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "errors": [{
                    "code": 302,
                    "description": "SHELL_NOT_CLOSED",
                    "id": "",
                    "info": "Location hole: (84916.2, 447602, 0.31)",
                    "type": "Error"
                }],
                "id": "b31bc9c46-00ba-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 21,
                "numbershells": 1,
                "numbervertices": 14,
                "type": "Solid",
                "validity": false
            }],
            "type": "Building",
            "validity": false
        },
        {
            "errors_feature": null,
            "id": "b31bc9c4b-00ba-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "errors": [{
                    "code": 302,
                    "description": "SHELL_NOT_CLOSED",
                    "id": "",
                    "info": "Location hole: (84915.5, 447606, 0.32)",
                    "type": "Error"
                }],
                "id": "b31bc9c4b-00ba-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 29,
                "numbershells": 1,
                "numbervertices": 20,
                "type": "Solid",
                "validity": false
            }],
            "type": "Building",
            "validity": false
        },
        {
            "errors_feature": null,
            "id": "b31bc9c50-00ba-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "errors": [{
                    "code": 302,
                    "description": "SHELL_NOT_CLOSED",
                    "id": "",
                    "info": "Location hole: (84914.1, 447586, 0.46)",
                    "type": "Error"
                }],
                "id": "b31bc9c50-00ba-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 27,
                "numbershells": 1,
                "numbervertices": 18,
                "type": "Solid",
                "validity": false
            }],
            "type": "Building",
            "validity": false
        },
        {
            "errors_feature": null,
            "id": "b31bc9c53-00ba-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "errors": [{
                    "code": 302,
                    "description": "SHELL_NOT_CLOSED",
                    "id": "",
                    "info": "Location hole: (84913.9, 447591, 0.45)",
                    "type": "Error"
                }],
                "id": "b31bc9c53-00ba-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 17,
                "numbershells": 1,
                "numbervertices": 12,
                "type": "Solid",
                "validity": false
            }],
            "type": "Building",
            "validity": false
        },
        {
            "errors_feature": null,
            "id": "b31bc9c58-00ba-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "errors": [{
                    "code": 302,
                    "description": "SHELL_NOT_CLOSED",
                    "id": "",
                    "info": "Location hole: (84923.6, 447611, 0.31)",
                    "type": "Error"
                }],
                "id": "b31bc9c58-00ba-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 85,
                "numbershells": 1,
                "numbervertices": 58,
                "type": "Solid",
                "validity": false
            }],
            "type": "Building",
            "validity": false
        },
        {
            "errors_feature": null,
            "id": "b31bc9c5d-00ba-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "errors": [{
                    "code": 302,
                    "description": "SHELL_NOT_CLOSED",
                    "id": "",
                    "info": "Location hole: (84915.6, 447582, 0.46)",
                    "type": "Error"
                }],
                "id": "b31bc9c5d-00ba-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 24,
                "numbershells": 1,
                "numbervertices": 16,
                "type": "Solid",
                "validity": false
            }],
            "type": "Building",
            "validity": false
        },
        {
            "errors_feature": null,
            "id": "b31bc9c62-00ba-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "errors": [{
                    "code": 302,
                    "description": "SHELL_NOT_CLOSED",
                    "id": "",
                    "info": "Location hole: (84929.5, 447583, 0.49)",
                    "type": "Error"
                }],
                "id": "b31bc9c62-00ba-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 41,
                "numbershells": 1,
                "numbervertices": 28,
                "type": "Solid",
                "validity": false
            }],
            "type": "Building",
            "validity": false
        },
        {
            "errors_feature": null,
            "id": "b31bcc275-00ba-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "errors": [{
                    "code": 302,
                    "description": "SHELL_NOT_CLOSED",
                    "id": "",
                    "info": "Location hole: (84927, 447607, 0.21)",
                    "type": "Error"
                }],
                "id": "b31bcc275-00ba-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 25,
                "numbershells": 1,
                "numbervertices": 16,
                "type": "Solid",
                "validity": false
            }],
            "type": "Building",
            "validity": false
        },
        {
            "errors_feature": null,
            "id": "b31bcc27a-00ba-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "errors": [{
                    "code": 302,
                    "description": "SHELL_NOT_CLOSED",
                    "id": "",
                    "info": "Location hole: (84930.8, 447605, 0.19)",
                    "type": "Error"
                }],
                "id": "b31bcc27a-00ba-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 20,
                "numbershells": 1,
                "numbervertices": 14,
                "type": "Solid",
                "validity": false
            }],
            "type": "Building",
            "validity": false
        },
        {
            "errors_feature": null,
            "id": "b31bcc27f-00ba-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "errors": [{
                    "code": 302,
                    "description": "SHELL_NOT_CLOSED",
                    "id": "",
                    "info": "Location hole: (84933.6, 447600, 0.16)",
                    "type": "Error"
                }],
                "id": "b31bcc27f-00ba-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 39,
                "numbershells": 1,
                "numbervertices": 26,
                "type": "Solid",
                "validity": false
            }],
            "type": "Building",
            "validity": false
        },
        {
            "errors_feature": null,
            "id": "b31bcc293-00ba-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "errors": [{
                    "code": 302,
                    "description": "SHELL_NOT_CLOSED",
                    "id": "",
                    "info": "Location hole: (84872, 447572, 0.18)",
                    "type": "Error"
                }],
                "id": "b31bcc293-00ba-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 25,
                "numbershells": 1,
                "numbervertices": 16,
                "type": "Solid",
                "validity": false
            }],
            "type": "Building",
            "validity": false
        },
        {
            "errors_feature": null,
            "id": "b31bcc29d-00ba-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "errors": [{
                    "code": 302,
                    "description": "SHELL_NOT_CLOSED",
                    "id": "",
                    "info": "Location hole: (84876.1, 447575, 0.19)",
                    "type": "Error"
                }],
                "id": "b31bcc29d-00ba-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 33,
                "numbershells": 1,
                "numbervertices": 21,
                "type": "Solid",
                "validity": false
            }],
            "type": "Building",
            "validity": false
        },
        {
            "errors_feature": null,
            "id": "b31bce9b7-00ba-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "errors": [{
                    "code": 302,
                    "description": "SHELL_NOT_CLOSED",
                    "id": "",
                    "info": "Location hole: (84878, 447579, 0.19)",
                    "type": "Error"
                }],
                "id": "b31bce9b7-00ba-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 20,
                "numbershells": 1,
                "numbervertices": 14,
                "type": "Solid",
                "validity": false
            }],
            "type": "Building",
            "validity": false
        },
        {
            "errors_feature": null,
            "id": "b31bce9c1-00ba-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "errors": [{
                    "code": 302,
                    "description": "SHELL_NOT_CLOSED",
                    "id": "",
                    "info": "Location hole: (84884.3, 447579, 0.22)",
                    "type": "Error"
                }],
                "id": "b31bce9c1-00ba-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 23,
                "numbershells": 1,
                "numbervertices": 16,
                "type": "Solid",
                "validity": false
            }],
            "type": "Building",
            "validity": false
        },
        {
            "errors_feature": null,
            "id": "b31bce9c6-00ba-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "errors": [{
                    "code": 302,
                    "description": "SHELL_NOT_CLOSED",
                    "id": "",
                    "info": "Location hole: (84881.9, 447574, 0.28)",
                    "type": "Error"
                }],
                "id": "b31bce9c6-00ba-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 32,
                "numbershells": 1,
                "numbervertices": 22,
                "type": "Solid",
                "validity": false
            }],
            "type": "Building",
            "validity": false
        },
        {
            "errors_feature": null,
            "id": "b31bce9cb-00ba-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "errors": [{
                    "code": 302,
                    "description": "SHELL_NOT_CLOSED",
                    "id": "",
                    "info": "Location hole: (84886.8, 447583, 0.23)",
                    "type": "Error"
                }],
                "id": "b31bce9cb-00ba-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 28,
                "numbershells": 1,
                "numbervertices": 18,
                "type": "Solid",
                "validity": false
            }],
            "type": "Building",
            "validity": false
        },
        {
            "errors_feature": null,
            "id": "b31bce9d5-00ba-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "errors": [{
                    "code": 302,
                    "description": "SHELL_NOT_CLOSED",
                    "id": "",
                    "info": "Location hole: (84890.5, 447584, 0.26)",
                    "type": "Error"
                }],
                "id": "b31bce9d5-00ba-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 33,
                "numbershells": 1,
                "numbervertices": 22,
                "type": "Solid",
                "validity": false
            }],
            "type": "Building",
            "validity": false
        },
        {
            "errors_feature": null,
            "id": "b31bce9df-00ba-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "errors": [{
                    "code": 302,
                    "description": "SHELL_NOT_CLOSED",
                    "id": "",
                    "info": "Location hole: (84889.8, 447588, 0.28)",
                    "type": "Error"
                }],
                "id": "b31bce9df-00ba-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 29,
                "numbershells": 1,
                "numbervertices": 20,
                "type": "Solid",
                "validity": false
            }],
            "type": "Building",
            "validity": false
        },
        {
            "errors_feature": null,
            "id": "b31bd10f5-00ba-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "errors": [{
                    "code": 302,
                    "description": "SHELL_NOT_CLOSED",
                    "id": "",
                    "info": "Location hole: (84896.9, 447588, 0.28)",
                    "type": "Error"
                }],
                "id": "b31bd10f5-00ba-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 19,
                "numbershells": 1,
                "numbervertices": 14,
                "type": "Solid",
                "validity": false
            }],
            "type": "Building",
            "validity": false
        },
        {
            "errors_feature": null,
            "id": "b31bd10ff-00ba-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "errors": [{
                    "code": 302,
                    "description": "SHELL_NOT_CLOSED",
                    "id": "",
                    "info": "Location hole: (84900.2, 447591, 0.28)",
                    "type": "Error"
                }],
                "id": "b31bd10ff-00ba-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 19,
                "numbershells": 1,
                "numbervertices": 14,
                "type": "Solid",
                "validity": false
            }],
            "type": "Building",
            "validity": false
        },
        {
            "errors_feature": null,
            "id": "b31bd110e-00ba-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "errors": [{
                    "code": 302,
                    "description": "SHELL_NOT_CLOSED",
                    "id": "",
                    "info": "Location hole: (84902.7, 447594, 0.27)",
                    "type": "Error"
                }],
                "id": "b31bd110e-00ba-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 34,
                "numbershells": 1,
                "numbervertices": 22,
                "type": "Solid",
                "validity": false
            }],
            "type": "Building",
            "validity": false
        },
        {
            "errors_feature": null,
            "id": "b31bd1111-00ba-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "errors": [{
                    "code": 302,
                    "description": "SHELL_NOT_CLOSED",
                    "id": "",
                    "info": "Location hole: (84904.2, 447598, 0.29)",
                    "type": "Error"
                }],
                "id": "b31bd1111-00ba-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 31,
                "numbershells": 1,
                "numbervertices": 20,
                "type": "Solid",
                "validity": false
            }],
            "type": "Building",
            "validity": false
        },
        {
            "errors_feature": null,
            "id": "b31bd1116-00ba-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "errors": [{
                    "code": 302,
                    "description": "SHELL_NOT_CLOSED",
                    "id": "",
                    "info": "Location hole: (84859.7, 447563, 0.09)",
                    "type": "Error"
                }],
                "id": "b31bd1116-00ba-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 26,
                "numbershells": 1,
                "numbervertices": 18,
                "type": "Solid",
                "validity": false
            }],
            "type": "Building",
            "validity": false
        },
        {
            "errors_feature": null,
            "id": "b31bd111b-00ba-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "errors": [{
                    "code": 302,
                    "description": "SHELL_NOT_CLOSED",
                    "id": "",
                    "info": "Location hole: (84862.7, 447565, 0.11)",
                    "type": "Error"
                }],
                "id": "b31bd111b-00ba-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 14,
                "numbershells": 1,
                "numbervertices": 10,
                "type": "Solid",
                "validity": false
            }],
            "type": "Building",
            "validity": false
        },
        {
            "errors_feature": null,
            "id": "b31bd382e-00ba-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "errors": [{
                    "code": 302,
                    "description": "SHELL_NOT_CLOSED",
                    "id": "",
                    "info": "Location hole: (84865.7, 447568, 0.12)",
                    "type": "Error"
                }],
                "id": "b31bd382e-00ba-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 21,
                "numbershells": 1,
                "numbervertices": 14,
                "type": "Solid",
                "validity": false
            }],
            "type": "Building",
            "validity": false
        },
        {
            "errors_feature": null,
            "id": "b31bd3833-00ba-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "errors": [{
                    "code": 302,
                    "description": "SHELL_NOT_CLOSED",
                    "id": "",
                    "info": "Location hole: (84867.2, 447572, 0.15)",
                    "type": "Error"
                }],
                "id": "b31bd3833-00ba-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 33,
                "numbershells": 1,
                "numbervertices": 22,
                "type": "Solid",
                "validity": false
            }],
            "type": "Building",
            "validity": false
        },
        {
            "errors_feature": null,
            "id": "b31bd384d-00ba-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "errors": [{
                    "code": 302,
                    "description": "SHELL_NOT_CLOSED",
                    "id": "",
                    "info": "Location hole: (84888.3, 447558, 0.61)",
                    "type": "Error"
                }],
                "id": "b31bd384d-00ba-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 40,
                "numbershells": 1,
                "numbervertices": 26,
                "type": "Solid",
                "validity": false
            }],
            "type": "Building",
            "validity": false
        },
        {
            "errors_feature": null,
            "id": "b31bd3852-00ba-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "errors": [{
                    "code": 302,
                    "description": "SHELL_NOT_CLOSED",
                    "id": "",
                    "info": "Location hole: (84904.8, 447561, 0.5)",
                    "type": "Error"
                }],
                "id": "b31bd3852-00ba-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 42,
                "numbershells": 1,
                "numbervertices": 28,
                "type": "Solid",
                "validity": false
            }],
            "type": "Building",
            "validity": false
        },
        {
            "errors_feature": null,
            "id": "b31bd3857-00ba-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "errors": [{
                    "code": 302,
                    "description": "SHELL_NOT_CLOSED",
                    "id": "",
                    "info": "Location hole: (84895.7, 447564, 0.4)",
                    "type": "Error"
                }],
                "id": "b31bd3857-00ba-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 32,
                "numbershells": 1,
                "numbervertices": 20,
                "type": "Solid",
                "validity": false
            }],
            "type": "Building",
            "validity": false
        },
        {
            "errors_feature": null,
            "id": "b31bd5f6c-00ba-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "errors": [{
                    "code": 302,
                    "description": "SHELL_NOT_CLOSED",
                    "id": "",
                    "info": "Location hole: (84899.6, 447562, 0.57)",
                    "type": "Error"
                }],
                "id": "b31bd5f6c-00ba-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 28,
                "numbershells": 1,
                "numbervertices": 20,
                "type": "Solid",
                "validity": false
            }],
            "type": "Building",
            "validity": false
        },
        {
            "errors_feature": null,
            "id": "b31bd5f71-00ba-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "errors": [{
                    "code": 302,
                    "description": "SHELL_NOT_CLOSED",
                    "id": "",
                    "info": "Location hole: (84883.3, 447572, 0.29)",
                    "type": "Error"
                }],
                "id": "b31bd5f71-00ba-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 31,
                "numbershells": 1,
                "numbervertices": 20,
                "type": "Solid",
                "validity": false
            }],
            "type": "Building",
            "validity": false
        },
        {
            "errors_feature": null,
            "id": "b31bd5f76-00ba-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "errors": [{
                    "code": 302,
                    "description": "SHELL_NOT_CLOSED",
                    "id": "",
                    "info": "Location hole: (84898.9, 447566, 0.45)",
                    "type": "Error"
                }],
                "id": "b31bd5f76-00ba-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 18,
                "numbershells": 1,
                "numbervertices": 12,
                "type": "Solid",
                "validity": false
            }],
            "type": "Building",
            "validity": false
        },
        {
            "errors_feature": null,
            "id": "b31bd5f7b-00ba-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "errors": [
                    {
                        "code": 302,
                        "description": "SHELL_NOT_CLOSED",
                        "id": "",
                        "info": "Location hole: (84902.2, 447569, 0.39)",
                        "type": "Error"
                    },
                    {
                        "code": 302,
                        "description": "SHELL_NOT_CLOSED",
                        "id": "",
                        "info": "Location hole: (84899.6, 447569, 0.39)",
                        "type": "Error"
                    }
                ],
                "id": "b31bd5f7b-00ba-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 48,
                "numbershells": 1,
                "numbervertices": 28,
                "type": "Solid",
                "validity": false
            }],
            "type": "Building",
            "validity": false
        },
        {
            "errors_feature": null,
            "id": "b31bdd428-00ba-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "errors": [{
                    "code": 302,
                    "description": "SHELL_NOT_CLOSED",
                    "id": "",
                    "info": "Location hole: (85022.4, 447523, 0.28)",
                    "type": "Error"
                }],
                "id": "b31bdd428-00ba-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 36,
                "numbershells": 1,
                "numbervertices": 24,
                "type": "Solid",
                "validity": false
            }],
            "type": "Building",
            "validity": false
        },
        {
            "errors_feature": null,
            "id": "b31bdd42d-00ba-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "errors": [{
                    "code": 302,
                    "description": "SHELL_NOT_CLOSED",
                    "id": "",
                    "info": "Location hole: (85030.3, 447521, 0.2)",
                    "type": "Error"
                }],
                "id": "b31bdd42d-00ba-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 25,
                "numbershells": 1,
                "numbervertices": 18,
                "type": "Solid",
                "validity": false
            }],
            "type": "Building",
            "validity": false
        },
        {
            "errors_feature": null,
            "id": "b31bdd432-00ba-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "errors": [{
                    "code": 302,
                    "description": "SHELL_NOT_CLOSED",
                    "id": "",
                    "info": "Location hole: (85035.4, 447502, 0.2)",
                    "type": "Error"
                }],
                "id": "b31bdd432-00ba-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 19,
                "numbershells": 1,
                "numbervertices": 14,
                "type": "Solid",
                "validity": false
            }],
            "type": "Building",
            "validity": false
        },
        {
            "errors_feature": null,
            "id": "b31bdd437-00ba-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "errors": [{
                    "code": 302,
                    "description": "SHELL_NOT_CLOSED",
                    "id": "",
                    "info": "Location hole: (85023.4, 447494, 0.19)",
                    "type": "Error"
                }],
                "id": "b31bdd437-00ba-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 14,
                "numbershells": 1,
                "numbervertices": 10,
                "type": "Solid",
                "validity": false
            }],
            "type": "Building",
            "validity": false
        },
        {
            "errors_feature": null,
            "id": "b31bdd43a-00ba-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "errors": [{
                    "code": 302,
                    "description": "SHELL_NOT_CLOSED",
                    "id": "",
                    "info": "Location hole: (85026.4, 447496, 0.19)",
                    "type": "Error"
                }],
                "id": "b31bdd43a-00ba-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 18,
                "numbershells": 1,
                "numbervertices": 12,
                "type": "Solid",
                "validity": false
            }],
            "type": "Building",
            "validity": false
        },
        {
            "errors_feature": null,
            "id": "b31bdd43f-00ba-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "errors": [{
                    "code": 302,
                    "description": "SHELL_NOT_CLOSED",
                    "id": "",
                    "info": "Location hole: (85029.5, 447498, 0.18)",
                    "type": "Error"
                }],
                "id": "b31bdd43f-00ba-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 18,
                "numbershells": 1,
                "numbervertices": 12,
                "type": "Solid",
                "validity": false
            }],
            "type": "Building",
            "validity": false
        },
        {
            "errors_feature": null,
            "id": "b31bdd442-00ba-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "errors": [{
                    "code": 302,
                    "description": "SHELL_NOT_CLOSED",
                    "id": "",
                    "info": "Location hole: (85028.8, 447516, 0.19)",
                    "type": "Error"
                }],
                "id": "b31bdd442-00ba-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 18,
                "numbershells": 1,
                "numbervertices": 12,
                "type": "Solid",
                "validity": false
            }],
            "type": "Building",
            "validity": false
        },
        {
            "errors_feature": null,
            "id": "b31bdd447-00ba-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "errors": [{
                    "code": 302,
                    "description": "SHELL_NOT_CLOSED",
                    "id": "",
                    "info": "Location hole: (85032.6, 447500, 0.18)",
                    "type": "Error"
                }],
                "id": "b31bdd447-00ba-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 14,
                "numbershells": 1,
                "numbervertices": 10,
                "type": "Solid",
                "validity": false
            }],
            "type": "Building",
            "validity": false
        },
        {
            "errors_feature": null,
            "id": "b31bdd44c-00ba-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "errors": [{
                    "code": 302,
                    "description": "SHELL_NOT_CLOSED",
                    "id": "",
                    "info": "Location hole: (85030.8, 447513, 0.19)",
                    "type": "Error"
                }],
                "id": "b31bdd44c-00ba-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 14,
                "numbershells": 1,
                "numbervertices": 10,
                "type": "Solid",
                "validity": false
            }],
            "type": "Building",
            "validity": false
        },
        {
            "errors_feature": null,
            "id": "b31bdd44f-00ba-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "errors": [{
                    "code": 302,
                    "description": "SHELL_NOT_CLOSED",
                    "id": "",
                    "info": "Location hole: (85035.4, 447502, 0.18)",
                    "type": "Error"
                }],
                "id": "b31bdd44f-00ba-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 18,
                "numbershells": 1,
                "numbervertices": 12,
                "type": "Solid",
                "validity": false
            }],
            "type": "Building",
            "validity": false
        },
        {
            "errors_feature": null,
            "id": "b31bdfb64-00ba-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "errors": [{
                    "code": 302,
                    "description": "SHELL_NOT_CLOSED",
                    "id": "",
                    "info": "Location hole: (85001.1, 447500, 0.23)",
                    "type": "Error"
                }],
                "id": "b31bdfb64-00ba-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 27,
                "numbershells": 1,
                "numbervertices": 18,
                "type": "Solid",
                "validity": false
            }],
            "type": "Building",
            "validity": false
        },
        {
            "errors_feature": null,
            "id": "b31bdfb67-00ba-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "errors": [{
                    "code": 302,
                    "description": "SHELL_NOT_CLOSED",
                    "id": "",
                    "info": "Location hole: (85003.1, 447497, 0.24)",
                    "type": "Error"
                }],
                "id": "b31bdfb67-00ba-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 21,
                "numbershells": 1,
                "numbervertices": 14,
                "type": "Solid",
                "validity": false
            }],
            "type": "Building",
            "validity": false
        },
        {
            "errors_feature": null,
            "id": "b31bdfb6a-00ba-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "errors": [{
                    "code": 302,
                    "description": "SHELL_NOT_CLOSED",
                    "id": "",
                    "info": "Location hole: (85005.1, 447494, 0.23)",
                    "type": "Error"
                }],
                "id": "b31bdfb6a-00ba-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 18,
                "numbershells": 1,
                "numbervertices": 12,
                "type": "Solid",
                "validity": false
            }],
            "type": "Building",
            "validity": false
        },
        {
            "errors_feature": null,
            "id": "b31bdfb6f-00ba-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "errors": [{
                    "code": 302,
                    "description": "SHELL_NOT_CLOSED",
                    "id": "",
                    "info": "Location hole: (85007.2, 447491, 0.22)",
                    "type": "Error"
                }],
                "id": "b31bdfb6f-00ba-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 17,
                "numbershells": 1,
                "numbervertices": 12,
                "type": "Solid",
                "validity": false
            }],
            "type": "Building",
            "validity": false
        },
        {
            "errors_feature": null,
            "id": "b31bdfb74-00ba-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "errors": [{
                    "code": 302,
                    "description": "SHELL_NOT_CLOSED",
                    "id": "",
                    "info": "Location hole: (85017.3, 447489, 0.19)",
                    "type": "Error"
                }],
                "id": "b31bdfb74-00ba-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 22,
                "numbershells": 1,
                "numbervertices": 14,
                "type": "Solid",
                "validity": false
            }],
            "type": "Building",
            "validity": false
        },
        {
            "errors_feature": null,
            "id": "b31bdfb77-00ba-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "errors": [{
                    "code": 302,
                    "description": "SHELL_NOT_CLOSED",
                    "id": "",
                    "info": "Location hole: (85020.3, 447491, 0.19)",
                    "type": "Error"
                }],
                "id": "b31bdfb77-00ba-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 10,
                "numbershells": 1,
                "numbervertices": 8,
                "type": "Solid",
                "validity": false
            }],
            "type": "Building",
            "validity": false
        },
        {
            "errors_feature": null,
            "id": "b31bdfb7a-00ba-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "errors": [{
                    "code": 302,
                    "description": "SHELL_NOT_CLOSED",
                    "id": "",
                    "info": "Location hole: (85014.2, 447487, 0.2)",
                    "type": "Error"
                }],
                "id": "b31bdfb7a-00ba-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 16,
                "numbershells": 1,
                "numbervertices": 12,
                "type": "Solid",
                "validity": false
            }],
            "type": "Building",
            "validity": false
        },
        {
            "errors_feature": null,
            "id": "b31bdfb7f-00ba-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "errors": [{
                    "code": 302,
                    "description": "SHELL_NOT_CLOSED",
                    "id": "",
                    "info": "Location hole: (84970.6, 447475, -0.11)",
                    "type": "Error"
                }],
                "id": "b31bdfb7f-00ba-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 29,
                "numbershells": 1,
                "numbervertices": 20,
                "type": "Solid",
                "validity": false
            }],
            "type": "Building",
            "validity": false
        },
        {
            "errors_feature": null,
            "id": "b31bdfb84-00ba-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "errors": [{
                    "code": 302,
                    "description": "SHELL_NOT_CLOSED",
                    "id": "",
                    "info": "Location hole: (84989, 447485, -0.12)",
                    "type": "Error"
                }],
                "id": "b31bdfb84-00ba-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 41,
                "numbershells": 1,
                "numbervertices": 26,
                "type": "Solid",
                "validity": false
            }],
            "type": "Building",
            "validity": false
        },
        {
            "errors_feature": null,
            "id": "b31bdfb89-00ba-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "errors": [{
                    "code": 302,
                    "description": "SHELL_NOT_CLOSED",
                    "id": "",
                    "info": "Location hole: (84976.3, 447487, 0)",
                    "type": "Error"
                }],
                "id": "b31bdfb89-00ba-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 34,
                "numbershells": 1,
                "numbervertices": 24,
                "type": "Solid",
                "validity": false
            }],
            "type": "Building",
            "validity": false
        },
        {
            "errors_feature": null,
            "id": "b31be229e-00ba-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "errors": [{
                    "code": 302,
                    "description": "SHELL_NOT_CLOSED",
                    "id": "",
                    "info": "Location hole: (84985.6, 447480, -0.12)",
                    "type": "Error"
                }],
                "id": "b31be229e-00ba-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 32,
                "numbershells": 1,
                "numbervertices": 22,
                "type": "Solid",
                "validity": false
            }],
            "type": "Building",
            "validity": false
        },
        {
            "errors_feature": null,
            "id": "b31be22a3-00ba-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "errors": [{
                    "code": 302,
                    "description": "SHELL_NOT_CLOSED",
                    "id": "",
                    "info": "Location hole: (85013.9, 447522, 0.3)",
                    "type": "Error"
                }],
                "id": "b31be22a3-00ba-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 70,
                "numbershells": 1,
                "numbervertices": 48,
                "type": "Solid",
                "validity": false
            }],
            "type": "Building",
            "validity": false
        },
        {
            "errors_feature": null,
            "id": "b31be22a8-00ba-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "errors": [{
                    "code": 302,
                    "description": "SHELL_NOT_CLOSED",
                    "id": "",
                    "info": "Location hole: (85000.4, 447534, 0.24)",
                    "type": "Error"
                }],
                "id": "b31be22a8-00ba-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 47,
                "numbershells": 1,
                "numbervertices": 32,
                "type": "Solid",
                "validity": false
            }],
            "type": "Building",
            "validity": false
        },
        {
            "errors_feature": null,
            "id": "b31be22ad-00ba-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "errors": [{
                    "code": 302,
                    "description": "SHELL_NOT_CLOSED",
                    "id": "",
                    "info": "Location hole: (85004.6, 447530, -0.14)",
                    "type": "Error"
                }],
                "id": "b31be22ad-00ba-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 36,
                "numbershells": 1,
                "numbervertices": 24,
                "type": "Solid",
                "validity": false
            }],
            "type": "Building",
            "validity": false
        },
        {
            "errors_feature": null,
            "id": "b31be22b0-00ba-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "errors": [{
                    "code": 302,
                    "description": "SHELL_NOT_CLOSED",
                    "id": "",
                    "info": "Location hole: (85032.8, 447511, 0.19)",
                    "type": "Error"
                }],
                "id": "b31be22b0-00ba-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 22,
                "numbershells": 1,
                "numbervertices": 14,
                "type": "Solid",
                "validity": false
            }],
            "type": "Building",
            "validity": false
        },
        {
            "errors_feature": null,
            "id": "b31be22b5-00ba-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "errors": [{
                    "code": 302,
                    "description": "SHELL_NOT_CLOSED",
                    "id": "",
                    "info": "Location hole: (85034.8, 447509, 0.2)",
                    "type": "Error"
                }],
                "id": "b31be22b5-00ba-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 10,
                "numbershells": 1,
                "numbervertices": 8,
                "type": "Solid",
                "validity": false
            }],
            "type": "Building",
            "validity": false
        },
        {
            "errors_feature": null,
            "id": "b31be22b8-00ba-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "errors": [{
                    "code": 302,
                    "description": "SHELL_NOT_CLOSED",
                    "id": "",
                    "info": "Location hole: (85036.4, 447508, 0.2)",
                    "type": "Error"
                }],
                "id": "b31be22b8-00ba-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 18,
                "numbershells": 1,
                "numbervertices": 12,
                "type": "Solid",
                "validity": false
            }],
            "type": "Building",
            "validity": false
        },
        {
            "errors_feature": null,
            "id": "b31be22bd-00ba-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "errors": [{
                    "code": 302,
                    "description": "SHELL_NOT_CLOSED",
                    "id": "",
                    "info": "Location hole: (85049.4, 447468, 0.29)",
                    "type": "Error"
                }],
                "id": "b31be22bd-00ba-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 154,
                "numbershells": 1,
                "numbervertices": 104,
                "type": "Solid",
                "validity": false
            }],
            "type": "Building",
            "validity": false
        },
        {
            "errors_feature": null,
            "id": "b31be22c2-00ba-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "errors": [{
                    "code": 302,
                    "description": "SHELL_NOT_CLOSED",
                    "id": "",
                    "info": "Location hole: (84999.1, 447502, 0.12)",
                    "type": "Error"
                }],
                "id": "b31be22c2-00ba-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 32,
                "numbershells": 1,
                "numbervertices": 22,
                "type": "Solid",
                "validity": false
            }],
            "type": "Building",
            "validity": false
        },
        {
            "errors_feature": null,
            "id": "b31be22c7-00ba-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "errors": [{
                    "code": 302,
                    "description": "SHELL_NOT_CLOSED",
                    "id": "",
                    "info": "Location hole: (84990.8, 447490, 0.07)",
                    "type": "Error"
                }],
                "id": "b31be22c7-00ba-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 37,
                "numbershells": 1,
                "numbervertices": 26,
                "type": "Solid",
                "validity": false
            }],
            "type": "Building",
            "validity": false
        },
        {
            "errors_feature": null,
            "id": "b31be22cc-00ba-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "errors": [{
                    "code": 302,
                    "description": "SHELL_NOT_CLOSED",
                    "id": "",
                    "info": "Location hole: (85010.3, 447526, -0.34)",
                    "type": "Error"
                }],
                "id": "b31be22cc-00ba-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 65,
                "numbershells": 1,
                "numbervertices": 42,
                "type": "Solid",
                "validity": false
            }],
            "type": "Building",
            "validity": false
        },
        {
            "errors_feature": null,
            "id": "b31be49e1-00ba-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "errors": [{
                    "code": 302,
                    "description": "SHELL_NOT_CLOSED",
                    "id": "",
                    "info": "Location hole: (84963.2, 447477, -0.11)",
                    "type": "Error"
                }],
                "id": "b31be49e1-00ba-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 33,
                "numbershells": 1,
                "numbervertices": 22,
                "type": "Solid",
                "validity": false
            }],
            "type": "Building",
            "validity": false
        },
        {
            "errors_feature": null,
            "id": "b31be49e6-00ba-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "errors": [{
                    "code": 302,
                    "description": "SHELL_NOT_CLOSED",
                    "id": "",
                    "info": "Location hole: (84965.5, 447486, -0.11)",
                    "type": "Error"
                }],
                "id": "b31be49e6-00ba-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 33,
                "numbershells": 1,
                "numbervertices": 22,
                "type": "Solid",
                "validity": false
            }],
            "type": "Building",
            "validity": false
        },
        {
            "errors_feature": null,
            "id": "b31be49eb-00ba-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "errors": [{
                    "code": 302,
                    "description": "SHELL_NOT_CLOSED",
                    "id": "",
                    "info": "Location hole: (84980.5, 447556, 0.16)",
                    "type": "Error"
                }],
                "id": "b31be49eb-00ba-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 46,
                "numbershells": 1,
                "numbervertices": 30,
                "type": "Solid",
                "validity": false
            }],
            "type": "Building",
            "validity": false
        },
        {
            "errors_feature": null,
            "id": "b31be49f0-00ba-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "errors": [{
                    "code": 302,
                    "description": "SHELL_NOT_CLOSED",
                    "id": "",
                    "info": "Location hole: (84976.7, 447560, 0.15)",
                    "type": "Error"
                }],
                "id": "b31be49f0-00ba-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 52,
                "numbershells": 1,
                "numbervertices": 35,
                "type": "Solid",
                "validity": false
            }],
            "type": "Building",
            "validity": false
        },
        {
            "errors_feature": null,
            "id": "b31be49f5-00ba-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "errors": [{
                    "code": 302,
                    "description": "SHELL_NOT_CLOSED",
                    "id": "",
                    "info": "Location hole: (84972, 447577, 0.17)",
                    "type": "Error"
                }],
                "id": "b31be49f5-00ba-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 93,
                "numbershells": 1,
                "numbervertices": 62,
                "type": "Solid",
                "validity": false
            }],
            "type": "Building",
            "validity": false
        },
        {
            "errors_feature": null,
            "id": "b31be49fa-00ba-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "errors": [{
                    "code": 302,
                    "description": "SHELL_NOT_CLOSED",
                    "id": "",
                    "info": "Location hole: (84956.6, 447571, 0.15)",
                    "type": "Error"
                }],
                "id": "b31be49fa-00ba-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 43,
                "numbershells": 1,
                "numbervertices": 28,
                "type": "Solid",
                "validity": false
            }],
            "type": "Building",
            "validity": false
        },
        {
            "errors_feature": null,
            "id": "b31c59cd7-00ba-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "errors": [{
                    "code": 302,
                    "description": "SHELL_NOT_CLOSED",
                    "id": "",
                    "info": "Location hole: (84970.8, 447548, 0.26)",
                    "type": "Error"
                }],
                "id": "b31c59cd7-00ba-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 21,
                "numbershells": 1,
                "numbervertices": 14,
                "type": "Solid",
                "validity": false
            }],
            "type": "Building",
            "validity": false
        },
        {
            "errors_feature": null,
            "id": "b31c59cdc-00ba-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "errors": [{
                    "code": 302,
                    "description": "SHELL_NOT_CLOSED",
                    "id": "",
                    "info": "Location hole: (84971.9, 447555, 0.12)",
                    "type": "Error"
                }],
                "id": "b31c59cdc-00ba-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 56,
                "numbershells": 1,
                "numbervertices": 38,
                "type": "Solid",
                "validity": false
            }],
            "type": "Building",
            "validity": false
        },
        {
            "errors_feature": null,
            "id": "b31c59cdf-00ba-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "errors": [{
                    "code": 302,
                    "description": "SHELL_NOT_CLOSED",
                    "id": "",
                    "info": "Location hole: (84950.5, 447566, 0.33)",
                    "type": "Error"
                }],
                "id": "b31c59cdf-00ba-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 19,
                "numbershells": 1,
                "numbervertices": 14,
                "type": "Solid",
                "validity": false
            }],
            "type": "Building",
            "validity": false
        },
        {
            "errors_feature": null,
            "id": "b31e18906-00ba-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "errors": [{
                    "code": 302,
                    "description": "SHELL_NOT_CLOSED",
                    "id": "",
                    "info": "Location hole: (84948.9, 447503, 0.02)",
                    "type": "Error"
                }],
                "id": "b31e18906-00ba-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 19,
                "numbershells": 1,
                "numbervertices": 14,
                "type": "Solid",
                "validity": false
            }],
            "type": "Building",
            "validity": false
        },
        {
            "errors_feature": null,
            "id": "b31e1890f-00ba-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "errors": [{
                    "code": 302,
                    "description": "SHELL_NOT_CLOSED",
                    "id": "",
                    "info": "Location hole: (84888.2, 447534, 0.21)",
                    "type": "Error"
                }],
                "id": "b31e1890f-00ba-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 10,
                "numbershells": 1,
                "numbervertices": 8,
                "type": "Solid",
                "validity": false
            }],
            "type": "Building",
            "validity": false
        },
        {
            "errors_feature": null,
            "id": "b31e18912-00ba-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "errors": [{
                    "code": 302,
                    "description": "SHELL_NOT_CLOSED",
                    "id": "",
                    "info": "Location hole: (84938.1, 447566, 0.34)",
                    "type": "Error"
                }],
                "id": "b31e18912-00ba-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 16,
                "numbershells": 1,
                "numbervertices": 12,
                "type": "Solid",
                "validity": false
            }],
            "type": "Building",
            "validity": false
        },
        {
            "errors_feature": null,
            "id": "b31e18915-00ba-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "errors": [{
                    "code": 302,
                    "description": "SHELL_NOT_CLOSED",
                    "id": "",
                    "info": "Location hole: (84931.5, 447561, 0.35)",
                    "type": "Error"
                }],
                "id": "b31e18915-00ba-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 10,
                "numbershells": 1,
                "numbervertices": 8,
                "type": "Solid",
                "validity": false
            }],
            "type": "Building",
            "validity": false
        },
        {
            "errors_feature": null,
            "id": "b31e18918-00ba-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "errors": [{
                    "code": 302,
                    "description": "SHELL_NOT_CLOSED",
                    "id": "",
                    "info": "Location hole: (84938.1, 447566, 0.35)",
                    "type": "Error"
                }],
                "id": "b31e18918-00ba-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 10,
                "numbershells": 1,
                "numbervertices": 8,
                "type": "Solid",
                "validity": false
            }],
            "type": "Building",
            "validity": false
        },
        {
            "errors_feature": null,
            "id": "b31e1b041-00ba-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "errors": [{
                    "code": 302,
                    "description": "SHELL_NOT_CLOSED",
                    "id": "",
                    "info": "Location hole: (84924.9, 447575, 0.41)",
                    "type": "Error"
                }],
                "id": "b31e1b041-00ba-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 14,
                "numbershells": 1,
                "numbervertices": 10,
                "type": "Solid",
                "validity": false
            }],
            "type": "Building",
            "validity": false
        },
        {
            "errors_feature": null,
            "id": "b31e1b046-00ba-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "errors": [{
                    "code": 302,
                    "description": "SHELL_NOT_CLOSED",
                    "id": "",
                    "info": "Location hole: (84927.3, 447577, 0.41)",
                    "type": "Error"
                }],
                "id": "b31e1b046-00ba-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 14,
                "numbershells": 1,
                "numbervertices": 10,
                "type": "Solid",
                "validity": false
            }],
            "type": "Building",
            "validity": false
        },
        {
            "errors_feature": null,
            "id": "b31e1b04b-00ba-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "errors": [{
                    "code": 302,
                    "description": "SHELL_NOT_CLOSED",
                    "id": "",
                    "info": "Location hole: (84929.9, 447579, 0.4)",
                    "type": "Error"
                }],
                "id": "b31e1b04b-00ba-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 18,
                "numbershells": 1,
                "numbervertices": 12,
                "type": "Solid",
                "validity": false
            }],
            "type": "Building",
            "validity": false
        },
        {
            "errors_feature": null,
            "id": "b31e1b050-00ba-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "errors": [{
                    "code": 302,
                    "description": "SHELL_NOT_CLOSED",
                    "id": "",
                    "info": "Location hole: (84932.9, 447585, 0.45)",
                    "type": "Error"
                }],
                "id": "b31e1b050-00ba-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 17,
                "numbershells": 1,
                "numbervertices": 12,
                "type": "Solid",
                "validity": false
            }],
            "type": "Building",
            "validity": false
        },
        {
            "errors_feature": null,
            "id": "b31e1b055-00ba-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "errors": [{
                    "code": 302,
                    "description": "SHELL_NOT_CLOSED",
                    "id": "",
                    "info": "Location hole: (84932.4, 447581, 0.39)",
                    "type": "Error"
                }],
                "id": "b31e1b055-00ba-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 22,
                "numbershells": 1,
                "numbervertices": 14,
                "type": "Solid",
                "validity": false
            }],
            "type": "Building",
            "validity": false
        },
        {
            "errors_feature": null,
            "id": "b31e1b05a-00ba-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "errors": [{
                    "code": 302,
                    "description": "SHELL_NOT_CLOSED",
                    "id": "",
                    "info": "Location hole: (84933, 447585, 0.4)",
                    "type": "Error"
                }],
                "id": "b31e1b05a-00ba-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 10,
                "numbershells": 1,
                "numbervertices": 8,
                "type": "Solid",
                "validity": false
            }],
            "type": "Building",
            "validity": false
        },
        {
            "errors_feature": null,
            "id": "b31e1b05d-00ba-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "errors": [{
                    "code": 302,
                    "description": "SHELL_NOT_CLOSED",
                    "id": "",
                    "info": "Location hole: (84937.7, 447588, 0.4)",
                    "type": "Error"
                }],
                "id": "b31e1b05d-00ba-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 10,
                "numbershells": 1,
                "numbervertices": 8,
                "type": "Solid",
                "validity": false
            }],
            "type": "Building",
            "validity": false
        },
        {
            "errors_feature": null,
            "id": "b31e1d770-00ba-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "errors": [{
                    "code": 302,
                    "description": "SHELL_NOT_CLOSED",
                    "id": "",
                    "info": "Location hole: (84924.9, 447556, 0.27)",
                    "type": "Error"
                }],
                "id": "b31e1d770-00ba-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 13,
                "numbershells": 1,
                "numbervertices": 10,
                "type": "Solid",
                "validity": false
            }],
            "type": "Building",
            "validity": false
        },
        {
            "errors_feature": null,
            "id": "b31e1d773-00ba-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "errors": [{
                    "code": 302,
                    "description": "SHELL_NOT_CLOSED",
                    "id": "",
                    "info": "Location hole: (84912.2, 447569, 0.43)",
                    "type": "Error"
                }],
                "id": "b31e1d773-00ba-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 16,
                "numbershells": 1,
                "numbervertices": 12,
                "type": "Solid",
                "validity": false
            }],
            "type": "Building",
            "validity": false
        },
        {
            "errors_feature": null,
            "id": "b31e1d778-00ba-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "errors": [{
                    "code": 302,
                    "description": "SHELL_NOT_CLOSED",
                    "id": "",
                    "info": "Location hole: (84922.4, 447574, 0.42)",
                    "type": "Error"
                }],
                "id": "b31e1d778-00ba-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 10,
                "numbershells": 1,
                "numbervertices": 8,
                "type": "Solid",
                "validity": false
            }],
            "type": "Building",
            "validity": false
        },
        {
            "errors_feature": null,
            "id": "b31e1d795-00ba-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "errors": [{
                    "code": 302,
                    "description": "SHELL_NOT_CLOSED",
                    "id": "",
                    "info": "Location hole: (84970.2, 447544, 0.24)",
                    "type": "Error"
                }],
                "id": "b31e1d795-00ba-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 14,
                "numbershells": 1,
                "numbervertices": 10,
                "type": "Solid",
                "validity": false
            }],
            "type": "Building",
            "validity": false
        },
        {
            "errors_feature": null,
            "id": "b31e1fea8-00ba-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "errors": [{
                    "code": 302,
                    "description": "SHELL_NOT_CLOSED",
                    "id": "",
                    "info": "Location hole: (84991.7, 447522, 0.19)",
                    "type": "Error"
                }],
                "id": "b31e1fea8-00ba-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 10,
                "numbershells": 1,
                "numbervertices": 8,
                "type": "Solid",
                "validity": false
            }],
            "type": "Building",
            "validity": false
        },
        {
            "errors_feature": null,
            "id": "b31e1feab-00ba-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "errors": [{
                    "code": 302,
                    "description": "SHELL_NOT_CLOSED",
                    "id": "",
                    "info": "Location hole: (84998, 447515, 0.2)",
                    "type": "Error"
                }],
                "id": "b31e1feab-00ba-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 10,
                "numbershells": 1,
                "numbervertices": 8,
                "type": "Solid",
                "validity": false
            }],
            "type": "Building",
            "validity": false
        },
        {
            "errors_feature": null,
            "id": "b31e1feae-00ba-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "errors": [{
                    "code": 302,
                    "description": "SHELL_NOT_CLOSED",
                    "id": "",
                    "info": "Location hole: (84985.3, 447532, 0.35)",
                    "type": "Error"
                }],
                "id": "b31e1feae-00ba-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 10,
                "numbershells": 1,
                "numbervertices": 8,
                "type": "Solid",
                "validity": false
            }],
            "type": "Building",
            "validity": false
        },
        {
            "errors_feature": null,
            "id": "b31e1feb1-00ba-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "errors": [{
                    "code": 302,
                    "description": "SHELL_NOT_CLOSED",
                    "id": "",
                    "info": "Location hole: (84967.5, 447497, 0.01)",
                    "type": "Error"
                }],
                "id": "b31e1feb1-00ba-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 19,
                "numbershells": 1,
                "numbervertices": 14,
                "type": "Solid",
                "validity": false
            }],
            "type": "Building",
            "validity": false
        },
        {
            "errors_feature": null,
            "id": "b31e1feb4-00ba-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "errors": [{
                    "code": 302,
                    "description": "SHELL_NOT_CLOSED",
                    "id": "",
                    "info": "Location hole: (84973.8, 447495, 0.01)",
                    "type": "Error"
                }],
                "id": "b31e1feb4-00ba-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 19,
                "numbershells": 1,
                "numbervertices": 14,
                "type": "Solid",
                "validity": false
            }],
            "type": "Building",
            "validity": false
        },
        {
            "errors_feature": null,
            "id": "b31e1feb7-00ba-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "errors": [{
                    "code": 302,
                    "description": "SHELL_NOT_CLOSED",
                    "id": "",
                    "info": "Location hole: (84979.4, 447490, 0.03)",
                    "type": "Error"
                }],
                "id": "b31e1feb7-00ba-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 22,
                "numbershells": 1,
                "numbervertices": 16,
                "type": "Solid",
                "validity": false
            }],
            "type": "Building",
            "validity": false
        },
        {
            "errors_feature": null,
            "id": "b31e1feba-00ba-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "errors": [{
                    "code": 302,
                    "description": "SHELL_NOT_CLOSED",
                    "id": "",
                    "info": "Location hole: (84961.3, 447499, 0.01)",
                    "type": "Error"
                }],
                "id": "b31e1feba-00ba-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 19,
                "numbershells": 1,
                "numbervertices": 14,
                "type": "Solid",
                "validity": false
            }],
            "type": "Building",
            "validity": false
        },
        {
            "errors_feature": null,
            "id": "b31e1febd-00ba-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "errors": [{
                    "code": 302,
                    "description": "SHELL_NOT_CLOSED",
                    "id": "",
                    "info": "Location hole: (84955.1, 447501, 0.01)",
                    "type": "Error"
                }],
                "id": "b31e1febd-00ba-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 19,
                "numbershells": 1,
                "numbervertices": 14,
                "type": "Solid",
                "validity": false
            }],
            "type": "Building",
            "validity": false
        },
        {
            "errors_feature": null,
            "id": "b41373904-00b4-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "b41373904-00b4-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 187,
                "numbervertices": 128,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "LandUse",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "b4137fbfc-00b4-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "b4137fbfc-00b4-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 23,
                "numbervertices": 25,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "LandUse",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "b4138231e-00b4-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "b4138231e-00b4-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 265,
                "numbervertices": 182,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "LandUse",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "b4138bef7-00b4-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "b4138bef7-00b4-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 586,
                "numbervertices": 359,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "LandUse",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "b413d2c2d-00b4-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "b413d2c2d-00b4-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 10,
                "numbervertices": 9,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "LandUse",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "b413e64b2-00b4-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "b413e64b2-00b4-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 21,
                "numbervertices": 14,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "LandUse",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "b413eb30b-00b4-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "b413eb30b-00b4-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 14,
                "numbervertices": 14,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "LandUse",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "b413feb75-00b4-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "b413feb75-00b4-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 115,
                "numbervertices": 74,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "LandUse",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "b41414b16-00b4-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "b41414b16-00b4-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 4,
                "numbervertices": 5,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "LandUse",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "b414283a4-00b4-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "b414283a4-00b4-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 3,
                "numbervertices": 5,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "LandUse",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "b4142aad2-00b4-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "b4142aad2-00b4-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 2,
                "numbervertices": 4,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "LandUse",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "b414394d7-00b4-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "b414394d7-00b4-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 2,
                "numbervertices": 4,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "LandUse",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "b414394ec-00b4-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "b414394ec-00b4-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 37,
                "numbervertices": 25,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "LandUse",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "b46c34501-2d29-11e6-9a38-393caa90be70",
            "primitives": [{
                "id": "b46c34501-2d29-11e6-9a38-393caa90be70(0)",
                "numberfaces": 12,
                "numbervertices": 11,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "PlantCover",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "b46c36c2c-2d29-11e6-9a38-393caa90be70",
            "primitives": [{
                "id": "b46c36c2c-2d29-11e6-9a38-393caa90be70(0)",
                "numberfaces": 1155,
                "numbervertices": 623,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "PlantCover",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "b46c407db-2d29-11e6-9a38-393caa90be70",
            "primitives": [{
                "id": "b46c407db-2d29-11e6-9a38-393caa90be70(0)",
                "numberfaces": 14,
                "numbervertices": 16,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "PlantCover",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "b46c42f03-2d29-11e6-9a38-393caa90be70",
            "primitives": [{
                "id": "b46c42f03-2d29-11e6-9a38-393caa90be70(0)",
                "numberfaces": 14,
                "numbervertices": 16,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "PlantCover",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "b491588b8-00b4-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "b491588b8-00b4-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 36,
                "numbervertices": 23,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "LandUse",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "b4915aff8-00b4-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "b4915aff8-00b4-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 63,
                "numbervertices": 48,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "LandUse",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "b4916e86b-00b4-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "b4916e86b-00b4-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 5,
                "numbervertices": 6,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "LandUse",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "b491736be-00b4-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "b491736be-00b4-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 11,
                "numbervertices": 13,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "LandUse",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "b4918966b-00b4-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "b4918966b-00b4-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 67,
                "numbervertices": 40,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "LandUse",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "b4918e3d0-00b4-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "b4918e3d0-00b4-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 14,
                "numbervertices": 10,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "LandUse",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "b4919a79b-00b4-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "b4919a79b-00b4-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 12,
                "numbervertices": 14,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "LandUse",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "b491d7828-00b4-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "b491d7828-00b4-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 4,
                "numbervertices": 5,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "LandUse",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "b4920103c-00b4-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "b4920103c-00b4-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 28,
                "numbervertices": 20,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "LandUse",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "b492196f9-00b4-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "b492196f9-00b4-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 148,
                "numbervertices": 89,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "LandUse",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "b49220b8c-00b4-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "b49220b8c-00b4-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 12,
                "numbervertices": 9,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "LandUse",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "b4922cf69-00b4-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "b4922cf69-00b4-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 48,
                "numbervertices": 32,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "LandUse",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "b4924564a-00b4-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "b4924564a-00b4-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 2,
                "numbervertices": 4,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "LandUse",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "b492762e2-00b4-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "b492762e2-00b4-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 6,
                "numbervertices": 7,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "LandUse",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "b492910e5-00b4-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "b492910e5-00b4-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 41,
                "numbervertices": 24,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "LandUse",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "b4929fae4-00b4-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "b4929fae4-00b4-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 4,
                "numbervertices": 6,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "LandUse",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "b492abedc-00b4-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "b492abedc-00b4-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 804,
                "numbervertices": 614,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "LandUse",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "b492c6bd0-00b4-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "b492c6bd0-00b4-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 2,
                "numbervertices": 4,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "LandUse",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "b492d56e7-00b4-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "b492d56e7-00b4-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 2,
                "numbervertices": 4,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "LandUse",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "b492e19ca-00b4-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "b492e19ca-00b4-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 69,
                "numbervertices": 41,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "LandUse",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "b492e6811-00b4-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "b492e6811-00b4-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 11,
                "numbervertices": 11,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "LandUse",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "b492f03ba-00b4-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "b492f03ba-00b4-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 54,
                "numbervertices": 34,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "LandUse",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "b49310031-00b4-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "b49310031-00b4-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 19,
                "numbervertices": 17,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "LandUse",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "b4931275f-00b4-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "b4931275f-00b4-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 15,
                "numbervertices": 14,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "LandUse",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "b4931c302-00b4-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "b4931c302-00b4-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 636,
                "numbervertices": 353,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "LandUse",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "b493349d4-00b4-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "b493349d4-00b4-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 16,
                "numbervertices": 13,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "LandUse",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "b49340dd5-00b4-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "b49340dd5-00b4-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 2,
                "numbervertices": 4,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "LandUse",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "b4935bab7-00b4-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "b4935bab7-00b4-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 34,
                "numbervertices": 23,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "LandUse",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "b49387a1d-00b4-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "b49387a1d-00b4-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 90,
                "numbervertices": 92,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "LandUse",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "b4939b281-00b4-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "b4939b281-00b4-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 8,
                "numbervertices": 7,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "LandUse",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "b69a8d7bc-2d38-11e6-9a38-393caa90be70",
            "primitives": [{
                "errors": [
                    {
                        "code": 102,
                        "description": "CONSECUTIVE_POINTS_SAME",
                        "id": "93",
                        "info": "",
                        "type": "Error"
                    },
                    {
                        "code": 102,
                        "description": "CONSECUTIVE_POINTS_SAME",
                        "id": "149",
                        "info": "",
                        "type": "Error"
                    }
                ],
                "id": "b69a8d7bc-2d38-11e6-9a38-393caa90be70(0)",
                "numberfaces": 302,
                "numbervertices": 302,
                "type": "MultiSurface",
                "validity": false
            }],
            "type": "WaterBody",
            "validity": false
        },
        {
            "errors_feature": null,
            "id": "b80066d8d-00c9-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "b80066d8d-00c9-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 2,
                "numbervertices": 4,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "Road",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "b8009a157-00c9-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "b8009a157-00c9-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 1,
                "numbervertices": 3,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "Road",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "b82575848-2d29-11e6-9a38-393caa90be70",
            "primitives": [{
                "id": "b82575848-2d29-11e6-9a38-393caa90be70(0)",
                "numberfaces": 327,
                "numbervertices": 207,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "LandUse",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "b8257ccdc-2d29-11e6-9a38-393caa90be70",
            "primitives": [{
                "id": "b8257ccdc-2d29-11e6-9a38-393caa90be70(0)",
                "numberfaces": 16,
                "numbervertices": 13,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "LandUse",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "b82590617-2d29-11e6-9a38-393caa90be70",
            "primitives": [{
                "id": "b82590617-2d29-11e6-9a38-393caa90be70(0)",
                "numberfaces": 139,
                "numbervertices": 138,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "LandUse",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "b825a1738-2d29-11e6-9a38-393caa90be70",
            "primitives": [{
                "id": "b825a1738-2d29-11e6-9a38-393caa90be70(0)",
                "numberfaces": 10,
                "numbervertices": 10,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "LandUse",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "b86c25248-00c8-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "b86c25248-00c8-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 126,
                "numbervertices": 88,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "GenericCityObject",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "b86c2a086-00c8-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "b86c2a086-00c8-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 2,
                "numbervertices": 4,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "GenericCityObject",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "b86c538a4-00c8-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "b86c538a4-00c8-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 5,
                "numbervertices": 7,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "GenericCityObject",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "b86c5adfd-00c8-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "b86c5adfd-00c8-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 15,
                "numbervertices": 13,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "GenericCityObject",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "b86c5ae06-00c8-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "b86c5ae06-00c8-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 6,
                "numbervertices": 7,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "GenericCityObject",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "b86c5d51d-00c8-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "b86c5d51d-00c8-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 2,
                "numbervertices": 4,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "GenericCityObject",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "b86c89463-00c8-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "b86c89463-00c8-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 25,
                "numbervertices": 21,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "GenericCityObject",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "b8e220996-00b3-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "b8e220996-00b3-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 40,
                "numbervertices": 25,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "PlantCover",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "b8e220999-00b3-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "b8e220999-00b3-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 37,
                "numbervertices": 23,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "PlantCover",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "b8e2209a5-00b3-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "b8e2209a5-00b3-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 92,
                "numbervertices": 93,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "PlantCover",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "b8e22f3bc-00b3-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "b8e22f3bc-00b3-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 10,
                "numbervertices": 8,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "PlantCover",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "b8e23693d-00b3-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "b8e23693d-00b3-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 50,
                "numbervertices": 28,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "PlantCover",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "b8e23ddc7-00b3-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "b8e23ddc7-00b3-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 16,
                "numbervertices": 12,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "PlantCover",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "b8e24c8ff-00b3-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "b8e24c8ff-00b3-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 36,
                "numbervertices": 21,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "PlantCover",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "b8e253d86-00b3-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "b8e253d86-00b3-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 88,
                "numbervertices": 47,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "PlantCover",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "b8e26eb7a-00b3-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "b8e26eb7a-00b3-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 21,
                "numbervertices": 14,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "PlantCover",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "b8e2823ff-00b3-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "b8e2823ff-00b3-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 41,
                "numbervertices": 24,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "PlantCover",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "b8e28998c-00b3-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "b8e28998c-00b3-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 83,
                "numbervertices": 45,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "PlantCover",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "b8e290e1c-00b3-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "b8e290e1c-00b3-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 18,
                "numbervertices": 20,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "PlantCover",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "b8e29d205-00b3-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "b8e29d205-00b3-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 52,
                "numbervertices": 31,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "PlantCover",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "b8e2a94ee-00b3-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "b8e2a94ee-00b3-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 104,
                "numbervertices": 99,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "PlantCover",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "b8e2dc9d5-00b3-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "b8e2dc9d5-00b3-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 36,
                "numbervertices": 25,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "PlantCover",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "b8e2e8cb2-00b3-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "b8e2e8cb2-00b3-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 88,
                "numbervertices": 47,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "PlantCover",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "b8e2f4faa-00b3-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "b8e2f4faa-00b3-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 94,
                "numbervertices": 51,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "PlantCover",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "b8e3061e0-00b3-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "b8e3061e0-00b3-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 2,
                "numbervertices": 4,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "PlantCover",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "b8e3061ec-00b3-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "b8e3061ec-00b3-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 92,
                "numbervertices": 92,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "PlantCover",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "b8e319a5c-00b3-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "b8e319a5c-00b3-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 12,
                "numbervertices": 9,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "PlantCover",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "b8e328488-00b3-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "b8e328488-00b3-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 188,
                "numbervertices": 99,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "PlantCover",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "b8e33202e-00b3-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "b8e33202e-00b3-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 276,
                "numbervertices": 149,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "PlantCover",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "b8e336e96-00b3-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "b8e336e96-00b3-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 26,
                "numbervertices": 16,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "PlantCover",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "b8e33bd04-00b3-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "b8e33bd04-00b3-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 42,
                "numbervertices": 25,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "PlantCover",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "b8e34317c-00b3-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "b8e34317c-00b3-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 54,
                "numbervertices": 30,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "PlantCover",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "b8e347fd5-00b3-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "b8e347fd5-00b3-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 18,
                "numbervertices": 12,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "PlantCover",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "b8e34ce31-00b3-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "b8e34ce31-00b3-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 14,
                "numbervertices": 10,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "PlantCover",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "b8e362de1-00b3-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "b8e362de1-00b3-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 239,
                "numbervertices": 126,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "PlantCover",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "b8e36a37d-00b3-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "b8e36a37d-00b3-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 106,
                "numbervertices": 100,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "PlantCover",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "b8e3717f5-00b3-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "b8e3717f5-00b3-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 200,
                "numbervertices": 107,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "PlantCover",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "b8e37180a-00b3-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "b8e37180a-00b3-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 71,
                "numbervertices": 43,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "PlantCover",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "b8e39d73d-00b3-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "b8e39d73d-00b3-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 71,
                "numbervertices": 39,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "PlantCover",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "b8e3a4cc7-00b3-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "b8e3a4cc7-00b3-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 32,
                "numbervertices": 19,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "PlantCover",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "b8e3ae885-00b3-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "b8e3ae885-00b3-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 104,
                "numbervertices": 98,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "PlantCover",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "b8e3bd29c-00b3-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "b8e3bd29c-00b3-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 46,
                "numbervertices": 29,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "PlantCover",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "b8e3c6f5d-00b3-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "b8e3c6f5d-00b3-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 116,
                "numbervertices": 63,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "PlantCover",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "b8e3c6f63-00b3-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "b8e3c6f63-00b3-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 98,
                "numbervertices": 52,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "PlantCover",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "b8e3d0b1b-00b3-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "b8e3d0b1b-00b3-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 38,
                "numbervertices": 25,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "PlantCover",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "b8e3d3258-00b3-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "b8e3d3258-00b3-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 10,
                "numbervertices": 9,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "PlantCover",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "b8e3d5974-00b3-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "b8e3d5974-00b3-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 10,
                "numbervertices": 8,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "PlantCover",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "b8e3f2ebd-00b3-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "b8e3f2ebd-00b3-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 60,
                "numbervertices": 33,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "PlantCover",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "b8e404005-00b3-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "b8e404005-00b3-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 80,
                "numbervertices": 44,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "PlantCover",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "b8e404008-00b3-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "b8e404008-00b3-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 5,
                "numbervertices": 6,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "PlantCover",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "b8e415141-00b3-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "b8e415141-00b3-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 24,
                "numbervertices": 15,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "PlantCover",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "b8e41ee11-00b3-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "b8e41ee11-00b3-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 4,
                "numbervertices": 5,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "PlantCover",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "b8e4289b7-00b3-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "b8e4289b7-00b3-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 22,
                "numbervertices": 14,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "PlantCover",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "b8e43e94c-00b3-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "b8e43e94c-00b3-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 198,
                "numbervertices": 197,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "PlantCover",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "b8e44d366-00b3-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "b8e44d366-00b3-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 781,
                "numbervertices": 413,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "PlantCover",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "b8e44faa0-00b3-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "b8e44faa0-00b3-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 2,
                "numbervertices": 4,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "PlantCover",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "b8e4548ff-00b3-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "b8e4548ff-00b3-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 8,
                "numbervertices": 7,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "PlantCover",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "b8e45490b-00b3-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "b8e45490b-00b3-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 101,
                "numbervertices": 54,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "PlantCover",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "b8e46330a-00b3-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "b8e46330a-00b3-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 127,
                "numbervertices": 67,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "PlantCover",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "b8e47e113-00b3-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "b8e47e113-00b3-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 151,
                "numbervertices": 79,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "PlantCover",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "b8e4aa043-00b3-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "b8e4aa043-00b3-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 170,
                "numbervertices": 90,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "PlantCover",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "b8e4b15d3-00b3-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "b8e4b15d3-00b3-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 86,
                "numbervertices": 46,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "PlantCover",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "b8e4bd8b0-00b3-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "b8e4bd8b0-00b3-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 54,
                "numbervertices": 53,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "PlantCover",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "b8e4ee645-00b3-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "b8e4ee645-00b3-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 12,
                "numbervertices": 9,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "PlantCover",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "b8e4fa919-00b3-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "b8e4fa919-00b3-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 110,
                "numbervertices": 59,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "PlantCover",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "b8e506d0e-00b3-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "b8e506d0e-00b3-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 46,
                "numbervertices": 27,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "PlantCover",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "b8e51a58d-00b3-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "b8e51a58d-00b3-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 52,
                "numbervertices": 50,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "PlantCover",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "b8e528fa4-00b3-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "b8e528fa4-00b3-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 102,
                "numbervertices": 98,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "PlantCover",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "b8e530428-00b3-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "b8e530428-00b3-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 27,
                "numbervertices": 17,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "PlantCover",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "b8e54165e-00b3-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "b8e54165e-00b3-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 50,
                "numbervertices": 29,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "PlantCover",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "b8e5527a9-00b3-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "b8e5527a9-00b3-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 62,
                "numbervertices": 34,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "PlantCover",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "b8e55c364-00b3-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "b8e55c364-00b3-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 12,
                "numbervertices": 9,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "PlantCover",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "b8e55ea86-00b3-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "b8e55ea86-00b3-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 10,
                "numbervertices": 8,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "PlantCover",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "b8e566010-00b3-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "b8e566010-00b3-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 18,
                "numbervertices": 12,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "PlantCover",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "b8e580e0a-00b3-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "b8e580e0a-00b3-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 141,
                "numbervertices": 74,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "PlantCover",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "b8e580e10-00b3-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "b8e580e10-00b3-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 100,
                "numbervertices": 97,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "PlantCover",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "b8e58829a-00b3-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "b8e58829a-00b3-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 18,
                "numbervertices": 12,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "PlantCover",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "b8e58d102-00b3-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "b8e58d102-00b3-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 39,
                "numbervertices": 23,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "PlantCover",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "b8e5993eb-00b3-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "b8e5993eb-00b3-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 42,
                "numbervertices": 24,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "PlantCover",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "b8e5aa630-00b3-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "b8e5aa630-00b3-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 124,
                "numbervertices": 67,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "PlantCover",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "b8e5b9032-00b3-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "b8e5b9032-00b3-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 46,
                "numbervertices": 27,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "PlantCover",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "b8e5bb778-00b3-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "b8e5bb778-00b3-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 6,
                "numbervertices": 6,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "PlantCover",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "b8e5cc8bd-00b3-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "b8e5cc8bd-00b3-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 76,
                "numbervertices": 41,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "PlantCover",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "b8e5e0130-00b3-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "b8e5e0130-00b3-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 66,
                "numbervertices": 37,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "PlantCover",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "b95c79603-00b3-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "b95c79603-00b3-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 166,
                "numbervertices": 87,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "PlantCover",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "b95c8a81e-00b3-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "b95c8a81e-00b3-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 14,
                "numbervertices": 10,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "PlantCover",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "b95c9e082-00b3-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "b95c9e082-00b3-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 8,
                "numbervertices": 7,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "PlantCover",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "b95cb8e76-00b3-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "b95cb8e76-00b3-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 6,
                "numbervertices": 6,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "PlantCover",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "b95cc2a0d-00b3-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "b95cc2a0d-00b3-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 19,
                "numbervertices": 13,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "PlantCover",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "b95cc786f-00b3-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "b95cc786f-00b3-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 99,
                "numbervertices": 53,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "PlantCover",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "b95cc9f9d-00b3-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "b95cc9f9d-00b3-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 246,
                "numbervertices": 130,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "PlantCover",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "b95ce263c-00b3-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "b95ce263c-00b3-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 112,
                "numbervertices": 59,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "PlantCover",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "b95cfd40c-00b3-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "b95cfd40c-00b3-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 329,
                "numbervertices": 172,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "PlantCover",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "b95d13392-00b3-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "b95d13392-00b3-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 141,
                "numbervertices": 74,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "PlantCover",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "b95d15abd-00b3-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "b95d15abd-00b3-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 16,
                "numbervertices": 11,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "PlantCover",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "b95d3cb76-00b3-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "b95d3cb76-00b3-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 34,
                "numbervertices": 21,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "PlantCover",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "b95d48e56-00b3-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "b95d48e56-00b3-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 45,
                "numbervertices": 26,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "PlantCover",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "b95d5a08f-00b3-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "b95d5a08f-00b3-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 38,
                "numbervertices": 28,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "PlantCover",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "b95d5c6c6-00b3-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "b95d5c6c6-00b3-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 27,
                "numbervertices": 17,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "PlantCover",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "b95d97113-00b3-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "b95d97113-00b3-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 40,
                "numbervertices": 27,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "PlantCover",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "b95da0cd1-00b3-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "b95da0cd1-00b3-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 85,
                "numbervertices": 46,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "PlantCover",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "b95da0cdd-00b3-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "b95da0cdd-00b3-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 72,
                "numbervertices": 39,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "PlantCover",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "b95da8252-00b3-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "b95da8252-00b3-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 60,
                "numbervertices": 33,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "PlantCover",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "b95dca4f1-00b3-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "b95dca4f1-00b3-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 37,
                "numbervertices": 22,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "PlantCover",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "b95de048f-00b3-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "b95de048f-00b3-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 57,
                "numbervertices": 32,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "PlantCover",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "b95df8b58-00b3-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "b95df8b58-00b3-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 50,
                "numbervertices": 28,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "PlantCover",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "b95e04e3b-00b3-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "b95e04e3b-00b3-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 69,
                "numbervertices": 38,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "PlantCover",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "b95e1395b-00b3-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "b95e1395b-00b3-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 42,
                "numbervertices": 25,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "PlantCover",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "b95e24a9a-00b3-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "b95e24a9a-00b3-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 82,
                "numbervertices": 45,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "PlantCover",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "b95e5572f-00b3-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "b95e5572f-00b3-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 10,
                "numbervertices": 8,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "PlantCover",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "b95e5ccd1-00b3-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "b95e5ccd1-00b3-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 107,
                "numbervertices": 57,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "PlantCover",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "b95e6b6dc-00b3-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "b95e6b6dc-00b3-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 16,
                "numbervertices": 11,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "PlantCover",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "b95e88c0d-00b3-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "b95e88c0d-00b3-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 32,
                "numbervertices": 20,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "PlantCover",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "b95ea39ef-00b3-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "b95ea39ef-00b3-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 8,
                "numbervertices": 7,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "PlantCover",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "b95ea6026-00b3-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "b95ea6026-00b3-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 52,
                "numbervertices": 29,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "PlantCover",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "b95eafcdb-00b3-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "b95eafcdb-00b3-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 10,
                "numbervertices": 8,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "PlantCover",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "b95ec5c64-00b3-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "b95ec5c64-00b3-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 30,
                "numbervertices": 18,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "PlantCover",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "b95ecd1fd-00b3-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "b95ecd1fd-00b3-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 54,
                "numbervertices": 30,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "PlantCover",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "b95ecf925-00b3-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "b95ecf925-00b3-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 46,
                "numbervertices": 26,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "PlantCover",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "b95ed1f59-00b3-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "b95ed1f59-00b3-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 28,
                "numbervertices": 17,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "PlantCover",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "b95ed4687-00b3-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "b95ed4687-00b3-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 12,
                "numbervertices": 9,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "PlantCover",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "b981072fa-00c9-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "b981072fa-00c9-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 3,
                "numbervertices": 5,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "Road",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "b9813a745-00c9-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "b9813a745-00c9-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 5,
                "numbervertices": 7,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "Road",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "b9813ce67-00c9-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "b9813ce67-00c9-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 25,
                "numbervertices": 27,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "Road",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "b9816dbab-00c9-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "b9816dbab-00c9-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 93,
                "numbervertices": 95,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "Road",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "b9817c598-00c9-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "b9817c598-00c9-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 16,
                "numbervertices": 18,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "Road",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "b981a0ff9-00c9-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "b981a0ff9-00c9-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 48,
                "numbervertices": 50,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "Road",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "b981aabab-00c9-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "b981aabab-00c9-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 193,
                "numbervertices": 185,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "Road",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "b981af9f2-00c9-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "b981af9f2-00c9-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 14,
                "numbervertices": 16,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "Road",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "b981ecb10-00c9-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "b981ecb10-00c9-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 2,
                "numbervertices": 4,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "Road",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "b981f8dcc-00c9-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "b981f8dcc-00c9-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 23,
                "numbervertices": 25,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "Road",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "b9821d845-00c9-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "b9821d845-00c9-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 6,
                "numbervertices": 8,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "Road",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "b98229afb-00c9-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "b98229afb-00c9-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 96,
                "numbervertices": 97,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "Road",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "b9824be2e-00c9-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "b9824be2e-00c9-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 61,
                "numbervertices": 61,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "Road",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "b98250c84-00c9-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "b98250c84-00c9-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 52,
                "numbervertices": 54,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "Road",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "b98272edb-00c9-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "b98272edb-00c9-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 63,
                "numbervertices": 61,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "Road",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "b9827560c-00c9-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "b9827560c-00c9-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 4,
                "numbervertices": 6,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "Road",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "b98295220-00c9-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "b98295220-00c9-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 2,
                "numbervertices": 4,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "Road",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "b9829794e-00c9-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "b9829794e-00c9-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 9,
                "numbervertices": 11,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "Road",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "b982f6cae-00c9-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "b982f6cae-00c9-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 2,
                "numbervertices": 4,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "Road",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "b98322b9f-00c9-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "b98322b9f-00c9-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 2,
                "numbervertices": 4,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "Road",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "b98349d40-00c9-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "b98349d40-00c9-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 5,
                "numbervertices": 7,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "Road",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "b9837d0a9-00c9-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "b9837d0a9-00c9-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 46,
                "numbervertices": 48,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "Road",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "b983909fb-00c9-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "b983909fb-00c9-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 89,
                "numbervertices": 91,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "Road",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "b983a1b0d-00c9-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "b983a1b0d-00c9-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 647,
                "numbervertices": 641,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "Road",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "b983e1262-00c9-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "b983e1262-00c9-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 3,
                "numbervertices": 5,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "Road",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "b983ed62d-00c9-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "b983ed62d-00c9-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 2,
                "numbervertices": 4,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "Road",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "b983f98fe-00c9-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "b983f98fe-00c9-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 14,
                "numbervertices": 16,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "Road",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "b984083fa-00c9-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "b984083fa-00c9-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 2,
                "numbervertices": 4,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "Road",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "b984231bb-00c9-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "b984231bb-00c9-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 9,
                "numbervertices": 11,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "Road",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "b984231ca-00c9-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "b984231ca-00c9-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 145,
                "numbervertices": 147,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "Road",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "b9845daba-00c9-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "b9845daba-00c9-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 5,
                "numbervertices": 7,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "Road",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "b98462904-00c9-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "b98462904-00c9-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 3,
                "numbervertices": 5,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "Road",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "b9847615f-00c9-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "b9847615f-00c9-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 2,
                "numbervertices": 4,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "Road",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "b98484b4f-00c9-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "b98484b4f-00c9-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 2,
                "numbervertices": 4,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "Road",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "b98490f1a-00c9-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "b98490f1a-00c9-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 2,
                "numbervertices": 4,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "Road",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "b984abcea-00c9-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "b984abcea-00c9-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 61,
                "numbervertices": 63,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "Road",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "b984eb436-00c9-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "b984eb436-00c9-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 2,
                "numbervertices": 4,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "Road",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "b98525e11-00c9-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "b98525e11-00c9-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 2,
                "numbervertices": 4,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "Road",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "b98554433-00c9-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "b98554433-00c9-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 4,
                "numbervertices": 6,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "Road",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "b98556b73-00c9-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "b98556b73-00c9-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 3,
                "numbervertices": 5,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "Road",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "b9856f206-00c9-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "b9856f206-00c9-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 2,
                "numbervertices": 4,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "Road",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "b985fcb64-00c9-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "b985fcb64-00c9-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 5,
                "numbervertices": 7,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "Road",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "b9f4dc812-00c9-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "b9f4dc812-00c9-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 17,
                "numbervertices": 17,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "Road",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "b9f4f9d10-00c9-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "b9f4f9d10-00c9-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 2,
                "numbervertices": 4,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "Road",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "b9f5123ac-00c9-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "b9f5123ac-00c9-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 63,
                "numbervertices": 65,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "Road",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "b9f531ed5-00c9-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "b9f531ed5-00c9-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 24,
                "numbervertices": 26,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "Road",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "b9f5409d1-00c9-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "b9f5409d1-00c9-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 2,
                "numbervertices": 4,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "Road",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "b9f556936-00c9-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "b9f556936-00c9-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 23,
                "numbervertices": 25,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "Road",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "b9f565329-00c9-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "b9f565329-00c9-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 6,
                "numbervertices": 8,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "Road",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "b9f56c89e-00c9-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "b9f56c89e-00c9-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 2,
                "numbervertices": 4,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "Road",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "b9f56efd5-00c9-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "b9f56efd5-00c9-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 2,
                "numbervertices": 4,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "Road",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "b9f576553-00c9-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "b9f576553-00c9-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 2,
                "numbervertices": 4,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "Road",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "b9f615017-00c9-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "b9f615017-00c9-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 125,
                "numbervertices": 125,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "Road",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "b9f68f153-00c9-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "b9f68f153-00c9-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 328,
                "numbervertices": 320,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "Road",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "b9f6bb041-00c9-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "b9f6bb041-00c9-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 8,
                "numbervertices": 10,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "Road",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "b9f6bb053-00c9-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "b9f6bb053-00c9-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 20,
                "numbervertices": 22,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "Road",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "b9f6c25cb-00c9-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "b9f6c25cb-00c9-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 15,
                "numbervertices": 13,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "Road",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "b9f6cc165-00c9-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "b9f6cc165-00c9-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 46,
                "numbervertices": 48,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "Road",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "b9f6e9666-00c9-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "b9f6e9666-00c9-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 2,
                "numbervertices": 4,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "Road",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "b9f6e966f-00c9-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "b9f6e966f-00c9-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 2,
                "numbervertices": 4,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "Road",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "b9f6fcec4-00c9-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "b9f6fcec4-00c9-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 20,
                "numbervertices": 22,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "Road",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "b9f70e0dc-00c9-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "b9f70e0dc-00c9-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 2,
                "numbervertices": 4,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "Road",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "b9f71cae4-00c9-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "b9f71cae4-00c9-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 106,
                "numbervertices": 108,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "Road",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "b9f724050-00c9-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "errors": [
                    {
                        "code": 104,
                        "description": "RING_SELF_INTERSECTION",
                        "id": "40",
                        "info": " outer ring (a triangle) is collapsed to a line",
                        "type": "Error"
                    },
                    {
                        "code": 104,
                        "description": "RING_SELF_INTERSECTION",
                        "id": "41",
                        "info": " outer ring (a triangle) is collapsed to a line",
                        "type": "Error"
                    }
                ],
                "id": "b9f724050-00c9-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 63,
                "numbervertices": 65,
                "type": "MultiSurface",
                "validity": false
            }],
            "type": "Road",
            "validity": false
        },
        {
            "errors_feature": null,
            "id": "b9f72b4d4-00c9-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "b9f72b4d4-00c9-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 2,
                "numbervertices": 4,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "Road",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "b9f732a64-00c9-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "b9f732a64-00c9-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 34,
                "numbervertices": 32,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "Road",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "b9f76379f-00c9-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "b9f76379f-00c9-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 10,
                "numbervertices": 12,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "Road",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "ba2bf3d0a-00c8-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "ba2bf3d0a-00c8-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 6,
                "numbervertices": 8,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "GenericCityObject",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "ba2c139a9-00c8-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "ba2c139a9-00c8-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 5,
                "numbervertices": 7,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "GenericCityObject",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "ba2c139ab-00c8-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "ba2c139ab-00c8-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 6,
                "numbervertices": 7,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "GenericCityObject",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "ba2c1d52d-00c8-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "ba2c1d52d-00c8-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 2,
                "numbervertices": 4,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "GenericCityObject",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "ba2c22373-00c8-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "ba2c22373-00c8-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 16,
                "numbervertices": 16,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "GenericCityObject",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "ba2c2bff4-00c8-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "ba2c2bff4-00c8-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 17,
                "numbervertices": 15,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "GenericCityObject",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "ba2c46d5d-00c8-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "ba2c46d5d-00c8-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 114,
                "numbervertices": 98,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "GenericCityObject",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "ba2c5a65f-00c8-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "ba2c5a65f-00c8-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 57,
                "numbervertices": 41,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "GenericCityObject",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "ba2c8da19-00c8-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "ba2c8da19-00c8-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 46,
                "numbervertices": 34,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "GenericCityObject",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "ba2c92854-00c8-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "ba2c92854-00c8-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 118,
                "numbervertices": 85,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "GenericCityObject",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "ba2ca6162-00c8-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "ba2ca6162-00c8-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 50,
                "numbervertices": 40,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "GenericCityObject",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "ba2cbe7b0-00c8-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "ba2cbe7b0-00c8-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 2,
                "numbervertices": 4,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "GenericCityObject",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "ba2cc0ecf-00c8-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "ba2cc0ecf-00c8-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 28,
                "numbervertices": 22,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "GenericCityObject",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "ba2cd20b1-00c8-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "ba2cd20b1-00c8-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 10,
                "numbervertices": 8,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "GenericCityObject",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "ba2cd9515-00c8-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "ba2cd9515-00c8-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 5,
                "numbervertices": 7,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "GenericCityObject",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "ba2cef542-00c8-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "ba2cef542-00c8-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 2,
                "numbervertices": 4,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "GenericCityObject",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "ba2d1b3a6-00c8-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "ba2d1b3a6-00c8-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 53,
                "numbervertices": 38,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "GenericCityObject",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "ba2d44bdf-00c8-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "ba2d44bdf-00c8-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 14,
                "numbervertices": 13,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "GenericCityObject",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "ba2d5fa48-00c8-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "ba2d5fa48-00c8-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 124,
                "numbervertices": 86,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "GenericCityObject",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "ba2d7ced0-00c8-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "ba2d7ced0-00c8-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 6,
                "numbervertices": 6,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "GenericCityObject",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "ba2d8b896-00c8-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "ba2d8b896-00c8-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 6,
                "numbervertices": 6,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "GenericCityObject",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "ba2dc146d-00c8-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "ba2dc146d-00c8-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 473,
                "numbervertices": 326,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "GenericCityObject",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "ba2de5e68-00c8-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "ba2de5e68-00c8-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 9,
                "numbervertices": 10,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "GenericCityObject",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "ba2defaf4-00c8-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "ba2defaf4-00c8-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 2,
                "numbervertices": 4,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "GenericCityObject",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "ba2dfe4b4-00c8-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "ba2dfe4b4-00c8-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 243,
                "numbervertices": 231,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "GenericCityObject",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "ba2e00bdc-00c8-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "ba2e00bdc-00c8-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 111,
                "numbervertices": 82,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "GenericCityObject",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "ba2e1e06f-00c8-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "ba2e1e06f-00c8-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 2,
                "numbervertices": 4,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "GenericCityObject",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "ba2e4514a-00c8-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "ba2e4514a-00c8-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 2,
                "numbervertices": 4,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "GenericCityObject",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "ba2e4c69a-00c8-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "ba2e4c69a-00c8-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 14,
                "numbervertices": 12,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "GenericCityObject",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "ba2e5d871-00c8-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "ba2e5d871-00c8-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 13,
                "numbervertices": 12,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "GenericCityObject",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "ba2e674f4-00c8-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "ba2e674f4-00c8-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 6,
                "numbervertices": 6,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "GenericCityObject",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "ba2e7acf3-00c8-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "ba2e7acf3-00c8-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 22,
                "numbervertices": 19,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "GenericCityObject",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "ba2e8e5f6-00c8-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "ba2e8e5f6-00c8-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 2,
                "numbervertices": 4,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "GenericCityObject",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "ba2ea451d-00c8-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "ba2ea451d-00c8-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 10,
                "numbervertices": 10,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "GenericCityObject",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "ba2ea9355-00c8-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "ba2ea9355-00c8-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 12,
                "numbervertices": 11,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "GenericCityObject",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "ba2ea9356-00c8-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "ba2ea9356-00c8-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 6,
                "numbervertices": 8,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "GenericCityObject",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "ba2ed2b76-00c8-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "ba2ed2b76-00c8-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 10,
                "numbervertices": 12,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "GenericCityObject",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "ba2ed529d-00c8-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "ba2ed529d-00c8-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 96,
                "numbervertices": 75,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "GenericCityObject",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "ba2ee8aa2-00c8-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "ba2ee8aa2-00c8-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 2,
                "numbervertices": 4,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "GenericCityObject",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "ba2eed8e4-00c8-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "ba2eed8e4-00c8-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 3,
                "numbervertices": 5,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "GenericCityObject",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "ba2f011e8-00c8-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "ba2f011e8-00c8-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 2,
                "numbervertices": 4,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "GenericCityObject",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "ba2f0601b-00c8-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "ba2f0601b-00c8-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 13,
                "numbervertices": 11,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "GenericCityObject",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "ba2f149e9-00c8-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "ba2f149e9-00c8-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 20,
                "numbervertices": 16,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "GenericCityObject",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "ba2f1bf47-00c8-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "ba2f1bf47-00c8-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 292,
                "numbervertices": 202,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "GenericCityObject",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "baeb0d610-00c9-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "baeb0d610-00c9-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 2,
                "numbervertices": 4,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "Road",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "baeb14b79-00c9-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "baeb14b79-00c9-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 2,
                "numbervertices": 4,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "Road",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "baeb4316e-00c9-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "baeb4316e-00c9-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 8,
                "numbervertices": 8,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "Road",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "baeb71848-00c9-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "baeb71848-00c9-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 12,
                "numbervertices": 14,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "Road",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "baeb96194-00c9-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "baeb96194-00c9-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 3,
                "numbervertices": 5,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "Road",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "baebac1f9-00c9-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "baebac1f9-00c9-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 40,
                "numbervertices": 42,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "Road",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "baebae90f-00c9-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "baebae90f-00c9-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 74,
                "numbervertices": 76,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "Road",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "baebae918-00c9-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "baebae918-00c9-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 2,
                "numbervertices": 4,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "Road",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "baebc6f96-00c9-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "baebc6f96-00c9-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 2,
                "numbervertices": 4,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "Road",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "baebf073e-00c9-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "baebf073e-00c9-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 10,
                "numbervertices": 12,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "Road",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "baec01841-00c9-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "baec01841-00c9-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 2,
                "numbervertices": 4,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "Road",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "baec0184a-00c9-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "baec0184a-00c9-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 55,
                "numbervertices": 53,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "Road",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "baec2b0ec-00c9-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "baec2b0ec-00c9-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 3,
                "numbervertices": 5,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "Road",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "baec2ff3f-00c9-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "baec2ff3f-00c9-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 2,
                "numbervertices": 4,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "Road",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "baec32664-00c9-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "baec32664-00c9-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 6,
                "numbervertices": 7,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "Road",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "baec76b97-00c9-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "baec76b97-00c9-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 4,
                "numbervertices": 6,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "Road",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "baec8f206-00c9-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "baec8f206-00c9-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 2,
                "numbervertices": 4,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "Road",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "baec91931-00c9-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "baec91931-00c9-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 2,
                "numbervertices": 4,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "Road",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "baecc264e-00c9-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "baecc264e-00c9-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 10,
                "numbervertices": 10,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "Road",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "baecdd400-00c9-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "baecdd400-00c9-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 20,
                "numbervertices": 22,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "Road",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "baece497b-00c9-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "baece497b-00c9-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 11,
                "numbervertices": 13,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "Road",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "baecfa8c8-00c9-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "baecfa8c8-00c9-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 2,
                "numbervertices": 4,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "Road",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "baed01e43-00c9-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "baed01e43-00c9-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 16,
                "numbervertices": 18,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "Road",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "baed35282-00c9-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "baed35282-00c9-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 2,
                "numbervertices": 4,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "Road",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "baed6123a-00c9-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "baed6123a-00c9-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 14,
                "numbervertices": 12,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "Road",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "baed74a77-00c9-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "baed74a77-00c9-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 2,
                "numbervertices": 4,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "Road",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "baed8a9c4-00c9-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "baed8a9c4-00c9-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 14,
                "numbervertices": 16,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "Road",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "baed8f811-00c9-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "baed8f811-00c9-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 8,
                "numbervertices": 8,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "Road",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "baedc2c50-00c9-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "baedc2c50-00c9-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 2,
                "numbervertices": 4,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "Road",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "baedd648a-00c9-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "baedd648a-00c9-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 10,
                "numbervertices": 12,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "Road",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "baee30a16-00c9-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "baee30a16-00c9-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 16,
                "numbervertices": 14,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "Road",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "baee50621-00c9-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "baee50621-00c9-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 8,
                "numbervertices": 8,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "Road",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "baee6656b-00c9-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "baee6656b-00c9-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 3,
                "numbervertices": 5,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "Road",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "baee70214-00c9-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "baee70214-00c9-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 2,
                "numbervertices": 4,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "Road",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "baee86179-00c9-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "baee86179-00c9-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 2,
                "numbervertices": 4,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "Road",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "baeeea27e-00c9-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "baeeea27e-00c9-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 2,
                "numbervertices": 4,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "Road",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "baef24c20-00c9-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "baef24c20-00c9-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 2,
                "numbervertices": 4,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "Road",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "baef3f9c3-00c9-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "baef3f9c3-00c9-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 128,
                "numbervertices": 130,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "Road",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "baef46f44-00c9-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "baef46f44-00c9-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 5,
                "numbervertices": 7,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "Road",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "baefcac78-00c9-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "baefcac78-00c9-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 8,
                "numbervertices": 8,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "Road",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "baefd21e7-00c9-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "baefd21e7-00c9-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 23,
                "numbervertices": 25,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "Road",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "baf005617-00c9-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "baf005617-00c9-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 17,
                "numbervertices": 15,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "Road",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "baf00f2b1-00c9-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "baf00f2b1-00c9-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 3,
                "numbervertices": 5,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "Road",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "baf01b573-00c9-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "baf01b573-00c9-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 2,
                "numbervertices": 4,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "Road",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "baf03b16f-00c9-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "baf03b16f-00c9-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 2,
                "numbervertices": 4,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "Road",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "baf03b17b-00c9-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "baf03b17b-00c9-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 2,
                "numbervertices": 4,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "Road",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "baf053805-00c9-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "baf053805-00c9-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 42,
                "numbervertices": 44,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "Road",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "baf05864c-00c9-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "baf05864c-00c9-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 49,
                "numbervertices": 51,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "Road",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "baf067030-00c9-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "baf067030-00c9-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 2,
                "numbervertices": 4,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "Road",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "baf06be8c-00c9-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "baf06be8c-00c9-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 2,
                "numbervertices": 4,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "Road",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "baf084513-00c9-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "baf084513-00c9-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 2,
                "numbervertices": 4,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "Road",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "baf0b7934-00c9-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "baf0b7934-00c9-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 89,
                "numbervertices": 91,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "Road",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "baf3f295d-2d29-11e6-9a38-393caa90be70",
            "primitives": [{
                "id": "baf3f295d-2d29-11e6-9a38-393caa90be70(0)",
                "numberfaces": 2,
                "numbervertices": 4,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "LandUse",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "baf3f2966-2d29-11e6-9a38-393caa90be70",
            "primitives": [{
                "id": "baf3f2966-2d29-11e6-9a38-393caa90be70(0)",
                "numberfaces": 2,
                "numbervertices": 4,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "LandUse",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "bbdc52a89-00b3-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "bbdc52a89-00b3-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 6,
                "numbervertices": 8,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "GenericCityObject",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "bdce6a385-fd58-11e5-8acc-1fc21a78c5fd",
            "primitives": [{
                "id": "bdce6a385-fd58-11e5-8acc-1fc21a78c5fd(0)",
                "numberfaces": 34,
                "numbervertices": 20,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "LandUse",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "be252b118-2d37-11e6-9a38-393caa90be70",
            "primitives": [{
                "id": "be252b118-2d37-11e6-9a38-393caa90be70(0)",
                "numberfaces": 8,
                "numbervertices": 8,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "GenericCityObject",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "be2539be1-2d37-11e6-9a38-393caa90be70",
            "primitives": [{
                "errors": [
                    {
                        "code": 102,
                        "description": "CONSECUTIVE_POINTS_SAME",
                        "id": "2",
                        "info": "",
                        "type": "Error"
                    },
                    {
                        "code": 102,
                        "description": "CONSECUTIVE_POINTS_SAME",
                        "id": "12",
                        "info": "",
                        "type": "Error"
                    }
                ],
                "id": "be2539be1-2d37-11e6-9a38-393caa90be70(0)",
                "numberfaces": 31,
                "numbervertices": 25,
                "type": "MultiSurface",
                "validity": false
            }],
            "type": "GenericCityObject",
            "validity": false
        },
        {
            "errors_feature": null,
            "id": "bea630875-00b8-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "bea630875-00b8-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 36,
                "numbervertices": 30,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "Bridge",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "bea632f90-00b8-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "bea632f90-00b8-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 14,
                "numbervertices": 16,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "Bridge",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "bedab6302-00c8-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "bedab6302-00c8-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 154,
                "numbervertices": 156,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "WaterBody",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "bedabd859-00c8-11e6-b420-2bdcc4ab5d7f",
            "primitives": [{
                "id": "bedabd859-00c8-11e6-b420-2bdcc4ab5d7f(0)",
                "numberfaces": 49,
                "numbervertices": 51,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "WaterBody",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "bfce80032-2d38-11e6-9a38-393caa90be70",
            "primitives": [{
                "id": "bfce80032-2d38-11e6-9a38-393caa90be70(0)",
                "numberfaces": 2,
                "numbervertices": 4,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "Road",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "bfce91150-2d38-11e6-9a38-393caa90be70",
            "primitives": [{
                "id": "bfce91150-2d38-11e6-9a38-393caa90be70(0)",
                "numberfaces": 5,
                "numbervertices": 7,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "Road",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "bfce93872-2d38-11e6-9a38-393caa90be70",
            "primitives": [{
                "id": "bfce93872-2d38-11e6-9a38-393caa90be70(0)",
                "numberfaces": 2,
                "numbervertices": 4,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "Road",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "bfce95fa3-2d38-11e6-9a38-393caa90be70",
            "primitives": [{
                "id": "bfce95fa3-2d38-11e6-9a38-393caa90be70(0)",
                "numberfaces": 37,
                "numbervertices": 37,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "Road",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "bfcea2371-2d38-11e6-9a38-393caa90be70",
            "primitives": [{
                "id": "bfcea2371-2d38-11e6-9a38-393caa90be70(0)",
                "numberfaces": 94,
                "numbervertices": 96,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "Road",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "bfcea4a8a-2d38-11e6-9a38-393caa90be70",
            "primitives": [{
                "id": "bfcea4a8a-2d38-11e6-9a38-393caa90be70(0)",
                "numberfaces": 3,
                "numbervertices": 5,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "Road",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "bfcea70b2-2d38-11e6-9a38-393caa90be70",
            "primitives": [{
                "id": "bfcea70b2-2d38-11e6-9a38-393caa90be70(0)",
                "numberfaces": 65,
                "numbervertices": 65,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "Road",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "bfcea97e3-2d38-11e6-9a38-393caa90be70",
            "primitives": [{
                "id": "bfcea97e3-2d38-11e6-9a38-393caa90be70(0)",
                "numberfaces": 3,
                "numbervertices": 5,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "Road",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "bfcea97e9-2d38-11e6-9a38-393caa90be70",
            "primitives": [{
                "id": "bfcea97e9-2d38-11e6-9a38-393caa90be70(0)",
                "numberfaces": 9,
                "numbervertices": 11,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "Road",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "bfceae630-2d38-11e6-9a38-393caa90be70",
            "primitives": [{
                "id": "bfceae630-2d38-11e6-9a38-393caa90be70(0)",
                "numberfaces": 3,
                "numbervertices": 5,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "Road",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "bfceb347d-2d38-11e6-9a38-393caa90be70",
            "primitives": [{
                "id": "bfceb347d-2d38-11e6-9a38-393caa90be70(0)",
                "numberfaces": 8,
                "numbervertices": 10,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "Road",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "bfcebaa0a-2d38-11e6-9a38-393caa90be70",
            "primitives": [{
                "id": "bfcebaa0a-2d38-11e6-9a38-393caa90be70(0)",
                "numberfaces": 186,
                "numbervertices": 188,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "Road",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "bfcec6cc0-2d38-11e6-9a38-393caa90be70",
            "primitives": [{
                "id": "bfcec6cc0-2d38-11e6-9a38-393caa90be70(0)",
                "numberfaces": 67,
                "numbervertices": 67,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "Road",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "bfcece247-2d38-11e6-9a38-393caa90be70",
            "primitives": [{
                "id": "bfcece247-2d38-11e6-9a38-393caa90be70(0)",
                "numberfaces": 3,
                "numbervertices": 5,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "Road",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "bfcedf371-2d38-11e6-9a38-393caa90be70",
            "primitives": [{
                "id": "bfcedf371-2d38-11e6-9a38-393caa90be70(0)",
                "numberfaces": 76,
                "numbervertices": 78,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "Road",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "bfcee1a90-2d38-11e6-9a38-393caa90be70",
            "primitives": [{
                "id": "bfcee1a90-2d38-11e6-9a38-393caa90be70(0)",
                "numberfaces": 4,
                "numbervertices": 6,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "Road",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "bfceeb72a-2d38-11e6-9a38-393caa90be70",
            "primitives": [{
                "id": "bfceeb72a-2d38-11e6-9a38-393caa90be70(0)",
                "numberfaces": 2,
                "numbervertices": 4,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "Road",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "bfceeb730-2d38-11e6-9a38-393caa90be70",
            "primitives": [{
                "id": "bfceeb730-2d38-11e6-9a38-393caa90be70(0)",
                "numberfaces": 2,
                "numbervertices": 4,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "Road",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "bfceede58-2d38-11e6-9a38-393caa90be70",
            "primitives": [{
                "id": "bfceede58-2d38-11e6-9a38-393caa90be70(0)",
                "numberfaces": 74,
                "numbervertices": 76,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "Road",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "bfcef52cd-2d38-11e6-9a38-393caa90be70",
            "primitives": [{
                "id": "bfcef52cd-2d38-11e6-9a38-393caa90be70(0)",
                "numberfaces": 5,
                "numbervertices": 7,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "Road",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "bfcf03dd2-2d38-11e6-9a38-393caa90be70",
            "primitives": [{
                "id": "bfcf03dd2-2d38-11e6-9a38-393caa90be70(0)",
                "numberfaces": 7,
                "numbervertices": 9,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "Road",
            "validity": true
        },
        {
            "errors_feature": null,
            "id": "bfcf03dd8-2d38-11e6-9a38-393caa90be70",
            "primitives": [{
                "id": "bfcf03dd8-2d38-11e6-9a38-393caa90be70(0)",
                "numberfaces": 2,
                "numbervertices": 4,
                "type": "MultiSurface",
                "validity": true
            }],
            "type": "Road",
            "validity": true
        }
    ],
    "features_overview": [
        {
            "total": 3,
            "type": "Bridge",
            "valid": 3
        },
        {
            "total": 160,
            "type": "Building",
            "valid": 0
        },
        {
            "total": 54,
            "type": "GenericCityObject",
            "valid": 53
        },
        {
            "total": 81,
            "type": "LandUse",
            "valid": 81
        },
        {
            "total": 126,
            "type": "PlantCover",
            "valid": 126
        },
        {
            "total": 143,
            "type": "Road",
            "valid": 142
        },
        {
            "total": 3,
            "type": "WaterBody",
            "valid": 2
        }
    ],
    "input_file": "delft.json",
    "parameters": {
        "overlap_tol": -1,
        "planarity_d2p_tol": 0.01,
        "planarity_n_tol": 20,
        "snap_tol": 0.001
    },
    "primitives_overview": [
        {
            "total": 160,
            "type": "Solid",
            "valid": 0
        },
        {
            "total": 410,
            "type": "MultiSurface",
            "valid": 407
        }
    ],
    "time": "Wed Apr 15 19:10:24 2020 CEST",
    "type": "val3dity_report",
    "val3dity_version": "2.2.0-beta.1",
    "validity": false
}