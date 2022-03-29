//
// Created by Vojtěch Pröschl on 28.03.2022.
//

#include "SmartConversion.h"
#include "Settings.h"

using namespace std;
using string_t = tuple<string,string>;


//region Simulation Settings Implementation
vector<string_t> SimulationSettings::get_contents(){
    vector<string_t> temp;
    temp.push_back(string_t("Duration",to_string(Duration)));
    temp.push_back(string_t("Substeps",to_string(Substeps)));
    temp.push_back(string_t("Framerate",to_string(Framerate)));
    return temp;
}

bool SimulationSettings::set_contents(const std::string &name,const std::string &value) {
    if(name == "Duration"){
        if(convert_size_t(value,Duration)){
            return true;
        }
    }
    else if(name == "Substeps"){
        if(convert_size_t(value,Substeps)){
            return true;
        }
    }
    else if(name == "Framerate"){
        if(convert_size_t(value,Framerate)){
            return true;
        }
    }
    else{
        return false;
    }
    return false;
}

//endregion

//region Playback Settings Implementation
vector<string_t> PlaybackSettings::get_contents() {
    vector<string_t> temp;
//    temp.push_back(string_t("Resolution", smart_to_string<size_t,2>(Resolution)));
//    temp.push_back(string_t("Background Color", smart_to_string<std::byte,3>(BackgroundColor)));
    return temp;
}

bool PlaybackSettings::set_contents(const std::string &name, const std::string &value) {

    return false;
}

//endregion

//region Export Settings Implementation

vector<string_t> ExportSettings::get_contents() {
    vector<string_t> temp;
//    temp.push_back(string_t("Resolution", smart_to_string<size_t,2>(Resolution)));
//    temp.push_back(string_t("Background Color", smart_to_string<std::byte,3>(BackgroundColor)));
//    temp.push_back(string_t("Render Folder", RenderFolder));
    return temp;
}

bool ExportSettings::set_contents(const std::string &name, const std::string &value) {

    return false;
}

//endregion
