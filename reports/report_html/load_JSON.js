var report =
{
  "CityObjects": [
  {
      type: "GenericCityObject",
      id: "id-1",
      errors: [
          {
            "code": 601,
            "description": "BUILDINGPARTS_OVERLAP",
            "id": "MISSING_ID_0 and MISSING_ID_1",
            "info": "",
            "type": "Error"
          },
          {
            "code": 601,
            "description": "BUILDINGPARTS_OVERLAP",
            "id": "MISSING_ID_0 and MISSING_ID_2",
            "info": "",
            "type": "Error"
          },
          {
            "code": 601,
            "description": "BUILDINGPARTS_OVERLAP",
            "id": "MISSING_ID_0 and MISSING_ID_5",
            "info": "",
            "type": "Error"
          },
          {
            "code": 601,
            "description": "BUILDINGPARTS_OVERLAP",
            "id": "MISSING_ID_1 and MISSING_ID_3",
            "info": "",
            "type": "Error"
          },
          {
            "code": 601,
            "description": "BUILDINGPARTS_OVERLAP",
            "id": "MISSING_ID_2 and MISSING_ID_3",
            "info": "",
            "type": "Error"
          }
      ],
      validity: false,
      primitives:
      [
          {
              type: "MultiSolid",
              id: "id-1(0)",
              errors: null,
              validity: false,
              numbersolids: 2,
              primitives: [
                  {
                    "errors": null,
                    "id": "all_hail_CityGML",
                    "numberfaces": 6,
                    "numbershells": 1,
                    "numbervertices": 8,
                    "type": "Solid",
                    "validity": true
                  },
                  {
                    "errors": [
                      {
                        "code": 302,
                        "description": "SHELL_NOT_CLOSED",
                        "id": "1",
                        "info": "Location hole: 1 0 3",
                        "type": "Error"
                     },
                    {
                      "code": 103,
                      "description": "NOT_CLOSED",
                      "id": "1-2",
                      "info": "Close that polygon already!",
                      "type": "Error"
                    }
                    ],
                    "id": "but_CityJSON_is_coming",
                    "numberfaces": 5,
                    "numbershells": 1,
                    "numbervertices": 8,
                    "type": "Solid",
                    "validity": false
                  }
              ]
          }
      ]
  },
  {
      type: "GenericCityObject",
      id: "id-2",
      errors: null,
      validity: true,
      primitives:
      [
          {
              type: "MultiSolid",
              id: "id-2(0)",
              errors: null,
              validity: true,
              primitives: []
          }

      ]
  }
  ],
  "InputErrors": null,
  "Primitives": [
    {
      "errors": [
        {
          "code": 302,
          "description": "SHELL_NOT_CLOSED",
          "id": "",
          "info": "Location hole: 0 0 1",
          "type": "Error"
        },
        {
          "code": 302,
          "description": "SHELL_NOT_CLOSED",
          "id": "",
          "info": "Location hole: 1 1 1",
          "type": "Error"
        }
      ],
      "id": "0",
      "numberfaces": 12,
      "numbershells": 1,
      "numbervertices": 9,
      "type": "Solid",
      "validity": false
    }
  ],
  "input_file": "../data/cityjson/msol2.json",
  "invalid_cityobjects": 1,
  "invalid_primitives": 1,
  "overlap_tol": -1.0,
  "overview_errors": [
    302,
    404,
    601,
    999
  ],
  "overview_errors_no_primitives": [
    1,
    2,
    1,
    4
  ],
  "planarity_d2p_tol": 0.01,
  "planarity_n_tol": 20.0,
  "snap_tol": 0.001,
  "time": "Tue Oct 10 16:16:23 2017 CEST",
  "total_cityobjects": 1,
  "total_primitives": 1,
  "type": "val3dity report",
  "val3dity_version": "2.0 beta 1",
  "valid_cityobjects": 0,
  "valid_primitives": 0
}
