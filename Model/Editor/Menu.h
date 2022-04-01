//
// Created by Vojtěch Pröschl on 28.03.2022.
//

#ifndef NPRG041_MENU_H
#define NPRG041_MENU_H

#include <vector>
#include <memory>
#include <iostream>
#include "../Shared/Settings.h"
#include "../Shared/SmartConversion.h"
#include "../Simulation/Simulation.h"


/* Menu should be able to solve request,
 *
 */

class Menu{
protected:
    Menu * parent = nullptr;
public:
    virtual Menu* solve_request(const std::string &) = 0; //Return null pointer if there was no change
    virtual void display() = 0;
    virtual std::string header() = 0;
};

class MainMenu : public Menu{
    /* This menu should serve as a hub for all other options */
    std::vector<Menu *> contents;
public:
    std::string header() override;
    Menu* solve_request(const std::string &) override;
    void add_menu_item(Menu *);
    void display() override;
};

class SolverSettingsMenu : public Menu{
    /* This menu is for manipulation with individual solvers */
    SolverSettings * settings;
public:
    Menu* solve_request(const std::string &) override;
    void display() override;
    SolverSettingsMenu(Menu *,SolverSettings *);
    std::string header() override;
};

class SolverMenu : public Menu{
    std::vector<std::unique_ptr<SolverSettings>> * solvers;
    std::vector<std::unique_ptr<SolverSettingsMenu>> contents;
    Menu* request_edit(const std::string &);
    Menu* request_add(const std::string &);
    Menu* request_remove(const std::string &);
    void build_menu();
public:
    std::string header() override;
    Menu* solve_request(const std::string &) override;
    void display() override;
    SolverMenu() = default;
    SolverMenu(Menu *, std::vector<std::unique_ptr<SolverSettings>> *);
};

class SimulationEditorMenu : public Menu{
    /* This menu is for changing simulation settings */
    SimulationSettings * settings;
public:
    std::string header() override;
    Menu* solve_request(const std::string &) override;
    void display() override;
    SimulationEditorMenu(Menu *, SimulationSettings *);
    SimulationEditorMenu() = default;
};

class SimulationRunnerMenu : public Menu{
    SimulationSettings * simulation_settings;
    std::vector<std::unique_ptr<SolverSettings>> * solvers;
public:
    std::string header() override;
    Menu* solve_request(const std::string &) override;
    void display() override;
    SimulationRunnerMenu(SimulationSettings *, std::vector<std::unique_ptr<SolverSettings>> *, Menu *);
    SimulationRunnerMenu() = default;
};

class SimulationViewMenu : public Menu{
//Todo: Implement
    /* In this menu you'l be able to open simulation view
     * Commands: view simulation, back
     * as well as change some of the view menu parameters
     */
};

class SimulationRenderMenu : public Menu{
//Todo: Implement
    /* In this menu youll be able to render the simulation
     * as well as change render settings
     */
};

class SimulationImportAndExportMenu : public Menu{
//Todo: Implement
    /* In this menu youll be able to import and export the simulation
     *
     */
};




#endif //NPRG041_MENU_H
