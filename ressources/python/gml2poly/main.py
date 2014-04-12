
# val3dity - Copyright (c) 2011, Hugo Ledoux.  All rights reserved.
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
from lxml import etree
import subprocess
from geomtools import Point, Vector
import geomtools
from gmltypes import Ring, Surface, Shell, Solid
from gmltypes import ValidationError

#-- global variable for namespaces used in the input file
ns = {}
bVerbose = False


def main():
    options, args = parse_arguments()
    global bVerbose
    bVerbose = options.verbose

    parser = etree.XMLParser(ns_clean=True)
    tree = etree.parse(args[0], parser)
    root = tree.getroot()
    for key in root.nsmap.keys():
        if root.nsmap[key].find('www.opengis.net/gml') != -1:
            ns['gml'] = "%s" % root.nsmap[key]
        if root.nsmap[key].find('www.citygml.org') != -1:
#--        if root.nsmap[key].find('http://www.opengis.net/citygml/1.0') != -1:
            ns['cgml'] = "%s" % root.nsmap[key]

    if ns['gml'] is None:
        print "The file doesn't have the GML namespace."
        sys.exit()

    if options.all == True:
        print "Validating all the solids"
        total = 0
        valid = 0
        invalid = 0
        for solid in root.findall(".//{%s}Solid" % ns['gml']):
            oshell = Shell(solid.find(".//{%s}exterior" % ns['gml']), ns['gml'])
            write_shell_to_file_poly('/tmp/s.poly', oshell)
            args = '/Users/hugo/projects/val3dity/code/cpp/val3dity /tmp/s.sh0.poly'.split()
            p = subprocess.Popen(args,stdout=subprocess.PIPE,stderr=subprocess.STDOUT)
            p.wait()
            if (p.returncode == 1):
                valid += 1
            else:
                invalid += 1
            total += 1
#            if total == 5:
#                break
        print "total:", total
        print "\tvalid:", valid
        print "\tinvalid", invalid
        sys.exit()

    solidnode = fetch_solid_node_from_gml_file(root, options)

#-- testing with MULTISURFACES and semantic 
#--    solidnode = root.find(".//{%s}cityObjectMember" % ns['cgml'])
    
    shells = [] #-- all the shells, including the outer one
    print "Processing outer shell"
    oshell = Shell(solidnode.find(".//{%s}exterior" % ns['gml']), ns['gml'])
    shells.append(oshell)
    
    print "# surface in oshell", shells[0].number_of_surfaces()
    print "# points in oshell", shells[0].number_of_points()
    #-- save in tetgen format
    write_shell_to_file_poly(args[0], oshell)
    write_shell_to_off_poly(args[0], oshell)

    #-- process interior shell(s), if any
    for i in solidnode.findall("{%s}interior" % ns['gml']):
        s = Shell(i, ns['gml'])
        # parse_gml_shell(i, s)
        shells.append(s)

    try:
        shells[0].validate()
    except ValidationError, inst:
        print inst
        sys.exit()

    print "done."



