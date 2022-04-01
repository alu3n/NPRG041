//
// Created by Vojtěch Pröschl on 01.04.2022.
//

#include "Turbulence.h"


using namespace std;
using string_t = tuple<string,string>;

constexpr string_view _amplitude = "Amplitude";
constexpr string_view _voxel_size = "Voxel Size";

constexpr size_t hash_range = 1000;


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

Eigen::Vector<double,3> TurbulenceSolver::turbulence_mapping(const Eigen::Vector<int, 3> & position) {

}

Eigen::Vector<double,3> TurbulenceSolver::turbulence_value(const Eigen::Vector<double, 3> & position) {
    /*      A.......B
     *     .       .
     *    C.......D.
     *    . E.......F
     *    ..       .
     *    G.......H
     */
    Eigen::Vector<int,3> A = {floor(position[0]),ceil(position[1]),floor(position[2])};
    Eigen::Vector<int,3> B = {ceil(position[0]),ceil(position[1]),floor(position[2])};
    Eigen::Vector<int,3> C = {floor(position[0]),ceil(position[1]),ceil(position[2])};
    Eigen::Vector<int,3> D = {ceil(position[0]),ceil(position[1]),ceil(position[2])};
    Eigen::Vector<int,3> E = {floor(position[0]),floor(position[1]),floor(position[2])};
    Eigen::Vector<int,3> F = {ceil(position[0]),floor(position[1]),floor(position[2])};
    Eigen::Vector<int,3> G = {floor(position[0]),floor(position[1]),ceil(position[2])};
    Eigen::Vector<int,3> H = {ceil(position[0]),floor(position[1]),ceil(position[2])};

    //Todo: Implement better interpolation;


}

bool TurbulenceSolver::Solve(std::vector<Particle> & particles) {
    for(auto && particle : particles){
        particle.velocity = this->turbulence_value(particle.position); //Todo: Change, this is temporary solution
    }
    return false;
}


TurbulenceSolver::TurbulenceSolver(SolverMetadata metadata, TurbulenceSolverSettings settings) : MidSolver(metadata) {
    this->settings = settings;
}

