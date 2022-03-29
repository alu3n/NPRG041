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
        if(sstream.rdbuf()->in_avail() > 0){
            sstream >> temp[i];
        }
        else{
            temp[i] = 0;
        }
    }

    return temp;
}

//endregion

//Todo: Create partial specialization for size_t to avoid errors
//Todo: Implement those conversions




#endif //NPRG041_SMARTCONVERSION_H
