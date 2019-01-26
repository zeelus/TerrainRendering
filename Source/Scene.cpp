//
// Created by Gilbert Gwizdala on 2019-01-26.
//

#include "Scene.h"
#include <iostream>
#include <string>

using namespace std;
using namespace std::string_literals;

void Scene::createScene() {
    std::cout << "Scene Created" << std::endl;
    auto cameraElement = createGameElement("camera");

}
