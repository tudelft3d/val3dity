/*
 val3dity - Copyright (c) 2011-2016, Hugo Ledoux.  All rights reserved.
 
 Redistribution and use in source and binary forms, with or without
 modification, are permitted provided that the following conditions are met:
     * Redistributions of source code must retain the above copyright
       notice, this list of conditions and the following disclaimer.
     * Redistributions in binary form must reproduce the above copyright
       notice, this list of conditions and the following disclaimer in the
       documentation and/or other materials provided with the distribution.
     * Neither the name of the authors nor the
       names of its contributors may be used to endorse or promote products
       derived from this software without specific prior written permission.

 THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 DISCLAIMED. IN NO EVENT SHALL HUGO LEDOUX BE LIABLE FOR ANY
 DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
*/

#include "input.h"

bool IOErrors::has_errors()
{
  if (_errors.size() == 0)
    return false;
  else
    return true;
}


void IOErrors::add_error(int code, std::string info)
{
  _errors[code].push_back(info);
  std::clog << "--> errors #" << code << " : " << info << std::endl;
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


std::string IOErrors::get_report_xml()
{
  std::stringstream ss;
  for (auto& err : _errors)
  {
    for (auto i : err.second)
    {
      ss << "\t<Error>" << std::endl;
      ss << "\t\t<code>" << err.first << "</code>" << std::endl;
      ss << "\t\t<type>" << errorcode2description(err.first) << "</type>" << std::endl;
      ss << "\t\t<info>" << i << "</info>" << std::endl;
      ss << "\t</Error>" << std::endl;
    }
  }
  return ss.str();
}


std::string errorcode2description(int code, bool qie) {
  if (qie == false) {
    switch(code)
    {
      case 0:   return string("STATUS_OK"); break;
      //-- RING
      case 101: return string("TOO_FEW_POINTS"); break;
      case 102: return string("CONSECUTIVE_POINTS_SAME"); break;
      case 103: return string("RING_NOT_CLOSED"); break;
      case 104: return string("RING_SELF_INTERSECTION"); break;
      case 105: return string("RING_COLLAPSED"); break;
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
      case 303: return string("NON_MANIFOLD_VERTEX"); break;
      case 304: return string("NON_MANIFOLD_EDGE"); break;
      case 305: return string("SEPARATE_PARTS"); break;
      case 306: return string("SHELL_SELF_INTERSECTION"); break;
      case 307: return string("POLYGON_WRONG_ORIENTATION"); break;
      case 309: return string("VERTICES_NOT_USED"); break;
      //-- SOLID
      case 401: return string("INTERSECTION_SHELLS"); break;
      case 402: return string("DUPLICATED_SHELLS"); break;
      case 403: return string("INNER_SHELL_OUTSIDE"); break;
      case 404: return string("INTERIOR_DISCONNECTED"); break;
      case 405: return string("WRONG_ORIENTATION_SHELL"); break;
      //-- OTHERS
      case 901: return string("INVALID_INPUT_FILE"); break;
      case 902: return string("EMPTY_PRIMITIVE"); break;
      case 999: return string("UNKNOWN_ERROR"); break;
      default:  return string("UNKNOWN_ERROR"); break;
    }
  }
  else { //-- return QIE error codes
    switch(code)
    {
      case 0:   return string("STATUS_OK"); break;
      //-- RING
      case 101: return string("GE_R_TOO_FEW_POINTS"); break;
      case 102: return string("GE_R_CONSECUTIVE_POINTS_SAME"); break;
      case 103: return string("GE_R_NOT_CLOSED"); break;
      case 104: return string("GE_R_SELF_INTERSECTION"); break;
      case 105: return string("GE_R_COLLAPSED"); break;
      //-- POLYGON
      case 201: return string("GE_P_INTERSECTION_RINGS"); break;
      case 202: return string("GE_P_DUPLICATED_RINGS"); break;
      case 203: return string("GE_P_NON_PLANAR_POLYGON_DISTANCE_PLANE"); break;
      case 204: return string("GE_P_NON_PLANAR_POLYGON_NORMALS_DEVIATION"); break;
      case 205: return string("GE_P_INTERIOR_DISCONNECTED"); break;
      case 206: return string("GE_P_HOLE_OUTSIDE"); break;
      case 207: return string("GE_P_INNER_RINGS_NESTED"); break;
      case 208: return string("GE_P_ORIENTATION_RINGS_SAME"); break;
      //-- SHELL
      case 301: return string("GE_S_TOO_FEW_POLYGONS"); break;
      case 302: return string("GE_S_NOT_CLOSED"); break;
      case 303: return string("GE_S_NON_MANIFOLD_VERTEX"); break;
      case 304: return string("GE_S_NON_MANIFOLD_EDGE"); break;
      case 305: return string("GE_S_SEPARATE_PARTS"); break;
      case 306: return string("GE_S_SELF_INTERSECTION"); break;
      case 307: return string("GE_S_POLYGON_WRONG_ORIENTATION"); break;
      //--SOLID
      case 401: return string("GE_SO_INTERSECTION_SHELLS"); break;
      case 402: return string("GE_SO_DUPLICATED_SHELLS"); break;
      case 403: return string("GE_SO_INNER_SHELL_OUTSIDE"); break;
      case 404: return string("GE_SO_INTERIOR_DISCONNECTED"); break;
      case 405: return string("GE_SO_WRONG_ORIENTATION_SHELL"); break;
      //-- OTHERS
      case 901: return string("INVALID_INPUT_FILE"); break;
      case 999: return string("UNKNOWN_ERROR"); break;
      default:  return string("UNKNOWN_ERROR"); break;
    }
  }
}

//-- ignore XML namespace
std::string localise(std::string s)
{
  return "*[local-name(.) = '" + s + "']";
}


vector<int> process_gml_ring(pugi::xml_node n, Surface* sh, IOErrors& errs) {
  std::string s = "./" + localise("LinearRing") + "/" + localise("pos");
  pugi::xpath_node_set npos = n.select_nodes(s.c_str());
  vector<int> r;
  if (npos.size() > 0) //-- <gml:pos> used
  {
    for (pugi::xpath_node_set::const_iterator it = npos.begin(); it != npos.end(); ++it) {
      std::string buf;
      std::stringstream ss(it->node().child_value());
      std::vector<std::string> tokens;
      while (ss >> buf)
        tokens.push_back(buf);
      Point3 p(std::stod(tokens[0]), std::stod(tokens[1]), std::stod(tokens[2]));
      r.push_back(sh->add_point(p));
    }
  }
  else //-- <gml:posList> used
  {
    std::string s = "./" + localise("LinearRing") + "/" + localise("posList");
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
      Point3 p(std::stod(coords[i]), std::stod(coords[i+1]), std::stod(coords[i+2]));
      r.push_back(sh->add_point(p));
    }
  }
  return r;
}


