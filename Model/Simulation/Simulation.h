//
// Created by Vojtěch Pröschl on 28.03.2022.
//

#ifndef NPRG041_SIMULATION_H
#define NPRG041_SIMULATION_H

#include <vector>
#include <memory>
#include "Cache.h"
#include "Particle.h"
#include "Solver.h"
#include "../Shared/Settings.h"

//Note: This class is implemented in the Settings.cpp
class SimulationSettings final : public Settings{
    int Duration = default_duration; //In seconds
    int Substeps = default_substeps; //Per frame
    int Framerate = default_framerate; //Per second
    std::string CacheFolder = std::string(default_cache_folder);
public:
    std::vector<std::tuple<std::string,std::string>> get_contents() override;
    bool set_contents(const std::string & name,const std::string & value) override;
};

class Simulation{
private:
    SimulationSettings settings;
    std::vector<std::unique_ptr<PreSolver>> pre_solvers;
    std::vector<std::unique_ptr<MidSolver>> mid_solvers;
    std::vector<std::unique_ptr<PostSolver>> post_solvers;

    bool simulate_step;
    bool simulate_frame;
public:
    Simulation(const SimulationSettings &, std::vector<SolverSettings *>);
    Cache & Simulate();
};



#endif //NPRG041_SIMULATION_H
