import sys
import StringIO

def main():
  fIn = open(sys.argv[1])
  # fOut = open(sys.argv[1]+".off", 'w')
  fOut = convert(fIn)
  print fOut.getvalue()

def convert(fIn):
  fOut = StringIO.StringIO()
  #-- skip the header
  l = fIn.next()
  while (len(l) == 0) or (l[0] == '#'):
    l = fIn.next()


  numVertices = int(l.split()[0])
  lstVertices = []
  for i in range(numVertices):
    lstVertices.append(fIn.next())

  #-- skip the crap in between
  l = fIn.next()
  while (len(l) < 3) or (l[0] == '#'):
    l = fIn.next()

  numFaces = int(l.split()[0])
  lstFaces = []
  holes = []
  for i in range(numFaces):
    l = fIn.next()
    if l.split()[0] == "1":
      lstFaces.append(fIn.next())
    else:
      lstFaces.append(fIn.next())
      holes.append(len(lstFaces))
      lstFaces.append(fIn.next())
      fIn.next()

  fOut.write("OFF\n" + str(numVertices) + " " + str(len(lstFaces)) + " 0\n")
  for l in lstVertices:
    v = l.split()
    fOut.write(v[1] + " " + v[2] + " " + v[3] +"\n")
  for i,l in enumerate(lstFaces):
    if holes.count(i) == 0:
      fOut.write(l)
    else:
      fOut.write(l[:-1] + "\t255\t0\t0\n")
  return fOut

if __name__ == "__main__":
    main()  

