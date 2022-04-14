//
// Created by Vojtěch Pröschl on 29.03.2022.
//

#ifndef NPRG041_SOURCE_H
#define NPRG041_SOURCE_H

#include <random>
#include "../../Solver.h"
#include "../../../../Dependencies/Eigen/Eigen"
#include "../../../Shared/Settings.h"

class SourceSolverSettings : public SolverSettings{
public:
    int count = 240; //Ammount of particles sourced per second (will be done stochastically)
    double source_radius = 1;
    Eigen::Vector<double,3> position = {0,0,0};
    Eigen::Vector<double,2> velocity_x_range = {-10,10}; //(vel_x_min,vel_x_max)
    Eigen::Vector<double,2> velocity_y_range = {-10,10};
    Eigen::Vector<double,2> velocity_z_range = {-10,10};
    Eigen::Vector<double,2> size_range = {0,1};
    Eigen::Vector<double,2> density_range = {0,1};

    std::vector<std::tuple<std::string,std::string>> get_contents() override;
    bool set_contents(const std::string & name, const std::string & value) override;
    SolverType get_type() override;
};

class SourceSolver : public PreSolver{
    SourceSolverSettings settings;
    void source_particle(std::vector<Particle> &);
    std::default_random_engine generator;
public:
    bool Solve(std::vector<Particle> &) override;
    SourceSolver(SolverMetadata,SourceSolverSettings);
};

#endif //NPRG041_SOURCE_H
