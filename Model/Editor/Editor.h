//
// Created by Vojtěch Pröschl on 28.03.2022.
//

#ifndef NPRG041_EDITOR_H
#define NPRG041_EDITOR_H

#include <memory>
#include "Menu.h"

class Editor{
//region Data
    std::vector<std::unique_ptr<SolverSettingsMenu>> solvers; //Solvers that will be translated into the simulation
    SimulationSettings simulation_settings;
    PlaybackSettings playback_settings;
    ExportSettings exportSettings;

//endregion

//region Main Menu
    MainMenu main_menu;
//endregion

//region Simulation Editor
    //Todo: Implement
//endregion

//region Simulation Runner Menu
    //Todo: Implement
//endregion

//region Simulation View Menu
    //Todo: Implement
//endregion

//region Simulation Export
    //Todo: Implement
//endregion

//region Simulation Import and Export
    //Todo: Implement
//endregion

};

#endif //NPRG041_EDITOR_H
