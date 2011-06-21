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
   must display the following acknowledgement:
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



#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Triangulation_vertex_base_with_info_2.h>
#include <CGAL/Constrained_triangulation_plus_2.h>
#include <CGAL/intersections.h>
#include <CGAL/Polygon_2.h>
#include <CGAL/basic.h>

#include <CGAL/Polyhedron_3.h>
#include <CGAL/IO/Polyhedron_iostream.h>
#include <CGAL/intersections.h>

#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <set>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;

typedef K::Point_2  Point2;
typedef K::Point_3  Point3;
typedef K::Vector_3 Vector;
typedef K::Triangle_3 Triangle;

typedef CGAL::Triangulation_vertex_base_with_info_2 <unsigned,K>  Vb;
typedef CGAL::Constrained_triangulation_face_base_2<K>            Fb;
typedef CGAL::Triangulation_data_structure_2<Vb,Fb>               TDS;
typedef CGAL::Exact_intersections_tag                             Itag;
typedef CGAL::Constrained_triangulation_2<K, TDS, Itag>           CTa;
typedef CGAL::Constrained_triangulation_plus_2<CTa>               CT;
typedef CGAL::Polygon_2<K> Polygon;

typedef CGAL::Polyhedron_3<K>  Polyhedron;

#define PI 3.14159265


using namespace std;


void create_polygon(const vector< Point3 > &lsPts, const vector<int>& ids, Polygon &p);
void construct_ct(const vector< Point3 > &lsPts, const vector< vector<int> >& pgnids, const vector<Polygon>& lsRings, vector<int*>& oneface);
int projection_plane(Point3 p0, Point3 p1, Point3 p2);
bool is_face_planar(const vector<int*>& trs, const vector<Point3>& lsPts, float angleTolerance = 1);
void getTriangulatedShell(ifstream& infile, vector< vector<int*> >&shell, vector<Point3>& lsPts);
void check2manifoldness(Polyhedron* p);
Polyhedron* getPolyhedronDS(const vector< vector<int*> >&shell, const vector<Point3>& lsPts);
bool isPolyhedronGeometricallyConsistent(Polyhedron* p);
void test(void);


//--------------------------------------------------------------

void test(void)
{

}


int main(int argc, char* const argv[])
{
//  test();
//  return 0;
  if (argc != 2)
  {
    cout << "You have to give an input POLY file." << endl;
    exit(1);
  }
  ifstream infile(argv[1], ifstream::in);
  if (!infile)
  {
    cout << "File not there." << endl;
    exit(1);
  }

  vector< Point3 > lsPts;
  vector< vector<int*> > shell; //-- the triangulated shell, each triangle is triplet of IDs from lsPts
  getTriangulatedShell(infile, shell, lsPts);
  
  Polyhedron* p = getPolyhedronDS(shell, lsPts);
  check2manifoldness(p);
  
  delete p;

  cout << "\nbye bye." << endl;
  return 0;
}


void check2manifoldness(Polyhedron* p)
{
  bool isValid = true;
//-- 1. check combinatorial consistency ---
  if (p->empty() == true)
  {
    std::cout << "INVALID: one/several of the faces have wrong orientation, or dangling faces." << std::endl;
    isValid = false;
  }
  else
  {
    if (p->is_closed() == false)
    {
      cout << "INVALID: one or more faces are missing, 2-manifold not closed." << endl;
      // TODO: find the missing faces and report
      isValid = false;
    }
    else
    {
// 2. check geometrical consistency ---
      isValid = isPolyhedronGeometricallyConsistent(p);
    }
  }

  if (isValid == true)
  {
    cout << "2-manifold valid." << endl;
    cout << "# vertices: " << p->size_of_vertices() << endl;
    cout << "# faces: " << p->size_of_facets() << endl;
  }
}



bool isPolyhedronGeometricallyConsistent(Polyhedron* p)
{
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
          cout << "&&&&&&&&&& POINT TOUCHING!" << endl;
      }
    }
    if (count > 3)
      cout << "###############PROBLEMS!!!!!!!" << endl;
  }
  return true;
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

  cout << "OFF file saved to /home/hugo/temp/zzz.off" << endl;
  fstream filestr ("/home/hugo/temp/zzz.off", fstream::out);
  filestr << offrep.str();
  filestr.close();
