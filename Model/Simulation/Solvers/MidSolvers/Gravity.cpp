//
// Created by Vojtěch Pröschl on 01.04.2022.
//

#include "Gravity.h"
#include "../../../Shared/SmartConversion.h"

using namespace std;
using string_t = tuple<string,string>;

constexpr string_view _force = "Force";

bool GravitySolver::Solve(std::vector<Particle> & Particles) {
    //Todo: Make this more realistic
    double force_multiplier = (1.0)/(metadata.framerate*metadata.substeps);
    for(auto && particle : Particles){
        particle.velocity += force_multiplier*settings.force;
    }
}

GravitySolver::GravitySolver(SolverMetadata metadata, GravitySolverSettings settings) : MidSolver(metadata) {
    this->settings = settings;
}


std::vector<std::tuple<std::string, std::string>> GravitySolverSettings::get_contents() {
    vector<string_t> temp;
    temp.emplace_back(string_t(_force,smart_to_string<double,3>(force)));
    return temp;
}



bool GravitySolverSettings::set_contents(const std::string &name, const std::string &value) {
    if(name == _force){
        force = convert_to_vector<double,3>(value);
    }
    return false;
}

SolverType GravitySolverSettings::get_type() {
    return SolverType::Gravity;
}