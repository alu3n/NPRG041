//
// Created by Vojtěch Pröschl on 02.04.2022.
//

#ifndef NPRG041_ATTRACT_H
#define NPRG041_ATTRACT_H

#include "../../../Shared/SmartConversion.h"
#include "../../Solver.h"
#include "../../../../Dependencies/Eigen/Eigen"
#include "../../../Shared/Settings.h"

class AttractSolverSettings : public SolverSettings{
public:
    Eigen::Vector<double,3> position = {0,0,0};
    double range = 1;
    double amplitude = 1;
    std::vector<std::tuple<std::string,std::string>> get_contents() override;
    bool set_contents(const std::string & name, const std::string & value) override;
    SolverType get_type() override;
};

class AttractSolver : public MidSolver{
    AttractSolverSettings settings;
public:
    bool Solve(std::vector<Particle> &) override;
    AttractSolver(SolverMetadata,AttractSolverSettings);
};


#endif //NPRG041_ATTRACT_H
