
std::string indexhtml = R"(
<!DOCTYPE html>
<html lang="en">
    <head>
        <meta charset="utf-8"/>
        <link rel="stylesheet" type="text/css" href="index.css">
        <title>val3dity report</title>
    </head>

    <body>
        <div id="header">
            <div class="content">
                <h1>val3dity report
                </h1>
            </div>
        </div>

        <table id="input">
            <tr>
                <td> Input file: </td>
                <td id="in_file"></td>
            </tr>
            <tr>
                <td>val3dity version:</td>
                <td id=version></td>
            </tr>
            <tr>
                <td>Validation time:</td>
                <td id=time></td>
            </tr>
        </table>

        <h3>Parameters used for validation</h3>
        <table id="params">
            <tr>
                <td>
                    <a href="http://val3dity.readthedocs.io/en/v2/usage/#planarity-d2p-tol" target="_blank">
                        planarity_d2p_tol:
                    </a>
                </td>
                <td id=planarity_d2p_tol></td>
            </tr>
            <tr>
                <td>
                    <a href="http://val3dity.readthedocs.io/en/v2/usage/#planarity-n-tol" target="_blank">
                        planarity_n_tol:
                    </a>
                </td>
                <td id=planarity_n_tol></td>
            </tr>
            <tr>
                <td>
                    <a href="http://val3dity.readthedocs.io/en/v2/usage/#snap-tol" target="_blank">
                        snap_tol:
                    </a>
                </td>
                <td id=snap_tol></td>
            </tr>
            <tr>
                <td>
                    <a href="http://val3dity.readthedocs.io/en/v2/usage/#overlap-tol" target="_blank">
                        overlap_tol:
                    </a>
                </td>
                <td id=overlap_tol></td>
            </tr>
        </table>

        <h3>Validation summary</h3>

        <script src="report.js"></script>
        <script src="val3dityconfig.js"></script>
    </body>
</html>
)";


std::string cityobjectshtml = R"(
<!DOCTYPE html>
<html lang="en">
    <head>
        <meta charset="utf-8"/>
        <link rel="stylesheet" type="text/css" href="index.css" />
        <title>CityObjects</title>
    </head>

    <body>
        <div id="header">
            <div class="content">
                <h2>CityObjects in <b id="infile"></b>
                </h2>
                <br/>
                <button href="#" class="filter_link" data-filter="all">All</button>
                <button href="#" class="filter_link" data-filter="true">Valid</button>
                <button id="invalid" href="#" class="filter_link" data-filter="false">Invalid</button>
            </div>
        </div>

        <button id="expandAll">Expand All</button>
        <button id="collapseAll">Collapse All</button>
        <div id="tree"></div>

        <script src="https://ajax.googleapis.com/ajax/libs/jquery/3.2.1/jquery.min.js"></script>
        <script src="treeview.js"></script>
        <script src="report.js"></script>

        <script>
            var input = report.input_file;
            document.getElementById("infile").innerHTML = input.split("/").pop();

            if (report.CityObjects != null) {
                // Grab expand/collapse buttons
                var expandAll = document.getElementById('expandAll');
                var collapseAll = document.getElementById('collapseAll');

                // Create tree
                var t = new TreeView(report.CityObjects, 'tree');

                // Attach events
                expandAll.onclick = function () { t.expandAll(); };
                collapseAll.onclick = function () { t.collapseAll(); };
            } else {
                // do nothing
            }

            // filter tree
            var $treeElements = $('.tree-leaf');

            $('.filter_link').click(function(e){
                e.preventDefault();
                // get the category from the attribute
                var filterVal = $(this).data('filter');

                if (filterVal === 'all') {
                  $treeElements.show();
                } else {
                   // hide all then filter the ones to show, but always include the errors
                   $treeElements.hide().filter("[validity=" + filterVal + "]").show();
                }
            });

        </script>

    </body>
</html>
)";

std::string indexcss = R"(
/* Page-wide styles */
html, body, h1, h2, h3, p, table, td, th {
    margin: 0;
    padding: 0;
    border: 0;
    outline: 0;
    font-weight: inherit;
    font-style: inherit;
    font-size: 100%;
    font-family: inherit;
    vertical-align: baseline;
    }

