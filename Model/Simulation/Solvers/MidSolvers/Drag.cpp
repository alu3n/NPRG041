//
// Created by Vojtěch Pröschl on 04.04.2022.
//

#include <math.h>
#include "Drag.h"

using namespace std;
constexpr string_view _fluid_density = "Fluid Density";

//Those numbers are obtained from a physics book
constexpr double basic_drag_multiplier = 0.5; //the lower the number the stronger the drag force
constexpr double sphere_drag_coefficient = 0.5;


std::vector<std::tuple<std::string, std::string>> DragSolverSettings::get_contents() {
    vector<tuple<string,string>> temp;
    temp.emplace_back(tuple<string,string>(_fluid_density, to_string(fluid_density)));
    return temp;
}

bool DragSolverSettings::set_contents(const std::string &name, const std::string &value) {
    if(name == _fluid_density){
        fluid_density = convert_to_type<double>(value);
    }
    return false;
}

SolverType DragSolverSettings::get_type() {
    return SolverType::Drag;
}

bool DragSolver::Solve(std::vector<Particle> & particles) {
    //Implementation for sphere, might add other shapes in the future

    auto time_steps = metadata.framerate*metadata.substeps;
    for(auto && particle : particles){
        //Note: We assume that the fluid isn't moving
        double cross_sectional_area =  M_PI*pow(particle.size/2,2);

        double drag_force = (1.0/2)*sphere_drag_coefficient*(particle.velocity.norm())*settings.fluid_density*cross_sectional_area;

        particle.velocity *= pow(pow(basic_drag_multiplier,drag_force),1.0/time_steps);
    }
    return true;
}

DragSolver::DragSolver(SolverMetadata metadata, DragSolverSettings settings) : MidSolver(metadata){
    this->settings = settings;
}
