//
// Created by Vojtěch Pröschl on 28.03.2022.
//

#ifndef NPRG041_EDITOR_H
#define NPRG041_EDITOR_H

#include <memory>
#include "Menu.h"
#include "../Simulation/Simulation.h"

class Editor{
public:
    Editor();
    void Loop();
    void Step(const std::string &);
private:
    bool cached = false;
    Menu* active_menu;

    std::vector<std::unique_ptr<SolverSettings>> solvers; //Solvers that will be translated into the simulation
    SimulationSettings simulation_settings;
    PlaybackSettings playback_settings;
    RenderSettings export_settings;

    MainMenu main_menu;

    SolverMenu solver_menu;
    SimulationEditorMenu simulation_editor_menu;
    SimulationRunnerMenu simulation_runner_menu;

    void initialize_folders();
};

#endif //NPRG041_EDITOR_H