Surface* process_gml_compositesurface(pugi::xml_node n, int id, map<std::string, pugi::xpath_node>& dallpoly, double tol_snap, IOErrors& errs) 
{
  std::string s = ".//" + localise("surfaceMember");
  pugi::xpath_node_set nsm = n.select_nodes(s.c_str());
  Surface* sh = new Surface(id, tol_snap);
  int i = 0;
  for (pugi::xpath_node_set::const_iterator it = nsm.begin(); it != nsm.end(); ++it)
  {
    vector< vector<int> > oneface;
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
    s = ".//" + localise("exterior");
    pugi::xpath_node ring = p.node().select_node(s.c_str());
    vector<int> r = process_gml_ring(ring.node(), sh, errs);
    if (fliporientation == true) 
      std::reverse(r.begin(), r.end());
    if (r.front() != r.back())
      sh->add_error(103, p.node().attribute("gml:id").value());
    else
      r.pop_back(); 
    oneface.push_back(r);
    //-- interior rings
    s = ".//" + localise("interior");
    pugi::xpath_node_set nint = it->node().select_nodes(s.c_str());
    for (pugi::xpath_node_set::const_iterator it = nint.begin(); it != nint.end(); ++it) {
      vector<int> r = process_gml_ring(it->node(), sh, errs);
      if (fliporientation == true) 
        std::reverse(r.begin(), r.end());
      if (r.front() != r.back())
        sh->add_error(103, p.node().attribute("gml:id").value());
      else
        r.pop_back(); 
      oneface.push_back(r);
    }
    sh->add_face(oneface, p.node().attribute("gml:id").value());
    i++;
  }
  return sh;
}


