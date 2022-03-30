//
// Created by Vojtěch Pröschl on 29.03.2022.
//

#ifndef NPRG041_CACHE_H
#define NPRG041_CACHE_H

#include <vector>
#include "Particle.h"

constexpr std::string_view file_name = "cache";
constexpr std::string_view file_suffix = "txt";

class Cache{
private:
    int frame_count;
    std::string location;
    std::string particle_serialize(const Particle &);
    Particle particle_deserialize(const std::string &);
public:
    bool cache_frame(int, const std::vector<Particle> &);
    bool load_frame(int, std::vector<Particle> &);
};

#endif //NPRG041_CACHE_H
