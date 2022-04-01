//
// Created by Vojtěch Pröschl on 29.03.2022.
//

#ifndef NPRG041_SOLVER_H
#define NPRG041_SOLVER_H

#include <vector>
#include "Particle.h"

enum class SolverType{
    Source,
    Gravity,
    Turbulence
};

struct SolverMetadata{
    int substeps;
    int framerate;
    double step_duration;
    SolverMetadata(int,int);
};

class Solver{
public:
    explicit Solver(SolverMetadata metadata) : metadata{metadata}{};
protected:
    SolverMetadata metadata;
};

class PreSolver : public Solver{

public:
    explicit PreSolver(SolverMetadata metadata) : Solver(metadata){};
    virtual bool Solve(std::vector<Particle> &) = 0;
};

class MidSolver : public Solver{

public:
    explicit MidSolver(SolverMetadata metadata) : Solver(metadata){};
    virtual bool Solve(std::vector<Particle> &) = 0;
};

class PostSolver : public Solver{

public:
    explicit PostSolver(SolverMetadata metadata) : Solver(metadata){};
    virtual bool Solve(std::vector<Particle> &) = 0;
};



#endif //NPRG041_SOLVER_H
