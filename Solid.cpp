//
//  Solid.cpp
//  val3dity
//
//  Created by Hugo Ledoux on 12/08/15.
//
//

#include "Solid.h"
#include "Shell.h"
#include <CGAL/Nef_polyhedron_3.h>
#include <CGAL/IO/Polyhedron_iostream.h>
#include <CGAL/IO/Nef_polyhedron_iostream_3.h>

#ifdef VAL3DITY_USE_EPECSQRT
  typedef CGAL::Exact_predicates_exact_constructions_kernel_with_sqrt Ke;
#else
  typedef CGAL::Exact_predicates_exact_constructions_kernel   Ke;
  typedef CGAL::Polyhedron_3<Ke>                              PolyhedronExact;
#endif

typedef CGAL::Nef_polyhedron_3<Ke>                          Nef_polyhedron;

//-- to keep track of all gml:Solids in a GML file
int Solid::_counter = 1;

Solid::Solid()
{
  _id = std::to_string(_counter);
  _counter++;
}


Solid::Solid(Shell2* sh)
{
  _shells.push_back(sh);
  _id = std::to_string(_counter);
  _counter++;
}

Solid::~Solid()
{
  // TODO: destructor for Solid, memory-management jongens
}

Shell2* Solid::get_oshell()
{
  return _shells[0];
}


void Solid::set_oshell(Shell2* sh)
{
  if (_shells.empty())
    _shells.push_back(sh);
  else
    _shells[0] = sh;
}


const vector<Shell2*>& Solid::get_shells()
{
  return _shells;
}


void Solid::add_ishell(Shell2* sh)
{
  _shells.push_back(sh);
}


bool Solid::validate()
{
  std::clog << "I'm validating the solid" << std::endl;
  return true;
}


int Solid::num_ishells()
{
  return (_shells.size() - 1);
}


std::string Solid::get_id()
{
  return _id;
}


void Solid::set_id(std::string id)
{
  _id = id;
}


void Solid::add_error(int code, int shell1, int shell2, std::string info)
{
  // TODO: how to store these errors? shell-shell numbers?
  // std::pair<int, std::string> a(faceid, info);
  // _errors[code].push_back(a);
  // std::clog << "--> errors #" << code << " for Shell " << this->_id << std::endl;
  std::clog << "ADDING SOLID ERROR" << std::endl;
}


// bool validate_solid_with_nef(vector<CgalPolyhedron*> &polyhedra, cbf cb)
bool Solid::validate_solid_with_nef()
{
  if (this->num_ishells() == 0)
    return true;
  vector<CgalPolyhedron*> polyhedra;
  for (auto& sh : this->get_shells())
    polyhedra.push_back(sh->get_cgal_polyhedron());
    
  bool isValid = true;
  std::stringstream st;
  std::clog << "Inspecting interactions between the " << polyhedra.size() << " shells";
  vector<Nef_polyhedron> nefs;
  vector<CgalPolyhedron*>::const_iterator polyhedraIt;
  for (polyhedraIt = polyhedra.begin(); polyhedraIt != polyhedra.end(); polyhedraIt++)
  {
#ifdef VAL3DITY_USE_EPECSQRT
     Nef_polyhedron onef(**polyhedraIt);
#else
     std::stringstream offrep (stringstream::in | stringstream::out);
     offrep << **polyhedraIt;
     PolyhedronExact pe;
     offrep >> pe;
     Nef_polyhedron onef(pe);
//    std::cout << "convertion to exact polyhedron done." << std::endl;
#endif

     nefs.push_back(onef);
  }
  vector<Nef_polyhedron>::iterator nefsIt = nefs.begin();
  Nef_polyhedron nef;
  nef += (*nefsIt);
  nefsIt++;
  int numvol = 2;
  bool success = true;
  for ( ; nefsIt != nefs.end(); nefsIt++) 
  {
    nef -= (*nefsIt);
    nef.regularization();
    numvol++;
    if (nef.number_of_volumes() != numvol)
    {
      success = false;
      break;
    }
  }
  if (success == false) //-- the Nef is not valid, pairwise testing to see what's wrong
  {
    isValid = false;
//-- start with oshell<-->ishells
    nefsIt = nefs.begin();
    nefsIt++;
    int no = 1;
    for ( ; nefsIt != nefs.end(); nefsIt++) 
    {
      nef.clear();
      nef += *(nefs.begin());
      nef -= *nefsIt;
      nef.regularization(); 
      if (nef.number_of_volumes() != 3)
      {
        if (nef.number_of_volumes() > 3)
        {
          //-- check if ishell is a subset of oshell
          if ((*nefsIt <= nefs[0]) == true)
            this->add_error(404, 0, no, "");
          else
          {
            this->add_error(402, 0, no, "");
            this->add_error(404, 0, no, "");
          }
        }
        else //-- nef.number_of_volumes() < 3
        {
          //-- perform union
          nef.clear();
          nef += *(nefs.begin());
          nef += *nefsIt;
          nef.regularization();
          if (nef.number_of_volumes() == 3)
            this->add_error(403, -1, -1, "");
          else
          {
            if ((*nefsIt <= nefs[0]) == true)
              this->add_error(401, 0, no, "");
            else
            {
              nef.clear();
              nef = nefs[0].intersection(nefsIt->interior());
              nef.regularization();
              if (nef.is_empty() == true)
              {
                this->add_error(401, 0, no, "");
                this->add_error(403, 0, no, "");
              }
              else
                this->add_error(402, 0, no, "");
            }
          }
        }
      }
    no++;
    }

//-- then check ishell<-->ishell interactions
    nefsIt = nefs.begin();
    nefsIt++;
    vector<Nef_polyhedron>::iterator nefsIt2;
    no = 1;
    int no2;
    for ( ; nefsIt != nefs.end(); nefsIt++)
    {
      nefsIt2 = nefsIt;
      nefsIt2++;
      no2 = no + 1;
      for ( ; nefsIt2 != nefs.end(); nefsIt2++)
      {
        nef.clear();
        nef += *nefsIt;
        nef += *nefsIt2;
        nef.regularization();
        if (nef.number_of_volumes() > 3)
          this->add_error(402, no, no2, "Both shells completely overlap");
        else if (nef.number_of_volumes() < 3)
        {
          //-- either they are face adjacent or overlap
          nef.clear();
          nef = nefsIt->interior();
          nef = nef.intersection(nefsIt2->interior());
          nef.regularization();
          if (nef.is_empty() == true)
            this->add_error(401, no, no2, "");
          else
            this->add_error(402, no, no2, "");
        }
        no2++;
      }
      no++;
    }
  }
  return isValid;
}