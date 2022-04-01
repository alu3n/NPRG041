//
// Created by Vojtěch Pröschl on 29.03.2022.
//

#include "../Menu.h"

using namespace std;

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
    auto data = settings->get_contents();

    cout << endl;
    cout << "# SIMULATION EDITOR MENU" << endl;
    cout << "# Settings:" << endl;
    for(auto && x : data){
        cout << "# - " << get<0>(x) << ": " << get<1>(x) << endl;
    }
    cout << "# Aviable commands:" << endl;
    cout << "# - back" << endl;
    cout << "# - set {attribute name} {value}" << endl;
    cout << endl;

    //Todo: Finish implementation
}

//Todo: Finish requests and change the text output to match solver editor menu
