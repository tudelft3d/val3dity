
from optparse import OptionParser
import sys
import string
import StringIO
import os
import shutil
from lxml import etree
import subprocess
from geomtools import Point, Vector
import geomtools
from gmltypes import Ring, Surface, Shell

ns = {}
bVerbose = False
TEMPFOLDER = ""

def main():
    options, args = parse_arguments()
    st = 1e-3
    if options.snap_tolerance is not None:
        st = options.snap_tolerance
    process(args[0], args[1], st)


def process(fIn, tempfolder, snap_tolerance = 1e-3):
    global TEMPFOLDER
    TEMPFOLDER = tempfolder

    try:
        t = float(snap_tolerance)
        if (t >= 0.0):
            print "Using tolerance for snapping of", snap_tolerance
            geomtools.TOLERANCE = float(snap_tolerance)
        else:
            print "snap tolerance can't be negative, using 1e-3."
    except:
        print "snap tolerance impossible, using 1e-3."

    parser = etree.XMLParser(ns_clean=True)
    tree = etree.parse(fIn, parser)
    root = tree.getroot()
    for key in root.nsmap.keys():
        if root.nsmap[key].find('www.opengis.net/gml') != -1:
            ns['gml'] = "%s" % root.nsmap[key]

    if ns['gml'] is None:
        print "The file doesn't have the GML namespace."
        return 0

    solidid = 1
    try:
        for solid in root.findall(".//{%s}Solid" % ns['gml']):
            gmlid = solid.get("{%s}id" % ns['gml'])
            if gmlid == None:
                gmlid = str(solidid)
            solidid += 1
            shells = [Shell(solid.find("{%s}exterior" % ns['gml']), ns['gml'])]
            for ishellnode in solid.findall("{%s}interior" % ns['gml']):
                shells.append(Shell(ishellnode, ns['gml']))
            for i, shell in enumerate(shells):
                write_shell_to_file_poly(gmlid, shell, i)
        print "Number of POLY files created:", solidid-1
    except:
        print "ERROR: problems while parsing the XML file."
        return 0
    return 1


def write_shell_to_file_poly(gmlid, shell, no = 0):
    try:
        name = "%s/%s.%d.poly" % (TEMPFOLDER, gmlid, no)
        fOut = open(name, 'w')
        fOut.write(shell.str_poly().getvalue())
        fOut.close()
        # print "Output written to " + name
    except IOError, (errno, strerror):
        print "I/O error(%s): %s" % (errno, strerror)


def clean_xml_tag(tag):
    """Desc:  Method to clean a xml tag, so that the {} in the ns are removed

       In:    tag: string of the namespace
       Out:   the cleaned tag

    """
    tag = tag.lstrip('{')
    tag = tag.rstrip('}')
    return tag


def parse_arguments():
    usage = "Usage: %prog [options] input\n(--help for a list of options)"
    parser = OptionParser(usage)
    parser.add_option("--snap_tolerance", dest="snap_tolerance",
                      help="tolerance for snapping of vertices (default: 1e-3 unit)")
    parser.add_option("-v", "--verbose",
                      action="store_true", dest="verbose")
    parser.add_option("-q", "--quiet",
                      action="store_false", dest="verbose", default=False)
    (options, args) = parser.parse_args()

    if len(args) != 2:
        parser.error("The input file (*.gml or *.xml) must be specified; and the folder for the POLYs.")
    fIn = args[0]
    if fIn[-3:] != "gml" and fIn[-3:] != "xml":
        parser.error("The input file must be a GML/XML file.")
    return options, args


if __name__ == "__main__":
    main()

