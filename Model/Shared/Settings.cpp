//
// Created by Vojtěch Pröschl on 28.03.2022.
//


#include "../Simulation/Simulation.h"
#include "SmartConversion.h"
#include "Settings.h"
#include "Bound.h"

using namespace std;
using string_t = tuple<string,string>;


//region Simulation Settings Implementation
vector<string_t> SimulationSettings::get_contents(){ //Todo: Rework the simulation settings menu
    vector<string_t> temp;
    temp.emplace_back(string_t("Duration",to_string(Duration)));
    temp.emplace_back(string_t("Substeps",to_string(Substeps)));
    temp.emplace_back(string_t("Framerate",to_string(Framerate)));
    temp.emplace_back(string_t("CacheFolder", CacheFolder));
    return temp;
}

bool SimulationSettings::set_contents(const std::string &name,const std::string &value) {
    if(name == "1"){
        Duration = bound<int>(convert_to_type<int>(value),min_duration,max_duration);
    }
    else if(name == "2"){
        Substeps = bound<int>(convert_to_type<int>(value),min_substeps,max_substeps);
    }
    else if(name == "3"){
        Framerate = bound<int>(convert_to_type<int>(value),min_framerate,max_framerate);
    }
    else if(name == "4") {
        CacheFolder = value;
    }
    else{
        return false;
    }
    return true;
}

//endregion

//region Playback Settings Implementation
vector<string_t> PlaybackSettings::get_contents() {
    vector<string_t> temp;
    temp.emplace_back(string_t("Resolution", smart_to_string<int,2>(Resolution)));
    temp.emplace_back(string_t("BackgroundColor", smart_to_string<int,3>(BackgroundColor)));
    return temp;
}

bool PlaybackSettings::set_contents(const std::string &name, const std::string &value) {
    if(name == "Resolution"){
        Resolution = bound_vector<int,2>(convert_to_vector<int,2>(value),min_playback_res,max_playback_res);
    }
    else if(name == "BackgroundColor"){
        BackgroundColor = bound_vector<int,3>(convert_to_vector<int,3>(value),min_color,max_color);
    }
    else{
        return false;
    }
    return true;
}

//endregion

//region Export Settings Implementation

vector<string_t> RenderSettings::get_contents() {
    vector<string_t> temp;
    temp.emplace_back(string_t("Resolution", smart_to_string<int,2>(Resolution)));
    temp.emplace_back("BackgroundColor",smart_to_string<int,3>(BackgroundColor));
    temp.emplace_back("RenderFolder",RenderFolder);
    return temp;
}

bool RenderSettings::set_contents(const std::string &name, const std::string &value) {
    if(name == "Resolution"){
        Resolution = bound_vector<int,2>(convert_to_vector<int,2>(value),min_playback_res,max_playback_res);
    }
    else if(name == "BackgroundColor"){
        BackgroundColor = bound_vector<int,3>(convert_to_vector<int,3>(value),min_color,max_color);
    }
    else if(name == "RenderFolder"){
        RenderFolder = value;
    }
    else{
        return false;
    }
    return true;
}

//endregion
