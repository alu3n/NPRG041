//
// Created by Vojtěch Pröschl on 29.03.2022.
//

#include <iostream>
#include <memory>
#include "Simulation.h"
#include "Solver.h"
#include "Solvers/PreSolvers/Source.h"
#include "Solvers/MidSolvers/Gravity.h"
#include "Solvers/MidSolvers/Turbulence.h"
#include "../../Render/DebRenderer.h"

using namespace std;


using namespace std;

bool Simulation::simulation_core(std::vector<Particle> & particles) {
    for(auto && particle : particles){
        particle.position += ((1.0)/(settings.Framerate*settings.Substeps))*particle.velocity;
    }
}

Simulation::Simulation(const SimulationSettings & settings, std::vector<SolverSettings *> solvers_settings) {
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
        }
    }
}

Cache &Simulation::Simulate() {
    Cache temp(this->settings.CacheFolder);
    std::vector<Particle> data;
    int frame_count = this->settings.Framerate*this->settings.Duration;
    for(int i = 0; i < frame_count; i++){
        cout << "Simulating frame " << i << endl;
        simulate_frame(data);
        temp.cache_frame(i,data);
    }

    DebRenderer renderer(500,500,10,"Render");
    renderer.RenderCache(temp);

    return temp;
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
        cout << "Presolving!" << endl;
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