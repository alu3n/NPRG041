//
// Created by Vojtěch Pröschl on 29.03.2022.
//

#include "../../../Shared/SmartConversion.h"
#include "Source.h"

using namespace std;

constexpr string_view _count = "Count";
constexpr string_view _position = "Position";
constexpr string_view _velocity_range_x = "Velocity Range X";
constexpr string_view _velocity_range_y = "Velocity Range Y";
constexpr string_view _velocity_range_z = "Velocity Range Z";
constexpr string_view _size_range = "Size Range";
constexpr string_view _density_range = "Density Range";

using string_t = tuple<string,string>;

bool SourceSolver::Solve(std::vector<Particle> & particles) {
    double time_window = (1.0)/(metadata.substeps*metadata.framerate);
    int source_count = std::floor(settings.count*time_window);
    double leftover_probability = settings.count*time_window - source_count;

    std::uniform_real_distribution basic_distribution(0,1);

    for(int i = 0; i < source_count; i++){
        source_particle(particles);
    }

    if(leftover_probability < basic_distribution(generator)){
        source_particle(particles);
    }

}

SourceSolver::SourceSolver(SolverMetadata metadata, SourceSolverSettings settings) : PreSolver(metadata) {
    this->settings = settings;
}

void SourceSolver::source_particle(std::vector<Particle> & particles) {

    std::uniform_real_distribution x_distribution(settings.velocity_x_range[0],settings.velocity_x_range[1]);
    std::uniform_real_distribution y_distribution(settings.velocity_y_range[0],settings.velocity_y_range[1]);
    std::uniform_real_distribution z_distribution(settings.velocity_z_range[0],settings.velocity_z_range[1]);

    Particle temp;
    temp.position = settings.position;
    temp.velocity = {x_distribution(generator),y_distribution(generator),z_distribution(generator)};

    particles.push_back(temp);
}

SolverType SourceSolverSettings::get_type() {
    return SolverType::Source;
}

vector<tuple<string,string>> SourceSolverSettings::get_contents() {
    vector<tuple<string,string>> temp;
    temp.emplace_back(string_t(_count,to_string(count)));
    temp.emplace_back(string_t(_position, smart_to_string<double,3>(position)));
    temp.emplace_back(string_t(_velocity_range_x, smart_to_string<double,2>(velocity_x_range)));
    temp.emplace_back(string_t(_velocity_range_y, smart_to_string<double,2>(velocity_y_range)));
    temp.emplace_back(string_t(_velocity_range_z, smart_to_string<double,2>(velocity_z_range)));
    temp.emplace_back(string_t(_size_range, smart_to_string<double,2>(size_range)));
    temp.emplace_back(string_t(_density_range, smart_to_string<double,2>(density_range)));
    return temp;
}

bool SourceSolverSettings::set_contents(const std::string &name, const std::string &value) {
    if(name == _count){
        stringstream sstream(value);
        sstream >> count;
    }
    else if(name == _position){
        position = convert_to_vector<double,3>(value);
    }
    else if(name == _velocity_range_x){
        velocity_x_range = convert_to_vector<double,2>(value);
    }
    else if(name == _velocity_range_y){
        velocity_y_range = convert_to_vector<double,2>(value);
    }
    else if(name == _velocity_range_z){
        velocity_z_range = convert_to_vector<double,2>(value);
    }
    else if(name == _density_range){
        density_range = convert_to_vector<double,2>(value);
    }
    else if(name == _size_range){
        size_range = convert_to_vector<double,2>(value);
    }
    return true;
}