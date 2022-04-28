#include <iostream>
#include "Model/Editor/Editor.h"
#include "Model/Shared/Settings.h"
#include "Dependencies/Eigen/Eigen"
#include "Model/Shared/SmartConversion.h"
#include "Model/Simulation/Cache.h"

using namespace std;

int main() {
    Editor editor;
    editor.Loop();
}
