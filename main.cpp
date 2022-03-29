#include <iostream>
#include "Model/Shared/Settings.h"
#include "Dependencies/Eigen/Eigen"
#include "Model/Shared/SmartConversion.h"

using namespace std;

int main() {
//    SimulationSettings S;
//    S.set_contents("Substeps"," 100");
//
//    for(auto && x : S.get_contents()){
//        std::cout << std::get<0>(x) + " " + std::get<1>(x) << std::endl;
//    }

//    Eigen::Vector<int,5> test(1,2,3,2,1);
//    std::cout << smart_to_string<int,5>(test) << std::endl;

    std::string test_double1 = "-1.1";
    std::string test_vector1 = "(-1.5,1.0,3,-0.003)";
    std::string test_vector2 = "-1 -1 -1 -1";

    cout << convert_to_type<double>(test_double1) << endl;

    cout << convert_to_vector<double,4>(test_vector1) << endl;

    cout << convert_to_vector<int,4>(test_vector2) << endl;

}
