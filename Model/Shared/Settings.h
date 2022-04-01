//
// Created by Vojtěch Pröschl on 28.03.2022.
//

#ifndef NPRG041_SETTINGS_H
#define NPRG041_SETTINGS_H

#include "../../Dependencies/Eigen/Core"

#include <vector>
#include <string>
#include <tuple>
#include "../Simulation/Solver.h"

//region Bounding constants
//Simulation settings
constexpr int max_duration = 600; //In seconds
constexpr int min_duration = 1;
constexpr int max_substeps = 100;
constexpr int min_substeps = 1;
constexpr int max_framerate = 120;
constexpr int min_framerate = 12;

//Playback settings
constexpr int max_playback_res = 2048;
constexpr int min_playback_res = 128;

//Export settings
constexpr int max_render_res = 2048;
constexpr int min_render_res = 128;

//Shared
constexpr int min_color = 0;
constexpr int max_color = 255;

//endregion

//region Default settings

//Default simulation settings
constexpr int default_duration = 10;
constexpr int default_substeps = 1;
constexpr int default_framerate = 24;
constexpr std::string_view  default_cache_folder = "Cache";

//Default playback settings
constexpr int default_playback_resolution_x = 1000;
constexpr int default_playback_resolution_y = 1000;
constexpr int default_playback_background_color_r = 0;
constexpr int default_playback_background_color_g = 0;
constexpr int default_playback_background_color_b = 0;

//Default render settings
constexpr int default_render_resolution_x = 1000;
constexpr int default_render_resolution_y = 1000;
constexpr int default_render_background_color_r = 0;
constexpr int default_render_background_color_g = 0;
constexpr int default_render_background_color_b = 0;
constexpr std::string_view default_render_folder = "./Render";

//endregion

class Settings{
public:
    virtual std::vector<std::tuple<std::string,std::string>> get_contents() = 0;
    virtual bool set_contents(const std::string & name, const std::string & value) = 0;
};

/* SOLVER SETTINGS
 * Each solver has to have it's own settings class which will serve as its constructor
 */

class SolverSettings : public Settings{
public:
    virtual SolverType get_type() = 0;
    //Purely virtual
};

//Global Settings

class PlaybackSettings final : public Settings{
    Eigen::Vector<int,2> Resolution = Eigen::Vector<int,2>(default_playback_resolution_x,default_playback_resolution_y);
    Eigen::Vector<int,3> BackgroundColor = Eigen::Vector<int,3>(default_render_background_color_r,default_render_background_color_g,default_render_background_color_b);
public:
    std::vector<std::tuple<std::string,std::string>> get_contents() override;
    bool set_contents(const std::string & name,const std::string & value) override;
};

class RenderSettings final : public Settings{
    Eigen::Vector<int,2> Resolution = Eigen::Vector<int,2>(default_render_resolution_x,default_render_resolution_y);
    std::string RenderFolder = std::string(default_render_folder);
    Eigen::Vector<int,3> BackgroundColor = Eigen::Vector<int,3>(default_render_background_color_r,default_render_background_color_g,default_render_background_color_b);
public:
    std::vector<std::tuple<std::string,std::string>> get_contents() override;
    bool set_contents(const std::string & name,const std::string & value) override;
};



#endif //NPRG041_SETTINGS_H
