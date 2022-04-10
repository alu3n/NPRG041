//
// Created by Vojtěch Pröschl on 29.03.2022.
//

#include "../Menu.h"

using namespace std;

Menu *MainMenu::solve_request(const std::string & request) {
    int index = convert_to_type<int>(request);
    if(index > 0 && contents.size() >= index){
        return contents[index-1];
    }
    else{
        return nullptr;
    }
}

void MainMenu::display() {
    int i = 1;
    system("clear");
    cout << "# MAIN MENU" << endl;
    cout << "## OPTIONS:" << endl;
    for(auto && x : contents){
        cout << "> " << "(" << i << ") " << x->header() << endl;
        i++;
    }
}

void MainMenu::add_menu_item(Menu * item) {
    contents.push_back(item);
}

string MainMenu::header() {
    return "Main Menu";
}