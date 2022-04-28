//
// Created by Vojtěch Pröschl on 01.04.2022.
//

#include "Turbulence.h"

constexpr int modulo_size_x = 7589; //Should be prime for good distribution
constexpr int modulo_size_y = 1879;
constexpr int modulo_size_z = 997;


using namespace std;
using string_t = tuple<string,string>;

constexpr string_view _amplitude = "Amplitude";
constexpr string_view _voxel_size = "Voxel Size";



SolverType TurbulenceSolverSettings::get_type() {
    return SolverType::Turbulence;
}

bool TurbulenceSolverSettings::set_contents(const std::string &name, const std::string &value) {
    if(name == _amplitude){
        amplitude = convert_to_type<double>(value);
        return true;
    }
    else if(name == _voxel_size){
        voxel_size = convert_to_type<double>(value);
        return true;
    }
    return false;
}

std::vector<std::tuple<std::string, std::string>> TurbulenceSolverSettings::get_contents() {
    vector<string_t> temp;
    temp.emplace_back(string_t(_amplitude,to_string(amplitude)));
    temp.emplace_back(string_t(_voxel_size,to_string(voxel_size)));
    return temp;
}

bool TurbulenceSolver::Solve(std::vector<Particle> & particles) {
    double time_multiplier = 1.0/(metadata.framerate*metadata.substeps);

    for(auto && particle : particles){
        Eigen::Vector<double,3> noise_val{0,0,0};
        for(int i = 1; i <= this->settings.noise_count; ++i){
            noise_val += (1.0/i)* interpolate_value_matrix(particle.position,this->settings.voxel_size);
        }
        particle.velocity += settings.amplitude*time_multiplier*noise_val;
    }

    return true;
}



constexpr double seed_x = -123.1293;
constexpr double seed_y = 31.230;
constexpr double seed_z = 109.3001;

Eigen::Vector<double, 3> TurbulenceSolver::get_noise_anchor(const Eigen::Vector<double, 3> &position) {
    return {
            ((double)((hash_function(position[0])+hash_function(position[0] - position[1] - position[2] + seed_x))%modulo_size_x))/modulo_size_x-0.5,
            ((double)((hash_function(position[1])+hash_function(position[0] - position[1] - position[2] + seed_y))%modulo_size_y))/modulo_size_y-0.5,
            ((double)((hash_function(position[2])+hash_function(position[0] - position[1] - position[2] + seed_z))%modulo_size_z))/modulo_size_z-0.5
    };
}

long TurbulenceSolver::hash_position(double seed, const Eigen::Vector<double, 3> &position) {
    return hash_function(position[0] + position[1] + position[2] + seed);
}

Eigen::Vector<double, 3>
TurbulenceSolver::interpolate_value_matrix(const Eigen::Vector<double, 3> &position, double voxel_size) {
    Eigen::Vector<double,3> starting_point = {(floor(position[0]/voxel_size)-1)*voxel_size,
                                              (floor(position[1]/voxel_size)-1)*voxel_size,
                                              (floor(position[2]/voxel_size)-1)*voxel_size};
    array<array<array<double,4>,4>,4> distances;
    array<array<array<Eigen::Vector<double,3>,4>,4>,4> values;

    double distance_sum = 0;
    for(int x = 0; x < 4; ++x){
        for(int y = 0; y < 4; ++y){
            for(int z = 0; z < 4; ++z){
                Eigen::Vector<double, 3> pos = {(starting_point[0])+x*voxel_size,
                                                (starting_point[1])+y*voxel_size,
                                                (starting_point[2])+z*voxel_size};
                values[x][y][z] = get_noise_anchor(pos);
                distances[x][y][z] = (pos-position).norm();
                distance_sum += distances[x][y][z];
            }
        }
    }
    Eigen::Vector<double,3> velocity{0,0,0};
    for(int x = 0; x < 4; x++){
        for(int y = 0; y < 4; y++){
            for(int z = 0; z < 4; z++){
                velocity += ((1-distances[x][y][z]/distance_sum)*(1-distances[x][y][z]/distance_sum))*values[x][y][z];//Todo: this is wrong - just for debug
            }
        }
    }
    return velocity;
}




TurbulenceSolver::TurbulenceSolver(SolverMetadata metadata, TurbulenceSolverSettings settings) : MidSolver(metadata) {
    this->settings = settings;
}

