//
// Created by Vojtěch Pröschl on 29.03.2022.
//

#include <sstream>
#include "../Menu.h"
#include "../../../Render/DebRenderer.h"

constexpr int min_res_x = 50;
constexpr int min_res_y = 50;
constexpr double min_scale = 0.001;

using namespace std;

string SimulationRunnerMenu::header() {
    return "Simulation Runner Menu";
}

Menu* SimulationRunnerMenu::solve_request(const std::string & request) {
    string dbg_rndr = "debug render";
    if(request == "back"){
        return parent;
    }
    else if(request == "run"){
        std::vector<SolverSettings *> solver_settings;
        for(auto && x : *solvers){
            solver_settings.push_back(x.get());
        }
        Simulation sim(*this->simulation_settings,solver_settings);
        cached = true;
        cache = sim.Simulate();

        cout << "SIMULATION COMPLETE" << endl;
    }
    else if(request.substr(0,dbg_rndr.size()) == dbg_rndr){
        if(cached){
            stringstream  sstream(request.substr(dbg_rndr.size()));
            if(request.substr(dbg_rndr.size()).size()==0) return nullptr;
            int res_x, res_y;
            double scale;
            sstream >> res_x;
            sstream >> res_y;
            sstream >> scale;
            if(scale < min_scale){
                scale = min_scale;
            }
            if(res_x < min_res_x){
                res_x = min_res_x;
            }
            if(res_y < min_res_y){
                res_y = min_res_y;
            }
            DebRenderer renderer(res_x,res_y,scale,simulation_settings->CacheFolder);
            renderer.RenderCache(this->cache);
        }
    }
    return nullptr;
}

void SimulationRunnerMenu::display() {
    system("clear");

    cout << "# SIMULATION RUNNER MENU" << endl;
    cout << "## Available commands" << endl;
    cout << "> back" << endl;
    cout << "> run" << endl;
    cout << "> debug render {res_x} {res_y} {scale}" << endl;
}

SimulationRunnerMenu::SimulationRunnerMenu(SimulationSettings * settings, std::vector<std::unique_ptr<SolverSettings>> * solvers, Menu * parent) {
    this->simulation_settings = settings;
    this->solvers = solvers;
    this->parent = parent;
}

