//
// Created by Vojtěch Pröschl on 28.03.2022.
//

#ifndef NPRG041_SETTINGS_H
#define NPRG041_SETTINGS_H

enum class settings_type{
    SimulationSettings
};

class Settings{

};

class SolverSettings : public Settings{

};

class SimulationSettings final : public Settings{

};

#endif //NPRG041_SETTINGS_H
