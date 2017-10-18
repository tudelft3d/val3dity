var report = {                                  // the report is not JSON, but a JS object, stored in the 'report' variable
    "CityObjects": [                            // an array of objects, instead of an object in itself
        {
            "id": "id-1"                        // the ID has its own key
        },
        {
            "id": "id-2"
        }
    ],
    "errors": [                                 // a shallow array only, and not [ [{},{}] ]
        {},
        {}
    ],
    "overview_errors": [],                      // underscore instead of hypen
    "overview_errors_no_primitives": []         // underscore instead of hypen
};
