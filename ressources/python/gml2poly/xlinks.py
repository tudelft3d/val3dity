from lxml import etree
import sys

ns = {}

fIn = '/Users/hugo/data/val3dity/Munchen/LOD2_4424_5482_solid.gml'

parser = etree.XMLParser(ns_clean=True)
tree = etree.parse(fIn, parser)
root = tree.getroot()
for key in root.nsmap.keys():
    if root.nsmap[key].find('http://www.opengis.net/citygml/building/') != -1:
        ns['cgml_building'] = "%s" % root.nsmap[key]
    if root.nsmap[key].find('www.opengis.net/gml') != -1:
        ns['gml'] = "%s" % root.nsmap[key]
    if root.nsmap[key].find('www.w3.org/1999/xlink') != -1:
        ns['xlink'] = "%s" % root.nsmap[key]
    if root.nsmap[key].find('www.citygml.org') != -1:
        ns['cgml'] = "%s" % root.nsmap[key]

if ns['gml'] is None:
    print "The file doesn't have the GML namespace."
    sys.exit()

print ns['xlink']


# print root.xpath("{%s}href" % ns['xlink'])
# sys.exit()

# solids = root.findall(".//{%s}Solid" % ns['gml'])
# print "# gml:Solids:", len(solids)

r = root.findall(".//{%s}surfaceMember[@{%s}href]" % (ns['gml'], ns['xlink']))
if r is not None:
    print "sm", len(r)
d = {}
for each in r:
    x = each.attrib["{%s}href" % ns['xlink']]
    for n in root.findall(".//{%s}Polygon[@{%s}id]" % (ns['gml'], ns['gml'])):
        if n.attrib["{%s}id" % ns['gml']] == x:
            d[x] = n
            # print n.tag
            # each.append(x)
            # etree.SubElement(each, n)
            break
print len(d)

#-- one test
r = root.find(".//{%s}surfaceMember[@{%s}href]" % (ns['gml'], ns['xlink']))
a = r.attrib["{%s}href" % ns['xlink']]
if a is not None:
    print a
    n = d[a]
else:
    n = etree.SubElement(r, '{%s}Polygon' % ns['gml'], nsmap=ns)    

for x in n:
    print x
    for y in x:
        for z in y:
            print z.text

print "\ndone."


# [0].attrib["{%s}href" % ns['xlink']]

# r = root.findall(".//{%s}Polygon[@{%s}href]" % (ns['gml'], ns['xlink']))
# if r is not None:
#     print "sm", len(r)
# r = root.findall(".//{%s}Solid[@{%s}href]" % (ns['gml'], ns['xlink']))
# if r is not None:
#     print "sm", len(r)


# buildings = root.findall(".//{%s}Building" % ns['cgml_building'])
# print "# Buildings:", len(buildings)
# for b in buildings:
#     a = b.findall(".//{%s}Solid" % ns['gml'])
#     if len(a) == 0:
#         print "Building w/o gml:Solid"
#     else:
#         print "all buildings have solids"
