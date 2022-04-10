//
// Created by Vojtěch Pröschl on 02.04.2022.
//

#ifndef NPRG041_VORTEX_H
#define NPRG041_VORTEX_H

#include "../../../Shared/SmartConversion.h"
#include "../../Solver.h"
#include "../../../../Dependencies/Eigen/Eigen"
#include "../../../Shared/Settings.h"

class VortexSolverSettings : public SolverSettings{
public:
    Eigen::Vector<double,3> position;
    Eigen::Vector<double,3> rotation_axis;
    double range;
    double amplitude;
    std::vector<std::tuple<std::string,std::string>> get_contents() override;
    bool set_contents(const std::string & name, const std::string & value) override;
    SolverType get_type() override;
};

class VortexSolver : public MidSolver{
    VortexSolverSettings settings;
public:
    bool Solve(std::vector<Particle> &) override;
    VortexSolver(SolverMetadata,VortexSolverSettings);
};

#endif //NPRG041_VORTEX_H

