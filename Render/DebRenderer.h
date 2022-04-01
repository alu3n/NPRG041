//
// Created by Vojtěch Pröschl on 31.03.2022.
//

#ifndef NPRG041_DEBRENDERER_H
#define NPRG041_DEBRENDERER_H

#include "../Model/Simulation/Cache.h"

class DebRenderer{
    int resolution_x;
    int resolution_y;
    double scale;
    std::string location;
public:
    DebRenderer(int,int,double,std::string);
    void RenderCache(const Cache &);
};



#endif //NPRG041_DEBRENDERER_H
