//
// Created by Vojtěch Pröschl on 29.03.2022.
//

#include "../Menu.h"

using namespace std;

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
    for(auto && parameter : settings->get_contents()){
        cout << "# - " << get<0>(parameter) << " = " << get<1>(parameter) << endl;
    }
    cout << "asdasdasda";
    //Todo: Finish implementation
}

SolverSettingsMenu::SolverSettingsMenu(Menu * parent,  SolverSettings * settings) {
    this->parent = parent;
    this->settings = settings;
}

