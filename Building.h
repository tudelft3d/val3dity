//
//  Building.h
//  val3dity
//
//  Created by Hugo Ledoux on 27/10/16.
//
//

#ifndef Building_h
#define Building_h


#include "Primitive.h"
#include <string>
#include <vector>

class BuildingPart
{
public:
  BuildingPart  ();
  ~BuildingPart ();

  bool          validate(double tol_planarity_d2p, double tol_planarity_normals);
  bool          is_valid();
  bool          is_empty();
  std::string   get_report_xml();

  std::string   get_id();
  void          set_id(std::string id);

  void          add_primitive(Primitive* p);

protected:
  std::string                _id;
  std::vector<Primitive*>    _lsPrimitives;
};

class Building
{
public:
  Building  ();
  ~Building ();
  
  bool          validate(double tol_planarity_d2p, double tol_planarity_normals);
  bool          is_valid();
  bool          is_empty();
  std::string   get_report_xml();
  
  std::string   get_id();
  void          set_id(std::string id);

  void          add_primitive(Primitive* p);
  
  void          add_buildingpart(BuildingPart* bp);
  bool          has_parts();
  
protected:
  std::string                _id;
  std::vector<Primitive*>    _lsPrimitives;
  std::vector<BuildingPart*> _lsBP;
};


#endif /* Building_h */
