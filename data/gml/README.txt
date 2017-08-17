
# csol1.gml
CompositeSolid with 2 cubes adjacent
valid

# csol1b.gml
CompositeSolid with 2 cubes adjacent, file w/o CityGML namespace!
a dummy GenericGML is put instead
valid


# csol2.gml
CompositeSolid with 3 cubes adjacent
cube 1-2 overlap by 1cm
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

# csol7.gml
CompositeSolid with: (1) cube+py1; (2) py1 filling the void
valid

# csol8.gml
CompositeSolid with: (1) cube+py1; (2) py1 filling the void
but intersection of the two
invalid: 501

# msol1.gml
MultiSolid with 2 cubes
valid 

# msol2.gml
MultiSolid with 3 cubes adjacent
valid 

# msol3.gml
MultiSolid with 2 cubes
cube 0 has a missing face
invalid: 302