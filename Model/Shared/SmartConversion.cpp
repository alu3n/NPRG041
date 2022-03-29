//
// Created by Vojtěch Pröschl on 28.03.2022.
//

#include "SmartConversion.h"

//region From String
bool convert_size_t(const std::string & value, size_t & out){
    std::stringstream sstream(value);
    size_t temp;
    sstream >> temp;
    if(std::to_string(temp) == value){
        out = temp;
        return true;
    }
    return false;
}

//endregion
//Todo: Finish implementing other conversions
