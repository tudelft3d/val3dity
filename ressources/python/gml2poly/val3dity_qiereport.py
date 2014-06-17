import os
import sys
import shutil
import glob
import subprocess
from lxml import etree
from StringIO import StringIO
import gml2poly

VAL3DITY_FOLDER = '/Users/hugo/projects/val3dity'
VAL3DITYEXE     = '%s/val3dity' % (VAL3DITY_FOLDER)
GML2POLY_EXE    = 'python %s/ressources/python/gml2poly/gml2poly.py' % (VAL3DITY_FOLDER)
TEMPFOLDER      = 'tmp'
SNAP            = 0.001

dErrors = {
  100: 'REPEATED_POINTS',
  110: 'RING_NOT_CLOSED',   
  120: 'RING_SELF_INTERSECT',
  200: 'SELF_INTERSECTION',  
  210: 'NON_PLANAR_SURFACE',                     
  220: 'INTERIOR_DISCONNECTED',
  230: 'HOLE_OUTSIDE',
  240: 'HOLES_ARE_NESTED',                      
  250: 'ORIENTATION_RINGS_SAME',
  300: 'NOT_VALID_2_MANIFOLD',
  301: 'SURFACE_NOT_CLOSED',                     
  302: 'DANGLING_FACES',                         
  303: 'FACE_ORIENTATION_INCORRECT_EDGE_USAGE',  
  304: 'FREE_FACES',                             
  305: 'SURFACE_SELF_INTERSECTS',                
  306: 'VERTICES_NOT_USED',                      
  310: 'SURFACE_NORMALS_WRONG_ORIENTATION',      
  400: 'SHELLS_FACE_ADJACENT',                   
  410: 'SHELL_INTERIOR_INTERSECT',               
  420: 'INNER_SHELL_OUTSIDE_OUTER',              
  430: 'INTERIOR_OF_SHELL_NOT_CONNECTED', 
}


def main():
    os.chdir(sys.argv[1])
    ingmls = glob.glob('*.gml')
    print ingmls

    for gml in ingmls:
        if (construct_polys(gml) == 1):
            print "constructed."
            validate_polys(gml)
        # shutil.rmtree(TEMPFOLDER)


def construct_polys(gml):
    print "\nExtracting the <gml:Solids> for", gml
    if not os.path.exists(TEMPFOLDER):
        os.mkdir(TEMPFOLDER)
    else:
        shutil.rmtree(TEMPFOLDER)
        os.mkdir(TEMPFOLDER)
    s = "%s %s %s --snap_tolerance %s" % (GML2POLY_EXE, gml, TEMPFOLDER, SNAP)
    os.system(s)
    polys = os.listdir(TEMPFOLDER)
    if len(polys) == 1 and polys[0] == 'error': 
        return 0
    else:
        return 1


def validate_polys(gml):
  dFiles = {}
  for f in os.listdir('./tmp'):
    if f[-4:] == 'poly':
      i = (f.split('.poly')[0]).rfind('.')
      f1 = f[:i]
      if f1 not in dFiles:
        dFiles[f1] = [f]
      else:
        dFiles[f1].append(f)

  for solidname in dFiles:
    # validate with val3dity
    str1 = VAL3DITY_FOLDER + "/val3dity -xml " +  " ".join(dFiles[solidname])
    print str1
    op = subprocess.Popen(str1.split(' '),
                          stdout=subprocess.PIPE, 
                          stderr=subprocess.PIPE)
    R = op.poll()
    if R:
      res = op.communicate()
      raise ValueError(res[1])
    o =  op.communicate()[0]
    if o.find('ERROR') != -1:
      i = o.find('<errorCode>')
      while (i != -1):
        # if exampleerrors.count(o[i+11:i+14]) == 0:
          # exampleerrors.append(o[i+11:i+14])
        tmp = o[i+1:].find('<errorCode>')
        if tmp == -1:
          i = -1
        else:
          i = tmp + i + 1
      # o = '\t<Solid>\n\t\t<id>' + solidname + '</id>\n' + o + '\t</Solid>'
    
  # totalxml = []
  # totalxml.append('<val3dity>')
  # a = (gml).rfind('/')
  # totalxml.append('\t<inputFile>' + (gml)[a+1:] + '</inputFile>')
  # totalxml.append('\t<snaptolerance>' + str(SNAP) + '</snaptolerance>')
  # # totalxml.append('\t<time>' + time + '</time>')
  # totalxml.append("\n".join(xmlsolids))
  # totalxml.append('</val3dity>')
  
  # summary += "Number of invalid solids: %d\n" % invalidsolids
  # if (invalidsolids == 0):
  #   summary += "Hourrraaa!\n"
  # else:
  #   summary += "Errors present:\n"
  #   for each in exampleerrors:
  #     summary += each + " " + str(dErrors[int(each)]) + "\n"
  # return totalxml, summary

if __name__ == "__main__":
    main()
  