Solid* process_gml_solid(pugi::xpath_node nsolid, Primitive3D prim, map<std::string, pugi::xpath_node>& dallpoly, double tol_snap, IOErrors& errs)
{
  //-- exterior shell
  Solid* sol = new Solid;
  if (nsolid.node().attribute("gml:id") != 0)
    sol->set_id(std::string(nsolid.node().attribute("gml:id").value()));
  if (prim == SOLID) 
  {
    std::string s = "./" + localise("exterior");
    pugi::xpath_node next = nsolid.node().select_node(s.c_str());
    sol->set_oshell(process_gml_compositesurface(next.node(), 0, dallpoly, tol_snap, errs));
    //-- interior shells
    s = "./" + localise("interior");
    pugi::xpath_node_set nint = nsolid.node().select_nodes(s.c_str());
    int id = 1;
    for (pugi::xpath_node_set::const_iterator it = nint.begin(); it != nint.end(); ++it)
    {
      sol->add_ishell(process_gml_compositesurface(it->node(), id, dallpoly, tol_snap, errs));
      id++;
    }
  }
  else //-- both for CS and MS it's the same parsing 
  {
    sol->set_oshell(process_gml_compositesurface(nsolid.node(), 0, dallpoly, tol_snap, errs));
  }
  return sol;
}


void process_gml_building(vector<Solid*>& lsSolids, pugi::xpath_node nbuilding, Primitive3D prim, map<std::string, pugi::xpath_node>& dallpoly, double tol_snap, IOErrors& errs)
{
  std::string id_building;
  std::string id_buildingpart;
  if (nbuilding.node().attribute("gml:id") != 0)
    id_building = std::string(nbuilding.node().attribute("gml:id").value());
  else
    id_building = "";
  std::string s1 = ".//" + localise("BuildingPart");
  std::string s2;
  if (prim == SOLID)
    s2 = ".//" + localise("Solid");
  else if (prim == MULTISURFACE)
    s2 = ".//" + localise("MultiSurface");
  else
    return;
  pugi::xpath_node_set nbps = nbuilding.node().select_nodes(s1.c_str());
  if (nbps.empty() == false)
  {
    for (auto& nbp : nbps)
    {
      if (nbp.node().attribute("gml:id") != 0)
        id_buildingpart = std::string(nbp.node().attribute("gml:id").value());
      else
        id_buildingpart = "";
      pugi::xpath_node_set nsolids = nbp.node().select_nodes(s2.c_str());
      for (auto& nsolid : nsolids)
      {
        Solid* sol = process_gml_solid(nsolid, prim, dallpoly, tol_snap, errs);
//        sol->set_id_building(id_building);
//        sol->set_id_buildingpart(id_buildingpart);
        lsSolids.push_back(sol);
      }
    }
  }
  else
  {
    pugi::xpath_node_set nsolids = nbuilding.node().select_nodes(s2.c_str());
    for (auto& nsolid : nsolids)
    {
      Solid* sol = process_gml_solid(nsolid, prim, dallpoly, tol_snap, errs);
//      sol->set_id_building(id_building);
      lsSolids.push_back(sol);
    }
  }
}


void readGMLfile(std::vector<Solid*>& lsSolids, string &ifile, Primitive3D prim, bool buildings, IOErrors& errs, double tol_snap, int& nobuildings)
{
  std::cout << "Reading file: " << ifile << std::endl;
  pugi::xml_document doc;
  if (!doc.load_file(ifile.c_str())) 
  {
    errs.add_error(901, "Input file not found.");
    return;
  }

  //-- gml:Solid parsing and counting
  std::string s = "//";
  if (prim == SOLID)
    s += localise("Solid");
  else if (prim == COMPOSITESURFACE)
    s += localise("CompositeSurface");
  else 
    s += localise("MultiSurface");
  pugi::xpath_query myquery(s.c_str());
  pugi::xpath_node_set nsolids = myquery.evaluate_node_set(doc);
  std::cout << "Parsing the file..." << std::endl;
  if (prim == SOLID)
    std::cout << "# of <gml:Solid> found: ";
  else if (prim == COMPOSITESURFACE)
    std::cout << "# of <gml:CompositeSurface> found: ";
  else 
    std::cout << "# of <gml:MultiSurface> found: ";
  std::cout << nsolids.size() << std::endl;

  //-- CityGML Buildings
  pugi::xpath_node_set nbuildings;
  if (buildings == true) 
  {
    s = "//" + localise("Building");
    nbuildings = doc.select_nodes(s.c_str());
    nobuildings = nbuildings.size();
    std::cout << "# of CityGML Buildings found: " << nbuildings.size() << std::endl;
  }

  //-- build dico of xlinks
  //-- for <gml:Polygon>
  s = "//" + localise("Polygon") + "[@" + localise("id") + "]";
  pugi::xpath_node_set nallpoly = doc.select_nodes(s.c_str());
  if (nallpoly.size() > 0)
   std::cout << "XLinks found, resolving them..." << std::flush;
  map<std::string, pugi::xpath_node> dallpoly;
  for (pugi::xpath_node_set::const_iterator it = nallpoly.begin(); it != nallpoly.end(); ++it)
  {
   dallpoly[it->node().attribute("gml:id").value()] = *it;
  }
  //-- for <gml:OrientableSurface>
  s = "//" + localise("OrientableSurface") + "[@" + localise("id") + "]";
  pugi::xpath_node_set nallosurf = doc.select_nodes(s.c_str());
  // map<std::string, pugi::xpath_node> dallpoly;
  for (pugi::xpath_node_set::const_iterator it = nallosurf.begin(); it != nallosurf.end(); ++it)
  {
   dallpoly[it->node().attribute("gml:id").value()] = *it;
  }

  //-- checking xlinks validity now, not to be bitten later
  s = "//" + localise("surfaceMember") + "[@" + localise("href") + "]";
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
  if (buildings == true) 
  {
    for (auto& nbuilding: nbuildings)
    {
      process_gml_building(lsSolids, nbuilding, prim, dallpoly, tol_snap, errs);
    }
  }
  else 
  {
    for(auto& nsolid: nsolids)
    {
      Solid* sol = process_gml_solid(nsolid, prim, dallpoly, tol_snap, errs);
      lsSolids.push_back(sol);
    }
  }
  std::cout << "Input file correctly parsed without errors." << std::endl;
}


