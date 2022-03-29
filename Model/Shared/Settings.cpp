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
    temp.emplace_back(string_t("Duration",to_string(Duration)));
    temp.emplace_back(string_t("Substeps",to_string(Substeps)));
    temp.emplace_back(string_t("Framerate",to_string(Framerate)));
    temp.emplace_back(string_t("CacheFolder", CacheFolder));
    return temp;
}

bool SimulationSettings::set_contents(const std::string &name,const std::string &value) {
    if(name == "Duration"){

    }
    else if(name == "Substeps"){

    }
    else if(name == "Framerate"){

    }
    else if(name == "CacheFolder"){

    }
    return false;
}

//endregion

//region Playback Settings Implementation
vector<string_t> PlaybackSettings::get_contents() {
    vector<string_t> temp;
    temp.emplace_back(string_t("Resolution", smart_to_string<size_t,2>(Resolution)));
    temp.emplace_back(string_t("BackgroundColor", smart_to_string<int,3>(BackgroundColor)));
    return temp;
}

bool PlaybackSettings::set_contents(const std::string &name, const std::string &value) {

    return false;
}

//endregion

//region Export Settings Implementation

vector<string_t> RenderSettings::get_contents() {
    vector<string_t> temp;
    temp.emplace_back(string_t("Resolution", smart_to_string<size_t,2>(Resolution)));
    temp.emplace_back("BackgroundColor",smart_to_string<int,3>(BackgroundColor));
    temp.emplace_back("RenderFolder",RenderFolder);
    return temp;
}

bool RenderSettings::set_contents(const std::string &name, const std::string &value) {

    return false;
}

//endregion