/* Set baseline grid to 16 pt. */
body {
    font-family: georgia, serif;
    font-size: 1em;
    }

html>body {
    font-size: 16px;
    }

/* Set base font size to 12/16 */
p {
    font-size: .75em;           /* 12/16 */
    line-height: 1.33333333em;  /* 16/12 */
    }

table {
    border-collapse: collapse;
    }
td {
    vertical-align: top;
}

#header {
    background: #f8f8f8;
    width: 100%;
    border-bottom: 1px solid #eee;
    }

#header .content {
    padding: 1em 3em;
    }

h1 {
    font-size: 1.5em;
    display: inline-block;
}

h2 {
    font-size: 1.25em;
    display: inline-block;
}

h3 {
    padding: 1em 0 0 3em;
    font-size: 1em;
    font-weight: bold;
}

table {
    border-collapse: collapse;
    width: 80%;
    margin-left: 5em;
    position: relative;
}

td {
    padding: 8px;
    text-align: left;
    border-bottom: 1px solid #ddd;
}

th {
    text-align: left;
    font-style: italic;
}

table#summary tr:hover {
    padding-top: .5em;
    background-color: #f5f5f5;
}

table#errors {
    margin-top: 20px;
}

#errors th {
    padding-bottom: 10px;
}

a {
    text-decoration: none;
    color: inherit;
    }
a:hover {
    text-decoration: underline;
    color: inherit;
    }

.linear-ring-level{
    background-color: #FED2D2
}
.polygon-level{
    background-color: #76D36B
}
.shell-level{
    background-color: #F2AF60
}
.solid-level{
    background-color: #1BD2FF
}
.solid-interactions-level{
    background-color: #FDA4FF
}
.citygml-building{
    background-color: #D2A471
}
.others{
    background-color: #1CE0E3
}


/* Treeview */
div#tree {
    margin-top: 1em;
    margin-left: 5em;
}

button {
    font-family: sans-serif;
    font-size: .8em;
    cursor: pointer;
    border: 1px solid;
    border-color: #999 #999 #999 #999;
    padding: .2em .35em;
}

button#expandAll {
    margin-left: 6em;
    margin-top: 1em;
}

.filter_link {
    margin: .75em .1em;
}

button#invalid {
    background: #FF8C75;
}

.tree-leaf {
    position: relative;
    padding-top: 5px;
}
.tree-leaf .tree-child-leaves, .tree-error-code {
    display: block;
    margin-left: 3em;
}
.tree-leaf .hidden {
    display: none;
}
.tree-leaf .tree-expando {
    /*background: #ddd;*/
    border-radius: 10px;
    cursor: pointer;
    float: left;
    height: 10px;
    line-height: 10px;
    position: relative;
    text-align: center;
    top: 4px;
    width: 10px;
}
.tree-leaf .hidden {
    visibility: hidden;
}
.tree-leaf .tree-expando:hover {
    /*background: #aaa;*/
}
.tree-leaf .tree-leaf-text, .tree-error-code {
    display: table-cell;
    cursor: pointer;
    float: left;
    margin-left: 10px;
}

.tree-leaf .tree-leaf-id {
    display: table-cell;
    cursor: pointer;
    float: left;
    padding-left: 60px;
    padding-right: 20px;
    font-style: italic;
}

.tree-leaf .tree-leaf-nrfaces, .tree-leaf-nrvertices, .tree-leaf-nrshells, .tree-leaf-nrsolids, .tree-error-info {
    display: table-cell;
    float: left;
    padding-left: 20px;
}

/*.tree-leaf .tree-leaf-text:hover {
    color: blue;
}*/
.tree-leaf .tree-leaf-content:before, .tree-leaf .tree-leaf-content:after {
    content: " ";
    display: table;
}
.tree-leaf .tree-leaf-content:after {
    clear: both;
}
)";