//  cout << "*********" << endl << offrep.str() << "*********" << endl;

  Polyhedron* P = new Polyhedron();
  offrep >> *P;
  return P;
}


void getTriangulatedShell(ifstream& infile, vector< vector<int*> >&shell, vector<Point3>& lsPts)
{
  //-- read the points
  int num, tmpint;
  float tmpfloat;
  infile >> num >> tmpint >> tmpint >> tmpint;
  vector< Point3 >::iterator iPoint3;
  for (int i = 0; i < num; i++)
  {
    Point3 p;
    infile >> tmpint >> p;
    lsPts.push_back(p);
  }

  //-- read the facets
  infile >> num >> tmpint;
  int numf, numpt;
  for (int i = 0; i < num; i++)
  {
//    cout << "---- face ---- " << i << endl;
    infile >> numf >> tmpint;
    //-- read oring (there's always one and only one)
    infile >> numpt;
    vector<int> ids(numpt);
    for (int k = 0; k < numpt; k++)
      infile >> ids[k];
    //-- get projected Polygon
    int proj = projection_plane(lsPts[ids[0]], lsPts[ids[1]], lsPts[ids[2]]);
//    cout << "proj :" << proj << endl;
    Polygon pgn;
    vector<Polygon> lsRings;
    create_polygon(lsPts, ids, pgn);
    lsRings.push_back(pgn);
    vector< vector<int> > pgnids;
    pgnids.push_back(ids);

    //-- check for irings
    for (int j = 1; j < numf; j++)
    {
      infile >> numpt;
      vector<int> ids(numpt);
      for (int l = 0; l < numpt; l++)
        infile >> ids[l];
      //-- get projected Polygon
      Polygon pgn;
      create_polygon(lsPts, ids, pgn);
      lsRings.push_back(pgn);
      pgnids.push_back(ids);
    }
    //-- skip the line about point defining the hole (mandatory in a POLY file)
    if (numf > 1)
      infile >> tmpint >> tmpfloat >> tmpfloat >> tmpfloat;

    //-- get projected CT
    vector<int*> oneface;
    construct_ct(lsPts, pgnids, lsRings, oneface);

    //-- modify orientation of every triangle if necessary
    bool invert = false;
    Vector v0 = unit_normal( lsPts[ids[0]], lsPts[ids[1]], lsPts[ids[2]] );
    if (proj == 2)
    {
      Vector n(0, 0, 1);
      if ( (v0*n) < 0)
        invert = true;
    }
    else if (proj == 1)
    {
      Vector n(0, 1, 0);
      if ( (v0*n) > 0)
        invert = true;
    }
    else
    {
      Vector n(1, 0, 0);
      if ( (v0*n) < 0)
        invert = true;
    }
    if ( invert == true ) //-- invert
    {
//      cout << "invert a face orientation." << endl;
      vector<int*>::iterator it3 = oneface.begin();
      int tmp;
      int* id;
      for ( ; it3 != oneface.end(); it3++)
      {
        id = *it3;
        tmp = id[0];
        id[0] = id[1];
        id[1] = tmp;
      }
    }

    shell.push_back(oneface);
    //-- check planarity
    if (is_face_planar(oneface, lsPts) == false)
    {
      cout << "Face not planar" << endl;
    }
  }

  cout << "---Global stats---" << endl;
  cout << "# faces: " << shell.size() << endl;
  vector< vector<int*> >::const_iterator it = shell.begin();
  for ( ; it != shell.end(); it++)
  {
    cout << "# tr: " << it->size() << endl;
  }
}

void create_polygon(const vector< Point3 > &lsPts, const vector<int>& ids, Polygon &pgn)
{
  int proj = projection_plane(lsPts[ids[0]], lsPts[ids[1]], lsPts[ids[2]]);
  //-- build projected polygon
  vector<int>::const_iterator it = ids.begin();
  for ( ; it != ids.end(); it++)
  {
    Point3 p = lsPts[*it];
    if (proj == 2)
      pgn.push_back(Point2(p.x(), p.y()));
    else if (proj == 1)
      pgn.push_back(Point2(p.x(), p.z()));
    else
      pgn.push_back(Point2(p.y(), p.z()));
  }
  if (pgn.is_counterclockwise_oriented() == false)
    pgn.reverse_orientation();
//  cout << "polygon " << pgn << endl;
//  cout << pgn.area() << endl;
//  cout << pgn.size() << endl;
//  cout << pgn[3] << endl;
//    cout << "convex? " << pgn.is_convex() << endl;
//  cout << pgn.is_counterclockwise_oriented() << endl;
}


