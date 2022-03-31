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
    Cache temp;
    std::vector<Particle> data;
    int frame_count = this->settings.Framerate*this->settings.Duration;
    for(int i = 0; i < frame_count; i++){
        simulate_frame(data);
        temp.cache_frame(0,data);
    }
}

bool Simulation::simulate_frame(std::vector<Particle> & data) {
    for(int i = 0; i < this->settings.Substeps; i++){
        simulate_step(data);
    }
}

bool Simulation::simulate_step(std::vector<Particle> & data) {
    pre_solve(data);
    mid_solve(data);
    post_solve(data);
}

bool Simulation::pre_solve(std::vector<Particle> & data){
    for(auto && solver : pre_solvers){
        solver->Solve(data);
    }
}

bool Simulation::mid_solve(std::vector<Particle> & data) {
    for(auto && solver : mid_solvers){
        solver->Solve(data);
    }
}

bool Simulation::post_solve(std::vector<Particle> & data) {
    for(auto && solver : post_solvers){
        solver->Solve(data);
    }
}