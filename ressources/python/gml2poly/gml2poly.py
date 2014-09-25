# val3dity - Copyright (c) 2011-2014, Hugo Ledoux.  All rights reserved.
# 
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions are met:
#     * Redistributions of source code must retain the above copyright
#       notice, this list of conditions and the following disclaimer.
#     * Redistributions in binary form must reproduce the above copyright
#       notice, this list of conditions and the following disclaimer in the
#       documentation and/or other materials provided with the distribution.
#     * Neither the name of the authors nor the
#       names of its contributors may be used to endorse or promote products
#       derived from this software without specific prior written permission.
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
# ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
# WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
# DISCLAIMED. IN NO EVENT SHALL HUGO LEDOUX BE LIABLE FOR ANY
# DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
# (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
# LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
# ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
# (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS


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
    process(args[0], args[1], options.multisurface, st)


def process(fIn, tempfolder, multisurface, snap_tolerance = '1e-3'):
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

    try:
        parser = etree.XMLParser(ns_clean=True)
        tree = etree.parse(fIn, parser)
        root = tree.getroot()
        for key in root.nsmap.keys():
            if root.nsmap[key].find('www.opengis.net/gml') != -1:
                ns['gml'] = "%s" % root.nsmap[key]
            if root.nsmap[key].find('www.w3.org/1999/xlink') != -1:
                ns['xlink'] = "%s" % root.nsmap[key]

        if ns['gml'] is None:
            print "The file doesn't have the GML namespace."
            return 0

        #-- handling of (potential) xlinks
        dxlinks = {}
        if 'xlink' in ns:
            print "Oh no, the file might contain xlinks :/"
            print "Parsing whole file to find and store them."
            nodes = root.findall(".//{%s}surfaceMember[@{%s}href]" % (ns['gml'], ns['xlink']))
            if nodes is not None:
                print "There are %d xlinks for gml:surfaceMember" % len(nodes)
                for node in nodes:
                    x = node.attrib["{%s}href" % ns['xlink']]
                    if x[0] == '#':
                        x = x[1:]
                    for n in root.findall(".//{%s}Polygon[@{%s}id]" % (ns['gml'], ns['gml'])):
                        if n.attrib["{%s}id" % ns['gml']] == x:
                            dxlinks[x] = n
                            break
            print "dico of xlinks", len(dxlinks)
        else:
            dxlinks = None

        if (multisurface == True):
        #-- Process <gml:MultiSurface> instead of <gml:Solid>
            msid = 1
            for ms in root.findall(".//{%s}MultiSurface" % ns['gml']):
                gmlid = ms.get("{%s}id" % ns['gml'])
                if gmlid == None:
                    gmlid = str(msid)
                msid += 1
                ms = Shell(ms, dxlinks, ns)
                write_shell_to_file_poly(gmlid, ms, 0)
            print "Number of POLY files created:", msid-1
        else:
            solidid = 1
            for solid in root.findall(".//{%s}Solid" % ns['gml']):
                gmlid = solid.get("{%s}id" % ns['gml'])
                if gmlid == None:
                    gmlid = str(solidid)
                solidid += 1
                shells = [Shell(solid.find("{%s}exterior" % ns['gml']), dxlinks, ns)]
                for ishellnode in solid.findall("{%s}interior" % ns['gml']):
                    shells.append(Shell(ishellnode, dxlinks, ns))
                for i, shell in enumerate(shells):
                    write_shell_to_file_poly(gmlid, shell, i)
            print "Number of POLY files created:", solidid-1
    except:
        name = "%s/error" % (TEMPFOLDER)
        fOut = open(name, 'w')
        fOut.write(name)
        fOut.close()
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
    parser.add_option("-s", "--multisurface",
                      action="store_true", dest="multisurface", default=False)
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

