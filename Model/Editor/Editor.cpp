//
// Created by Vojtěch Pröschl on 29.03.2022.
//

#include <iostream>
#include "Editor.h"

Editor::Editor() {
    active_menu = &main_menu;
    solver_menu = SolverMenu(&main_menu,&solvers);
    simulation_editor_menu = SimulationEditorMenu(&main_menu,&simulation_settings);
    main_menu.add_menu_item(&solver_menu);
    main_menu.add_menu_item(&simulation_editor_menu);
}

void Editor::Loop() {
    active_menu->display();
    std::string line;
    while(std::getline(std::cin,line)){
        this->Step(line);
    }
}

void Editor::Step(const std::string & input) {
    Menu * temp = active_menu->solve_request(input);
    if(temp != nullptr) active_menu = temp;
    active_menu->display();
}