std::string primitiveshtml = R"(
<!DOCTYPE html>
<html lang="en">
    <head>
        <meta charset="utf-8"/>
        <link rel="stylesheet" type="text/css" href="index.css">
        <title>Primitives</title>
    </head>

    <body>
        <div id="header">
            <div class="content">
                <h2>Primitives in <b id="infile"></b>
                </h2>
                <br/>
                <button href="#" class="filter_link" data-filter="all">All</button>
                <button href="#" class="filter_link" data-filter="true">Valid</button>
                <button id="invalid" href="#" class="filter_link" data-filter="false">Invalid</button>
            </div>
        </div>

        <button id="expandAll">Expand All</button>
        <button id="collapseAll">Collapse All</button>
        <div id="tree"></div>

        <script src="https://ajax.googleapis.com/ajax/libs/jquery/3.2.1/jquery.min.js"></script>
        <script src="treeview.js"></script>
        <script src="report.js"></script>

        <script>
            var input = report.input_file;
            document.getElementById("infile").innerHTML = input.split("/").pop();

            if (report.Primitives != null) {
                // Grab expand/collapse buttons
                var expandAll = document.getElementById('expandAll');
                var collapseAll = document.getElementById('collapseAll');

                // Create tree
                var t = new TreeView(report.Primitives, 'tree');

                // Attach events
                expandAll.onclick = function () { t.expandAll(); };
                collapseAll.onclick = function () { t.collapseAll(); };
            } else {
                // do nothing
            }

            // filter tree
            var $treeElements = $('.tree-leaf');

            $('.filter_link').click(function(e){
                e.preventDefault();
                // get the category from the attribute
                var filterVal = $(this).data('filter');

                if (filterVal === 'all') {
                  $treeElements.show();
                } else {
                   // hide all then filter the ones to show, but always include the errors
                   $treeElements.hide().filter("[validity=" + filterVal + "]").show();
                }
            });

        </script>

    </body>
</html>
)";

std::string treeviewjs = R"(
// Adapted from js-treeview, see: https://github.com/justinchmura/js-treeview

