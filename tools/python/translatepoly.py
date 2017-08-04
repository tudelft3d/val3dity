import sys
import StringIO

def main():
    fIn = open(sys.argv[1])
    fOut = translate(fIn)
    print fOut.getvalue()

def translate(fIn):
    fOut = StringIO.StringIO()
    #-- skip the header
    l = fIn.next()
    while (len(l) == 0) or (l[0] == '#'):
        l = fIn.next()
    numVertices = int(l.split()[0])
    lsV = []
    for i in range(numVertices):
        v = fIn.next().split()
        lsV.append([int(v[0]), float(v[1]), float(v[2]), float(v[3])])
    #-- find the minx and miny
    minx = 9e10
    miny = 9e10
    for v in lsV:
        if (v[1] < minx):
            minx = v[1]
        if (v[2] < miny):
            miny = v[2]
    # print minx, miny
    #--translate
    fOut.write("%d 3 0 0\n" % len(lsV))
    for i,v in enumerate(lsV):
        fOut.write("%d %f %f %f\n" % 
                  (i, 
                  v[1] - minx, 
                  v[2] - miny,
                  v[3])
                  )
    #-- write the rest as is
    try:
        l = fIn.next()
        while (l != None):
            fOut.write(l)
            l = fIn.next()
    except:
        return fOut

if __name__ == "__main__":
    main()  

