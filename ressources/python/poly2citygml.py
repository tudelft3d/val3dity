#!/usr/bin/env python

import sys


def main():
  
  fin = open(sys.argv[1])
  
  nov = int(fin.readline().split()[0])
  lsPts = []
  for i in range(nov):
    lsPts.append(map(float, fin.readline().split()[1:4]))
  
  print '\t\t\t\t<gml:Solid>'
  print '\t\t\t\t\t<gml:exterior>'
  print '\t\t\t\t\t\t<gml:CompositeSurface>'
  
  nof = int(fin.readline().split()[0])
  for i in range(nof):
    print '\t\t\t\t\t\t\t<gml:surfaceMember>'
    print '\t\t\t\t\t\t\t\t<gml:Polygon>'
    print '\t\t\t\t\t\t\t\t\t<gml:exterior>'
    print '\t\t\t\t\t\t\t\t\t\t<gml:LinearRing>'
    a = map(int, fin.readline().split())
    oring = map(int, fin.readline().split())
    oring.pop(0)
    poly = []
    for each in oring:
      poly.append('\t\t\t\t\t\t\t\t\t\t\t<gml:pos>' + str(lsPts[each][0]) + " " + str(lsPts[each][1]) + " " + str(lsPts[each][2])  + '</gml:pos>')
    poly.append('\t\t\t\t\t\t\t\t\t\t\t<gml:pos>' + str(lsPts[oring[0]][0]) + " " + str(lsPts[oring[0]][1]) + " " + str(lsPts[oring[0]][2])  + '</gml:pos>')
    print "\n".join(poly)
    print '\t\t\t\t\t\t\t\t\t\t</gml:LinearRing>'
    print '\t\t\t\t\t\t\t\t\t</gml:exterior>'    
    
    if a[0] > 1:
      print '\t\t\t\t\t\t\t\t\t<gml:interior>'
      print '\t\t\t\t\t\t\t\t\t\t<gml:LinearRing>'
      for j in range(a[0]-1):
        iring = map(int, fin.readline().split())
        iring.pop(0)
        poly = []
        for each in iring:
          poly.append('\t\t\t\t\t\t\t\t\t\t\t<gml:pos>' + str(lsPts[each][0]) + " " + str(lsPts[each][1]) + " " + str(lsPts[each][2])  + '</gml:pos>')
        poly.append('\t\t\t\t\t\t\t\t\t\t\t<gml:pos>' + str(lsPts[iring[0]][0]) + " " + str(lsPts[iring[0]][1]) + " " + str(lsPts[iring[0]][2])  + '</gml:pos>')
        print "\n".join(poly)
        fin.readline().split() #--pass that line
      print '\t\t\t\t\t\t\t\t\t\t</gml:LinearRing>'
      print '\t\t\t\t\t\t\t\t\t</gml:interior>'
    
    print '\t\t\t\t\t\t\t\t</gml:Polygon>'    
    print '\t\t\t\t\t\t\t</gml:surfaceMember>'

  print '\t\t\t\t\t\t</gml:CompositeSurface>'
  print '\t\t\t\t\t</gml:exterior>'
  print '\t\t\t\t</gml:Solid>'

    #     print '<gml:Solid>'
    #     print '<gml:exterior>'
    #     print '<gml:CompositeSurface>'
    #     print self.get_surface_member(floor)
    #     print self.get_surface_member(ceiling)
    #     print self.get_walls()
    #     print '</gml:CompositeSurface>'
    #     print '</gml:exterior>'
    #     print '</gml:Solid>'


if __name__ == "__main__":
  # Load shape file

  print '<?xml version="1.0" encoding="utf-8"?>'
  print '<CityModel xmlns="http://www.citygml.org/citygml/1/0/0" xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance" xmlns:xlink="http://www.w3.org/1999/xlink" xmlns:gml="http://www.opengis.net/gml" xsi:schemaLocation="http://www.citygml.org/citygml/1/0/0 http://www.citygml.org/citygml/1/0/0/CityGML.xsd">'
  print '\t<cityObjectMember>'
  print '\t\t<Building>'
  print '\t\t\t<lod1Solid>'
  main()
  print '\t\t\t</lod1Solid>'
  print '\t\t</Building>'
  print '\t</cityObjectMember>'
  print '</CityModel>'

#/* ex: set ts=4 sw=4 expandtab: */
