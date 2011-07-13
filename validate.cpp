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

#include "validate.h"

// CGAL classes
#include <CGAL/Triangulation_vertex_base_with_info_2.h>
#include <CGAL/Constrained_triangulation_plus_2.h>
#include <CGAL/intersections.h>
#include <CGAL/Polygon_2.h>
#include <CGAL/basic.h>

#include <CGAL/Polyhedron_3.h>
#include <CGAL/IO/Polyhedron_iostream.h>
#include <CGAL/intersections.h>

#include <CGAL/Nef_polyhedron_3.h>
#include <CGAL/IO/Nef_polyhedron_iostream_3.h>

// CGAL typedefs
typedef CGAL::Triangulation_vertex_base_with_info_2 <unsigned,K>  Vb;
typedef CGAL::Constrained_triangulation_face_base_2<K>            Fb;
typedef CGAL::Triangulation_data_structure_2<Vb,Fb>               TDS;
typedef CGAL::Exact_intersections_tag                             Itag;
typedef CGAL::Constrained_triangulation_2<K, TDS, Itag>           CTa;
typedef CGAL::Constrained_triangulation_plus_2<CTa>               CT;
typedef CGAL::Polygon_2<K> Polygon;

typedef CGAL::Polyhedron_3<K>       Polyhedron;
typedef CGAL::Polyhedron_3<Ke>       PolyhedronExact;
typedef CGAL::Nef_polyhedron_3<Ke>  Nef_polyhedron;

// misc
#define PI 3.14159265

bool is_face_planar(const vector<int*>& trs, const vector<Point3>& lsPts, float angleTolerance = 1);
bool checkPlanarityFaces(vector< vector<int*> >&shell, vector<Point3>& lsPts);
bool check2manifoldness(Polyhedron* p);
CGAL::Orientation checkGlobalOrientationNormales(Polyhedron* p);
Polyhedron* getPolyhedronDS(const vector< vector<int*> >&shell, const vector<Point3>& lsPts);
bool isPolyhedronGeometricallyConsistent(Polyhedron* p);
Polyhedron* validateTriangulatedPolyhedraShell(triangulatedPolyhedraShell& tshell, bool isOutershell);


//--------------------------------------------------------------

void validatePolyHedra(vector<triangulatedPolyhedraShell*> &polyhedraShells, bool& isValid)
{
   isValid = true;

   if (polyhedraShells.size() < 1)
   {
      cout << "You have to give at least one input polyhedron." << endl;
      isValid = false;
      return;
   }

   cout << "Validating " << polyhedraShells.size() << " shell(s)." << endl << endl;

   // First, let's do a quick validation of the outer shell
   cout << "Reading outer shell: " << 0 << endl;

   Polyhedron* p = validateTriangulatedPolyhedraShell(*(polyhedraShells[0]), true);  
   if (p != NULL)
      cout << "Outer shell valid.\n" << endl;
   else
      cout << "Outer shell invalid.\n" << endl;

    vector<Polyhedron*> polyhedra;
    polyhedra.push_back(p);  

    for (unsigned int i=1; i<polyhedraShells.size(); i++)
    {
       cout << "Validating inner shell #" << (i-1) << endl;

       p = validateTriangulatedPolyhedraShell(*(polyhedraShells[i]), false);  
       if (p != NULL)
          cout << "Inner shell valid.\n" << endl;
       else
          cout << "Inner shell invalid.\n" << endl;
       polyhedra.push_back(p);
    }

    //-- if all the shells are valid, then put them in a Nef_polyhedron type
    vector<Polyhedron*>::iterator polyhedraIt = polyhedra.begin();
    for ( ; polyhedraIt != polyhedra.end(); polyhedraIt++)
    {
       if (*polyhedraIt == NULL)
       {
          isValid = false;
          break;
       }
    }
    if (isValid == true)
    {
       if (polyhedra.size() == 1)
          cout << "Solid is valid." << endl;
       else
       {
          cout << "Calculating interactions between the shells." << endl;
          vector<Nef_polyhedron> nefs;
          for (polyhedraIt = polyhedra.begin(); polyhedraIt != polyhedra.end(); polyhedraIt++)
          {
             stringstream offrep (stringstream::in | stringstream::out);
             offrep << **polyhedraIt;
             PolyhedronExact pe;
             offrep >> pe;
             Nef_polyhedron onef(pe);
             nefs.push_back(onef);
          }
          vector<Nef_polyhedron>::iterator nefsIt = nefs.begin();
          Nef_polyhedron solid = *nefsIt;
          nefsIt++;
          for ( ; nefsIt != nefs.end(); nefsIt++) 
             solid -= *nefsIt;
          if (solid.number_of_volumes() == (polyhedra.size()+1))
             cout << "Valid solid. Hourrraaa!" << endl;
          else
             cout << "Invalid solid :(" << endl;
       }
    }
    return;

}


