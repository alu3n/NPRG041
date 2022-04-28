//
// Created by Vojtěch Pröschl on 29.03.2022.
//

#include <iostream>
#include <memory>
#include <chrono>
#include <algorithm>
#include "Simulation.h"
#include "Solver.h"
#include "Solvers/PreSolvers/Source.h"
#include "Solvers/MidSolvers/Gravity.h"
#include "Solvers/MidSolvers/Turbulence.h"
#include "Solvers/MidSolvers/Drag.h"

using namespace std;


using namespace std;

bool Simulation::simulation_core(std::vector<Particle> & particles) {
    for(auto && particle : particles){
        particle.position += ((1.0)/(settings.Framerate*settings.Substeps))*particle.velocity;
    }
}

Simulation::Simulation(const SimulationSettings & settings, const std::vector<SolverSettings *> & solvers_settings) {
    this->settings = settings;
    SolverMetadata metadata(settings.Substeps,settings.Framerate);
    for(auto && x : solvers_settings){
        auto type = x->get_type();
        switch(type){
            case SolverType::Source:
                pre_solvers.emplace_back(make_unique<SourceSolver>(metadata,*(dynamic_cast<SourceSolverSettings*>(x))));
                break;
            case SolverType::Gravity:
                mid_solvers.emplace_back(make_unique<GravitySolver>(metadata,*(dynamic_cast<GravitySolverSettings*>(x))));
                break;
            case SolverType::Turbulence:
                mid_solvers.emplace_back(make_unique<TurbulenceSolver>(metadata,*(dynamic_cast<TurbulenceSolverSettings*>(x))));
            default:
                break;
            case SolverType::Drag:
                mid_solvers.emplace_back(make_unique<DragSolver>(metadata,*(dynamic_cast<DragSolverSettings*>(x))));
                break;
        }
    }
}

Cache Simulation::Simulate() {
    Cache temp(this->settings.CacheFolder);
    std::vector<Particle> data;

    auto start = chrono::steady_clock::now();

    int frame_count = this->settings.Framerate*this->settings.Duration;
    for(int i = 0; i < frame_count; i++){
        status_print(data,i,frame_count);
        simulate_frame(data);
        temp.cache_frame(i,data);
    }

    auto end = chrono::steady_clock::now();

    cout << "Simulation Time: " << chrono::duration_cast<chrono::milliseconds>(end - start).count() << " ms" << endl; //Todo: Make this visible after clean
    return temp;
}

bool Simulation::simulate_frame(std::vector<Particle> & data) {
    for(int i = 0; i < this->settings.Substeps; ++i){
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
    return true;
}

bool Simulation::mid_solve(std::vector<Particle> & data) {
    for(auto && solver : mid_solvers){
        solver->Solve(data);
    }
    simulation_core(data);
    return true;
}

bool Simulation::post_solve(std::vector<Particle> & data) {
    for(auto && solver : post_solvers){
        solver->Solve(data);
    }
    return true;
}

void Simulation::status_print(const std::vector<Particle> & particles, int frame_num, int frame_count) {
    system("clear");
    cout << "# SIMULATING FRAME " << frame_num+1 << "/" << frame_count << " #" << endl;
    cout << "- Particle count: " << particles.size() << endl;
}

void Simulation::age(std::vector<Particle> & particles) {
    for(auto && particle :particles){
        particle.age+=1.0/this->settings.Framerate;
    }
}

std::vector<Particle> Simulation::remove_corpses(std::vector<Particle> & particles) {
    std::vector<Particle> temp;
    for(auto && particle : particles){
        if(particle.age >= particle.life){
            temp.push_back(particle);
        }
    }
    return temp;
}