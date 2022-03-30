//
// Created by Vojtěch Pröschl on 29.03.2022.
//

#include "Source.h"

using namespace std;

bool SourceSolver::Solve(std::vector<Particle> & particles) {
    //Todo: Improve speed of this solver - this solution is slow -> Make better stochastic sourcing
    double source_probability = settings.count/((double)metadata.substeps*metadata.framerate);
    for(int i = 0; i < settings.count; i++){
        if((static_cast <float> (rand()) / static_cast <float> (RAND_MAX))<source_probability){
            this->source_particle(particles);
        }
    }
    return true;
}

SourceSolver::SourceSolver(SolverMetadata metadata, SourceSolverSettings settings) : PreSolver(metadata) {
    this->settings = settings;
    rand();
}

void SourceSolver::source_particle(std::vector<Particle> & particles) {
    //Todo: Implement this method
}

SolverType SourceSolverSettings::get_type() {
    return SolverType::Source;
}

vector<tuple<string,string>> SourceSolverSettings::get_contents() {
    vector<tuple<string,string>> temp;
    return temp;
    //Todo: Implement this method
}

bool SourceSolverSettings::set_contents(const std::string &name, const std::string &value) {
    //Todo: Implement this method
    return false;
}