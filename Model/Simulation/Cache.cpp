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

Cache::Cache(std::string location) {
    this->location = location;
    this->frame_count = 0;
}

bool Cache::cache_frame(int frame_number, const std::vector<Particle> & particles) {
    string cache_location = location + "/" +string(file_name) + to_string(frame_number) + "." + string(file_suffix);

    ofstream file(cache_location);

    if(!file.is_open()) {
        cout << "Caching failed!" << endl;
        return false;
    }

    for(auto && p : particles){
        file << this->particle_serialize(p);
    }

    //Todo: Create folder if it isnt there

    frame_count++;
    file.close();
    return true;
}

bool Cache::load_frame(int frame_number, std::vector<Particle> & particles) const {
    string cache_location = location + "/" +string(file_name) + to_string(frame_number) + "." + string(file_suffix);
    ifstream file(cache_location);

    if(!file.is_open()){
        return false;
    }

    particles = vector<Particle>();

    string line;

    while(getline(file,line)){
        Particle temp = this->particle_deserialize(line);
        particles.push_back(temp);
    }

    return true;
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

Particle Cache::particle_deserialize(const std::string & str) const {
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