def fetch_solid_node_from_gml_file(root, options):
    """Desc:  Fetch the desired gml:Solid from a GML file

       In:    root: root of the gml file
              options: .solid contains the gml:id of the gml:Solid
                       .building contains the gml:id of the building
                       .lod contains the lod (1 -> 5)
       Out:   the node in the xml file of the gml:Solid is returned

       Note:  If the desired building/lod is not found in the file, an Exception
              is raised.

    """
    found = False
    if options.solid is None and options.building is None:
        thesolid = root.find(".//{%s}Solid" % ns['gml'])
        if thesolid is None:
            if root.tag == ("{%s}Solid" % ns['gml']):
                thesolid = root
                found = True
            else:
                raise Exception("The input file doesn't contain any gml:Solid.")
        else:
            found = True
    elif found == False and options.solid is not None:
        if options.verbose:
            print "Looking for gml:Solid %s" % options.solid
        for i in root.findall(".//{%s}Solid" % ns['gml']):
            if i.get("{%s}id" % ns['gml']) == options.solid:
                thesolid = i
                found = True
                break
        if found == False:
            raise Exception("The solid " + options.solid + " is not in the input file.")
        else:
            if options.verbose == True:
                print "Processing gml:Solid %s" % options.solid
    elif found == False: #-- maybe a CityGML file
        if options.building == None:
            thebuilding = root.find(".//{%s}Building" % ns['cgml'])
            if thebuilding != None:
                found = True
        else:
            if options.verbose:
                print "Looking for Building %s" % options.building
            for i in root.findall(".//{%s}Building" % ns['cgml']):
                if i.get("{%s}id" % ns['gml']) == options.building:
                    thebuilding = i
                    found = True
                    break
            if found == False:
                for i in root.findall(".//{%s}BuildingPart" % ns['cgml']):
                    if i.get("{%s}id" % ns['gml']) == options.building:
                        thebuilding = i
                        found = True
                        break
        if found == False:
            raise Exception("Building not found in the file.")

        #-- is the Building in buildingParts?
        parts = thebuilding.findall("{%s}consistsOfBuidingPart" % ns['cgml'])
        if len(parts) != 0:
            raise Exception("The building " + str(thebuilding.get("{%s}id" % ns['gml'])) + " consists of several parts, give one as input.")

        #-- find the correct lod for the building
        thesolid = None
        if options.lod == None:
            for child in thebuilding:
                if 'lod' in clean_xml_tag(child.tag):
                    lodsolid = child
                    thesolid = child.find("{%s}Solid" % ns['gml'])
                    break
        else:
            lodsolid = thebuilding.find("{%s}lod%sSolid" %  (ns['cgml'], options.lod))
            if lodsolid != None:
                thesolid = lodsolid.find("{%s}Solid" % ns['gml'])
        if thesolid == None:
            raise Exception("The building with given LOD doesn't exist in the file.")
        if options.verbose == True:
            print "Processing", thebuilding.get("{%s}id" % ns['gml']), "with", lodsolid.tag
    return thesolid




def write_shell_to_file_poly(fIn, shell):
    try:
        name = "".join([fIn[:fIn.rfind('.')], ".sh0.poly"])
        fOut = open(name, 'w')
        fOut.write(shell.str_poly().getvalue())
        fOut.close()
#        print "Output written to " + name
    except IOError, (errno, strerror):
        print "I/O error(%s): %s" % (errno, strerror)

def write_shell_to_off_poly(fIn, shell):
    try:
        name = "".join([fIn[:fIn.rfind('.')], ".sh0.off"])
        fOut = open(name, 'w')
        fOut.write(shell.str_off().getvalue())
        fOut.close()
        print "Output written to " + name
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
    parser.add_option("-s", "--solid", dest="solid",
                      help="Which gml:Solid in the input file to take (default is first)")
    parser.add_option("-b", "--building", dest="building",
                      help="Which building in the input file to take (default is first)")
    parser.add_option("-l", "--lod", dest="lod",
                      help="Which LOD of the building to use (default is first)")
    parser.add_option("-a", "--all", dest="all", action='store_true',
                      help="Validate all the Solids in the file.")
    parser.add_option("-v", "--verbose",
                      action="store_true", dest="verbose")
    parser.add_option("-q", "--quiet",
                      action="store_false", dest="verbose", default=False)
    (options, args) = parser.parse_args()

    if len(args) != 1:
        parser.error("The input file (*.gml or *.xml) must be specified.")
    fIn = args[0]
    if fIn[-3:] != "gml" and fIn[-3:] != "xml":
        parser.error("The input file must be a GML/XML file.")
    if options.lod is not None and options.building is None:
        parser.error("Specify the building for which you want that specific LOD.")
    return options, args


if __name__ == "__main__":
    main()

