import sys
import StringIO

def main():
  fIn = open(sys.argv[1])
  # fIn = open('/Users/hugo/temp/cgal-bug/a2.obj')
  # fIn = open('/Users/hugo/temp/cgal-bug/a_cleaned.off.obj')
  fOut = convert(fIn)
  print fOut.getvalue()

def convert(fIn):
  fOut = StringIO.StringIO()
  #-- skip the header
  lsVertices = []
  lsFaces = []
  for l in fIn:
    if (len(l) == 0) or (l[0] == '#'):    
      continue
    if (l[0] == 'v'):
      lsVertices.append(l)
    if (l[0] == 'f'):
      lsFaces.append(l)  
  # print len(lsVertices)
  # print len(lsFaces)
  fOut.write("OFF\n" + str(len(lsVertices)) + " " + str(len(lsFaces)) + " 0\n")
  for i in lsVertices:
    v = i.split()
    fOut.write(v[1] + " " + v[2] + " " + v[3] +"\n")
  for i in lsFaces:
    f = i.split()
    le = len(f) - 1
    fOut.write(str(le) + " ")
    for each in f[1:]:
      st = int(each) - 1
      fOut.write(str(st) + " ")
    fOut.write("\n")
  return fOut





  # while (len(l) == 0) or (l[0] == '#'):
  #   l = fIn.next()
  # lstVertices = []
  # while (l[0] == 'v')
  #   lstVertices.append(l[2:])
  #   l = fIn.next()
    
  # for i in range(numVertices):
  #   lstVertices.append(fIn.next())
  # #-- skip the crap in between
  # l = fIn.next()
  # while (len(l) < 3) or (l[0] == '#'):
  #   l = fIn.next()
  # numFaces = int(l.split()[0])
  # lstFaces = []
  # holes = []
  # for i in range(numFaces):
  #   l = fIn.next()
  #   if l.split()[0] == "1":
  #     lstFaces.append(fIn.next())
  #   else:
  #     print "ERROR: Holes present, use TetGen to produce a (triangulated) OFF file."
  #     sys.exit()
  # fOut.write("OFF\n" + str(numVertices) + " " + str(len(lstFaces)) + " 0\n")
  # for l in lstVertices:
  #   v = l.split()
  #   fOut.write(v[1] + " " + v[2] + " " + v[3] +"\n")
  # for i,l in enumerate(lstFaces):
  #   fOut.write(l)
  # return fOut

if __name__ == "__main__":
    main()  

 

