from lxml import etree
import sys

#-- global variable for namespaces used in the input file
ns = {}

fIn = sys.argv[1]
parser = etree.XMLParser(ns_clean=True)
tree = etree.parse(fIn, parser)
root = tree.getroot()
for key in root.nsmap.keys():
    if root.nsmap[key].find('http://www.opengis.net/citygml/building/') != -1:
        ns['cgml_building'] = "%s" % root.nsmap[key]
    if root.nsmap[key].find('www.opengis.net/gml') != -1:
        ns['gml'] = "%s" % root.nsmap[key]
    if root.nsmap[key].find('www.citygml.org') != -1:
        ns['cgml'] = "%s" % root.nsmap[key]
        print "yes citygml"

if ns['gml'] is None:
    print "The file doesn't have the GML namespace."
    sys.exit()

solids = root.findall(".//{%s}Solid" % ns['gml'])
print "# gml:Solids:", len(solids)

buildings = root.findall(".//{%s}Building" % ns['cgml_building'])
print "# Buildings:", len(buildings)
for b in buildings:
    a = b.findall(".//{%s}Solid" % ns['gml'])
    if len(a) == 0:
        print "Building w/o gml:Solid"
    else:
        print "all buildings have solids"
