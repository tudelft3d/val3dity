
# csol1.gml
CompositeSolid with 2 cubes adjacent
valid

# csol2.gml
CompositeSolid with 3 cubes adjacent
cube 1-2 overlap 
invalid: 501

# csol3.gml
CompositeSolid with 3 cubes 
cube 1 is not connected to other
invalid: 503

# csol4.gml
CompositeSolid with 3 cubes
cube 1-2 are identical 
invalid: 502

# csol5.gml
CompositeSolid with 3 cubes
cube 0 has an invalid ring
invalid: 104

# csol6.gml
CompositeSolid with 2 cubes
cube 0 has a missing face
invalid: 302
