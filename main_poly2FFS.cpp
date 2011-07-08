/*
Copyright (c) 2011, Hugo Ledoux
All rights reserved.
 
Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:
1. Redistributions of source code must retain the above copyright
   notice, this list of conditions and the following disclaimer.
2. Redistributions in binary form must reproduce the above copyright
   notice, this list of conditions and the following disclaimer in the
   documentation and/or other materials provided with the distribution.
3. All advertising materials mentioning features or use of this software
   must display the following acknowledgment:
   This product includes software developed by the <organization>.
4. Neither the name of the <organization> nor the
   names of its contributors may be used to endorse or promote products
   derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY <COPYRIGHT HOLDER> ''AS IS'' AND ANY
EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL <COPYRIGHT HOLDER> BE LIABLE FOR ANY
DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/


#include "input.h"
#include <isession.h>
#include <ilogfile.h>
#include <ifeature.h>
#include <igeometrytools.h>
#include <imesh.h>
 
// -----------------------------------------------------------
// Usage documentation for this method goes here.
//
int main(int argc, char* const argv[])
{

  if (argc < 2)
  {
    cout << "You have to give at least one input POLY file." << endl;
    return(0);
  }

  vector<fullShell*> polyhedraShells;
  readAllShells((argc-1), argv, polyhedraShells);

  // Initialize FMEObjects
  IFMESession* session(NULL);
  FME_createSession(session);
  session->init(NULL);
  IFMEGeometryTools* gt = session->getGeometryTools();

  IFMEMesh* mesh = gt->createMesh();
  vector<Point3>& thislsPts = polyhedraShells[0]->lsPts; // helpful alias

  // Add the vertex pool
  for (unsigned int i(0); i< thislsPts.size(); i++)
  {
     mesh->appendVertex(thislsPts[i].x(), thislsPts[i].y(), thislsPts[i].z());
  }

  // Read in all the faces (for now, into one big mesh).
  for (unsigned int j(0); j< polyhedraShells[0]->shell.size(); j++)
  {
     // Add all the triangles for this face
     vector<int*>& thistrs = polyhedraShells[0]->shell[j]; // helpful alias
     FME_UInt32 triangle[3];
     for (vector<int*>::const_iterator ittr = thistrs.begin() ; ittr != thistrs.end(); ittr++)
     {
        int* a = *ittr;
        triangle[0] = a[0];
        triangle[1] = a[1];
        triangle[2] = a[2];
        mesh->addMeshPart(3, triangle, NULL, NULL, 0);
     }
  }

  // See what we got...
  IFMEFeature* feature = session->createFeature();
  feature->setGeometry(mesh); mesh = NULL;
  session->logFile()->setFileName("C:\tmp\val3dity.log", FME_FALSE);
  session->logFile()->logFeature(*feature);

  // Shut down FMEObjects
  FME_destroySession(session);
  session = NULL;

  return(0);
}