(function (define) {
  'use strict';

  (function (root, factory) {
    if (typeof define === 'function' && define.amd) {
      define(factory);
    } else if (typeof exports === 'object') {
      module.exports = factory();
    } else {
      root.TreeView = factory();
    }
  }(window, function () {
    return (function () {

      /** List of events supported by the tree view */
      var events = [
        'expand',
        'expandAll',
        'collapse',
        'collapseAll',
        'select'
      ];

      /**
       * A forEach that will work with a NodeList and generic Arrays
       * @param {array|NodeList} arr The array to iterate over
       * @param {function} callback Function that executes for each element. First parameter is element, second is index
       * @param {object} The context to execute callback with
       */
      function forEach(arr, callback, scope) {
        var i, len = arr.length;
        for (i = 0; i < len; i += 1) {
          callback.call(scope, arr[i], i);
        }
      }

      /**
       * Emit an event from the tree view
       * @param {string} name The name of the event to emit
       */
      function emit(instance, name) {
        var args = [].slice.call(arguments, 2);
        if (events.indexOf(name) > -1) {
          if (instance.handlers[name] && instance.handlers[name] instanceof Array) {
            forEach(instance.handlers[name], function (handle) {
              window.setTimeout(function () {
                handle.callback.apply(handle.context, args);
              }, 0);
            });
          }
        } else {
          throw new Error(name + ' event cannot be found on TreeView.');
        }
      }

      /**
       * Renders the tree view in the DOM
       */
      function render(self) {
        var container = document.getElementById(self.node);
        var leaves = [], click;
        var renderLeaf = function (item) {
          var leaf = document.createElement('div');
          var content = document.createElement('div');
          var text = document.createElement('div');
          var expando = document.createElement('div');
          var id = document.createElement('div');
          var nrfaces = document.createElement('div');
          var nrvertices = document.createElement('div');
          var nrsolids = document.createElement('div');
          var nrshells = document.createElement('div');
          var colour_invalid = "#FF8C75";
          var errcode = document.createElement('div');
          var errinfo = document.createElement('div');

          leaf.setAttribute('class', 'tree-leaf');
          content.setAttribute('class', 'tree-leaf-content');
          content.setAttribute('data-item', JSON.stringify(item));

          if(item.code) {
              errcode.setAttribute('class', 'tree-error-code');
              errcode.textContent = item.code + " " + "\u2014" + " " + item.description;
              id.setAttribute('class', 'tree-leaf-id');
              id.textContent = "ID:" + "\u00A0" + item.id;
              errinfo.setAttribute('class', 'tree-error-info');
              errinfo.textContent = "Info:" + "\u00A0" + item.info;
              content.appendChild(errcode);
              content.appendChild(id);
              content.appendChild(errinfo);
              // set attribute so that errors stay in the filtered tree when 'Invalid'
              leaf.setAttribute('validity', 'false');
          } else {
              text.setAttribute('class', 'tree-leaf-text');
              text.textContent = item.type;
              id.setAttribute('class', 'tree-leaf-id');
              id.textContent = "ID:" + "\u00A0" + item.id;
              expando.setAttribute('class', 'tree-expando ' + (item.expanded ? 'expanded' : ''));
              expando.textContent = item.expanded ? '&#150;' : '+';

              if(!item.validity) {
                //   set colour to red if invalid
                text.style.background = colour_invalid;
                id.style.background = colour_invalid;
                leaf.setAttribute('validity', 'false');
              } else {
                leaf.setAttribute('validity', 'true');
              }

              content.appendChild(expando);
              content.appendChild(text);
              content.appendChild(id);

              if(item.numbersolids != undefined) {
                  nrsolids.setAttribute('class', 'tree-leaf-nrsolids');
                  nrsolids.textContent = "Solids:" + "\u00A0" + item.numbersolids;
                  content.appendChild(nrsolids);
                  if(!item.validity){
                      nrsolids.style.background = colour_invalid;
                  }
              }
              if(item.numbervertices != undefined) {
                  nrshells.setAttribute('class', 'tree-leaf-nrshells');
                  nrshells.textContent = "Shells:" + "\u00A0" + item.numbershells;
                  nrfaces.setAttribute('class', 'tree-leaf-nrfaces');
                  nrfaces.textContent = "Faces:" + "\u00A0" + item.numberfaces;
                  nrvertices.setAttribute('class', 'tree-leaf-nrvertices');
                  nrvertices.textContent = "Vertices:" + "\u00A0" + item.numbervertices;
                  if(!item.validity) {
                    nrshells.style.background = colour_invalid;
                    nrvertices.style.background = colour_invalid;
                    nrfaces.style.background = colour_invalid;
                  }
                  content.appendChild(nrshells);
                  content.appendChild(nrfaces);
                  content.appendChild(nrvertices);
              } else {
                //   nothing
              }
          }

          leaf.appendChild(content);

          if ((item.primitives && item.primitives.length > 0) ||
                (item.errors && item.errors.length > 0)
            ) {
            var children = document.createElement('div');
            children.setAttribute('class', 'tree-child-leaves');
            if (item.errors) {
                forEach(item.errors, function (child) {
                  var childLeaf = renderLeaf(child);
                  children.appendChild(childLeaf);
                });
                if (!item.expanded) {
                  children.classList.add('hidden');
                }
                leaf.appendChild(children);
            }
            if (item.primitives) {
                forEach(item.primitives, function (child) {
                  var childLeaf = renderLeaf(child);
                  children.appendChild(childLeaf);
                });
                if (!item.expanded) {
                  children.classList.add('hidden');
                }
                leaf.appendChild(children);
            }
          } else {
            expando.classList.add('hidden');
          }

          return leaf;
        };

        forEach(self.data, function (item) {
          leaves.push(renderLeaf.call(self, item));
        });
        container.innerHTML = leaves.map(function (leaf) {
          return leaf.outerHTML;
        }).join('');

        click = function (e) {
          var parent = (e.target || e.currentTarget).parentNode;
          var data = JSON.parse(parent.getAttribute('data-item'));
          var leaves = parent.parentNode.querySelector('.tree-child-leaves');
          if (leaves) {
            if (leaves.classList.contains('hidden')) {
              self.expand(parent, leaves);
            } else {
              self.collapse(parent, leaves);
            }
          } else {
            emit(self, 'select', {
              target: e,
              data: data
            });
          }
        };

        forEach(container.querySelectorAll('.tree-leaf-text'), function (node) {
          node.onclick = click;
        });
        forEach(container.querySelectorAll('.tree-expando'), function (node) {
          node.onclick = click;
        });
      }

      /**
       * @constructor
       * @property {object} handlers The attached event handlers
       * @property {object} data The JSON object that represents the tree structure
       * @property {DOMElement} node The DOM element to render the tree in
       */
      function TreeView(data, node) {
        this.handlers = {};
        this.node = node;
        this.data = data;
        render(this);
      }

      /**
       * Expands a leaflet by the expando or the leaf text
       * @param {DOMElement} node The parent node that contains the leaves
       * @param {DOMElement} leaves The leaves wrapper element
       */
      TreeView.prototype.expand = function (node, leaves, skipEmit) {
        var expando = node.querySelector('.tree-expando');
        expando.textContent = '-';
        leaves.classList.remove('hidden');
        if (skipEmit) { return; }
        emit(this, 'expand', {
          target: node,
          leaves: leaves
        });
      };

      TreeView.prototype.expandAll = function () {
        var self = this;
        var nodes = document.getElementById(self.node).querySelectorAll('.tree-expando');
        forEach(nodes, function (node) {
          var parent = node.parentNode;
          var leaves = parent.parentNode.querySelector('.tree-child-leaves');
          if (parent && leaves && parent.hasAttribute('data-item')) {
            self.expand(parent, leaves, true);
          }
        });
        emit(this, 'expandAll', {});
      };

      /**
       * Collapses a leaflet by the expando or the leaf text
       * @param {DOMElement} node The parent node that contains the leaves
       * @param {DOMElement} leaves The leaves wrapper element
       */
      TreeView.prototype.collapse = function (node, leaves, skipEmit) {
        var expando = node.querySelector('.tree-expando');
        expando.textContent = '+';
        leaves.classList.add('hidden');
        if (skipEmit) { return; }
        emit(this, 'collapse', {
          target: node,
          leaves: leaves
        });
      };

      /**
       */
      TreeView.prototype.collapseAll = function () {
        var self = this;
        var nodes = document.getElementById(self.node).querySelectorAll('.tree-expando');
        forEach(nodes, function (node) {
          var parent = node.parentNode;
          var leaves = parent.parentNode.querySelector('.tree-child-leaves');
          if (parent && leaves && parent.hasAttribute('data-item')) {
            self.collapse(parent, leaves, true);
          }
        });
        emit(this, 'collapseAll', {});
      };

      /**
       * Attach an event handler to the tree view
       * @param {string} name Name of the event to attach
       * @param {function} callback The callback to execute on the event
       * @param {object} scope The context to call the callback with
       */
      TreeView.prototype.on = function (name, callback, scope) {
        if (events.indexOf(name) > -1) {
          if (!this.handlers[name]) {
            this.handlers[name] = [];
          }
          this.handlers[name].push({
            callback: callback,
            context: scope
          });
        } else {
          throw new Error(name + ' is not supported by TreeView.');
        }
      };

      /**
       * Deattach an event handler from the tree view
       * @param {string} name Name of the event to deattach
       * @param {function} callback The function to deattach
       */
      TreeView.prototype.off = function (name, callback) {
        var index, found = false;
        if (this.handlers[name] instanceof Array) {
          this.handlers[name].forEach(function (handle, i) {
            index = i;
            if (handle.callback === callback && !found) {
              found = true;
            }
          });
          if (found) {
            this.handlers[name].splice(index, 1);
          }
        }
      };

      return TreeView;
    }());
  }));
}(window.define));
)";

