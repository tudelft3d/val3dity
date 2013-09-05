===============================================

All the datasets are stored in the POLY format: 
http://tetgen.berlios.de/fformats.poly.html

===============================================


cube
----
cube with 6 faces
valid

cube3
-----
cube with a hole in the top face
invalid: the inner ring isn't filled by another face, so not watertight

cube4
-----
one extra inner rings in another face
invalid: not watertight either

cube5
-----
cube3 where there are faces that fill the hole on top face
valid

cube6
-----
cube5 where hole is touching.
valid

cube8
-----
cube with an extra vertex on an edge. Only one of the 2 incident faces has
it explicitly. 
Is it valid? No idea... topology vs geometry. Oracle says 'valid'.

cube9
---------
cube with one face (face #0) with opposite orientation.
invalid
(oracle=54502)

cube10
------
cube with one face (bottom one) missing.
invalid
(oracle=54502)

cube11
------
cube with one extra face in the middle, splitting the cube  in two parts
invalid
(oracle=54502)

cube12
------
cube with one dangling face touching at one point only
the dangling face is the last in the list
invalid
(oracle=54502)

cube13
-------
cube with top face not planar
invalid

cube14
------
cube with normal pointing inwards
invalid

cube15
------
cube with one dangling face, touching only at one point.
the dangling face is the 1st in the list
invalid

cube16
------
cube with one extra face floating in the air, not touching
invalid

concave
------
cube but with concave top/bottom faces
valid

torus
-----
a "squared donut"
valid

torus2
------
torus where the hole touches the outside.
invalid.

house
-----
cube with a pyramidal roof
valid

house2
------
house with tip below the ground
invalid: self-intersection

house3
------
house with tip touching the bottom faces
invalid: self-intersection

house4
------
house with a flat roof (4 triangular faces)
valid


py1
---
a pyramid used as inner shell for cube
py1 = valid (although orientation of faces are wrong)
cube + py1 = valid

py2
---
pyramid touching top face one point. 
py2 = valid (although orientation of faces are wrong)
cube + py2 = valid
(Oracle is wrong on that one: oracle=54513)

py3
---
pyramid intersecting the cube (tip goes through the top face)
py3 = valid (although orientation of faces are wrong)
cube + py3 = invalid
Oracle agrees: oracle=54512

py4
---
bottom face is shared with bottom face of the cube
py4 = valid (although orientation of faces are wrong)
cube + py4 = invalid

py5
---
touching py1 at one point
cube + py1 + py5 = valid


py6
---
touching py1 along an edge
cube + py1 + py6 = valid

py7
---
sharing a face with py1 (face connected)
cube + py1 + py7 = invalid (2 holes face touching)

py8
---
sharing *partly* a face with py1 
cube + py1 + py8 = invalid (2 holes face touching)

py9
---
pyramid complete outside the outer shell of cube
py9 = valid (although orientation of faces are wrong)
cube + py9 = invalid

py10
----
pyramid outside the outer shell of cube, but face adjacent
py10 = valid (although orientation of faces are wrong)
cube + py10 = invalid


py11
----
pyramid encloses the whole cube
py11 = valid (although orientation of faces are wrong)
cube + py11 = invalid

blocker1
--------
kinda pyramid that splits the interior of cube into 2 non-connected parts
blocker1 = valid (although orientation of faces are wrong)
cube + blocker1 = invalid






