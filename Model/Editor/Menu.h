//
// Created by Vojtěch Pröschl on 28.03.2022.
//

#ifndef NPRG041_MENU_H
#define NPRG041_MENU_H

#include <vector>
#include "../Shared/Settings.h"

/* Menu should be able to solve request,
 *
 */

class Menu{
protected:
    Menu * parent = nullptr;
public:
    virtual Menu* solve_request(const std::string &) = 0; //Return null pointer if there was no change
    virtual void display() = 0;
};

class MainMenu : public Menu{
    std::vector<Menu *> contents;
public:
    Menu* solve_request(const std::string &) override;
    void display();
};

class SolverSettingsMenu : public Menu{
    std::vector<Settings *> contents;
public:
    Menu* solve_request(const std::string &) override;
    void display();
};

class SimulationEditorMenu : public Menu{
//Todo: Implement
};

class SimulationRunnerMenu : public Menu{
//Todo: Implement
};

class SimulationViewMenu : public Menu{
//Todo: Implement
};

class SimulationExportMenu : public Menu{
//Todo: Implement
};

class SimulationImportAndExportMenu : public Menu{
//Todo: Implement
};




#endif //NPRG041_MENU_H
