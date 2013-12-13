#!/usr/bin/env python
import sys

def main():
  if len(sys.argv) == 1:
    print "No input shell(s) given"
    sys.exit()
  header_stuff()
  lsShells = []
  processoneshell(open(sys.argv[1], 'r'), True)
  for f in sys.argv[2:]:
    processoneshell(open(f, 'r'), False)
  footer_stuff()

def processoneshell(s, exterior=True):  
  nov = int(s.readline().split()[0])
  lsPts = []
  for i in range(nov):
    lsPts.append(map(float, s.readline().split()[1:4]))
  if (exterior == True):
    print '\t\t\t\t\t<gml:exterior>'
  else:
    print '\t\t\t\t\t<gml:interior>'

  print '\t\t\t\t\t\t<gml:CompositeSurface>'
  nof = int(s.readline().split()[0])
  for i in range(nof):
    print '\t\t\t\t\t\t\t<gml:surfaceMember>'
    print '\t\t\t\t\t\t\t\t<gml:Polygon>'
    print '\t\t\t\t\t\t\t\t\t<gml:exterior>'
    print '\t\t\t\t\t\t\t\t\t\t<gml:LinearRing>'
    a = map(int, s.readline().split())
    oring = map(int, s.readline().split())
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
        iring = map(int, s.readline().split())
        iring.pop(0)
        poly = []
        for each in iring:
          poly.append('\t\t\t\t\t\t\t\t\t\t\t<gml:pos>' + str(lsPts[each][0]) + " " + str(lsPts[each][1]) + " " + str(lsPts[each][2])  + '</gml:pos>')
        poly.append('\t\t\t\t\t\t\t\t\t\t\t<gml:pos>' + str(lsPts[iring[0]][0]) + " " + str(lsPts[iring[0]][1]) + " " + str(lsPts[iring[0]][2])  + '</gml:pos>')
        print "\n".join(poly)
        s.readline().split() #--pass that line
      print '\t\t\t\t\t\t\t\t\t\t</gml:LinearRing>'
      print '\t\t\t\t\t\t\t\t\t</gml:interior>'
    print '\t\t\t\t\t\t\t\t</gml:Polygon>'    
    print '\t\t\t\t\t\t\t</gml:surfaceMember>'
  print '\t\t\t\t\t\t</gml:CompositeSurface>'
  if (exterior == True):
    print '\t\t\t\t\t</gml:exterior>'
  else:
    print '\t\t\t\t\t</gml:interior>'


    
def header_stuff():
  print '<?xml version="1.0" encoding="utf-8"?>'
  # print '<CityModel xmlns="http://www.citygml.org/citygml/1/0/0" xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance" xmlns:xlink="http://www.w3.org/1999/xlink" xmlns:gml="http://www.opengis.net/gml" xsi:schemaLocation="http://www.citygml.org/citygml/1/0/0 http://www.citygml.org/citygml/1/0/0/CityGML.xsd">'
  print '<CityModel xmlns:gml="http://www.opengis.net/gml" xmlns:bldg="http://www.opengis.net/citygml/building/2.0" xmlns:xlink="http://www.w3.org/1999/xlink" xmlns:xAL="urn:oasis:names:tc:ciq:xsdschema:xAL:2.0" xmlns:dem="http://www.opengis.net/citygml/relief/2.0" xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance" xmlns="http://www.opengis.net/citygml/2.0">'
  print '\t<cityObjectMember>'
  print '\t\t<Building>'
  print '\t\t\t<lod1Solid>'
  print '\t\t\t\t<gml:Solid>'

def footer_stuff():
  print '\t\t\t\t</gml:Solid>'
  print '\t\t\t</lod1Solid>'
  print '\t\t</Building>'
  print '\t</cityObjectMember>'
  print '</CityModel>'

  
if __name__ == "__main__":
  main()