bool checkPlanarityFaces(vector< vector<int*> >&shell, vector<Point3>& lsPts)
{
  vector< vector<int*> >::iterator faceIt = shell.begin();
  int i = 0;
  bool isValid = true;
  for ( ; faceIt != shell.end(); faceIt++)
  {
    if (is_face_planar(*faceIt, lsPts) == false)
    {
      cout << "\tFace #" << i << " not planar" << endl;
      isValid = false;
    }
    i++;
  }
  return isValid;
}  
  
Polyhedron* validateTriangulatedPolyhedraShell( triangulatedPolyhedraShell& tshell, bool isOutershell )
{
   bool isValid = true;
   if (checkPlanarityFaces(tshell.shell, tshell.lsPts) == true)
   {
      Polyhedron* p = getPolyhedronDS(tshell.shell, tshell.lsPts);
      //-- check if polyhedron is 2-manifold (includes intersection tests)
      bool isValid = check2manifoldness(p);
      //-- check if orientation of the normales is outwards or inwards
      if (isValid == true)
      {
         CGAL::Orientation orient = checkGlobalOrientationNormales(p);
         if ( ((isOutershell == true) && (orient != CGAL::CLOCKWISE)) || ((isOutershell == false) && (orient != CGAL::COUNTERCLOCKWISE)) ) 
         {
            cout << "\tNormales all pointing in wrong direction." << endl;
            isValid = false;
         }
      }
      if (isValid == true)
         return p;
      else 
      {
         delete p;
         return NULL;
      }
   }
   else
      return NULL;
}
  
  

CGAL::Orientation checkGlobalOrientationNormales(Polyhedron* p)
{
  //-- get a 'convex corner', sorting order is x-y-z
  Polyhedron::Vertex_iterator vIt;
  vIt = p->vertices_begin();
  Polyhedron::Vertex_handle cc = vIt;
  vIt++;

  for ( ; vIt != p->vertices_end(); vIt++)
  {
    if (vIt->point().x() > cc->point().x())
      cc = vIt;
    else if (vIt->point().x() == cc->point().x())
    {
      if (vIt->point().y() > cc->point().y())
        cc = vIt;
      else if (vIt->point().y() == cc->point().y())
      {
        if (vIt->point().z() > cc->point().z())
          cc = vIt;
      }
    }
  }
//  cout << "CONVEX CORNER IS: " << cc->point() << endl;

  Polyhedron::Halfedge_handle curhe = cc->halfedge();
  Polyhedron::Halfedge_handle otherhe;
  otherhe = curhe->opposite()->next();
  CGAL::Orientation orient = orientation( curhe->vertex()->point(),
                                          curhe->next()->vertex()->point(),
                                          curhe->next()->next()->vertex()->point(),
                                          otherhe->vertex()->point() );
  
  while (orient == CGAL::COPLANAR)
  {
    otherhe = otherhe->next()->opposite()->next();
    orient = orientation( curhe->vertex()->point(),
                          curhe->next()->vertex()->point(),
                          curhe->next()->next()->vertex()->point(),
                          otherhe->vertex()->point() );
  }
  return orient;
}


bool check2manifoldness(Polyhedron* p)
{
  bool isValid = true;
//-- 1. check combinatorial consistency ---
  if (p->empty() == true)
  {
    std::cout << "\tOne/several of the faces have wrong orientation, or dangling faces." << std::endl;
    isValid = false;
  }
  else
  {
    if (p->is_closed() == false)
    {
      cout << "\tOne or more faces are missing, 2-manifold not closed." << endl;
      // TODO: find the missing faces and report
      isValid = false;
    }
    else
    {
// 2. check geometrical consistency (aka intersection tests between faces) ---
      isValid = isPolyhedronGeometricallyConsistent(p);
    }
  }
  return isValid;

//  if (isValid == true)
//  {
//    cout << "2-manifold valid." << endl;
//    cout << "# vertices: " << p->size_of_vertices() << endl;
//    cout << "# faces: " << p->size_of_facets() << endl;
//  }
}



