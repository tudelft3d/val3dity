#!/usr/bin/env python

import os, sys

#DESCRIPTION
#the original version is made by Hugo Ledoux
#John modified it to assemble multiple polys (with semantics) into a CityGML
#the semantics (optional) of a poly is represented as
#first line: "# " + building id(string)
#for each face: number of outer ring(int) + " " + number of inner ring(int) + " # " + surface id(string) + " # " + surface semantics(string)
#surface semantics is the code list of boundary surfaces(BUILDING_WALL_SURFACE; BUILDING_ROOF_SURFACE; #BUILDING_GROUND_SURFACE etc.)

def convert():
    
  #open a folder contains multiple poly files
  if len(sys.argv) != 2:
      print 'usage: polys2acitygml.py FOLDERNAME'
      sys.exit()
  str_folderpath = sys.argv[1]
  if not os.path.exists(str_folderpath):
      print 'Folder path ' + str_folderpath + 'does not exist'
      sys.exit()
      
  #open the polyfiles in the folder
  os.chdir(str_folderpath)
  dFiles = []
  for f in os.listdir('.'):
      if f[-4:] == 'poly':
         dFiles.append(f)
  if len(dFiles) == 0:
      print 'No poly files found in the folder'
      sys.exit()
      
  #read all the polyfiles and compose a citygml
  #gml: name Polys2acitygml building
  #gml: Building gml:id
  for f in dFiles:
      #
      str_buildingid = ''
      is_Solid = -1
      #
      fin = open(f)
      #read the first line and try to extract semantics
      str_firstline = fin.readline().split()
      if str_firstline[0] == '#':
          #read the building id
          str_buildingid = str_firstline[1]
          #whether the geometry is a solid:1 or a multisurface:0
          is_Solid = int(fin.readline().split()[1])
          #the point information
          str_firstline = int(fin.readline().split()[0])
      else:
          #no semanics
          str_buildingid = '-1'
          #we assume it is a solid
          is_Solid = 1
          #the point information
          str_firstline = int(str_firstline[0])
      #read all the points
      lsPts = []
      for i in range(str_firstline):
          lsPts.append(map(float, fin.readline().split()[1:4]))
      
      print '\t\t<bldg:Building gml:id="' + str_buildingid + '">'
      #read all the surface and extract thr polygonid and surfacetype, if avaliable
      str_polygontype = ''
      str_polygonid = ''
      
      
      if is_Solid == 1:
          #solid
          print '\t\t\t<bldg:lod2Solid>'
          print '\t\t\t\t<gml:Solid>'
          print '\t\t\t\t\t<gml:exterior>'
          print '\t\t\t\t\t\t<gml:CompositeSurface>'
          
      nof = int(fin.readline().split()[0])
      for i in range(nof):
          #read surface information
          str_polygoninfo = fin.readline().split()
          num_rings = int(str_polygoninfo[0])
          #num_intrings = int(str_polygoninfo[1])
          if len(str_polygoninfo) >= 4:
              str_polygonid = str_polygoninfo[3]
          if len(str_polygoninfo) >= 6:
              str_polygontype = match_surface_type(str_polygoninfo[5])
          #read geometry
          if is_Solid == 1:
              print '\t\t\t\t\t\t\t<gml:surfaceMember>'
              if str_polygonid != '':
                  print '\t\t\t\t\t\t\t\t<gml:Polygon gml:id="' + str_polygonid + '">'
              else:
                  print '\t\t\t\t\t\t\t\t<gml:Polygon>'                  
              #exterior ring
              print '\t\t\t\t\t\t\t\t\t<gml:exterior>'
              print '\t\t\t\t\t\t\t\t\t\t<gml:LinearRing>'
              
              oring = map(int, fin.readline().split())
              oring.pop(0)
              poly = []
              for each in oring:
                  poly.append('\t\t\t\t\t\t\t\t\t\t\t<gml:pos>' + str(lsPts[each][0]) + " " + str(lsPts[each][1]) + " " + str(lsPts[each][2])  + '</gml:pos>')
              poly.append('\t\t\t\t\t\t\t\t\t\t\t<gml:pos>' + str(lsPts[oring[0]][0]) + " " + str(lsPts[oring[0]][1]) + " " + str(lsPts[oring[0]][2])  + '</gml:pos>')
              print "\n".join(poly)
              print '\t\t\t\t\t\t\t\t\t\t</gml:LinearRing>'
              print '\t\t\t\t\t\t\t\t\t</gml:exterior>'      
              
              #interior rings
              if num_rings > 1:
                  for j in range(num_rings-1):
                      print '\t\t\t\t\t\t\t\t\t<gml:interior>'
                      print '\t\t\t\t\t\t\t\t\t\t<gml:LinearRing>'
                      iring = map(int, fin.readline().split())
                      iring.pop(0)
                      poly = []
                      for each in iring:
                          poly.append('\t\t\t\t\t\t\t\t\t\t\t<gml:pos>' + str(lsPts[each][0]) + " " + str(lsPts[each][1]) + " " + str(lsPts[each][2])  + '</gml:pos>')
                      poly.append('\t\t\t\t\t\t\t\t\t\t\t<gml:pos>' + str(lsPts[iring[0]][0]) + " " + str(lsPts[iring[0]][1]) + " " + str(lsPts[iring[0]][2])  + '</gml:pos>')
                      print "\n".join(poly)
                      print '\t\t\t\t\t\t\t\t\t\t</gml:LinearRing>'
                      print '\t\t\t\t\t\t\t\t\t</gml:interior>'
                  for j in range(num_rings-1):
                      fin.readline().split() #--pass the holepoints
              #    
              print '\t\t\t\t\t\t\t\t</gml:Polygon>'    
              print '\t\t\t\t\t\t\t</gml:surfaceMember>'
          else:
              #multisurface
              print '\t\t\t<bldg:boundedBy>'
              if str_polygontype != '':
                  print '\t\t\t\t<bldg:' + str_polygontype + '>'
              print '\t\t\t\t\t<bldg:lod2MultiSurface>'
              print '\t\t\t\t\t\t<gml:MultiSurface>'
              print '\t\t\t\t\t\t\t<gml:surfaceMember>'
              if str_polygonid != '':
                  print '\t\t\t\t\t\t\t\t<gml:Polygon gml:id="' + str_polygonid + '">'
              else:
                  print '\t\t\t\t\t\t\t\t<gml:Polygon>'
              #exterior ring
              print '\t\t\t\t\t\t\t\t\t<gml:exterior>'
              print '\t\t\t\t\t\t\t\t\t\t<gml:LinearRing>'
              
              oring = map(int, fin.readline().split())
              oring.pop(0)
              poly = []
              for each in oring:
                  poly.append('\t\t\t\t\t\t\t\t\t\t\t<gml:pos>' + str(lsPts[each][0]) + " " + str(lsPts[each][1]) + " " + str(lsPts[each][2])  + '</gml:pos>')
              poly.append('\t\t\t\t\t\t\t\t\t\t\t<gml:pos>' + str(lsPts[oring[0]][0]) + " " + str(lsPts[oring[0]][1]) + " " + str(lsPts[oring[0]][2])  + '</gml:pos>')
              print "\n".join(poly)
              print '\t\t\t\t\t\t\t\t\t\t</gml:LinearRing>'
              print '\t\t\t\t\t\t\t\t\t</gml:exterior>'    
              
              #interior rings
              if num_rings > 1:
                  for j in range(num_rings-1):
                      print '\t\t\t\t\t\t\t\t\t<gml:interior>'
                      print '\t\t\t\t\t\t\t\t\t\t<gml:LinearRing>'
                      iring = map(int, fin.readline().split())
                      iring.pop(0)
                      poly = []
                      for each in iring:
                          poly.append('\t\t\t\t\t\t\t\t\t\t\t<gml:pos>' + str(lsPts[each][0]) + " " + str(lsPts[each][1]) + " " + str(lsPts[each][2])  + '</gml:pos>')
                      poly.append('\t\t\t\t\t\t\t\t\t\t\t<gml:pos>' + str(lsPts[iring[0]][0]) + " " + str(lsPts[iring[0]][1]) + " " + str(lsPts[iring[0]][2])  + '</gml:pos>')
                      print "\n".join(poly)
                      print '\t\t\t\t\t\t\t\t\t\t</gml:LinearRing>'
                      print '\t\t\t\t\t\t\t\t\t</gml:interior>'
                  for j in range(num_rings-1):
                      fin.readline().split() #--pass the holepoints
                 
              print '\t\t\t\t\t\t\t\t</gml:Polygon>'      
              print '\t\t\t\t\t\t\t</gml:surfaceMember>'
              print '\t\t\t\t\t\t</gml:MultiSurface>'
              print '\t\t\t\t\t</bldg:lod2MultiSurface>'
              if str_polygontype != '':
                  print '\t\t\t\t</bldg:' + str_polygontype + '>'
              print '\t\t\t</bldg:boundedBy>'
              
              
      if is_Solid == 1:
          #solid
          print '\t\t\t\t\t\t</gml:CompositeSurface>'
          print '\t\t\t\t\t</gml:exterior>'         
          print '\t\t\t\t</gml:Solid>'
          print '\t\t\t</bldg:lod2Solid>'
          
          
      #finish        
      print '\t\t</bldg:Building>'
     
     
