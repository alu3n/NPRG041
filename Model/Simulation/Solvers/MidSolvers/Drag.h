//
// Created by Vojtěch Pröschl on 02.04.2022.
//

#ifndef NPRG041_DRAG_H
#define NPRG041_DRAG_H

#include "../../../Shared/SmartConversion.h"
#include "../../Solver.h"
#include "../../../../Dependencies/Eigen/Eigen"
#include "../../../Shared/Settings.h"

class DragSolverSettings : public SolverSettings{
public:
//    double fluid_density = 1;
    double fluid_density = 1;
    std::vector<std::tuple<std::string,std::string>> get_contents() override;
    bool set_contents(const std::string & name, const std::string & value) override;
    SolverType get_type() override;
};

class DragSolver : public MidSolver{
    DragSolverSettings settings;
public:
    bool Solve(std::vector<Particle> &) override;
    DragSolver(SolverMetadata,DragSolverSettings);
};

#endif //NPRG041_DRAG_H