bool isPolyhedronGeometricallyConsistent(Polyhedron* p)
{
  bool isValid = true;
  Polyhedron::Facet_iterator curF, otherF;
  curF = p->facets_begin();
  for ( ; curF != p->facets_end(); curF++)
  {
    Polyhedron::Halfedge_handle heH;
    heH = curF->halfedge();
    Polyhedron::Vertex_handle vh[3];
    vh[0] = heH->vertex();
    vh[1] = heH->next()->vertex();
    vh[2] = heH->next()->next()->vertex();

    //-- check all the incident faces to the 3
    set<Polyhedron::Facet_handle> incidentFaces;
    set<Polyhedron::Facet_handle>::iterator itFh;
    Polyhedron::Halfedge_around_vertex_circulator circ;
    for (int i=0; i<3; i++)
    {
      circ = vh[i]->vertex_begin();
      do 
      {
        incidentFaces.insert(circ->facet());
      } while ( ++circ != vh[i]->vertex_begin() );
    }
    
    otherF = p->facets_begin();
    Triangle t1( vh[0]->point(), vh[1]->point(), vh[2]->point() );
    int count = 0;
    for ( ; otherF != p->facets_end(); otherF++)
    {
      if (otherF != curF)
      {
        Polyhedron::Halfedge_handle heoH = otherF->halfedge();
        Triangle t2( heoH->vertex()->point(), heoH->next()->vertex()->point(), heoH->next()->next()->vertex()->point() );
        
        CGAL::Object re = intersection(t1, t2);
        K::Point_3 apoint;
        K::Segment_3 asegment;
        if (assign(asegment, re))
          count++;
        else if (assign(apoint, re) && (incidentFaces.count(otherF) == 0) )
        {
          cout << "\tSelf-intersection of type POINT." << endl;
          isValid = false;
        }
      }
    }
    if (count > 3)
    {
      cout << "\tSelf-intersection of type SEGMENT." << endl;
      isValid = false;
    }
  }
  return isValid;
}





Polyhedron* getPolyhedronDS(const vector< vector<int*> >&shell, const vector<Point3>& lsPts)
{
  //-- construct the 2-manifold, using the "batch" way
  stringstream offrep (stringstream::in | stringstream::out);
  vector< vector<int*> >::const_iterator it = shell.begin();
  int noFaces = 0;
  for ( ; it != shell.end(); it++)
    noFaces += it->size();
  offrep << "OFF" << endl << lsPts.size() << " " << noFaces << " 0" << endl;

  vector<Point3>::const_iterator itPt = lsPts.begin();
  for ( ; itPt != lsPts.end(); itPt++)
    offrep << *itPt << endl;

  for (it = shell.begin(); it != shell.end(); it++)
  {
    vector<int*>::const_iterator it2 = it->begin();
    for ( ; it2 != it->end(); it2++)
    {
      int* tmp = *it2;
      offrep << "3 " << tmp[0] << " " << tmp[1] << " " << tmp[2] << endl;
    }
  }
  Polyhedron* P = new Polyhedron();
  offrep >> *P;
  return P;
}

bool is_face_planar(const vector<int*> &trs, const vector<Point3>& lsPts, float angleTolerance)
{
   vector<int*>::const_iterator ittr = trs.begin();
   int* a = *ittr;
   Vector v0 = unit_normal( lsPts[a[0]], lsPts[a[1]], lsPts[a[2]]);
   ittr++;
   bool isPlanar = true;
   for ( ; ittr != trs.end(); ittr++)
   {
      a = *ittr;
      Vector v1 = unit_normal( lsPts[a[0]], lsPts[a[1]], lsPts[a[2]] );
      if ( (acos(CGAL::to_double(v0*v1))*180/PI) > angleTolerance)
      {
         //      cout << "---face not planar " << (acos((double)(v0*v1))*180/PI) << endl;
         isPlanar = false;
         break;
      }
   }
   return isPlanar;
}

