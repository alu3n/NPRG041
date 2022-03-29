//
// Created by Vojtěch Pröschl on 28.03.2022.
//

#ifndef NPRG041_SETTINGS_H
#define NPRG041_SETTINGS_H

#include "../../Dependencies/Eigen/Core"

#include <vector>
#include <string>
#include <tuple>

/* Todo: Make smart converters for all used datatypes
 *
 */

class Settings{
public:
    virtual std::vector<std::tuple<std::string,std::string>> get_contents() = 0;
    virtual bool set_contents(const std::string & name, const std::string & value) = 0;
};

/* SOLVER SETTINGS
 * Each solver has to have it's own settings class which will serve as its constructor
 */

class SolverSettings : public Settings{

};

//Global Settings
class SimulationSettings final : public Settings{
    size_t Duration = 10; //In seconds
    size_t Substeps = 1; //Per frame
    size_t Framerate = 24; //Per second
    std::string CacheFolder = ".";
public:
    std::vector<std::tuple<std::string,std::string>> get_contents() override;
    bool set_contents(const std::string & name,const std::string & value) override;
};

class PlaybackSettings final : public Settings{
    Eigen::Vector<size_t,2> Resolution;
    Eigen::Vector<std::byte,3> BackgroundColor;
public:
    std::vector<std::tuple<std::string,std::string>> get_contents() override;
    bool set_contents(const std::string & name,const std::string & value) override;
};

class ExportSettings final : public Settings{
    Eigen::Vector<size_t,2> Resolution;
    std::string RenderFolder;
    Eigen::Vector<std::byte,3> BackgroundColor;
public:
    std::vector<std::tuple<std::string,std::string>> get_contents() override;
    bool set_contents(const std::string & name,const std::string & value) override;
};


#endif //NPRG041_SETTINGS_H