std::string val3dityconfigjs = R"(
var errors = {
    "101": {
        "name": "101 – TOO_FEW_POINTS",
        "link": {
            "href": "http://val3dity.readthedocs.io/en/v2/errors/#too-few-points"
        }
    },
    "102": {
        "name": "102 – CONSECUTIVE_POINTS_SAME",
        "link": {
            "href": "http://val3dity.readthedocs.io/en/v2/errors/#consecutive-points-same"
        }
    },
    "103": {
        "name": "103 – NOT_CLOSED",
        "link": {
            "href": "http://val3dity.readthedocs.io/en/v2/errors/#not-closed"
        }
    },
    "104": {
        "name": "104 – SELF_INTERSECTION",
        "link": {
            "href": "http://val3dity.readthedocs.io/en/v2/errors/#self-intersection"
        }
    },
    "201": {
        "name": "201 – INTERSECTION_RINGS",
        "link": {
            "href": "http://val3dity.readthedocs.io/en/v2/errors/#intersection-rings"
        }
    },
    "202": {
        "name": "202 – DUPLICATED_RINGS",
        "link": {
            "href": "http://val3dity.readthedocs.io/en/v2/errors/#duplicated-rings"
        }
    },
    "203": {
        "name": "203 – NON_PLANAR_POLYGON_DISTANCE_PLANE",
        "link": {
            "href": "http://val3dity.readthedocs.io/en/v2/errors/#non-planar-polygon-distance-plane"
        }
    },
    "204": {
        "name": "204 – NON_PLANAR_POLYGON_NORMALS_DEVIATION",
        "link": {
            "href": "http://val3dity.readthedocs.io/en/v2/errors/#non-planar-polygon-normals-deviation"
        }
    },
    "205": {
        "name": "205 – INTERIOR_DISCONNECTED",
        "link": {
            "href": "http://val3dity.readthedocs.io/en/v2/errors/#interior-disconnected"
        }
    },
    "206": {
        "name": "206 – INNER_RING_OUTSIDE",
        "link": {
            "href": "http://val3dity.readthedocs.io/en/v2/errors/#inner-ring-outside"
        }
    },
    "207": {
        "name": "207 – INNER_RINGS_NESTED",
        "link": {
            "href": "http://val3dity.readthedocs.io/en/v2/errors/#inner-rings-nested"
        }
    },
    "208": {
        "name": "208 – ORIENTATION_RINGS_SAME",
        "link": {
            "href": "http://val3dity.readthedocs.io/en/v2/errors/#orientation-rings-same"
        }
    },
    "301": {
        "name": "301 – TOO_FEW_POLYGONS",
        "link": {
            "href": "http://val3dity.readthedocs.io/en/v2/errors/#too-few-polygons"
        }
    },
    "302": {
        "name": "302 – NOT_CLOSED",
        "link": {
            "href": "http://val3dity.readthedocs.io/en/v2/errors/#error-302"
        }
    },
    "303": {
        "name": "303 – NON_MANIFOLD_VERTEX",
        "link": {
            "href": "http://val3dity.readthedocs.io/en/v2/errors/#non-manifold-vertex"
        }
    },
    "304": {
        "name": "304 – NON_MANIFOLD_EDGE",
        "link": {
            "href": "http://val3dity.readthedocs.io/en/v2/errors/#non-manifold-edge"
        }
    },
    "305": {
        "name": "305 – MULTIPLE_CONNECTED_COMPONENTS",
        "link": {
            "href": "http://val3dity.readthedocs.io/en/v2/errors/#multiple-connected-components"
        }
    },
    "306": {
        "name": "306 – SELF_INTERSECTION",
        "link": {
            "href": "http://val3dity.readthedocs.io/en/v2/errors/#error-306"
        }
    },
    "307": {
        "name": "307 – POLYGON_WRONG_ORIENTATION",
        "link": {
            "href": "http://val3dity.readthedocs.io/en/v2/errors/#polygon-wrong-orientation"
        }
    },
    "401": {
        "name": "401 – INTERSECTION_SHELLS",
        "link": {
            "href": "http://val3dity.readthedocs.io/en/v2/errors/#intersection-shells"
        }
    },
    "402": {
        "name": "402 – DUPLICATED_SHELLS",
        "link": {
            "href": "http://val3dity.readthedocs.io/en/v2/errors/#duplicated-shells"
        }
    },
    "403": {
        "name": "403 – INNER_SHELL_OUTSIDE",
        "link": {
            "href": "http://val3dity.readthedocs.io/en/v2/errors/#inner-shell-outside"
        }
    },
    "404": {
        "name": "404 – INTERIOR_DISCONNECTED",
        "link": {
            "href": "http://val3dity.readthedocs.io/en/v2/errors/#error-404"
        }
    },
    "405": {
        "name": "405 – WRONG_ORIENTATION_SHELL",
        "link": {
            "href": "http://val3dity.readthedocs.io/en/v2/errors/#wrong-orientation-shell"
        }
    },
    "501": {
        "name": "501 – INTERSECTION_SOLIDS",
        "link": {
            "href": "http://val3dity.readthedocs.io/en/v2/errors/#intersection-solids"
        }
    },
    "502": {
        "name": "502 – DUPLICATED_SOLIDS",
        "link": {
            "href": "http://val3dity.readthedocs.io/en/v2/errors/#duplicated-solids"
        }
    },
    "503": {
        "name": "503 – DISCONNECTED_SOLIDS",
        "link": {
            "href": "http://val3dity.readthedocs.io/en/v2/errors/#disconnected-solids"
        }
    },
    "601": {
        "name": "601 – BUILDINGPARTS_OVERLAP",
        "link": {
            "href": "http://val3dity.readthedocs.io/en/v2/errors/#buildingparts-overlap"
        }
    },
    "901": {
        "name": "901 – INVALID_INPUT_FILE",
        "link": {
            "href": "http://val3dity.readthedocs.io/en/v2/errors/#invalid-input-file"
        }
    },
    "902": {
        "name": "902 – EMPTY_PRIMITIVE",
        "link": {
            "href": "http://val3dity.readthedocs.io/en/v2/errors/#empty-primitive"
        }
    },
    "903": {
        "name": "903 – WRONG_INPUT_PARAMETERS",
        "link": {
            "href": "http://val3dity.readthedocs.io/en/v2/errors/#wrong-input-parameters"
        }
    },
    "999": {
        "name": "999 – UNKNOWN_ERROR",
        "link": {
            "href": "http://val3dity.readthedocs.io/en/v2/errors/#unknown-error"
        }
    }
}

