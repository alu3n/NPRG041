//
// Created by Vojtěch Pröschl on 29.03.2022.
//

#include "Simulation.h"

Simulation::Simulation(const SimulationSettings & settings, std::vector<SolverSettings *> solvers_settings) {
    this->settings = settings;
    for(auto && x : solvers_settings){
        auto type = x->get_type();
        switch(type){
            case SolverType::Source:
                break;
            default:
                break;
        }
    }
}

Cache &Simulation::Simulate() {

}

bool Simulation::simulate_frame() {

}

bool Simulation::simulate_step() {

}