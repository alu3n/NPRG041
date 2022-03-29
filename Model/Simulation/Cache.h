//
// Created by Vojtěch Pröschl on 29.03.2022.
//

#ifndef NPRG041_CACHE_H
#define NPRG041_CACHE_H

#include <vector>
#include "Particle.h"

class Cache{
private:
    int frame_count;
    std::string location;
public:
    bool cache_frame(int, const std::vector<Particle> &);
    bool load_frame(int, std::vector<Particle> &);

    //Todo: vec_to_cache, cache_to_vec
};

#endif //NPRG041_CACHE_H