void construct_ct(const vector< Point3 > &lsPts, const vector< vector<int> >& pgnids, const vector<Polygon>& lsRings, vector<int*>& oneface)
{
  vector<int> ids = pgnids[0];
  int proj = projection_plane(lsPts[ids[0]], lsPts[ids[1]], lsPts[ids[2]]);

  CT ct;
  vector< vector<int> >::const_iterator it = pgnids.begin();
  for ( ; it != pgnids.end(); it++)
  {
    vector<Point2> pts2d;
    vector<int>::const_iterator it2 = it->begin();
    for ( ; it2 != it->end(); it2++)
    {
      Point3 p1  = lsPts[*it2];
      if (proj == 2)
        pts2d.push_back( Point2(p1.x(), p1.y()) );
      else if (proj == 1)
        pts2d.push_back( Point2(p1.x(), p1.z()) );
      else
        pts2d.push_back( Point2(p1.y(), p1.z()) );
    }

    vector<Point2>::const_iterator itPt;
    CT::Vertex_handle v0;
    CT::Vertex_handle v1;
    CT::Vertex_handle firstv;
    itPt = pts2d.begin();
    v0 = ct.insert(*itPt);
    firstv = v0;
    it2 = it->begin();
    v0->info() = *it2;
    itPt++;
    it2++;
    for (; itPt != pts2d.end(); itPt++)
    {
      v1 = ct.insert(*itPt);
      v1->info() = *it2;
      ct.insert_constraint(v0, v1);
      v0 = v1;
      it2++;
    }
    ct.insert_constraint(v0,firstv);
  }
//  cout << "faces " << ct.number_of_faces() << endl;
//  cout << "vertices " << ct.number_of_vertices() << endl;
//  cout << "constraints " << ct.number_of_constraints() << endl;

  //-- fetch all the triangles forming the polygon (with holes)
  CT::Finite_faces_iterator fi = ct.finite_faces_begin();
  for( ; fi != ct.finite_faces_end(); fi++)
  {
    Point2 centre = barycenter( ct.triangle(fi).vertex(0), 1,
                                ct.triangle(fi).vertex(1), 1,
                                ct.triangle(fi).vertex(2), 1);
    bool inside = true;
    if (lsRings[0].has_on_negative_side(centre))
      inside = false;
    else
    {
      vector<Polygon>::const_iterator itpgn = lsRings.begin();
      itpgn++;
      for ( ; itpgn != lsRings.end(); itpgn++)   //-- check irings
      {
        if (itpgn->has_on_positive_side(centre))
        {
          inside = false;
          break;
        }
      }
    }
    if (inside == true)
    {
      //-- add the IDs to the face
      int* tr = new int[3];
      tr[0] = fi->vertex(0)->info();
      tr[1] = fi->vertex(1)->info();
      tr[2] = fi->vertex(2)->info();
      oneface.push_back(tr);
    }
  }
}

bool is_face_planar(const vector<int*> &trs, const vector<Point3>& lsPts, float angleTolerance)
{
  vector<int*>::const_iterator ittr = trs.begin();
  int* a = *ittr;
  Vector v0 = unit_normal( lsPts[a[0]], lsPts[a[1]], lsPts[a[2]]);
  ittr++;
  for ( ; ittr != trs.end(); ittr++)
  {
    a = *ittr;
    Vector v1 = unit_normal( lsPts[a[0]], lsPts[a[1]], lsPts[a[2]] );
    if ( acos((float) (v0*v1)*180/PI) < angleTolerance)
      return false;
  }
  return true;
}


int projection_plane(Point3 p0, Point3 p1, Point3 p2)
{
  //-- calculate normale
  Vector v = normal(p0, p1, p2);
  int m = 0;
  int n = 1;
  int proj = 2; //-- xy plane
  if (v.z() == 0.0)
  {
    if (v.y() == 0.0)
      proj = 0; //-- yz plane
    else
      proj = 1; //-- xz plane
  }
  return proj;
}


