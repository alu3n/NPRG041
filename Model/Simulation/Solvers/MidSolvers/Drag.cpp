//
// Created by Vojtěch Pröschl on 04.04.2022.
//

#include "Drag.h"

using namespace std;
constexpr string_view _drag_coefficient = "Drag Coefficient";


std::vector<std::tuple<std::string, std::string>> DragSolverSettings::get_contents() {
    vector<tuple<string,string>> temp;
    temp.emplace_back(tuple<string,string>(_drag_coefficient, to_string(drag_coefficient)));
    return temp;
}

bool DragSolverSettings::set_contents(const std::string &name, const std::string &value) {
    if(name == _drag_coefficient){
        drag_coefficient = convert_to_type<double>(value);
    }
    return false;
}

SolverType DragSolverSettings::get_type() {
    return SolverType::Drag;
}

bool DragSolver::Solve(std::vector<Particle> & particles) {
    auto time_steps = metadata.framerate*metadata.substeps;
    for(auto && particle : particles){
        particle.velocity *= pow(settings.drag_coefficient,1.0/time_steps);
    }
    return true;
    //Todo: Make this solver more physically accurate
}

DragSolver::DragSolver(SolverMetadata metadata, DragSolverSettings settings) : MidSolver(metadata){
    this->settings = settings;
}
