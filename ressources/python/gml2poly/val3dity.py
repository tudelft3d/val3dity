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
import os
import sys
import shutil
import glob
import subprocess
from lxml import etree
from StringIO import StringIO
import gml2poly

VAL3DITYEXE = '/Users/hugo/projects/val3dity/val3dity'
TEMPFOLDER  = '/Users/hugo/temp/tmpolys'

dErrors = {
  101: 'TOO_FEW_POINTS',
  102: 'CONSECUTIVE_POINTS_SAME',
  103: 'RING_NOT_CLOSED',
  104: 'RING_SELF_INTERSECTION',
  105: 'RING_COLLAPSED',
  201: 'INTERSECTION_RINGS',
  202: 'DUPLICATED_RINGS',
  203: 'NON_PLANAR_POLYGON_DISTANCE_PLANE',
  204: 'NON_PLANAR_POLYGON_NORMALS_DEVIATION',
  205: 'POLYGON_INTERIOR_DISCONNECTED',
  206: 'HOLE_OUTSIDE',
  207: 'INNER_RINGS_NESTED',
  208: 'ORIENTATION_RINGS_SAME',
  300: 'NOT_VALID_2_MANIFOLD',
  301: 'TOO_FEW_POLYGONS',
  302: 'SHELL_NOT_CLOSED',
  303: 'NON_MANIFOLD_VERTEX',
  304: 'NON_MANIFOLD_EDGE',
  305: 'MULTIPLE_CONNECTED_COMPONENTS',
  306: 'SHELL_SELF_INTERSECTION',
  307: 'POLYGON_WRONG_ORIENTATION',
  308: 'ALL_POLYGONS_WRONG_ORIENTATION',
  309: 'VERTICES_NOT_USED',
  401: 'SHELLS_FACE_ADJACENT',
  402: 'INTERSECTION_SHELLS',
  403: 'INNER_SHELL_OUTSIDE_OUTER',
  404: 'SOLID_INTERIOR_DISCONNECTED',
}



def main():
  options, args = parse_arguments()
  fin = open(args[0])
  if construct_polys(fin, options.multisurface):
    validate_polys(fin, options.multisurface)
  # shutil.rmtree(TEMPFOLDER)

def construct_polys(fin, multisurface):
  print "Extracting the 3D primitives from the CityGML file"
  if not os.path.exists(TEMPFOLDER):
    os.mkdir(TEMPFOLDER)
  else:
    shutil.rmtree(TEMPFOLDER)
    os.mkdir(TEMPFOLDER)
  re = gml2poly.process(fin, TEMPFOLDER, multisurface)
  return re


def validate_polys(fin, multisurface):
  print "Validating each Solid/MultiSurface"
  # validate each building/shell
  os.chdir(TEMPFOLDER)
  dFiles = {}
  for f in os.listdir(TEMPFOLDER):
    if f[-4:] == 'poly':
      i = (f.split('.poly')[0]).rfind('.')
      f1 = f[:i]
      if f1 not in dFiles:
        dFiles[f1] = [f]
      else:
        dFiles[f1].append(f)
  i = 0
  print "Number of Solids/MultiSurfaces in file:", len(dFiles)
  invalidsolids = 0
  xmlsolids = []
  exampleerrors = []
  for solidname in dFiles:
    t = open(dFiles[solidname][0])
    t.readline()
    if t.readline().split()[1] == '0':
      multisurface = True
    else:
      multisurface = False
    t.close()
    
    # validate with val3dity
    if multisurface:
      str1 = VAL3DITYEXE + " -xml -multisurface " +  " ".join(dFiles[solidname])
    else:
      str1 = VAL3DITYEXE + " -xml " +  " ".join(dFiles[solidname])
    op = subprocess.Popen(str1.split(' '),
                          stdout=subprocess.PIPE, 
                          stderr=subprocess.PIPE)
    R = op.poll()
    if R:
       res = op.communicate()
       raise ValueError(res[1])
    o =  op.communicate()[0]
    if o.find('ERROR') != -1:
      invalidsolids += 1
      i = o.find('<errorCode>')
      while (i != -1):
        if exampleerrors.count(o[i+11:i+14]) == 0:
          exampleerrors.append(o[i+11:i+14])
        tmp = o[i+1:].find('<errorCode>')
        if tmp == -1:
          i = -1
        else:
          i = tmp + i + 1
      if multisurface:
        o = '\t<Solid>\n\t\t<id>' + solidname + '</id>\n' + o + '\t</Solid>'
      else:
        o = '\t<MultiSurface>\n\t\t<id>' + solidname + '</id>\n' + o + '\t</MultiSurface>'
      xmlsolids.append(o)
 

  totalxml = []
  totalxml.append('<ValidatorContext>')
  totalxml.append('\t<inputFile>' + fin.name + '</inputFile>')
  totalxml.append("\n".join(xmlsolids))
  totalxml.append('</ValidatorContext>')
  s = fin.name
  s = s[:-4] + '_report.xml'
  fout = open(s, 'w')
  fout.write('\n'.join(totalxml))
  fout.close()
  if multisurface:
    print "Invalid MultiSurfaces: ", invalidsolids
  else:
    print "Invalid Solids: ", invalidsolids
  print "Errors present:"
  for each in exampleerrors:
    print each, dErrors[int(each)]
  print "Report of the validation:", s

def parse_arguments():
    usage = "Usage: %prog [options] input\n(--help for a list of options)"
    parser = OptionParser(usage)
    parser.add_option("-s", "--multisurface",
                      action="store_true", dest="multisurface", default=False)
    (options, args) = parser.parse_args()

    if len(args) != 1:
        parser.error("The input file (*.gml or *.xml) must be specified.")
    fIn = args[0]
    if fIn[-3:] != "gml" and fIn[-3:] != "xml":
        parser.error("The input file must be a GML/XML file.")
    return options, args


if __name__ == "__main__":
    main()
  
