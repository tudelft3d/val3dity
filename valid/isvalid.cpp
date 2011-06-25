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


#include <CGAL/Exact_predicates_exact_constructions_kernel.h>
#include <CGAL/Polyhedron_3.h>
#include <CGAL/IO/Polyhedron_iostream.h>
#include <CGAL/Nef_polyhedron_3.h>
#include <CGAL/IO/Nef_polyhedron_iostream_3.h>

#include <vector>
#include <iostream>
#include <fstream>

typedef CGAL::Exact_predicates_exact_constructions_kernel Kernel;
typedef CGAL::Polyhedron_3<Kernel>  Polyhedron;
typedef CGAL::Nef_polyhedron_3<Kernel>  Nef_polyhedron;

typedef Kernel::Vector_3  Vector_3;
typedef Kernel::Point_3  Point_3;
typedef Kernel::Aff_transformation_3  Aff_transformation_3;

int main(int argc, char* const argv[]) 
{
  if (argc < 2)
  {
    std::cout << "You have to give at least one input OFF file." << std::endl;
    return(0);
  }
  
  int numShells = (argc - 1);
  std::cout << "Processing " << numShells << " file(s)." << std::endl;
  
  std::cout << "Reading file " << argv[1] << std::endl;
  Polyhedron oshell;
  std::ifstream infile;
  infile.open(argv[1], std::ifstream::in);
  infile >> oshell;
  Nef_polyhedron onef(oshell);
  
  std::vector< Nef_polyhedron > inefs;
  for (int i=2; i<argc; i++)
  {
    std::cout << "Reading file " << argv[i] << std::endl;
    Polyhedron ishell;
    std::ifstream infile;
    infile.open(argv[i], std::ifstream::in);
    infile >> ishell;
    Nef_polyhedron inef(ishell);
    inefs.push_back(inef);
  }

  Nef_polyhedron solid = onef;
  std::vector<Nef_polyhedron>::iterator inefsIt = inefs.begin();
  for ( ; inefsIt != inefs.end(); inefsIt++) 
    solid -= *inefsIt;
  
 // std::cout << "---Stats for onef---" << std::endl;
//	std::cout << "# volumes " << onef.number_of_volumes() << std::endl;

	
//  Nef_polyhedron solid = onef - inefs[0];
	std::cout << "---Stats for solid---" << std::endl;
	std::cout << "# volumes " << solid.number_of_volumes() << std::endl;

	
//  Nef_polyhedron solid2 = onef + inefs[0];
//	std::cout << "\n---Stats for solid2---" << std::endl;
//	std::cout << "# volumes " << solid2.number_of_volumes() << std::endl;
  
 // Nef_polyhedron::Volume_const_handle c;
//  Nef_polyhedron::Object_handle o = solid.locate(Point_3(0.4, 0.4, 0.31));
//  CGAL::assign(c,o);
//  std::cout << "Locating volume" << c->mark() << std::endl;
  
  
	
	if (solid.number_of_volumes() == (numShells+1))
    std::cout << "Valid." << std::endl;
  else
    std::cout << "Invalid. " << solid.number_of_volumes() << std::endl;
  
  
}
/*
  Nef_polyhedron N1(N);
  Aff_transformation_3 aff(CGAL::SCALING, 0.2);
  N1.transform(aff);
  Nef_polyhedron N2(N1);
  Aff_transformation_3 aff2(CGAL::TRANSLATION, Vector_3(0.1, 0.1, 0.1));
  N1.transform(aff2);
  Aff_transformation_3 aff3(CGAL::TRANSLATION, Vector_3(0.3, 0.1, 0.1));
  N2.transform(aff3);
*/
  
//  std::cout << "---Stats for onef---" << std::endl;
//  std::cout << "Simple? " << onef.is_simple() << std::endl;
//  std::cout << "Valid? " << onef.is_valid() << std::endl;  
//  std::cout << "# volumes " << onef.number_of_volumes() << std::endl;
//
//  std::cout << "---Stats for inef---" << std::endl;
//  std::cout << "Simple? " << inef.is_simple() << std::endl;
//  std::cout << "Valid? " << inef.is_valid() << std::endl;  
//  std::cout << "# volumes " << inef.number_of_volumes() << std::endl;

//  solid -= N2;
  
//  std::cout << "---Stats for solid---" << std::endl;
//  std::cout << "Simple? " << solid.is_simple() << std::endl;
//  std::cout << "Valid? " << solid.is_valid() << std::endl;  
//  std::cout << "# volumes " << solid.number_of_volumes() << std::endl;
//  
//    if(solid.is_simple()) {
//      solid.convert_to_Polyhedron(P);
//      std::cout << P;
//    }
//}
