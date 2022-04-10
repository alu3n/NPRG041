//
// Created by Vojtěch Pröschl on 29.03.2022.
//

#include <map>
#include "../../Simulation/Solvers/PreSolvers/Source.h"
#include "../../Simulation/Solvers/MidSolvers/Gravity.h"
#include "../../Simulation/Solvers/MidSolvers/Turbulence.h"
#include "../../Simulation/Solvers/MidSolvers/Drag.h"
#include "../../Simulation/Solvers/MidSolvers/Vortex.h"
#include "../Menu.h"

using namespace std;

constexpr string_view back = "back";
constexpr string_view edit_solver = "edit solver";
constexpr string_view add_solver = "add solver";
constexpr string_view remove_solver = "remove solver";

void SolverMenu::build_menu() {
    contents = std::vector<std::unique_ptr<SolverSettingsMenu>>();
    for(auto && x : *solvers){
        contents.push_back(std::make_unique<SolverSettingsMenu>(this,x.get()));
    }
}

string SolverMenu::header() {
    return "Solver Menu";
}

Menu* SolverMenu::request_edit(const std::string & request) {
    stringstream sstream(request.substr(edit_solver.size()));
    int index;
    sstream >> index;
    cout << "INDEX: "<< index << endl;
    if(index > 0 && index <= solvers->size()){
        return contents[index-1].get();
    }
    return nullptr;
}

Menu* SolverMenu::request_add(const std::string & request) {
    if(request.length() == add_solver.length()) return nullptr;
    auto solver_name = request.substr(add_solver.size()+1);
    if(solver_name == "source"){
        solvers->emplace_back(std::make_unique<SourceSolverSettings>());
        this->build_menu();
    }
    else if(solver_name == "gravity"){
        solvers->emplace_back(std::make_unique<GravitySolverSettings>());
        this->build_menu();
    }
    else if(solver_name == "turbulence"){
        solvers->emplace_back(std::make_unique<TurbulenceSolverSettings>());
        this->build_menu();
    }
    else if(solver_name == "drag"){
        solvers->emplace_back(std::make_unique<DragSolverSettings>());
        this->build_menu();
    }
    else if(solver_name == "vortex"){
        solvers->emplace_back(std::make_unique<VortexSolverSettings>());
        this->build_menu();
    }
    return nullptr;
}

Menu* SolverMenu::request_remove(const std::string & request) {
    //Todo: Implement this
    return nullptr;
}

Menu* SolverMenu::solve_request(const std::string & request) {
    if(request.substr(0,back.size()) == back){
        return parent;
    }
    else if(request.substr(0,edit_solver.size()) == edit_solver){
        return this->request_edit(request);
    }
    else if(request.substr(0,add_solver.size()) == add_solver){
        return this->request_add(request);
    }
    else if(request.substr(0,remove_solver.size()) == remove_solver){
        return this->request_remove(request);
    }
    return nullptr;
}

void SolverMenu::display() {
    system("clear");
    cout << "# SOLVER MENU" << endl;
    cout << "## Active solvers:" << endl;

    int id = 1;
    for(auto && solver : *this->solvers){
        switch(solver->get_type()){
            case SolverType::Source:
                cout << "> (" << id << ") " << "Source" << endl;
                break;
            case SolverType::Gravity:
                cout << "> (" << id << ") " << "Gravity" << endl;
                break;
            case SolverType::Turbulence:
                cout << "> (" << id << ") " << "Turbulence" << endl;
                break;
            case SolverType::Drag:
                cout << "> (" << id << ") " << "Drag" << endl;
                break;
            case SolverType::Vortex:
                cout << "> (" << id << ") " << "Vortex" << endl;
                break;
        }
        id++;
    }

    cout << "## Available commands:" << endl;
    cout << "> back" << endl;
    cout << "> edit solver {solver index}" << endl;
    cout << "> add solver {solver name}" << endl;
    cout << "> remove solver {solver index}" << endl;

    cout << "## Available solvers:" << endl;
    cout << "> source" << endl;
    cout << "> gravity" << endl;
    cout << "> turbulence" << endl;
    cout << "> drag" << endl;
    cout << "> vortex" << endl;

}

SolverMenu::SolverMenu(Menu * parent, std::vector<std::unique_ptr<SolverSettings>> * solvers) {
    this->parent = parent;
    this->solvers = solvers;
    this->build_menu();
}

