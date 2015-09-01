/*
 val3dity - Copyright (c) 2011-2015, Hugo Ledoux.  All rights reserved.
 
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


Shell*       process_gml_shell(pugi::xml_node n, int id, map<std::string, pugi::xpath_node>& dallpoly, double tol_snap, IOErrors& errs, bool translatevertices = true);
vector<int>   process_gml_ring(pugi::xml_node n, Shell* sh, IOErrors& errs);

std::string   localise(std::string s);

/////

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
      ss << "\t" << err.first << " -- " << errorcode2description(err.first) << std::endl;
      ss << "\t\tInfo: " << i << std::endl;
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
      case 206: return string("HOLE_OUTSIDE"); break;
      case 207: return string("INNER_RINGS_NESTED"); break;
      case 208: return string("ORIENTATION_RINGS_SAME"); break;
      //-- SHELL
      case 300: return string("NOT_VALID_2_MANIFOLD"); break;
      case 301: return string("TOO_FEW_POLYGONS"); break;
      case 302: return string("SHELL_NOT_CLOSED"); break;
      case 303: return string("NON_MANIFOLD_VERTEX"); break;
      case 304: return string("NON_MANIFOLD_EDGE"); break;
      case 305: return string("MULTIPLE_CONNECTED_COMPONENTS"); break;
      case 306: return string("SHELL_SELF_INTERSECTION"); break;
      case 307: return string("POLYGON_WRONG_ORIENTATION"); break;
      case 308: return string("ALL_POLYGONS_WRONG_ORIENTATION"); break;
      case 309: return string("VERTICES_NOT_USED"); break;
      //--SOLID
      case 401: return string("SHELLS_FACE_ADJACENT"); break;
      case 402: return string("INTERSECTION_SHELLS"); break;
      case 403: return string("INNER_SHELL_OUTSIDE_OUTER"); break;
      case 404: return string("SOLID_INTERIOR_DISCONNECTED"); break;
      case 901: return string("INVALID_INPUT_FILE"); break;
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
      case 305: return string("GE_S_MULTIPLE_CONNECTED_COMPONENTS"); break;
      case 306: return string("GE_S_SELF_INTERSECTION"); break;
      case 307: return string("GE_S_POLYGON_WRONG_ORIENTATION"); break;
      case 308: return string("GE_S_ALL_POLYGONS_WRONG_ORIENTATION"); break;
      //--SOLID
      case 401: return string("GE_SO_SHELLS_FACE_ADJACENT"); break;
      case 402: return string("GE_SO_INTERSECTION_SHELLS"); break;
      case 403: return string("GE_SO_INNER_SHELL_OUTSIDE_OUTER"); break;
      case 404: return string("GE_SO_INTERIOR_DISCONNECTED"); break;
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


vector<int> process_gml_ring(pugi::xml_node n, Shell* sh, IOErrors& errs) {
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
      errs.add_error(901, "Error: GML way to represent gml:Polygon not handled.");
      return r;
    }
    std::string buf;
    std::stringstream ss(pl.node().child_value());
    std::vector<std::string> tokens;
    while (ss >> buf)
      tokens.push_back(buf);
    if (tokens.size() % 3 != 0)
    {
      errs.add_error(901, "Error: <gml:posList> has bad coordinates.");
      return r;
    }
    for (auto it = tokens.begin(); it != tokens.end(); it++)
    {
      Point3 p(std::stod(*it), std::stod(*++it), std::stod(*++it));
      r.push_back(sh->add_point(p));
    }
  }
  r.pop_back();
  return r;
}


Shell* process_gml_shell(pugi::xml_node n, int id, map<std::string, pugi::xpath_node>& dallpoly, double tol_snap, IOErrors& errs, bool translatevertices) {
  std::string s = ".//" + localise("surfaceMember");
  pugi::xpath_node_set nsm = n.select_nodes(s.c_str());
  Shell* sh = new Shell(id, tol_snap);
  for (pugi::xpath_node_set::const_iterator it = nsm.begin(); it != nsm.end(); ++it)
  {
    vector< vector<int> > oneface;
    bool bxlink = false;
    pugi::xml_node tmpnode = it->node();
    pugi::xpath_node p;
    for (pugi::xml_attribute attr = tmpnode.first_attribute(); attr; attr = attr.next_attribute())
    {
      if (strcmp(attr.value(), "xlink:href") != 0) {
        bxlink = true;
        break;
      }
    }
    if (bxlink == true)
      p = dallpoly[it->node().attribute("xlink:href").value()];
    else
    {
      std::string s2 = "./" + localise("Polygon");
      p = it->node().select_node(s2.c_str());
    }
    //-- exterior ring (only 1)
    s = "./" + localise("exterior");
    pugi::xpath_node ring = p.node().select_node(s.c_str());
    oneface.push_back(process_gml_ring(ring.node(), sh, errs));
    //-- interior rings
    s = "./" + localise("interior");
    pugi::xpath_node_set nint = it->node().select_nodes(s.c_str());
    for (pugi::xpath_node_set::const_iterator it = nint.begin(); it != nint.end(); ++it) {
      oneface.push_back(process_gml_ring(it->node(), sh, errs));
    }
    sh->add_face(oneface);
  }
  if (translatevertices == true)
    sh->translate_vertices();
  return sh;
}


vector<Solid> readGMLfile(string &ifile, IOErrors& errs, double tol_snap, bool translatevertices)
{
  std::cout << "Reading file: " << ifile << std::endl;
  vector<Solid> lsSolids;
  pugi::xml_document doc;
  if (!doc.load_file(ifile.c_str())) 
  {
    errs.add_error(901, "Input file not found.");
    return lsSolids;
  }
  std::string s = "//" + localise("Solid");
  pugi::xpath_query myquery(s.c_str());
  pugi::xpath_node_set nsolids = myquery.evaluate_node_set(doc);
  std::cout << "# of gml:Solids found: " << nsolids.size() << std::endl;
  std::clog << "...parsing the file and building the solids." << std::endl;

  //-- build dico of xlinks
  s = "//" + localise("Polygon") + "[@" + localise("id") + "]";
  pugi::xpath_node_set nallpoly = doc.select_nodes(s.c_str());
  map<std::string, pugi::xpath_node> dallpoly;
  for (pugi::xpath_node_set::const_iterator it = nallpoly.begin(); it != nallpoly.end(); ++it)
  {
    dallpoly[it->node().attribute("gml:id").value()] = *it;
  }
  map<std::string, pugi::xpath_node> dxlinks;
  s = "//" + localise("surfaceMember") + "[@" + localise("href") + "]";
  pugi::xpath_node_set nsmxlink = doc.select_nodes(s.c_str());
  for (pugi::xpath_node_set::const_iterator it = nsmxlink.begin(); it != nsmxlink.end(); ++it)
    dxlinks[it->node().attribute("xlink:href").value()] = dallpoly[it->node().attribute("xlink:href").value()];

  for(auto& nsolid: nsolids)
  {
    //-- exterior shell
    Solid sol;
    if (nsolid.node().attribute("gml:id") != 0)
      sol.set_id(std::string(nsolid.node().attribute("gml:id").value()));
    std::string s = "./" + localise("exterior");
    pugi::xpath_node next = nsolid.node().select_node(s.c_str());
    sol.set_oshell(process_gml_shell(next.node(), 0, dallpoly, tol_snap, errs));
    //-- interior shells
    s = "./" + localise("interior");
    pugi::xpath_node_set nint = nsolid.node().select_nodes(s.c_str());
    int id = 1;
    for (pugi::xpath_node_set::const_iterator it = nint.begin(); it != nint.end(); ++it)
    {
      sol.add_ishell(process_gml_shell(it->node(), id, dallpoly, tol_snap, errs));
      id++;
    }
    lsSolids.push_back(sol);
  }
  if (translatevertices == true)
  std::clog << "done." << std::endl;
  return lsSolids;
}




Shell* readPolyfile(std::string &ifile, int shellid, IOErrors& errs, bool translatevertices)
{
  std::clog << "Reading file: " << ifile << std::endl;
  std::stringstream st;
  ifstream infile(ifile.c_str(), ifstream::in);
  if (!infile)
  {
    errs.add_error(901, "Input file not found.");
    return NULL;
  }
  Shell* sh = new Shell(shellid);  
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
  //-- translate all vertices to (minx, miny)
  if (translatevertices == true)
    sh->translate_vertices();
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
      sh->add_error(103, i);
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
        sh->add_error(103, i);
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

