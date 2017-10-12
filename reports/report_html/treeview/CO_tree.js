var tree = [
{
    type: "GenericCityObject",
    id: "id-1",
    errors: [
      [
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
      ]
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
];

// var tree = [
//     {
//         name: 'Vegetables',
//         children: []
//     },
//     {
//         name: 'Fruits',
//         children:
//         [
//             {
//                 name: 'Apple',
//                 children: []
//             },
//             {
//                 name: 'Orange',
//                 children: []
//             },
//             {
//                 name: 'Lemon',
//                 children: []
//             }
//         ]
//     },
//     {
//         name: 'Candy',
//         children:
//         [
//             {
//                 name: 'Gummies',
//                 children: []
//             },
//             {
//                 name: 'Chocolate',
//                 children:
//                 [
//                     {
//                         name: 'M & M\'s',
//                         children: []
//                     },
//                     {
//                         name: 'Hershey Bar',
//                         children: []
//                     }
//                 ]
//             },
//         ]
//     },
//     {
//         name: 'Bread',
//         children: []
//     }
// ];
