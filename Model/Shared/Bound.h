//
// Created by Vojtěch Pröschl on 29.03.2022.
//

#ifndef NPRG041_BOUND_H
#define NPRG041_BOUND_H

#include "../../Dependencies/Eigen/Core"

template<typename T>
T bound(const T & val, const T & min, const T & max){
    auto temp = val;
    if(temp < min){
        temp = min;
    }
    if(temp > max){
        temp = max;
    }
    return temp;
}

template<typename T, size_t size>
Eigen::Vector<T,size> bound_vector(const Eigen::Vector<T,size> & val, const T & min, const T & max){
    Eigen::Vector<T,size> temp = val;
    for(size_t i = 0; i < size; i++){
        temp[i] = bound(temp[i],min,max);
    }
    return temp;
//    return Eigen::Vector<T,size>();
}

#endif //NPRG041_BOUND_H
