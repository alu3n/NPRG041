//
// Created by Vojtěch Pröschl on 29.03.2022.
//

#ifndef NPRG041_PARTICLE_H
#define NPRG041_PARTICLE_H

#include "../../Dependencies/Eigen/Eigen"

enum class particle_type {
    //Todo: Incorporate this...
};

struct Particle{
    Eigen::Vector<double,3> position;
    Eigen::Vector<double,3> velocity;
    Eigen::Vector<double,3> color; //Color \in [0,1]^3
    double size;
    double density;
};

#endif //NPRG041_PARTICLE_H
