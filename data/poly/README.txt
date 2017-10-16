

All the datasets are stored in the [POLY](http://tetgen.berlios.de/fformats.poly.html) format: 


# cube
  * unit cube with 6 faces
  * valid

# cube2 / 206
  * unit cube with a hole in top face located outside
  * invalid (in 2D the top face is not acc. to SFS)

# cube3 / 302_1
  * unit cube with a hole (inner ring) in the top face
  * invalid (the inner ring isn't filled by another face, so not watertight)

# cube4 / 306_2
  * unit cube with one extra face inside another face
  * invalid 

# cube5
  * cube3 where there are extra faces that fill the hole on top face
  * valid

# cube6
  * cube5 where hole (inner ring) is touching the outer ring of a face
  * valid

# cube8 / 304
  * unit cube with an extra vertex on an edge. Only one of the 2 incident faces has
it explicitly. 
  * invalid (geometrically valid, but topologically invalid. Thus: invalid) 
  * note: Oracle Spatial reports valid 

# cube9 / 307
  * unit cube with one face (face #0) with opposite orientation
  * invalid

# cube10 / 302
  * unit cube with one face missing (bottom one)
  * invalid

# cube11 / 304_1
  * unit cube with one extra face in the middle, splitting the cube in two parts
  * invalid

# cube12 / 303
  * unit cube with one dangling face touching the cube at one point only; the dangling face is the last in the list
  * invalid

# cube13
  * cube3 with one surface filling the hole
  * valid

# cube14
  * axis-aligned cube with normals all pointing inwards
  * invalid
  
# cube14r
  * axis-UNaligned cube with normals all pointing inwards; 
  * invalid
 
# cube14r2
  * axis-UNaligned cube with normals all pointing outwards; the first extreme point along x has a flat star
  * valid
  
# cube15
  * cube with one dangling face, touching only at one point; the dangling face is the 1st in the list
  * invalid

# cube16 / 305
  * cube with one extra face "floating" in the air, not touching
  * invalid

# cube17 / 105
  * cube3 where inner ring is collapsed to a line
  * invalid

# cube18 / 104
  * cube1 where top face has a bow tie 
  * invalid

# cube19 / 208
  * unit cube with a hole (inner ring) in the top face having same orientation as outer ring
  * invalid

# cube20 / 301
  * flat cube, ie with volume of 0, only 2 surfaces
  * invalid

# cube21 / 305_1
  * 2 unit cubes not touching at all, one above the other separated by 1unit
  * invalid

# cube22
  * unit cube with top face having 3 triangles forming the square
  * valid

# cube23 / 104_1
  * unit cube with top face having a self-intersecting surface (2D invalid), 2 of the faces of cube22 are 'bundled' as one polygon (which self-intersects)
  * invalid: 2D projected surface is not valid, but whole in 3D is

# cube25
  * cube translated by (99999990, 99999990) so that big coordinates
  * valid

# cube26
  * cube translated by (3333399999990, 3333399999990) so that big coordinates
  * valid
  
# cube27
  * cube with -100.0 as z-coordinates
  * valid

# cube28 / 101
  * cube top face a line (with only 2 vertices)
  * invalid

# cube29 / 303_1
  * 2 unit cubes touching at one vertex
  * invalid

# cube30 / 202
  * unit cube with a duplicate inner ring top face
  * invalid

# cube31 / 201
  * unit cube with a intersecting rings in top face
  * invalid

# cube32 / 205
  * unit cube with a polygon with interior disconnected in top face
  * invalid

# cube33 / 207
  * unit cube with a polygon with nested rings in top face
  * invalid

# duplicates / 102
  * cube with one duplicate vertex (repeated in a ring)
  * invalid

# toofewpts / 101
  * cube with top face having only 2 points
  * invalid

# toofewpolys / 301_1
  * cube with only 3 surfaces
  * invalid

# p1e-?
  * cube with one point of top surface moved upward by 1e-? units
  * valid? it depends on the tolerance used

# snap1e-?
  * cube with top surface having one vertex moved a bit, to test snapping in GML input
  * valid? it depends on the tolerance used

# pfold1
  * cube with an almost vertical fold in the top surface, aka as the "Kevin Wiebe's case" 
  * The shift is 1mm, so a plane fitting doesn't detect that case well.
  * invalid

# pfold2
  * cube with a vertical fold in the top surface, aka as the "Kevin Wiebe's case" 
  * The shift is 1mm, so a plane fitting doesn't detect that case well.
  * a vertical shift makes the projection tricky
  * invalid

# m26
  * solid #26 in "Josef's Muchen data"
  * surface #12 ain't planar 

# m41
  * solid #41 in "Josef's Muchen data", crashing is no translation
  * valid


# concave
  * concave shape; top and bottom faces are concave polygons
  * valid

# torus
  * a "squared donut", genus of the shell is 1
  * valid

# torus2 / 306_3
  * torus where the hole in the top/bottom faces touches the side surfaces
  * invalid

# house
  * cube with a pyramidal roof
  * valid

# house2 / 306
  * house with tip below the ground
  * invalid

# house3 /306_1
  * house with tip touching the bottom faces
  * invalid

# house4
  * house with a flat roof (4 triangular faces)
  * valid

# py1 / inner_pyramid
  * invalid as outer shell (all normals pointing inwards)
  * a pyramid used as inner shell for cube
  * cube + py1 = valid

# py2 / inner_pyramid_1
  * invalid as outer shell (all normals pointing inwards)
  * pyramid touching top face one point. 
  * cube + py2 = valid
  * (Oracle is wrong on that one: oracle=54513)

# py3 / 401_1
  * invalid as outer shell (all normals pointing inwards)
  * pyramid intersecting the cube (tip goes through the top face)
  * cube + py3 = invalid
  * (Oracle agrees: oracle=54512)

# py4 / 401_6
  * invalid as outer shell (all normals pointing inwards)
  * bottom face is shared with bottom face of the cube
  * cube + py4 = invalid

# py5 / inner_pyramid_2
  * invalid as outer shell (all normals pointing inwards)
  * touching py1 at one point
  * cube + py1 + py5 = valid

# py6 / inner_pyramid_3
  * invalid as outer shell (all normals pointing inwards)
  * touching py1 along an edge
  * cube + py1 + py6 = valid

# py7 / 401_4
  * invalid as outer shell (all normals pointing inwards)
  * sharing a face with py1 (face connected)
  * cube + py1 + py7 = invalid (2 holes face touching)

# py8 / 401_5
  * invalid as outer shell (all normals pointing inwards)
  * sharing *partly* a face with py1 
  * cube + py1 + py8 = invalid (2 holes face touching)

# py9 / 403
  * invalid as outer shell (all normals pointing inwards)
  * pyramid complete outside the outer shell of cube
  * cube + py9 = invalid

# py10 / 403_1
  * invalid as outer shell (all normals pointing inwards)
  * pyramid outside the outer shell of cube, but face adjacent
  * cube + py10 = invalid

# py11
  * invalid as outer shell (all normals pointing inwards)
  * pyramid encloses the whole cube
  * cube + py11 = invalid

# blocker1
  * invalid as outer shell (all normals pointing inwards)
  * kinda pyramid that splits the interior of cube into 2 non-connected parts
  * cube + blocker1 = invalid

