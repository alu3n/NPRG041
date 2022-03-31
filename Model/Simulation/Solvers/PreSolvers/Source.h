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
    int count; //Ammount of particles sourced per second (will be done stochastically)
    Eigen::Vector<double,2> velocity_x_range; //(vel_x_min,vel_x_max)
    Eigen::Vector<double,2> velocity_y_range;
    Eigen::Vector<double,2> velocity_z_range;
    Eigen::Vector<double,2> size_range;
    Eigen::Vector<double,2> density_range;
    //Todo: Add possibility to source different shapes

    std::vector<std::tuple<std::string,std::string>> get_contents() override;
    bool set_contents(const std::string & name, const std::string & value) override;
    SolverType get_type() override;
};

/* Sourcing should be stochastic
 */
class SourceSolver : public PreSolver{
    SourceSolverSettings settings;
    void source_particle(std::vector<Particle> &);
public:
    bool Solve(std::vector<Particle> &) override;
    SourceSolver(SolverMetadata,SourceSolverSettings);
};

#endif //NPRG041_SOURCE_H
