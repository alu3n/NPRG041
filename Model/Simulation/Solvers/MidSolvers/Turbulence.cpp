//
// Created by Vojtěch Pröschl on 01.04.2022.
//

#include "Turbulence.h"

constexpr int modulo_size = 7589; //Should be prime for good distribution


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


std::array<std::tuple<Eigen::Vector<double, 3>, double>, 8>
TurbulenceSolver::get_corners(const Eigen::Vector<double, 3> &point) {
    auto A = get_corner(point,0,0,0);
    auto B = get_corner(point,1,0,0);
    auto C = get_corner(point,0,1,0);
    auto D = get_corner(point,0,0,1);
    auto E = get_corner(point,1,1,0);
    auto F = get_corner(point,0,1,1);
    auto G = get_corner(point,1,0,1);
    auto H = get_corner(point,1,1,1);

    auto sum = get<1>(A) + get<1>(B) + get<1>(C) + get<1>(D) + get<1>(E) + get<1>(F) + get<1>(G) + get<1>(H);

    get<1>(A) /= sum;
    get<1>(B) /= sum;
    get<1>(C) /= sum;
    get<1>(D) /= sum;
    get<1>(E) /= sum;
    get<1>(F) /= sum;
    get<1>(G) /= sum;
    get<1>(H) /= sum;

    return {A,B,C,D,E,F,G,H};
}



Eigen::Vector<double, 3> TurbulenceSolver::compute_noise(Eigen::Vector<double, 3> position) {
    Eigen::Vector<double,3> temp{((double) (hash_function(position[0]) % modulo_size)+0.001)/modulo_size-0.5,
                                 ((double) (hash_function(position[1]) % modulo_size)+0.001)/modulo_size-0.5,
                                 ((double) (hash_function(position[2]) % modulo_size)+0.001)/modulo_size-0.5};

//    temp /= temp.norm();d
//    cout << temp << endl;

//    cout << ((double) (hash_function(position[0]) % modulo_size)+1)/modulo_size << endl;
return temp;

}

std::tuple<Eigen::Vector<double, 3>, double> TurbulenceSolver::get_corner(const Eigen::Vector<double, 3> position, bool x, bool y, bool z) {
    Eigen::Vector<double,3> temp;

    if(x){
        temp[0] = std::floor(position[0]/settings.voxel_size);
    }
    else{
        temp[0] = std::ceil(position[0]/settings.voxel_size);
    }

    if(y){
        temp[1] = std::floor(position[1]/settings.voxel_size);
    }
    else{
        temp[1] = std::ceil(position[1]/settings.voxel_size);
    }

    if(z){
        temp[2] = std::floor(position[2]/settings.voxel_size);
    }
    else{
        temp[2] = std::ceil(position[2]/settings.voxel_size);
    }

    double temp2 = (temp-position).norm();



    return {compute_noise(temp),temp2};
}




bool TurbulenceSolver::Solve(std::vector<Particle> & particles) {
    //Todo: Improve turbulence solver

    double time_multiplier = 1.0/(metadata.framerate*metadata.substeps);

    for(auto && particle : particles){
        auto corners = get_corners(particle.position);
        Eigen::Vector<double,3> noise_vector{0,0,0};
        for(int i = 0; i < 8; i++){
            noise_vector += (std::get<1>(corners[i])*std::get<1>(corners[i]))*std::get<0>(corners[i]);

        }
        particle.velocity += time_multiplier*settings.amplitude*noise_vector;
    }

    /* Process:
     * - Get corners with their distance (typles)
     * - Compute hash noise for each corner
     * - Interpolate the result
     */

    return false;
}


TurbulenceSolver::TurbulenceSolver(SolverMetadata metadata, TurbulenceSolverSettings settings) : MidSolver(metadata) {
    this->settings = settings;
}

