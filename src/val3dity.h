#include "nlohmann-json/json.hpp"

using json = nlohmann::json;

namespace val3dity
{

  
std::vector<bool> validate_tu3djson(json& j,
                    double tol_snap=0.001, 
                    double planarity_d2p_tol=0.01, 
                    double planarity_n_tol=20.0, 
                    double overlap_tol=-1.0);


  bool validate_cityjson(json& j, 
                         double tol_snap=0.001, 
                         double planarity_d2p_tol=0.01, 
                         double planarity_n_tol=20.0, 
                         double overlap_tol=-1.0);

}

