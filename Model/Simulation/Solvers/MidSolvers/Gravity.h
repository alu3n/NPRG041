//
// Created by Vojtěch Pröschl on 01.04.2022.
//

#ifndef NPRG041_GRAVITY_H
#define NPRG041_GRAVITY_H

#include "../../../Shared/SmartConversion.h"
#include "../../Solver.h"
#include "../../../../Dependencies/Eigen/Eigen"
#include "../../../Shared/Settings.h"

class GravitySolverSettings : public SolverSettings{
public:
    Eigen::Vector<double,3> force = {0,-4,0};
    std::vector<std::tuple<std::string,std::string>> get_contents() override;
    bool set_contents(const std::string & name, const std::string & value) override;
    SolverType get_type() override;
};

class GravitySolver : public MidSolver{
    GravitySolverSettings settings;
public:
    bool Solve(std::vector<Particle> &) override;
    GravitySolver(SolverMetadata,GravitySolverSettings);
};

#endif //NPRG041_GRAVITY_H
