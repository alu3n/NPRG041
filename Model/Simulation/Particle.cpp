//
// Created by Vojtěch Pröschl on 30.03.2022.
//

#include <iostream>
#include "Particle.h"
#include "../Shared/SmartConversion.h"

using namespace std;

void Particle::print() {
    cout << "Position: "<< smart_to_string<double,3>(position) << endl;
    cout << "Velocity: " << smart_to_string<double,3>(velocity) << endl;
    cout << "Color: " << smart_to_string<double,3>(color) << endl;
    cout << "Size: " << size << endl;
    cout << "Density: " << density << endl;
}