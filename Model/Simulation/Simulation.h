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

//Todo: Create solver to move according to the velocity

//Note: This class is implemented in the Settings.cpp
class SimulationSettings final : public Settings{
public:
    int Duration = default_duration; //In seconds
    int Substeps = default_substeps; //Per frame
    int Framerate = default_framerate; //Per second
    std::string CacheFolder = std::string(default_cache_folder);
    std::vector<std::tuple<std::string,std::string>> get_contents() override;
    bool set_contents(const std::string & name,const std::string & value) override;
};

class Simulation{
private:
    SimulationSettings settings;
    std::vector<std::unique_ptr<PreSolver>> pre_solvers;
    std::vector<std::unique_ptr<MidSolver>> mid_solvers;
    std::vector<std::unique_ptr<PostSolver>> post_solvers;

    void status_print(const std::vector<Particle> &, int, int);
    void age(std::vector<Particle> &);
    static std::vector<Particle> remove_corpses(std::vector<Particle> &);

    bool simulate_step(std::vector<Particle> &);
    bool simulate_frame(std::vector<Particle> &);
    bool pre_solve(std::vector<Particle> &);
    bool mid_solve(std::vector<Particle> &);
    bool post_solve(std::vector<Particle> &);
    bool simulation_core(std::vector<Particle> &);
public:
    Simulation(const SimulationSettings &, const std::vector<SolverSettings *> &);
    Cache Simulate();
};



#endif //NPRG041_SIMULATION_H
