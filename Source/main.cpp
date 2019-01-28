//
// Created by Gilbert Gwizdala on 2018-12-19.
//

#include <string>
#include "Engine/EngineApplication.h"
#include "Scene.h"


int main(int argc, char** argv) {


    std::string windowName = "Terrain rendererSystem";
    EngineApplication engineApplication(800, 600, windowName);
    Scene scene;
    engineApplication.setScene(scene);

    int exitCode = engineApplication.run(argc, argv);

    return exitCode;
}

