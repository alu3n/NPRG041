//
// Created by Vojtěch Pröschl on 01.04.2022.
//

#ifndef NPRG041_TURBULENCE_H
#define NPRG041_TURBULENCE_H


#include <functional>
#include "../../../Shared/SmartConversion.h"
#include "../../Solver.h"
#include "../../../../Dependencies/Eigen/Eigen"
#include "../../../Shared/Settings.h"

class TurbulenceSolverSettings : public SolverSettings{
public:
    double voxel_size = 2.0;
    double amplitude = 1.0;
    std::vector<std::tuple<std::string,std::string>> get_contents() override;
    bool set_contents(const std::string & name, const std::string & value) override;
    SolverType get_type() override;
};

class TurbulenceSolver : public MidSolver{
    TurbulenceSolverSettings settings;
    std::hash<int> hash_function;
    Eigen::Vector<double,3> turbulence_value(const Eigen::Vector<double,3> &);
    Eigen::Vector<double,3> turbulence_mapping(const Eigen::Vector<int,3> &);
public:
    bool Solve(std::vector<Particle> &) override;
    TurbulenceSolver(SolverMetadata,TurbulenceSolverSettings);
};

#endif //NPRG041_TURBULENCE_H
