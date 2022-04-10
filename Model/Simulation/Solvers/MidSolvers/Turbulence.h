//
// Created by Vojtěch Pröschl on 01.04.2022.
//

#ifndef NPRG041_TURBULENCE_H
#define NPRG041_TURBULENCE_H


#include <functional>
#include <array>
#include "../../../Shared/SmartConversion.h"
#include "../../Solver.h"
#include "../../../../Dependencies/Eigen/Eigen"
#include "../../../Shared/Settings.h"

class TurbulenceSolverSettings : public SolverSettings{
public:
    double voxel_size = 1.0; //Todo: Make voxel size 0 impossible
    double amplitude = 50.0;
    std::vector<std::tuple<std::string,std::string>> get_contents() override;
    bool set_contents(const std::string & name, const std::string & value) override;
    SolverType get_type() override;
};

class TurbulenceSolver : public MidSolver{
    TurbulenceSolverSettings settings;
    std::array<std::tuple<Eigen::Vector<double,3>,double>,8> get_corners(const Eigen::Vector<double,3> & point);
    Eigen::Vector<double,3> compute_noise(Eigen::Vector<double,3> position);
    std::tuple<Eigen::Vector<double, 3>, double> get_corner(const Eigen::Vector<double,3> position, bool x, bool y, bool z);
    std::hash<double> hash_function;
public:
    bool Solve(std::vector<Particle> &) override;
    TurbulenceSolver(SolverMetadata,TurbulenceSolverSettings);
};

#endif //NPRG041_TURBULENCE_H
