//
// Created by Vojtěch Pröschl on 28.03.2022.
//

#include <iostream>
#include "Menu.h"
#include "../Shared/SmartConversion.h"

using namespace std;

//region Main Menu Implementation
Menu *MainMenu::solve_request(const std::string & request) {
    int index = convert_to_type<int>(request);
//    cout << index;
    if(index > 0 && contents.size() <= index){
//        cout <<"salazar";
        return contents[index-1];
    }
    else{
        return nullptr;
    }

}

void MainMenu::display() {
    int i = 1;
    cout << "# MAIN MENU" << endl;
    cout << "# OPTIONS:" << endl;
    for(auto && x : contents){
        cout << "# - " << x->header() << " (" << i << ")" <<endl;
        i++;
    }
}

void MainMenu::add_menu_item(Menu * item) {
    contents.push_back(item);
}

string MainMenu::header() {
    return "Main Menu";
}

//endregion

//region Solver Settings Menu Implementation
string SolverSettingsMenu::header() {
    return "Solver Settings Menu";
}

Menu *SolverSettingsMenu::solve_request(const std::string & request) {
    if(request == "back"){
        return parent;
    }
    return nullptr;
    //Todo: Finish implementation
}

void SolverSettingsMenu::display() {
    //Todo: Finish implementation
}

SolverSettingsMenu::SolverSettingsMenu(Menu * parent,  SolverSettings * settings) {
    this->parent = parent;
    this->settings = settings;
}


//endregion

//region Solver Menu Implementation

//Private
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

//Public
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

//endregion

//region SimulationEditorMenu
std::string SimulationEditorMenu::header() {
    return "Simulation Editor Menu";
}

Menu* SimulationEditorMenu::solve_request(const std::string & request) {
    if(request == "back"){
        return parent;
    }
    return nullptr;
    //Todo: Finish implementation
}

SimulationEditorMenu::SimulationEditorMenu(Menu * parent, SimulationSettings * settings) {
    this->parent = parent;
    this->settings = settings;
}

void SimulationEditorMenu::display() {
    cout << "# SIMULATION EDITOR MENU" << endl;
    //Todo: Finish implementation
}

//endregion