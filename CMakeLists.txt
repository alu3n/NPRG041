cmake_minimum_required(VERSION 3.21)
project(NPRG041)

set(CMAKE_CXX_STANDARD 20)

add_executable(NPRG041
        main.cpp
        Model/Shared/Settings.cpp
        Model/Editor/Editor.cpp
        Model/Editor/Menu/MainMenu.cpp
        Model/Editor/Menu/SimulationEditorMenu.cpp
        Model/Editor/Menu/SimulationImportAndExportMenu.cpp
        Model/Editor/Menu/SimulationRenderMenu.cpp
        Model/Editor/Menu/SimulationRunnerMenu.cpp
        Model/Editor/Menu/SimulationViewMenu.cpp
        Model/Editor/Menu/SolverMenu.cpp
        Model/Editor/Menu/SolverSettingsMenu.cpp
        Model/Simulation/Cache.cpp
        Model/Simulation/Solvers/PreSolvers/Source.cpp
        Model/Simulation/Simulation.cpp
        Model/Simulation/Particle.cpp
        )

