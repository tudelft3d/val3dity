#include <CGAL/Exact_predicates_exact_constructions_kernel.h>
#include <CGAL/Polyhedron_3.h>
#include <CGAL/IO/Polyhedron_iostream.h>
#include <CGAL/Nef_polyhedron_3.h>
#include <CGAL/IO/Nef_polyhedron_iostream_3.h>
#include <iostream>
#include <fstream>


typedef CGAL::Exact_predicates_exact_constructions_kernel Kernel;
typedef CGAL::Polyhedron_3<Kernel>  Polyhedron;
typedef CGAL::Nef_polyhedron_3<Kernel>  Nef_polyhedron;

typedef Kernel::Vector_3  Vector_3;
typedef Kernel::Aff_transformation_3  Aff_transformation_3;

int main(int argc, char* const argv[]) 
{
  if (argc != 2)
  {
    std::cout << "You have to give an input OFF file." << std::endl;
    return(0);
  }

  Polyhedron P;
  std::ifstream infile;
  infile.open(argv[1], std::ifstream::in);
  infile >> P;
/*  
  Polyhedron P1;
   std::ifstream infile1;
  infile1.open("/tmp/smallcube.off", std::ifstream::in);
  infile1 >> P1;
*/
  
  if (P.empty() == true)
  {
    std::cout << "P Invalid 2-manifold" << std::endl;
    return(0);
  }
/*  if (P1.empty() == true)
  {
    std::cout << "P1 Invalid 2-manifold" << std::endl;
    return(0);
  }
*/

  Nef_polyhedron N(P);
//  Nef_polyhedron N1(P1);

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
  
  std::cout << "---Stats for N---" << std::endl;
  std::cout << "Simple? " << N.is_simple() << std::endl;
  std::cout << "Valid? " << N.is_valid() << std::endl;  
  std::cout << "# volumes " << N.number_of_volumes() << std::endl;

  /*
  std::cout << "---Stats for N1---" << std::endl;
  std::cout << "Simple? " << N1.is_simple() << std::endl;
  std::cout << "Valid? " << N1.is_valid() << std::endl;  
  std::cout << "# volumes " << N1.number_of_volumes() << std::endl;

  Nef_polyhedron solid = N - N1;
  solid -= N2;
  
  std::cout << "---Stats for solid---" << std::endl;
  std::cout << "Simple? " << solid.is_simple() << std::endl;
  std::cout << "Valid? " << solid.is_valid() << std::endl;  
  std::cout << "# volumes " << solid.number_of_volumes() << std::endl;
  
    if(solid.is_simple()) {
      solid.convert_to_Polyhedron(P);
      std::cout << P;
    }
*/    
}
