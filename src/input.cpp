/*
  val3dity 

  Copyright (c) 2011-2017, 3D geoinformation research group, TU Delft  

  This file is part of val3dity.

  val3dity is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  val3dity is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with val3dity.  If not, see <http://www.gnu.org/licenses/>.

  For any information or further details about the use of val3dity, contact
  Hugo Ledoux
  <h.ledoux@tudelft.nl>
  Faculty of Architecture & the Built Environment
  Delft University of Technology
  Julianalaan 134, Delft 2628BL, the Netherlands
*/

#include "input.h"
#include "Primitive.h"
#include "Feature.h"
#include "CityObject.h"
#include "GenericObject.h"
#include "IndoorCell.h"
#include "Surface.h"
#include "MultiSurface.h"
#include "CompositeSurface.h"
#include "Solid.h"
#include "CompositeSolid.h"
#include "MultiSolid.h"


using namespace std;
using json = nlohmann::json;

namespace val3dity
{

double _minx = 9e15;
double _miny = 9e15;  

//-- XML namespaces map
std::map<std::string, std::string> NS; 

bool IOErrors::has_errors()
{
  if (_errors.size() == 0)
    return false;
  else
    return true;
}

bool IOErrors::has_specific_error(int i) 
{
  if (_errors.count(i) == 0)
    return false;
  else
    return true;
}

std::set<int> IOErrors::get_unique_error_codes()
{
  std::set<int> errs;
  for (auto& err : _errors)
    for (auto i : err.second)
      errs.insert(std::get<0>(err));
  return errs;
}


void IOErrors::add_error(int code, std::string info)
{
  _errors[code].push_back(info);
  std::cout << "ERROR " << code << " : " << info << std::endl;
}


std::string IOErrors::get_report_text()
{
  std::stringstream ss;
  for (auto& err : _errors)
  {
    for (auto i : err.second)
    {
      ss << err.first << " -- " << errorcode2description(err.first) << std::endl;
      ss << "\tInfo: " << i << std::endl;
    }
  }
  return ss.str();
}


json IOErrors::get_report_json()
{
  json j;
  for (auto& err : _errors)
  {
    for (auto i : err.second)
    {
      json jj;
      jj["type"] = "Error";
      jj["code"] = err.first;
      jj["description"] = errorcode2description(err.first);
      jj["info"] = i;
      j.push_back(jj);
    }
  }
  return j;
}


std::string errorcode2description(int code) {
  switch(code)
  {
    case 0:   return string("STATUS_OK"); break;
    //-- RING
    case 101: return string("TOO_FEW_POINTS"); break;
    case 102: return string("CONSECUTIVE_POINTS_SAME"); break;
    case 103: return string("RING_NOT_CLOSED"); break;
    case 104: return string("RING_SELF_INTERSECTION"); break;
    //-- POLYGON
    case 201: return string("INTERSECTION_RINGS"); break;
    case 202: return string("DUPLICATED_RINGS"); break;
    case 203: return string("NON_PLANAR_POLYGON_DISTANCE_PLANE"); break;
    case 204: return string("NON_PLANAR_POLYGON_NORMALS_DEVIATION"); break;
    case 205: return string("POLYGON_INTERIOR_DISCONNECTED"); break;
    case 206: return string("INNER_RING_OUTSIDE"); break;
    case 207: return string("INNER_RINGS_NESTED"); break;
    case 208: return string("ORIENTATION_RINGS_SAME"); break;
    //-- SHELL
    case 300: return string("NOT_VALID_2_MANIFOLD"); break;
    case 301: return string("TOO_FEW_POLYGONS"); break;
    case 302: return string("SHELL_NOT_CLOSED"); break;
    case 303: return string("NON_MANIFOLD_CASE"); break;
    case 305: return string("MULTIPLE_CONNECTED_COMPONENTS"); break;
    case 306: return string("SHELL_SELF_INTERSECTION"); break;
    case 307: return string("POLYGON_WRONG_ORIENTATION"); break;
    // case 309: return string("VERTICES_NOT_USED"); break;
    //-- SOLID & MULTISOLID
    case 401: return string("INTERSECTION_SHELLS"); break;
    case 402: return string("DUPLICATED_SHELLS"); break;
    case 403: return string("INNER_SHELL_OUTSIDE"); break;
    case 404: return string("SOLID_INTERIOR_DISCONNECTED"); break;
    case 405: return string("WRONG_ORIENTATION_SHELL"); break;
    //-- COMPOSITESOLID
    case 501: return string("INTERSECTION_SOLIDS"); break;
    case 502: return string("DUPLICATED_SOLIDS"); break;
    case 503: return string("DISCONNECTED_SOLIDS"); break;
    //-- CityGML objects
    case 601: return string("BUILDINGPARTS_OVERLAP"); break;
    case 609: return string("CITYOBJECT_HAS_NO_GEOMETRY"); break;
    //-- OTHERS
    case 901: return string("INVALID_INPUT_FILE"); break;
    case 902: return string("EMPTY_PRIMITIVE"); break;
    case 903: return string("WRONG_INPUT_PARAMETERS"); break;
    case 999: return string("UNKNOWN_ERROR"); break;
    default:  return string("UNKNOWN_ERROR"); break;
  }
}

//-- ignore XML namespace
std::string localise(std::string s)
{
  return "*[local-name(.) = '" + s + "']";
}

  
std::string remove_xml_namespace(const char* input)
{
  std::string s = input;
  return s.substr(s.find_first_of(":") + 1);
}


vector<int> process_gml_ring(const pugi::xml_node& n, Surface* sh, IOErrors& errs) {
  std::string s = "./" + NS["gml"] + "LinearRing" + "/" + NS["gml"] + "pos";
  pugi::xpath_node_set npos = n.select_nodes(s.c_str());
  std::vector<int> r;
  if (npos.size() > 0) //-- <gml:pos> used
  {
    for (pugi::xpath_node_set::const_iterator it = npos.begin(); it != npos.end(); ++it) {
      std::string buf;
      std::stringstream ss(it->node().child_value());
      std::vector<std::string> tokens;
      while (ss >> buf)
        tokens.push_back(buf);
      long double x = std::stold(tokens[0]);
      x -= _minx;
      long double y = std::stold(tokens[1]);
      y -= _miny;
      Point3 p(double(x), double(y), std::stod(tokens[2]));
      r.push_back(sh->add_point(p));
    }
  }
  else //-- <gml:posList> used
  {
    std::string s = "./" + NS["gml"] + "LinearRing" + "/" + NS["gml"] + "posList";
    pugi::xpath_node pl = n.select_node(s.c_str());
    if (pl == NULL)
    {
      throw 901;
    }
    std::string buf;
    std::stringstream ss(pl.node().child_value());
    std::vector<std::string> coords;
    while (ss >> buf)
      coords.push_back(buf);
    if (coords.size() % 3 != 0)
    {
      errs.add_error(901, "Error: <gml:posList> has bad coordinates.");
      return r;
    }
    for (int i = 0; i < coords.size(); i += 3)
    {
      long double x = std::stold(coords[i]);
      x -= _minx;
      long double y = std::stold(coords[i+1]);
      y -= _miny;
      Point3 p(double(x), double(y), std::stod(coords[i+2]));
      r.push_back(sh->add_point(p));
    }
  }
  return r;
}


Surface* process_gml_surface(const pugi::xml_node& n, int id, std::map<std::string, pugi::xpath_node>& dallpoly, double tol_snap, IOErrors& errs) 
{
  std::string s = ".//" + NS["gml"] + "surfaceMember";
  pugi::xpath_node_set nsm = n.select_nodes(s.c_str());
  Surface* sh = new Surface(id, tol_snap);
  int i = 0;
  for (pugi::xpath_node_set::const_iterator it = nsm.begin(); it != nsm.end(); ++it)
  {
    std::vector< std::vector<int> > oneface;
    bool bxlink = false;
    pugi::xml_node tmpnode = it->node();
    pugi::xpath_node p;
    bool fliporientation = false;
    for (pugi::xml_attribute attr = tmpnode.first_attribute(); attr; attr = attr.next_attribute())
    {
      if (strcmp(attr.value(), "xlink:href") != 0) {
        bxlink = true;
        break;
      }
    }
    if (bxlink == true) 
    {
      std::string k = it->node().attribute("xlink:href").value();
      if (k[0] == '#')
        k = k.substr(1);
      p = dallpoly[k];
    }
    else
    {
      for (pugi::xml_node child : it->node().children()) 
      {
        if (std::string(child.name()).find("Polygon") != std::string::npos) {
          p = child;
          break;
        }
        else if (std::string(child.name()).find("OrientableSurface") != std::string::npos) {
          if (std::strncmp(child.attribute("orientation").value(), "-", 1) == 0)
            fliporientation = true;
          for (pugi::xml_node child2 : child.children()) 
          {
            if (std::string(child2.name()).find("baseSurface") != std::string::npos) 
            {
              std::string k = child2.attribute("xlink:href").value();
              if (k != "")
              {
                if (k[0] == '#')
                  k = k.substr(1);
                p = dallpoly[k];
                break;
              }
              for (pugi::xml_node child3 : child2.children())
              {
                if (std::string(child3.name()).find("Polygon") != std::string::npos)
                {
                  p = child;
                  break;
                }
              }
            }
          }
          break;
        }
        else if (std::string(child.name()).find("CompositeSurface") != std::string::npos) 
          break;
        else {
          throw 901;
        }
      }
    }

    //-- this is to handle CompositeSurfaces part of MultiSurfaces
    if (p == NULL) 
      continue;
    
    if (std::strncmp(p.node().attribute("orientation").value(), "-", 1) == 0)
      fliporientation = true;
    //-- exterior ring (only 1)
    s = ".//" + NS["gml"] + "exterior";
    pugi::xpath_node ring = p.node().select_node(s.c_str());
    std::vector<int> r = process_gml_ring(ring.node(), sh, errs);
    if (fliporientation == true) 
      std::reverse(r.begin(), r.end());
    if (r.front() != r.back())
    {
      if (p.node().attribute("gml:id") == 0)
        sh->add_error(103, std::to_string(i));
      else
        sh->add_error(103, p.node().attribute("gml:id").value());
    }
    else
      r.pop_back(); 
    oneface.push_back(r);
    //-- interior rings
    s = ".//" + NS["gml"] + "interior";
    pugi::xpath_node_set nint = p.node().select_nodes(s.c_str());
    for (pugi::xpath_node_set::const_iterator it = nint.begin(); it != nint.end(); ++it) {
      std::vector<int> r = process_gml_ring(it->node(), sh, errs);
      if (fliporientation == true) 
        std::reverse(r.begin(), r.end());
      if (r.front() != r.back())
      {
        if (p.node().attribute("gml:id") == 0)
          sh->add_error(103, std::to_string(i));
        else
          sh->add_error(103, p.node().attribute("gml:id").value());
      }
      else
        r.pop_back(); 
      oneface.push_back(r);
    }
    sh->add_face(oneface, p.node().attribute("gml:id").value());
    i++;
  }
  return sh;
}


Solid* process_gml_solid(const pugi::xml_node& nsolid, std::map<std::string, pugi::xpath_node>& dallpoly, double tol_snap, IOErrors& errs)
{
  //-- exterior shell
  Solid* sol = new Solid;
  if (nsolid.attribute("gml:id") != 0)
    sol->set_id(std::string(nsolid.attribute("gml:id").value()));
  std::string s = "./" + NS["gml"] + "exterior";
  pugi::xpath_node next = nsolid.select_node(s.c_str());
  sol->set_oshell(process_gml_surface(next.node(), 0, dallpoly, tol_snap, errs));
  //-- interior shells
  s = "./" + NS["gml"] + "interior";
  pugi::xpath_node_set nint = nsolid.select_nodes(s.c_str());
  int id = 1;
  for (pugi::xpath_node_set::const_iterator it = nint.begin(); it != nint.end(); ++it)
  {
    sol->add_ishell(process_gml_surface(it->node(), id, dallpoly, tol_snap, errs));
    id++;
  }
  return sol;
}


MultiSolid* process_gml_multisolid(const pugi::xml_node& nms, std::map<std::string, pugi::xpath_node>& dallpoly, double tol_snap, IOErrors& errs)
{
  MultiSolid* ms = new MultiSolid;
  if (nms.attribute("gml:id") != 0)
    ms->set_id(std::string(nms.attribute("gml:id").value()));
  std::string s = ".//" + NS["gml"] + "Solid";
  pugi::xpath_node_set nn = nms.select_nodes(s.c_str());
  for (pugi::xpath_node_set::const_iterator it = nn.begin(); it != nn.end(); ++it)
  {
    Solid* s = process_gml_solid(it->node(), dallpoly, tol_snap, errs);
    if (s->get_id() == "")
      s->set_id(std::to_string(ms->number_of_solids()));
    ms->add_solid(s);
  }
  return ms;
}


CompositeSolid* process_gml_compositesolid(const pugi::xml_node& nms, std::map<std::string, pugi::xpath_node>& dallpoly, double tol_snap, IOErrors& errs)
{
  CompositeSolid* cs = new CompositeSolid;
  if (nms.attribute("gml:id") != 0)
    cs->set_id(std::string(nms.attribute("gml:id").value()));
  std::string s = ".//" + NS["gml"] + "Solid";
  pugi::xpath_node_set nn = nms.select_nodes(s.c_str());
  for (pugi::xpath_node_set::const_iterator it = nn.begin(); it != nn.end(); ++it)
  {
    Solid* s = process_gml_solid(it->node(), dallpoly, tol_snap, errs);
    if (s->get_id() == "")
      s->set_id(std::to_string(cs->number_of_solids()));
    cs->add_solid(s);
  }

  return cs;
}



MultiSurface* process_gml_multisurface(const pugi::xml_node& nms, std::map<std::string, pugi::xpath_node>& dallpoly, double tol_snap, IOErrors& errs)
{
  MultiSurface* ms = new MultiSurface;
  if (nms.attribute("gml:id") != 0)
    ms->set_id(std::string(nms.attribute("gml:id").value()));
  Surface* s = process_gml_surface(nms, 0, dallpoly, tol_snap, errs);
  ms->set_surface(s);
  return ms;
}

CompositeSurface* process_gml_compositesurface(const pugi::xml_node& nms, std::map<std::string, pugi::xpath_node>& dallpoly, double tol_snap, IOErrors& errs)
{
  CompositeSurface* cs = new CompositeSurface;
  if (nms.attribute("gml:id") != 0)
    cs->set_id(std::string(nms.attribute("gml:id").value()));
  Surface* s = process_gml_surface(nms, 0, dallpoly, tol_snap, errs);
  cs->set_surface(s);
  return cs;
}

void print_information(std::string &ifile)
{
  std::cout << "Reading file: " << ifile << std::endl;
  pugi::xml_document doc;
  if (!doc.load_file(ifile.c_str())) 
  {
    std::cout << "Input file not found and/or incorrect GML file." << std::endl;
    return;
  }
  //-- parse namespace
  std::map<std::string, std::string> ns;
  pugi::xml_node ncm = doc.first_child();
  std::string vcitygml;
  get_namespaces(ncm, vcitygml);
  if (vcitygml.empty() == true) {
    std::cout << "File does not have the CityGML namespace. Abort." << std::endl;
    return;
  }
  std::cout << "++++++++++++++++++++ GENERAL +++++++++++++++++++++" << std::endl;
  std::cout << "CityGML version: " << vcitygml << std::endl;
  report_primitives(doc);
  report_building(doc);
}

void report_building(pugi::xml_document& doc) {
  std::cout << "++++++++++++++++++++ BUILDINGS +++++++++++++++++++" << std::endl;
  
  std::string s = "//" + NS["building"] + "Building";
  int nobuildings = doc.select_nodes(s.c_str()).size();
  print_info_aligned("Building", nobuildings);

  s = "//" + NS["building"] + "Building" + "/" + NS["building"] + "consistsOfBuildingPart" + "[1]";
  int nobwbp = doc.select_nodes(s.c_str()).size();
  print_info_aligned("without BuildingPart", (nobuildings - nobwbp), true);
  print_info_aligned("having BuildingPart", nobwbp, true);
  s = "//" + NS["building"] + "Building" + "[@" + NS["gml"] + "id]";
  print_info_aligned("with gml:id", doc.select_nodes(s.c_str()).size(), true);

  s = "//" + NS["building"] + "BuildingPart";
  int nobuildingparts = doc.select_nodes(s.c_str()).size();
  print_info_aligned("BuildingPart", nobuildingparts);
  s = "//" + NS["building"] + "BuildingPart" + "[@" + NS["gml"] + "id]";
  print_info_aligned("with gml:id", doc.select_nodes(s.c_str()).size(), true);
  for (int lod = 1; lod <= 3; lod++) {
    std::cout << "LOD" << lod << std::endl;
    int totals = 0;
    int totalms = 0;
    int totalsem = 0;
    report_building_each_lod(doc, lod, totals, totalms, totalsem);
    print_info_aligned("Building stored in gml:Solid", totals, true);
    print_info_aligned("Building stored in gml:MultiSurface", totalms, true);
    print_info_aligned("Building with semantics for surfaces", totalsem, true);
  }
  std::cout << "++++++++++++++++++++++++++++++++++++++++++++++++++" << std::endl;
}

void print_info_aligned(std::string o, size_t number, bool tab) {
  if (tab == false)
    std::cout << std::setw(40) << std::left  << o;
  else
    std::cout << "    " << std::setw(36) << std::left  << o;
  std::cout << std::setw(10) << std::right << number << std::endl;
}

void report_building_each_lod(pugi::xml_document& doc, int lod, int& total_solid, int& total_ms, int& total_sem) {
  total_solid = 0;
  total_ms = 0;
  total_sem = 0;
  std::string slod = "lod" + std::to_string(lod);
  std::string s = "//" + NS["building"] + "Building";
  pugi::xpath_node_set nb = doc.select_nodes(s.c_str());
  for (auto& b : nb) {
    std::string s1 = ".//" + NS["building"] + slod + "Solid";
    pugi::xpath_node_set tmp = b.node().select_nodes(s1.c_str());
    if (tmp.empty() == false) {
      for (auto& nbp : tmp) {
        total_solid++;
        break;
      }
    }
    s1 = ".//" + NS["building"] + slod + "MultiSurface";
    tmp = b.node().select_nodes(s1.c_str());
    if (tmp.empty() == false) {
      for (auto& nbp : tmp) {
        total_ms++;
        break;
      }
    }
    s1 = ".//" + NS["building"] + "boundedBy" + "//" + NS["building"] + slod + "MultiSurface";
    tmp = b.node().select_nodes(s1.c_str());
    if (tmp.empty() == false) {
      for (auto& nbp : tmp) {
        total_sem++;
        break;
      }
    }
  }
}





void report_primitives(pugi::xml_document& doc) {
  std::cout << "+++++++++++++++++++ PRIMITIVES +++++++++++++++++++" << std::endl;
  
  std::string s = "//" + NS["gml"] + "Solid";
  print_info_aligned("gml:Solid", doc.select_nodes(s.c_str()).size());

  s = "//" + NS["gml"] + "MultiSolid";
  print_info_aligned("gml:MultiSolid", doc.select_nodes(s.c_str()).size());

  s = "//" + NS["gml"] + "CompositeSolid";
  print_info_aligned("gml:CompositeSolid", doc.select_nodes(s.c_str()).size());
  
  s = "//" + NS["gml"] + "MultiSurface";
  print_info_aligned("gml:MultiSurface", doc.select_nodes(s.c_str()).size());
  
  s = "//" + NS["gml"] + "CompositeSurface";
  print_info_aligned("gml:CompositeSurface", doc.select_nodes(s.c_str()).size());

  s = "//" + NS["gml"] + "Polygon";
  print_info_aligned("gml:Polygon", doc.select_nodes(s.c_str()).size());

  std::cout << std::endl;
}


void process_json_surface(std::vector< std::vector<int> >& pgn, json& j, Surface* sh)
{
  std::vector< std::vector<int> > pgnids;
  for (auto& r : pgn)
  {
    std::vector<int> newr;
    for (auto& i : r)
    {
      double x;
      double y;
      double z;
      if (j.count("transform") == 0)
      {
        x = double(j["vertices"][i][0]);
        y = double(j["vertices"][i][1]);
        z = double(j["vertices"][i][2]);
      }
      else
      {
        x = (double(j["vertices"][i][0]) * double(j["transform"]["scale"][0])) + double(j["transform"]["translate"][0]);
        y = (double(j["vertices"][i][1]) * double(j["transform"]["scale"][1])) + double(j["transform"]["translate"][1]);
        z = (double(j["vertices"][i][2]) * double(j["transform"]["scale"][2])) + double(j["transform"]["translate"][2]);
      }
      x -= _minx;
      y -= _miny;
      Point3 p3(x, y, z);
      newr.push_back(sh->add_point(p3));
    }
    pgnids.push_back(newr);
  }
  sh->add_face(pgnids);
}


void read_file_cityjson(std::string &ifile, std::vector<Feature*>& lsFeatures, IOErrors& errs, double tol_snap)
{
  std::ifstream input(ifile);
  json j;
  try 
  {
    input >> j;
    // TODO: other validation for CityJSON and just not JSON stuff?
  }
  catch (nlohmann::detail::parse_error e) 
  {
    errs.add_error(901, "Input file not a valid JSON file.");
    return;
  }
  std::cout << "CityJSON input file" << std::endl;
  std::cout << "# City Objects found: " << j["CityObjects"].size() << std::endl;
  //-- compute (_minx, _miny)
  compute_min_xy(j);
  for (json::iterator it = j["CityObjects"].begin(); it != j["CityObjects"].end(); ++it) 
  {
    CityObject* co = new CityObject(it.key(), it.value()["type"]);
    int idgeom = 0;
    for (auto& g : it.value()["geometry"]) {
      std::string theid = it.key() + "(" + std::to_string(idgeom) + ")";
      if  (g["type"] == "Solid")
      {
        Solid* s = new Solid(theid);
        bool oshell = true;
        int c = 0;
        for (auto& shell : g["boundaries"]) 
        {
          Surface* sh = new Surface(c, tol_snap);
          c++;
          for (auto& polygon : shell) { 
            std::vector< std::vector<int> > pa = polygon;
            process_json_surface(pa, j, sh);
          }
          if (oshell == true)
          {
            oshell = false;
            s->set_oshell(sh);
          }
          else
            s->add_ishell(sh);
        }
        co->add_primitive(s);
      }
      else if ( (g["type"] == "MultiSurface") || (g["type"] == "CompositeSurface") ) 
      {
        Surface* sh = new Surface(-1, tol_snap);
        for (auto& p : g["boundaries"]) 
        { 
          std::vector< std::vector<int> > pa = p;
          process_json_surface(pa, j, sh);
        }
        if (g["type"] == "MultiSurface")
        {
          MultiSurface* ms = new MultiSurface(theid);
          ms->set_surface(sh);
          co->add_primitive(ms);
        }
        else
        {
          CompositeSurface* cs = new CompositeSurface(theid);
          cs->set_surface(sh);
          co->add_primitive(cs);
        }
      }
      else if (g["type"] == "MultiSolid") 
      {
        MultiSolid* ms = new MultiSolid(theid);
        for (auto& solid : g["boundaries"]) 
        {
          Solid* s = new Solid();
          bool oshell = true;
          for (auto& shell : solid) 
          {
            Surface* sh = new Surface(-1, tol_snap);
            for (auto& polygon : shell) { 
              std::vector< std::vector<int> > pa = polygon;
              process_json_surface(pa, j, sh);
            }
            if (oshell == true)
            {
              oshell = false;
              s->set_oshell(sh);
            }
            else
              s->add_ishell(sh);
          }
          ms->add_solid(s);
        }
        co->add_primitive(ms);
      }
      else if (g["type"] == "CompositeSolid") 
      {
        CompositeSolid* cs = new CompositeSolid(theid);
        for (auto& solid : g["boundaries"]) 
        {
          Solid* s = new Solid();
          bool oshell = true;
          for (auto& shell : solid) 
          {
            Surface* sh = new Surface(-1, tol_snap);
            for (auto& polygon : shell) { 
              std::vector< std::vector<int> > pa = polygon;
              process_json_surface(pa, j, sh);
            }
            if (oshell == true)
            {
              oshell = false;
              s->set_oshell(sh);
            }
            else
              s->add_ishell(sh);
          }
          cs->add_solid(s);
        }
        co->add_primitive(cs);
      }      
      idgeom++;
    }
    lsFeatures.push_back(co);
  }
}


void process_gml_file_indoorgml(pugi::xml_document& doc, std::vector<Feature*>& lsFeatures, std::map<std::string, pugi::xpath_node>& dallpoly, IOErrors& errs, double tol_snap)
{
  //-- 1. read each CellSpace in the file (the primal objects)
  std::string s = ".//" + NS["indoorgml"] + "CellSpace";
  pugi::xpath_node_set nn = doc.select_nodes(s.c_str());
  int pcounter = 0;
  for (pugi::xpath_node_set::const_iterator it = nn.begin(); it != nn.end(); ++it)
  {
    // std::cout << "---CellSpace" << std::endl;
    std::string theid   = "";
    std::string duality = "";
    //-- get the ID
    if (it->node().attribute("gml:id") != 0) {
      // std::cout << "\t" << it->node().attribute("gml:id").value() << std::endl;
      theid = it->node().attribute("gml:id").value();
    }
    else 
      theid = ("MISSING_ID_" + std::to_string(pcounter));
    //-- get the duality pointer (max one, sweet)
    s = NS["indoorgml"] + "duality";
    for (pugi::xml_node child : it->node().children(s.c_str()))
    {
      if (child.attribute("xlink:href") != 0) {
        // std::cout << "\t" << child.attribute("xlink:href").value() << std::endl;
        duality = child.attribute("xlink:href").value();
      }
    }
    IndoorCell* cell = new IndoorCell(theid, duality);
    //-- get the geometry, either Solid or Surface
    s = NS["indoorgml"] + "cellSpaceGeometry";
    for (pugi::xml_node child : it->node().children(s.c_str()))
    {
      s = NS["indoorgml"] + "Geometry3D";
      for (pugi::xml_node child2 : child.children(s.c_str()))
      {
        s = NS["gml"] + "Solid";
        for (pugi::xml_node child3 : child2.children(s.c_str()))
        {
          // std::cout << "Solid: " << child3.attribute("gml:id").value() << std::endl;
          Solid* s = process_gml_solid(child3, dallpoly, tol_snap, errs);
          if (s->get_id() == "")
            s->set_id("MISSING_ID");
          cell->add_primitive(s);
        }
      }
    }
    pcounter++;
    lsFeatures.push_back(cell);
  }
}




void process_gml_file_primitives(pugi::xml_document& doc, std::vector<Feature*>& lsFeatures, std::map<std::string, pugi::xpath_node>& dallpoly, IOErrors& errs, double tol_snap)
{
  primitives_walker walker;
  doc.traverse(walker);
  std::cout << "# 3D primitives found: " << walker.lsNodes.size() << std::endl;
  int primid = 0;
  std::string coid = "Primitives";
  GenericObject* o = new GenericObject("none");
  for (auto& prim : walker.lsNodes)
  {
    if (remove_xml_namespace(prim.name()).compare("Solid") == 0)
    {
      Solid* p = process_gml_solid(prim, dallpoly, tol_snap, errs);
      if (p->get_id().compare("") == 0)
        p->set_id(std::to_string(primid));
      o->add_primitive(p);
    }
    else if (remove_xml_namespace(prim.name()).compare("MultiSolid") == 0)
    {
      MultiSolid* p = process_gml_multisolid(prim, dallpoly, tol_snap, errs);
      if (p->get_id().compare("") == 0)
        p->set_id(std::to_string(primid));
      o->add_primitive(p);
    }      
    else if (remove_xml_namespace(prim.name()).compare("CompositeSolid") == 0)
    {
      CompositeSolid* p = process_gml_compositesolid(prim, dallpoly, tol_snap, errs);
      if (p->get_id().compare("") == 0)
        p->set_id(std::to_string(primid));
      o->add_primitive(p);
    }
    else if (remove_xml_namespace(prim.name()).compare("MultiSurface") == 0)
    {
      MultiSurface* p = process_gml_multisurface(prim, dallpoly, tol_snap, errs);
      if (p->get_id().compare("") == 0)
        p->set_id(std::to_string(primid));
      o->add_primitive(p);
    } 
    else if (remove_xml_namespace(prim.name()).compare("CompositeSurface") == 0)
    {
      CompositeSurface* p = process_gml_compositesurface(prim, dallpoly, tol_snap, errs);
      if (p->get_id().compare("") == 0)
        p->set_id(std::to_string(primid));
      o->add_primitive(p);
    } 
    primid++;
  }  
  lsFeatures.push_back(o);
}


void process_gml_file_city_objects(pugi::xml_document& doc, std::vector<Feature*>& lsFeatures, std::map<std::string, pugi::xpath_node>& dallpoly, IOErrors& errs, double tol_snap, bool geom_is_sem_surfaces)
{
  //-- read each CityObject in the file
  citygml_objects_walker walker;
  doc.traverse(walker);
  std::cout << "# City Objects found: " << walker.lsNodes.size() << std::endl;
  int cocounter = 0;
  //-- for each City Object parse its primitives
  for (auto& co : walker.lsNodes)
  {
    std::string cotype = remove_xml_namespace(co.name());
    std::string coid = "";
    if (co.attribute("gml:id") != 0)
      coid += co.attribute("gml:id").value();
    else
    {
      coid += "MISSING_ID_";
      coid += std::to_string(cocounter);
      cocounter++;
    }
    CityObject* o = new CityObject(coid, cotype);
    primitives_walker walker2;
    co.traverse(walker2);
    int pcounter = 0;
    if ( (geom_is_sem_surfaces == true) && (walker2.lsNodes.size() == 0) ) 
    { //-- WARNING: no geom in the CO!
      semantic_surfaces_walker walker3;
      co.traverse(walker3);
      for (auto& prim : walker3.lsNodes)
      {
        Primitive* p;
        p = process_gml_multisurface(prim, dallpoly, tol_snap, errs);
        if (p->get_id() == "")
          p->set_id("MISSING_ID_" + std::to_string(pcounter));
        o->add_primitive(p);
        pcounter++;
      }
    }
    else {
      for (auto& prim : walker2.lsNodes)
      {
        Primitive* p;
        if (remove_xml_namespace(prim.name()).compare("Solid") == 0)
          p = process_gml_solid(prim, dallpoly, tol_snap, errs);
        else if (remove_xml_namespace(prim.name()).compare("MultiSolid") == 0)
          p = process_gml_multisolid(prim, dallpoly, tol_snap, errs);
        else if (remove_xml_namespace(prim.name()).compare("CompositeSolid") == 0)
          p = process_gml_compositesolid(prim, dallpoly, tol_snap, errs);
        else if (remove_xml_namespace(prim.name()).compare("MultiSurface") == 0)
          p = process_gml_multisurface(prim, dallpoly, tol_snap, errs);
        else if (remove_xml_namespace(prim.name()).compare("CompositeSurface") == 0)
          p = process_gml_compositesurface(prim, dallpoly, tol_snap, errs);
        if (p->get_id() == "")
          p->set_id("MISSING_ID_" + std::to_string(pcounter));
        o->add_primitive(p);
        pcounter++;
      }
    }
    lsFeatures.push_back(o);
  }
}


void compute_min_xy(json& j)
{
  for (auto& v : j["vertices"])
  {
    if (v[0] < _minx)
      _minx = v[0];
    if (v[1] < _miny)
      _miny = v[1];
  }
  if (j.count("transform") != 0)
  {
    _minx = (_minx * double(j["transform"]["scale"][0])) + double(j["transform"]["translate"][0]);
    _miny = (_miny * double(j["transform"]["scale"][1])) + double(j["transform"]["translate"][1]);
  }
  std::cout << "Translating all coordinates by (-" << _minx << ", -" << _miny << ")" << std::endl;
  Primitive::set_translation_min_values(_minx, _miny);
  Surface::set_translation_min_values(_minx, _miny);
}


void compute_min_xy(pugi::xml_document& doc)
{
  std::string s = "//" + NS["gml"] + "posList";
  pugi::xpath_node_set nall = doc.select_nodes(s.c_str());
  for (auto& each : nall) 
  {
    std::string buf;
    std::stringstream ss(each.node().child_value());
    std::vector<std::string> coords;
    while (ss >> buf)
      coords.push_back(buf);
    for (int i = 0; i < coords.size(); i += 3)
    {
      if (std::stod(coords[0]) < _minx)
        _minx = std::stod(coords[0]);
      if (std::stod(coords[1]) < _miny)
        _miny = std::stod(coords[1]);
    }
  }
  s = "//" + NS["gml"] + "pos";
  nall = doc.select_nodes(s.c_str());
  for (auto& each : nall) 
  {
    std::string buf;
    std::stringstream ss(each.node().child_value());
    std::vector<std::string> tokens;
    while (ss >> buf)
      tokens.push_back(buf);
    if (std::stod(tokens[0]) < _minx)
      _minx = std::stod(tokens[0]);
    if (std::stod(tokens[1]) < _miny)
      _miny = std::stod(tokens[1]);
  }
  std::cout << "Translating all coordinates by (-" << _minx << ", -" << _miny << ")" << std::endl;
  Primitive::set_translation_min_values(_minx, _miny);
  Surface::set_translation_min_values(_minx, _miny);
}


void read_file_gml(std::string &ifile, std::vector<Feature*>& lsFeatures, IOErrors& errs, double tol_snap, bool geom_is_sem_surfaces)
{
  std::cout << "Reading file: " << ifile << std::endl;
  pugi::xml_document doc;
  if (!doc.load_file(ifile.c_str())) 
  {
    errs.add_error(901, "Input file not found.");
    return;
  }
  //-- parse namespace
  pugi::xml_node ncm = doc.first_child();
  std::string vcitygml;
  get_namespaces(ncm, vcitygml); //-- results in global variable NS in this unit
  if (NS.count("gml") == 0)
  {
    errs.add_error(901, "Input file does not have the GML namespace.");
    return;
  }
  //-- find (_minx, _miny)
  compute_min_xy(doc);
  //-- build dico of xlinks for <gml:Polygon>
  std::map<std::string, pugi::xpath_node> dallpoly;
  build_dico_xlinks(doc, dallpoly, errs);
  if ( (NS.count("citygml") != 0) && (ncm.name() == (NS["citygml"] + "CityModel")) )
  {
    std::cout << "CityGML input file" << std::endl;
    process_gml_file_city_objects(doc, lsFeatures, dallpoly, errs, tol_snap, geom_is_sem_surfaces);
  }
  else if ( (NS.count("indoorgml") != 0) && (ncm.name() == (NS["indoorgml"] + "IndoorFeatures")) ) {
    std::cout << "IndoorGML input file" << std::endl;
    process_gml_file_indoorgml(doc, lsFeatures, dallpoly, errs, tol_snap);
  }
  else
  {
    std::cout << "GML input file (ie not CityGML)" << std::endl;
    process_gml_file_primitives(doc, lsFeatures, dallpoly, errs, tol_snap);
  }
}


void get_namespaces(pugi::xml_node& root, std::string& vcitygml) {
  vcitygml = "";
  for (pugi::xml_attribute attr = root.first_attribute(); attr; attr = attr.next_attribute()) {
    std::string name = attr.name();
    if (name.find("xmlns") != std::string::npos) {
      // std::cout << attr.name() << "=" << attr.value() << std::endl;
      std::string value = attr.value();
      std::string sns;
      if (value.find("http://www.opengis.net/citygml/0") != std::string::npos) {
        sns = "citygml";
        vcitygml = "v0.4";
      }
      else if (value.find("http://www.opengis.net/citygml/1") != std::string::npos) {
        sns = "citygml";
        vcitygml = "v1.0";
      }
      else if (value.find("http://www.opengis.net/citygml/2") != std::string::npos) {
        sns = "citygml";
        vcitygml = "v2.0";
      }
      else if (value.find("http://www.opengis.net/gml") != std::string::npos)
        sns = "gml";
      else if ( (value.find("http://www.opengis.net/indoorgml/1") != std::string::npos) &&
                (value.find("core") != std::string::npos) ) {
        sns = "indoorgml";
      }
      else if (value.find("http://www.opengis.net/citygml/building") != std::string::npos)
        sns = "building";
      else if (value.find("http://www.opengis.net/citygml/relief") != std::string::npos)
        sns = "dem";
      else if (value.find("http://www.opengis.net/citygml/vegetation") != std::string::npos)
        sns = "veg";
      else if (value.find("http://www.opengis.net/citygml/waterbody") != std::string::npos)
        sns = "wtr";
      else if (value.find("http://www.opengis.net/citygml/landuse") != std::string::npos)
        sns = "luse";
      else if (value.find("http://www.opengis.net/citygml/transportation") != std::string::npos)
        sns = "tran";      
      else if (value.find("http://www.opengis.net/citygml/cityfurniture") != std::string::npos)
        sns = "frn";      
      else if (value.find("http://www.opengis.net/citygml/appearance") != std::string::npos)
        sns = "app";      
      else if (value.find("http://www.w3.org/1999/xlink") != std::string::npos)
        sns = "xlink";
      else
        sns = "";
      if (sns != "") {
        size_t pos = name.find(":");
        if (pos == std::string::npos) 
          NS[sns] = "";
        else 
          NS[sns] = name.substr(pos + 1) + ":";
      }    
    }
  }
}





void build_dico_xlinks(pugi::xml_document& doc, std::map<std::string, pugi::xpath_node>& dallpoly, IOErrors& errs)
{
  std::string s = "//" + NS["gml"] + "Polygon" + "[@" + NS["gml"] + "id]";
  pugi::xpath_node_set nallpoly = doc.select_nodes(s.c_str());
  if (nallpoly.size() > 0)
   std::cout << "XLinks found, resolving them..." << std::flush;
  for (pugi::xpath_node_set::const_iterator it = nallpoly.begin(); it != nallpoly.end(); ++it)
    dallpoly[it->node().attribute("gml:id").value()] = *it;
  //-- for <gml:OrientableSurface>
  s = "//" + NS["gml"] + "OrientableSurface" + "[@" + NS["gml"] + "id" + "]";
  pugi::xpath_node_set nallosurf = doc.select_nodes(s.c_str());
  for (pugi::xpath_node_set::const_iterator it = nallosurf.begin(); it != nallosurf.end(); ++it)
    dallpoly[it->node().attribute("gml:id").value()] = *it;
  //-- checking xlinks validity now, not to be bitten later
  s = "//" + NS["gml"] + "surfaceMember" + "[@" + NS["xlink"] + "href" + "]";
  pugi::xpath_node_set nsmxlink = doc.select_nodes(s.c_str());
  for (pugi::xpath_node_set::const_iterator it = nsmxlink.begin(); it != nsmxlink.end(); ++it) 
  {
    std::string k = it->node().attribute("xlink:href").value();
    if (k[0] == '#')
      k = k.substr(1);
    if (dallpoly.count(k) == 0) 
    {
      std::string r = "One XLink couldn't be resolved (";
      r += it->node().attribute("xlink:href").value();
      r += ")";
      errs.add_error(901, r);
      return;
    }
  }
  if (nallpoly.size() > 0)
    std::cout << "done." << std::endl;
}


Surface* read_file_poly(std::string &ifile, int shellid, IOErrors& errs)
{
  std::cout << "Reading file: " << ifile << std::endl;
  std::stringstream st;
  ifstream infile(ifile.c_str(), ifstream::in);
  if (!infile)
  {
    errs.add_error(901, "Input file not found.");
    return NULL;
  }
  //-- read the points
  int num, tmpint;
  float tmpfloat;
  double x, y, z;
  infile >> num >> tmpint >> tmpint >> tmpint;
  //-- compute (_minx, _miny)
  for (int i = 0; i < num; i++)
  {
    infile >> tmpint >> x >> y >> z;
    if (x < _minx)
      _minx = x;
    if (y < _miny)
      _miny = y;
  }
  std::cout << "Translating all coordinates by (-" << _minx << ", -" << _miny << ")" << std::endl;
  Primitive::set_translation_min_values(_minx, _miny);
  Surface::set_translation_min_values(_minx, _miny);
  infile.close();
  infile.open(ifile.c_str(), std::ifstream::in);
  infile >> num >> tmpint >> tmpint >> tmpint;
  //-- read verticess
  Surface* sh = new Surface(shellid);  
  for (int i = 0; i < num; i++)
  {
    infile >> tmpint >> x >> y >> z;
    x -= _minx;
    y -= _miny;
    Point3 p(x, y, z);
    sh->add_point(p);
  }
  //-- read the facets
  infile >> num >> tmpint;
  int numf, numpt, numholes;
  string s;
  for (int i = 0; i < num; i++)
  {
    numholes = 0;
    infile >> numf;
    while(true) {
      if (infile.peek() == '\n')
        break;
      else if (infile.peek() == ' ')
        infile.ignore();
      else
        infile >> numholes;
    }
    //-- read oring (there's always one and only one)
    infile >> numpt;
    if (numpt == -1) {
      sh->add_error(103, std::to_string(i));
      continue;
    }
    std::vector<int> ids(numpt);
    for (int k = 0; k < numpt; k++)
      infile >> ids[k];
    std::vector< std::vector<int> > pgnids;
    pgnids.push_back(ids);
    //-- check for irings
    for (int j = 1; j < numf; j++)
    {
      infile >> numpt;
      if (numpt == -1) {
        sh->add_error(103, std::to_string(i));
        continue;
      }
      std::vector<int> ids(numpt);
      for (int l = 0; l < numpt; l++)
        infile >> ids[l];
      pgnids.push_back(ids);
    }
    //-- skip the line about points defining holes (if present)
    for (int j = 0; j < numholes; j++)
      infile >> tmpint >> tmpfloat >> tmpfloat >> tmpfloat;
    sh->add_face(pgnids);
  }
  return sh;
}

void printProgressBar(int percent) {
  std::string bar;
  for(int i = 0; i < 50; i++){
    if( i < (percent / 2)) {
      bar.replace(i, 1, "=");
    }
    else if( i == (percent / 2)) {
      bar.replace(i, 1, ">");
    }
    else{
      bar.replace(i, 1, " ");
    }
  }
  std::cout << "\r" "[" << bar << "] ";
  std::cout.width(3);
  std::cout << percent << "%     " << std::flush;
}

Surface* read_file_off(std::string &ifile, int shellid, IOErrors& errs)
{
  std::cout << "Reading file: " << ifile << std::endl;
  std::stringstream st;
  ifstream infile(ifile.c_str(), ifstream::in);
  if (!infile)
  {
    errs.add_error(901, "Input file not found.");
    return NULL;
  }
  //-- read the points
  int numpt, numf, tmpint;
  std::string s;
  infile >> s;
  infile >> numpt >> numf >> tmpint;
  if ( (s != "OFF") || (numpt <= 0) ) {
    errs.add_error(901, "Input file not a valid OFF file.");
    return NULL;
  }
  //-- compute (_minx, _miny)
  for (int i = 0; i < numpt; i++)
  {
    double x, y, z;
    infile >> x >> y >> z;
    if (x < _minx)
      _minx = x;
    if (y < _miny)
      _miny = y;
  }
  std::cout << "Translating all coordinates by (-" << _minx << ", -" << _miny << ")" << std::endl;
  Primitive::set_translation_min_values(_minx, _miny);
  Surface::set_translation_min_values(_minx, _miny);
  //-- reset the file
  infile.close();
  infile.open(ifile.c_str(), std::ifstream::in);
  infile >> s;
  infile >> numpt >> numf >> tmpint;
  //-- read the points
  Surface* sh = new Surface(shellid);  
  for (int i = 0; i < numpt; i++)
  {
    double x, y, z;
    infile >> x >> y >> z;
    x -= _minx;
    y -= _miny;
    Point3 p(x, y, z);
    sh->add_point(p);
  }
  //-- read the facets
  for (int i = 0; i < numf; i++)
  {
    infile >> tmpint;
    std::vector<int> ids(tmpint);
    if (ids.empty() == true)
    {
      errs.add_error(901, "Some surfaces not defined correctly or are empty");
      return NULL;
    }
    for (int k = 0; k < tmpint; k++)
      infile >> ids[k];
    std::vector< std::vector<int> > pgnids;
    pgnids.push_back(ids);
    sh->add_face(pgnids);
  }
  return sh;
}


void read_file_obj(std::vector<Feature*>& lsFeatures, std::string &ifile, Primitive3D prim3d, IOErrors& errs, double tol_snap)
{
  std::cout << "Reading file: " << ifile << std::endl;
  std::ifstream infile(ifile.c_str(), std::ifstream::in);
  if (!infile)
  {
    errs.add_error(901, "Input file not found.");
    return;
  }
  //-- find (minx, miny)
  std::string l;
  while (std::getline(infile, l)) 
  {
    std::istringstream iss(l);
    if (l.substr(0, 2) == "v ") {
      std::string tmp;
      double x, y, z;
      iss >> tmp >> x >> y >> z;
      if (x < _minx)
        _minx = x;
      if (y < _miny)
        _miny = y;
    }
  }
  std::cout << "Translating all coordinates by (-" << _minx << ", -" << _miny << ")" << std::endl;
  Primitive::set_translation_min_values(_minx, _miny);
  Surface::set_translation_min_values(_minx, _miny);
  //-- read again file and parse everything
  infile.close();
  infile.open(ifile.c_str(), std::ifstream::in);
  int primid = 0;
  Surface* sh = new Surface(0, tol_snap);
  std::vector<Point3*> allvertices;
  GenericObject* o = new GenericObject("none");
  while (std::getline(infile, l)) {
    std::istringstream iss(l);
    if (l.substr(0, 2) == "v ") {
      std::string tmp;
      double x, y, z;
      iss >> tmp >> x >> y >> z;
      x -= _minx;
      y -= _miny;
      Point3 *p = new Point3(x, y, z);
      allvertices.push_back(p);
    }
    else if (l.substr(0, 2) == "o ") {
      if (sh->is_empty() == false)
      {
        if (prim3d == SOLID)
        {
          Solid* sol = new Solid(std::to_string(primid));
          sol->set_oshell(sh);
          o->add_primitive(sol);
        }
        else if ( prim3d == COMPOSITESURFACE)
        {
          CompositeSurface* cs = new CompositeSurface(std::to_string(primid));
          cs->set_surface(sh);
          o->add_primitive(cs);
        }
        else if (prim3d == MULTISURFACE)
        {
          MultiSurface* ms = new MultiSurface(std::to_string(primid));
          ms->set_surface(sh);
          o->add_primitive(ms);
        }
        primid++;
        sh = new Surface(0, tol_snap);
      }
      // else {
      //   errs.add_error(901, "Some surfaces not defined correctly or are empty");
      //   return;
      // }
    }
    else if (l.substr(0, 2) == "f ") {
      std::vector<int> r;
      std::string tmp;
      iss >> tmp;
      while (iss)
      {
        tmp.clear();
        iss >> tmp;
        if (tmp.compare("\\") == 0) {
          std::getline(infile, l);
          iss.str(l);
          continue;
        }
        if (tmp.empty() == false) {
          std::size_t k = tmp.find("/");
          Point3* tp = allvertices[std::stoi(tmp.substr(0, k)) - 1];
          r.push_back(sh->add_point(*tp));
        }
      }
      std::vector< std::vector<int> > pgnids;
      pgnids.push_back(r);
      sh->add_face(pgnids);
    }
  }
  if (sh->is_empty() == true) {
    errs.add_error(902, "Some surfaces not defined correctly or are empty");
    return;
  }
  if (prim3d == SOLID)
  {
    Solid* sol = new Solid(std::to_string(primid));
    sol->set_oshell(sh);
    o->add_primitive(sol);
  }
  else if ( prim3d == COMPOSITESURFACE)
  {
    CompositeSurface* cs = new CompositeSurface(std::to_string(primid));
    cs->set_surface(sh);
    o->add_primitive(cs);
  }
  else if (prim3d == MULTISURFACE)
  {
    MultiSurface* ms = new MultiSurface(std::to_string(primid));
    ms->set_surface(sh);
    o->add_primitive(ms);
  }
  for (auto& each : allvertices)
    delete each;
  allvertices.clear();
  lsFeatures.push_back(o);
} 

} // namespace val3dity
