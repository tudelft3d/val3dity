#!/usr/bin/env python

import sys

def main():
  status = 0
  fin = open(sys.argv[1])
  for l in fin:
    ll = l.split()
    if not ( (len(ll) == 0) or (ll[0] == "#") ):
      if status == 0:
        print ll[0], "3 0 0"
        status += 1
      elif status == 1:
        if len(ll) < 4:
          status += 1
          print ll[0], 0
        else:
          print " ".join(ll[0:4])
      elif status == 2:
        if ll.count('#') > 0:
          i = ll.index('#')
          ll = ll[:i]
        if (len(ll) != (int(ll[0])+1)):
          if len(ll) == 1:
            print ll[0], "0"
          elif len(ll) == 4: #-- hole point line
            print " ".join(ll)
          else:
            print ll[0], ll[1]
        else:
          print " ".join(ll)

  
if __name__ == "__main__":
  main()
