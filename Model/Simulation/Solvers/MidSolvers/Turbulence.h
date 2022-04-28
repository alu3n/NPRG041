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
    double amplitude = 10;
    int noise_count = 3; //Noise -> Turbulent noice (summing noise values together)
    std::vector<std::tuple<std::string,std::string>> get_contents() override;
    bool set_contents(const std::string & name, const std::string & value) override;
    SolverType get_type() override;
};

class TurbulenceSolver : public MidSolver{
    TurbulenceSolverSettings settings;
    std::hash<double> hash_function;
    Eigen::Vector<double,3> get_noise(const Eigen::Vector<double,3> & position, double voxel_size);

    Eigen::Vector<double,3> get_noise_anchor(const Eigen::Vector<double,3> & position);
    Eigen::Vector<double,3> interpolate_value_matrix(const Eigen::Vector<double,3> & position, double voxel_size);
    long hash_position(double seed, const Eigen::Vector<double, 3> & position);
public:
    bool Solve(std::vector<Particle> &) override;
    TurbulenceSolver(SolverMetadata,TurbulenceSolverSettings);
};

#endif //NPRG041_TURBULENCE_H
