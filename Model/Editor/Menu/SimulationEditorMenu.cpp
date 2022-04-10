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
    if(request.substr(0,3) == "set"){
        stringstream sstream(request.substr(3));
        int index;
        string val;
        sstream >> index;
        sstream >> val;
        if(index > 0 && index <= 4){
            settings->set_contents(to_string(index),val);
        }
    }

    return nullptr;

}

SimulationEditorMenu::SimulationEditorMenu(Menu * parent, SimulationSettings * settings) {
    this->parent = parent;
    this->settings = settings;
}

void SimulationEditorMenu::display() {
    auto data = settings->get_contents();

    system("clear");
    cout << "# SIMULATION EDITOR MENU" << endl;
    cout << "## Settings:" << endl;
    int i = 1;
    for(auto && x : data){
        cout << "> ("<< i << ") " << get<0>(x) << ": " << get<1>(x) << endl;
        i++;
    }
    cout << "## Available commands:" << endl;
    cout << "> back" << endl;
    cout << "> set {attribute id} {value}" << endl;
    cout << endl;

    //Todo: Finish implementation
}

//Todo: Finish requests and change the text output to match solver editor menu