function error_overview() {

  if ( (report.CityObjects == null) && (report.Primitives == null) ) {
    // idx_error_table();
    return;
  }
  if (report.overview_errors == null) {
    var h = document.createElement("H3")           
    var t = document.createTextNode("No errors!");
    h.appendChild(t);
    document.body.appendChild(h);
    var x = document.createElement("IMG");
    x.setAttribute("src", "http://geovalidation.bk.tudelft.nl/val3dity/img/welldone.png");
    x.setAttribute("alt", "The Pulpit Rock");
    document.body.appendChild(x);
    return;
  }
  else {
    var h = document.createElement("H3")           
    var t = document.createTextNode("Overview of errors");
    h.appendChild(t);
    document.body.appendChild(h);
    idx_error_table();
  }
}

function idx_error_table(){
   
    var body = document.body,
        tbl  = document.createElement('table');
    tbl.setAttribute('id', "errors");


    var tr = tbl.insertRow(0);
    var headers = ['Error', '# of primitives'];
    for (var i = 0; i < 2; i++){
        var h = document.createElement('th');
        h.appendChild(document.createTextNode(headers[i]));
        tr.appendChild(h);
    }

    var nr_errors = report.overview_errors.length;
    var l_errors = report.overview_errors;
    var nr_prims = report.overview_errors_no_primitives;

    for(var i = 0; i < nr_errors; i++){
        var tr = tbl.insertRow();
        var td0 = tr.insertCell(0);
        var td1 = tr.insertCell(1);
        var err = errors[l_errors[i]];
        var a = document.createElement('a');
        var linkText = document.createTextNode(err.name);
        a.appendChild(linkText);
        a.title = err.name;
        a.href = err.link.href;
        a.target = '_blank';
        td0.appendChild(a);
        if (nr_prims[i] < 0) {
            // this happens on input error
            td1.appendChild(document.createTextNode("\u2014"));
        } else {
            td1.appendChild(document.createTextNode(nr_prims[i]));
        }

        // set colour
        if (l_errors[i] < 200) {
            tr.setAttribute('class', 'linear-ring-level');
        } else if (100 < l_errors[i] && l_errors[i] < 300) {
            tr.setAttribute('class', 'polygon-level');
        } else if(200 < l_errors[i] && l_errors[i] < 400) {
            tr.setAttribute('class', 'shell-level');
        } else if (300 < l_errors[i] && l_errors[i] < 500) {
            tr.setAttribute('class', 'solid-level');
        } else if (400 < l_errors[i] && l_errors[i] < 600) {
            tr.setAttribute('class', 'solid-interactions-level');
        } else if (500 < l_errors[i] && l_errors[i] < 700) {
            tr.setAttribute('class', 'citygml-building');
        } else if (800 < l_errors[i] && l_errors[i] < 1000) {
            tr.setAttribute('class', 'others');
        }
    }
    body.appendChild(tbl);
}

