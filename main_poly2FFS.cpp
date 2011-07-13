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
#include <iline.h>
#include <idonut.h>
#include <icompositesurface.h>
#include <isimplearea.h>
#include <ipolygon.h>
#include <iface.h>
#include <isurface.h>
#include <ibrepsolid.h>

#include <iwriter.h>

void parseFilename( const std::string &inputFilename, std::string &outputpath, std::string &outputbasename );

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

  // Initialize FMEObjects
  IFMESession* session(NULL);
  FME_createSession(session);
  session->init(NULL);
  IFMEGeometryTools* gt = session->getGeometryTools();

  // Use the val3dity code to read in the .poly file
  vector<polyhedraShell*> polyhedraShells;
  readAllPolyhedraShells((argc-1), argv, polyhedraShells);

  // Let's loop through all the polyhedraShells we read in (one from each file)
  IFMEBRepSolid* polyhedraSolid = NULL;
  for(unsigned int phs(0); phs<polyhedraShells.size(); phs++)
  {
     polyhedraShell* thisPolyhedra = polyhedraShells[phs]; // helpful alias
     vector<Point3>& thislsPts = thisPolyhedra->lsPts; // helpful alias

     // Read in all the faces.
     IFMECompositeSurface* compositeSurface = gt->createCompositeSurface();
     for (unsigned int j(0); j< thisPolyhedra->shells.size(); j++)
     {
        // Add all the shells for this face.  The first one is the outer one.
        vector< vector<int> >& thisShell = thisPolyhedra->shells[j]; // helpful alias
        IFMESimpleArea* outerBoundary = NULL;
        IFMEDonut* boundary = NULL;
        for (unsigned int k(0); k < thisShell.size(); k++)
        {
           vector<int>& thisRing = thisShell[k]; // helpful alias
           IFMELine* oneLine = gt->createLineWithD(FME_TRUE);
           for (unsigned int v(0); v < thisRing.size(); v++)
           {
              oneLine->appendPointXYZ(thislsPts[thisRing[v]].x(), thislsPts[thisRing[v]].y(), thislsPts[thisRing[v]].z());
           }

           // Is this the outer one?
           if (0==k)
           {
              outerBoundary = gt->createPolygonByCurve(oneLine); oneLine = NULL;
           }
           else if (1==k) // the first hole?
           {
              boundary = gt->createDonutBySimpleArea(outerBoundary); outerBoundary = NULL;
              boundary->addInnerBoundaryCurve(oneLine); oneLine = NULL;
           }
           else
           {
              boundary->addInnerBoundaryCurve(oneLine); oneLine = NULL;
           }
        }

        if (NULL == boundary)
        {
           // We could make a triangle mesh here.
           //compositeSurface->appendPart(gt->createTriangulatedMeshFromGeometry(gt->createFaceByArea(outerBoundary, FME_CLOSE_3D_EXTEND_MODE))); outerBoundary = NULL;
           compositeSurface->appendPart(gt->createFaceByArea(outerBoundary, FME_CLOSE_3D_EXTEND_MODE)); outerBoundary = NULL;
        }
        else
        {
           // We could make a triangle mesh here.
           //compositeSurface->appendPartgt->createTriangulatedMeshFromGeometry(g(gt->createFaceByArea(boundary, FME_CLOSE_3D_EXTEND_MODE))); boundary = NULL;
           compositeSurface->appendPart(gt->createFaceByArea(boundary, FME_CLOSE_3D_EXTEND_MODE)); boundary = NULL;
        }
     }

     // Let's not have a composite if we just have one part.
     IFMESurface* finalSurface = NULL;
     if (1 == compositeSurface->numParts())
     {
        finalSurface = compositeSurface->removeEndPart();
     }
     else
     {
        finalSurface = compositeSurface;
     }
     compositeSurface = NULL;

     if (NULL == polyhedraSolid)
     {
        polyhedraSolid = gt->createBRepSolidBySurface(finalSurface);
     }
     else
     {
        polyhedraSolid->addInnerSurface(finalSurface);
     }
     finalSurface = NULL;
  }

  // Let's make the name of our output file.  This is harder than it needs to be!
  std::string outputfile;
  std::string outputpath;
  std::string outputbasename;
  for(int fname(1); fname<argc; fname++)
  {
     parseFilename(argv[fname], outputpath, outputbasename);
     if (fname>1)
     {
        outputfile += "_";
     }
     outputfile += outputbasename;
  }
  std::string outputfileName = outputpath + outputfile + ".ffs";

  // make a purdy little feature
  IFMEFeature* feature = session->createFeature();
  feature->setGeometry(polyhedraSolid); polyhedraSolid = NULL;
  feature->setFeatureType(outputfile.data());

  // Output what we got...
  IFMEUniversalWriter *wtr = session->createWriter("FFS", NULL);
  IFMEStringArray* parameters = session->createStringArray();
  wtr->open(outputfileName.data(), *parameters);
  wtr->write(*feature);
  wtr->close();

  // Clean up
  session->destroyFeature(feature); feature = NULL;
  session->destroyStringArray(parameters); parameters = NULL;
  session->destroyWriter(wtr); wtr = NULL;

  // Shut down FMEObjects
  FME_destroySession(session);
  session = NULL;

  return(0);
}

void parseFilename( const std::string &inputFilename, std::string &outputpath, std::string &outputbasename )
{
   // let's get the location to be the same as the first input file.
   int basenameloc(-1);
   basenameloc = inputFilename.find_last_of('/');
   if (-1==basenameloc)
   {
      basenameloc = inputFilename.find_last_of('\\');
   }
   if (-1!=basenameloc)
   {
      outputpath = inputFilename.substr(0,basenameloc+1);
   }

   int extentionloc = inputFilename.find_last_of('.');
   int extentionlength = inputFilename.size()-extentionloc;
   int basenamelength = inputFilename.size()-basenameloc-extentionlength-1;
   outputbasename = inputFilename.substr(basenameloc+1,basenamelength);
}

