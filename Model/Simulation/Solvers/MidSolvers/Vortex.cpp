//
// Created by Vojtěch Pröschl on 08.04.2022.
//

#include "Vortex.h"

using namespace std;
using string_t = tuple<string,string>;

constexpr string_view _amplitude = "Amplitude";
constexpr string_view _range = "Range";
constexpr string_view _position = "Position";
constexpr string_view _rotation_axis = "Rotation Axis";

bool VortexSolverSettings::set_contents(const std::string &name, const std::string &value) {
    if(name == _amplitude){
        amplitude = convert_to_type<double>(value);
        return true;
    }
    else if(name == _range){
        range = convert_to_type<double>(value);
        return true;
    }
    else if(name == _position){
        position = convert_to_vector<double,3>(value);
        return true;
    }
    else if(name == _rotation_axis){
        rotation_axis = convert_to_vector<double,3>(value);
        return true;
    }
}

SolverType VortexSolverSettings::get_type() {
    return SolverType::Vortex;
}

std::vector<std::tuple<std::string, std::string>> VortexSolverSettings::get_contents() {
    vector<string_t> temp;
    temp.emplace_back(string_t(_amplitude, to_string(amplitude)));
    temp.emplace_back(string_t(_range,to_string(range)));
    temp.emplace_back(string_t(_position,smart_to_string<double,3>(position)));
    temp.emplace_back(string_t(_rotation_axis,smart_to_string<double,3>(rotation_axis)));
    return temp;
}

bool VortexSolver::Solve(std::vector<Particle> & particles) {
    //Todo: Solve this part xd
}

VortexSolver::VortexSolver(SolverMetadata metadata, VortexSolverSettings settings) : MidSolver(metadata) {
    this->settings = settings;
}