function idx_validation_summary(){
    var body = document.body,
        tbl  = document.createElement('table');
    tbl.setAttribute('id', "summary");

    var tr = tbl.insertRow(0);
    var headers = [" ", "Total", "Valid", "Invalid"];
    for (var i = 0; i < 4; i++){
        var h = document.createElement('th');
        h.appendChild(document.createTextNode(headers[i]));
        tr.appendChild(h);
    }

    if (report.CityObjects != null) {
        var tr = tbl.insertRow();

        // cell CityObjects
        var td0 = tr.insertCell(0);
        var a = document.createElement('a');
        var linkText = document.createTextNode('CityObjects (click for more details)');
        a.appendChild(linkText);
        a.title = "CityObjects";
        a.href = "CityObjects.html";
        td0.appendChild(a);
        // cell Total
        var td_t = tr.insertCell(1);
        td_t.appendChild(document.createTextNode(report.total_cityobjects));
        // cell Valid
        var td_v = tr.insertCell(2);
        var CO_valid_pc = Math.round(report.valid_cityobjects / report.total_cityobjects * 100);
        var v = report.valid_cityobjects + ' (' + CO_valid_pc + '%)';
        td_v.appendChild(document.createTextNode(v));
        // cell Invalid
        var td_i = tr.insertCell(3);
        var CO_invalid_pc = Math.round(report.invalid_cityobjects / report.total_cityobjects * 100);
        var i = report.invalid_cityobjects + ' (' + CO_invalid_pc + '%)';
        td_i.appendChild(document.createTextNode(i));
    }

    if (report.Primitives != null) {
        var tr = tbl.insertRow();

        // cell Primitives
        var td0 = tr.insertCell(0);
        var a = document.createElement('a');
        var linkText = document.createTextNode('Primitives');
        a.appendChild(linkText);
        a.title = "Primitives";
        a.href = "Primitives.html";
        td0.appendChild(a);
        // cell Total
        var td_t = tr.insertCell(1);
        td_t.appendChild(document.createTextNode(report.total_primitives));
        // cell Valid
        var td_v = tr.insertCell(2);
        var p_valid_pc = Math.round(report.valid_primitives / report.total_primitives * 100);
        var v = report.valid_primitives + ' (' + p_valid_pc + '%)';
        td_v.appendChild(document.createTextNode(v));
        // cell Invalid
        var td_i = tr.insertCell(3);
        var p_invalid_pc = Math.round(report.invalid_primitives / report.total_primitives * 100);
        var i = report.invalid_primitives + ' (' + p_invalid_pc + '%)';
        td_i.appendChild(document.createTextNode(i));
    }

    body.appendChild(tbl);
}

idx_validation_summary();

// Populate index.html with the validation results from the json report
document.getElementById("in_file").innerHTML = report.input_file.split("/").pop();
document.getElementById("version").innerHTML = report.val3dity_version;
document.getElementById("time").innerHTML = report.time;
document.getElementById("planarity_d2p_tol").innerHTML = report.planarity_d2p_tol;
document.getElementById("planarity_n_tol").innerHTML = report.planarity_n_tol;
document.getElementById("snap_tol").innerHTML = report.snap_tol;
document.getElementById("overlap_tol").innerHTML = report.overlap_tol;

document.write('<br>');
error_overview();
)";

