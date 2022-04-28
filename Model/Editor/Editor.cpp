//
// Created by Vojtěch Pröschl on 29.03.2022.
//

#include <iostream>
#include <filesystem>
#include "Editor.h"

Editor::Editor() {
    active_menu = &main_menu;
    solver_menu = SolverMenu(&main_menu,&solvers);
    simulation_editor_menu = SimulationEditorMenu(&main_menu,&simulation_settings);
    simulation_runner_menu = SimulationRunnerMenu(&simulation_settings,&solvers,&main_menu);
    main_menu.add_menu_item(&solver_menu);
    main_menu.add_menu_item(&simulation_editor_menu);
    main_menu.add_menu_item(&simulation_runner_menu);
    initialize_folders();
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

void Editor::initialize_folders() {
    std::filesystem::create_directory("Output");
    std::filesystem::create_directory("Output/Render");
    std::filesystem::create_directory("Output/Geometry");
    std::filesystem::create_directory("Output/Cache");
}