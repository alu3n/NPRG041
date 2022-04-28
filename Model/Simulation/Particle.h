//
// Created by Vojtěch Pröschl on 29.03.2022.
//

#ifndef NPRG041_PARTICLE_H
#define NPRG041_PARTICLE_H

#include "../../Dependencies/Eigen/Eigen"

struct Particle{
    Eigen::Vector<double,3> position;
    Eigen::Vector<double,3> velocity;
    Eigen::Vector<double,3> color;
    double size = 0.1;
    double density = 0;
    double age = 0.5;
    double life = 1;
    void print();
};

#endif //NPRG041_PARTICLE_H
