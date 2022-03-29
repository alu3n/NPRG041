//
// Created by Vojtěch Pröschl on 29.03.2022.
//

#include "../Menu.h"

using namespace std;

void SolverMenu::add_solver() {

}

void SolverMenu::remove_solver() {

}

void SolverMenu::build_menu() {
    contents = std::vector<std::unique_ptr<SolverSettingsMenu>>();
    for(auto && x : *solvers){
        contents.push_back(std::make_unique<SolverSettingsMenu>(this,x.get()));
    }
}

string SolverMenu::header() {
    return "Solver Menu";
}

Menu* SolverMenu::solve_request(const std::string & request) {
    if(request == "back"){
        return parent;
    }
    return nullptr;
    //Todo: Finish implementation
}

void SolverMenu::display() {
    cout << "# SOLVER MENU" << endl;
    cout << "# Active solvers:" << endl;
    cout << "# ... TEMPORARY ..." << endl;
    cout << "# Aviable commands:" << endl;
    cout << "# - back" << endl;
    cout << "# - edit solver" << endl;
    cout << "# - add solver {solver name}" << endl;
    cout << "# - remove solver {solver index}" << endl;
    //Todo: Finish implementation
}

SolverMenu::SolverMenu(Menu * parent, std::vector<std::unique_ptr<SolverSettings>> * solvers) {
    this->parent = parent;
    this->solvers = solvers;
    this->build_menu();
}

