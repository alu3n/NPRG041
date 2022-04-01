//
// Created by Vojtěch Pröschl on 29.03.2022.
//

#include "../Menu.h"

//Todo: Finish implementation

using namespace std;

string SimulationRunnerMenu::header() {
    return "Simulation Runner Menu";
}

Menu* SimulationRunnerMenu::solve_request(const std::string & request) {
    if(request == "back"){
        return parent;
    }
    else if(request == "run"){
//        SimulationSettings s = *this->simulation_settings;
        std::vector<SolverSettings *> solver_settings;
        for(auto && x : *solvers){
            solver_settings.push_back(x.get());
        }
        Simulation sim(*this->simulation_settings,solver_settings);
        sim.Simulate();
        cout << "SIMULATION COMPLETE" << endl;
    }
    return nullptr;
}

void SimulationRunnerMenu::display() {
    cout << "# SIMULATION RUNNER MENU" << endl;
    cout << "## Aviable commands" << endl;
    cout << "> back" << endl;
    cout << "> run" << endl;
}

SimulationRunnerMenu::SimulationRunnerMenu(SimulationSettings * settings, std::vector<std::unique_ptr<SolverSettings>> * solvers, Menu * parent) {
    this->simulation_settings = settings;
    this->solvers = solvers;
    this->parent = parent;
}