Surface* readPolyfile(std::string &ifile, int shellid, IOErrors& errs)
{
  std::clog << "Reading file: " << ifile << std::endl;
  std::stringstream st;
  ifstream infile(ifile.c_str(), ifstream::in);
  if (!infile)
  {
    errs.add_error(901, "Input file not found.");
    return NULL;
  }
  Surface* sh = new Surface(shellid);  
  //-- read the points
  int num, tmpint;
  float tmpfloat;
  infile >> num >> tmpint >> tmpint >> tmpint;
  vector< Point3 >::iterator iPoint3;
  //-- read first line to decide if 0- or 1-based indexing
  bool zerobased = true;
  Point3 p;
  infile >> tmpint >> p;
  sh->add_point(p);
  if (tmpint == 1)
    zerobased = false;
  //-- process other vertices
  for (int i = 1; i < num; i++)
  {
    Point3 p;
    infile >> tmpint >> p;
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
    vector<int> ids(numpt);
    for (int k = 0; k < numpt; k++)
      infile >> ids[k];
    if (zerobased == false)
    {
      for (int k = 0; k < numpt; k++)
        ids[k] = (ids[k] - 1);      
    }
    vector< vector<int> > pgnids;
    pgnids.push_back(ids);
    //-- check for irings
    for (int j = 1; j < numf; j++)
    {
      infile >> numpt;
      if (numpt == -1) {
        sh->add_error(103, std::to_string(i));
        continue;
      }
      vector<int> ids(numpt);
      for (int l = 0; l < numpt; l++)
        infile >> ids[l];
      if (zerobased == false)
      {
        for (int k = 0; k < numpt; k++)
          ids[k] = (ids[k] - 1);      
      }
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


void readOBJfile(std::vector<Solid*>& lsSolids, std::string &ifile, IOErrors& errs, double tol_snap)
{
  std::cout << "Reading file: " << ifile << std::endl;
  std::ifstream infile(ifile.c_str(), std::ifstream::in);
  if (!infile)
  {
    errs.add_error(901, "Input file not found.");
    return;
  }
  std::cout << "Parsing the file..." << std::endl; 
  Surface* sh = new Surface(0, tol_snap);
  std::string l;
  std::vector<Point3*> allvertices;
  while (std::getline(infile, l)) {
    std::istringstream iss(l);
    if (l.substr(0, 2) == "v ") {
      Point3 *p = new Point3();
      std::string tmp;
      iss >> tmp >> *p;
      allvertices.push_back(p);
    }
    else if (l.substr(0, 2) == "o ") {
      if (sh->is_empty() == false)
      {
//        Solid* sol = new Solid(OBJ);
        Solid* sol = new Solid();
        sol->set_oshell(sh);
        lsSolids.push_back(sol);
        sh = new Surface(0, tol_snap);
      }
    }
    else if (l.substr(0, 2) == "f ") {
      vector<int> r;
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
      vector< vector<int> > pgnids;
      pgnids.push_back(r);
      sh->add_face(pgnids);
    }
  }
//  Solid* s = new Solid(OBJ);
  Solid* s = new Solid();
  s->set_oshell(sh);
  lsSolids.push_back(s);
  for (auto& each : allvertices)
    delete each;
  allvertices.clear();
} 

  