#match the polygon types to the correct xml node
def match_surface_type(str_polygontype):
    if str_polygontype == 'BUILDING_WALL_SURFACE':
        return 'WallSurface'
    elif str_polygontype == 'BUILDING_ROOF_SURFACE':
        return 'RoofSurface'
    elif str_polygontype == 'BUILDING_GROUND_SURFACE':
        return 'GroundSurface'
    elif str_polygontype == 'BUILDING_CEILING_SURFACE':
        return 'CeilingSurface'
    elif str_polygontype == 'BUILDING_CLOSURE_SURFACE':
        return 'ClosureSurface'
    elif str_polygontype == 'BUILDING_FLOOR_SURFACE':
        return 'FloorSurface'
    elif str_polygontype == 'BUILDING_INTERIORWALL_SURFACE':
        return 'InteriorWallSurface'
    
    
    
if __name__ == "__main__":
  # Load shape file

  print '<?xml version="1.0" encoding="utf-8"?>'
  print '<!-- CityGML Dataset created with the poly2citygml incorporating semantics -->'
  print '''<CityModel xmlns="http://www.opengis.net/citygml/2.0" 
          xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance" 
          xmlns:xlink="http://www.w3.org/1999/xlink" 
          xmlns:bldg="http://www.opengis.net/citygml/building/2.0"
          xmlns:gml="http://www.opengis.net/gml" 
          xsi:schemaLocation="http://www.opengis.net/citygml/2.0 http://schemas.opengis.net/citygml/2.0/cityGMLBase.xsd
              http://www.opengis.net/citygml/appearance/2.0 http://schemas.opengis.net/citygml/appearance/2.0/appearance.xsd
              http://www.opengis.net/citygml/building/2.0 http://schemas.opengis.net/citygml/building/2.0/building.xsd">'''
  print '\t<cityObjectMember>'
  convert()
  print '\t</cityObjectMember>'
  print '</CityModel>'

