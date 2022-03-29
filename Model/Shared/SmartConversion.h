//
// Created by Vojtěch Pröschl on 28.03.2022.
//

#ifndef NPRG041_SMARTCONVERSION_H
#define NPRG041_SMARTCONVERSION_H

#include <string>
#include <iostream>
#include "../../Dependencies/Eigen/Core"

//region To String
template<typename T, size_t size>
std::string smart_to_string(const Eigen::Vector<T,size> & vec){
    std::string tmp = "(";
    bool first = true;
    for(auto && x : vec){
        if(!first){
            tmp += ",";
        }
        else{
            first = false;
        }
        tmp += std::to_string(x);
    }
    tmp += ")";
    return tmp;
}

//endregion

//region From String
bool convert_size_t(const std::string &, size_t &);
bool convert_double(const std::string &, double &);


//Difference between those functions and their library variant is that they only accept exact conversion! This is crucial to avoid bugs.
template<typename T>
T convert_to_type(const std::string & str){
    T temp;

    std::stringstream sstream(str);
    sstream >> temp;

    return temp;
}

template<typename T, size_t size>
Eigen::Vector<T,size> convert_to_vector(const std::string & str){
    Eigen::Vector<T,size> temp;

    std::stringstream sstream(str);
    for(size_t i = 0; i < size; i++){
        sstream >> temp[i];
        sstream.seekp(1);
    }
}

//endregion


//Todo: Implement those conversions




#endif //NPRG041_SMARTCONVERSION_H
