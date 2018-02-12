var report = {
    "errors_dataset": null,
    "features": [{
        "errors_feature": null,
        "id": "id-1",
        "primitives": [{
            "errors": null,
            "id": "id-1(0)",
            "numbersolids": 2,
            "primitives": [{
                "errors": null,
                "id": "none",
                "numberfaces": 6,
                "numbershells": 1,
                "numbervertices": 8,
                "type": "Solid",
                "validity": true}, {
                "errors": [{
                    "code": 902,
                    "description": "EMPTY_PRIMITIVE",
                    "id": "",
                    "info": "empty Solid, contains no points and/or surfaces",
                    "type": "Error"
                }],
                "id": "none",
                "numberfaces": 0,
                "numbershells": 0,
                "numbervertices": 0,
                "type": "Solid",
                "validity": false
            }],
            "type": "CompositeSolid",
            "validity": false
        }],
        "type": "GenericCityObject",
        "validity": false
    }],
    "input_file": "./data/test_empty/empty_primitive.json",
    "invalid_features": 1,
    "invalid_primitives": 1,
    "overlap_tol": -1.0,
    "overview_errors": [902],
    "overview_features": ["GenericCityObject"],
    "overview_primitives": ["CompositeSolid"],
    "planarity_d2p_tol": 0.01,
    "planarity_n_tol": 20.0,
    "snap_tol": 0.001,
    "time": "Mon Feb 12 10:57:58 2018 UTC",
    "total_features": 1,
    "total_primitives": 1,
    "type": "val3dity report",
    "val3dity_version": "2.0.4",
    "valid_features": 0,
    "valid_primitives": 0
}
