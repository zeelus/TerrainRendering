//
// Created by Gilbert Gwizdala on 2019-03-13.
//

#include "Scene.h"
#include "ResourceManager.h"

Scene::Scene(): terrainTreeManager(3, 20) {

}

void Scene::init() {
    resourceManager = ResourceManager::getInstance();

    auto& model = renderingQueue.addStaticModel(resourceManager->loadModel("Resources/Models/tetrahedron.obj"));
    model.setPosition(glm::vec3(2, 0, 2));
    model.rotate(30.0f, glm::vec3(0.0f, 1.0f, 0.0));

    auto& model2 = renderingQueue.addStaticModel(resourceManager->loadModel("Resources/Models/cube.obj"));
    model2.setPosition(glm::vec3(0, 0, -2));

    auto& model3 = renderingQueue.addStaticModel(resourceManager->loadModel("Resources/Models/Suzanne.obj"));
    model3.rotate(-90.0f, glm::vec3(0.0f, 1.0f, 0.0));

    auto& deerModel = renderingQueue.addStaticModel(resourceManager->loadModel("Resources/Models/deer.obj"));
    deerModel.setPosition(glm::vec3(-3, 0, 2));
    deerModel.rotate(90.0f, glm::vec3(0.0f, 1.0f, 0.0));

}


