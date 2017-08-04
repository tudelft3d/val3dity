import sys
from lxml import etree
import uuid

def main():
    fIn = sys.argv[1]
    parser = etree.XMLParser(ns_clean=True)
    tree = etree.parse(fIn, parser)
    root = tree.getroot()
    for key in root.nsmap.keys():
        if root.nsmap[key].find('www.opengis.net/gml') != -1:
            gmlns = "%s" % root.nsmap[key]

    solidid = 1
    for solid in root.findall(".//{%s}Solid" % gmlns):
        gmlid = solid.get("{%s}id" % gmlns)
        if gmlid == None:
            solid.set("{%s}id" % gmlns, str(uuid.uuid4()))
        solidid += 1
      
    fOut = open(sys.argv[2], 'w')
    fOut.write(etree.tostring(root, pretty_print=True))
    fOut.close()
    return 1


if __name__ == "__main__":
    main()

