//
// Created by Vojtěch Pröschl on 31.03.2022.
//

#include "DebRenderer.h"
#include <iostream>
#include <fstream>

using namespace std;
DebRenderer::DebRenderer(int resolution_x, int resolution_y, double scale, std::string location) {
    this->resolution_x = resolution_x;
    this->resolution_y = resolution_y;
    this->scale = scale;
    this->location = location;
}

void DebRenderer::RenderCache(const Cache & cache) {
    int bigger_side = std::max(resolution_x,resolution_y);
    cout << "frame count: " << cache.frame_count << endl;
    for(int i = 0; i < cache.frame_count; i++){//Todo: construct the pixel array vector better
        cout << "Rendering frame: " << i << endl;
        std::vector<bool> temp(resolution_y,false);
        std::vector<std::vector<bool>> data;
        for(int i =0; i < resolution_x; i++) data.push_back(temp);
//        std::vector<std::vector<bool>> data(resolution_x,std::vector<bool>(resolution_y, bool(false)));
        std::vector<Particle> particles;
        cache.load_frame(i,particles);
//        cout << "CACHE PARTICLE COUNT:" << particles.size() << endl;
        for(auto && particle : particles){
            int p_x = floor(resolution_x/2 - particle.position[0]*bigger_side/scale);
            int p_y = floor(resolution_y/2 - particle.position[1]*bigger_side/scale);

//            cout << "PX: " << p_x << " PY: " << p_y << endl;
            if(p_x > 0 && p_x < resolution_x && p_y > 0 && p_y < resolution_y){
                data[p_y][p_x] = true;
            }
        }


        std::ofstream file(location + "/" + "render" + std::to_string(i) + ".pbm");

        file << "P1" << endl;
        file << resolution_x << " " << resolution_y << endl;//Todo: fix
        for(auto && x : data){
            for(auto && y : x){
                if(y){
                    file << "1" << endl;
//                    cout << "Rendering particle" << endl;
                }
                else{
                    file << "0" << endl;
                }
            }
        }
        file.close();
    }
}

