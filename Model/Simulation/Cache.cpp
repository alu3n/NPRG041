//
// Created by Vojtěch Pröschl on 30.03.2022.
//

#include <istream>
#include <fstream>
#include <iostream>
#include "Cache.h"

using namespace std;

//Todo: Possible improvement... create smarter cache format

/* Particle format
 * {pos_x};{pos_y};{pos_z};{vel_x};{vel_y};{vel_z};{col_r};{col_g};{col_b};{size};{density}\n
 */

bool Cache::cache_frame(int frame_number, const std::vector<Particle> & particles) {
    ofstream file(location + string(file_name) + to_string(frame_number) + "." + string(file_suffix));

    if(!file.is_open()) {
        return false;
    }

    for(auto && p : particles){
        file << this->particle_serialize(p);
    }

    file.close();
    return true;
}

bool Cache::load_frame(int frame_number, std::vector<Particle> & particles) {
    ifstream file(location + string(file_name) + to_string(frame_number) + "." + string(file_suffix));

    if(!file.is_open()){
        return false;
    }

    particles = vector<Particle>();

    string line;

    while(getline(file,line)){

    }

    //Todo: Check correctness of this method

}

std::string Cache::particle_serialize(const Particle & particle) {
    return to_string(particle.position[0]) + ";" +
        to_string(particle.position[1]) + ";" +
        to_string(particle.position[2]) + ";" +
        to_string(particle.velocity[0]) + ";" +
        to_string(particle.velocity[1]) + ";" +
        to_string(particle.velocity[2]) + ";" +
        to_string(particle.color[0]) + ";" +
        to_string(particle.color[1]) + ";" +
        to_string(particle.color[2]) + ";" +
        to_string(particle.size) + ";" +
        to_string(particle.density) + ";" +
        "\n";
}

Particle Cache::particle_deserialize(const std::string & str) {
    Particle temp;

    stringstream sstream(str);

    sstream >> temp.position[0];
    sstream.get();
    sstream >> temp.position[1];
    sstream.get();
    sstream >> temp.position[2];
    sstream.get();

    sstream >> temp.velocity[0];
    sstream.get();
    sstream >> temp.velocity[1];
    sstream.get();
    sstream >> temp.velocity[2];
    sstream.get();

    sstream >> temp.color[0];
    sstream.get();
    sstream >> temp.color[1];
    sstream.get();
    sstream >> temp.color[2];
    sstream.get();

    sstream >> temp.size;
    sstream.get();

    sstream >> temp.density;
    sstream.get();

    return temp;
}
