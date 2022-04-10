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
    else if(request.substr(0,3) == "set"){
        stringstream sstream(request.substr(3));
        int index;
        string value;
        sstream >> index;
        getline(sstream,value);
        if(index > 0 && index <= settings->get_contents().size()){
            settings->set_contents(get<0>(settings->get_contents()[index-1]),value);
        }
    }
    return nullptr;
}

void SolverSettingsMenu::display() {
    system("clear");

    cout << "# SOURCE SETTINGS MENU" << endl;
    cout << "## Source Settings:" << endl;
    int index = 1;
    for(auto && parameter : settings->get_contents()){
        cout << "> (" << index << ") "<< get<0>(parameter) << " = " << get<1>(parameter) << endl;
        index ++;
    }
    cout << "## Available commands:" << endl;
    cout << "> set {parameter id} {value}" << endl;
    cout << "> back" << endl;

}

SolverSettingsMenu::SolverSettingsMenu(Menu * parent,  SolverSettings * settings) {
    this->parent = parent;
    this->settings = settings;
}

