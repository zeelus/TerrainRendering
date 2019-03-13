//
// Created by Gilbert Gwizdala on 2018-12-19.
//

#include <string>
#include "Engine/EngineWindow.h"

int main(int argc, char** argv) {


    std::string windowName = "Terrain rendererSystem";
    Scene scene;
    EngineWindow engineApplication(800, 600, windowName, scene);

    int exitCode = engineApplication.run(argc, argv);

    return exitCode;
}

