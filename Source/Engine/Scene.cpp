//
// Created by Gilbert Gwizdala on 2019-03-13.
//

#include "Scene.h"
#include "ResourceManager.h""
#include "libs.h"
#include "../Renderer/Camera.h"
#include "../Statistic/Statistic.h"
#include "../Statistic/StatisticEvent.h"

const float MOVING_FORCE = 6.0f;

Scene::Scene(): terrainTreeManager(3.0f, 5, 40) {
	input = Input::getInstance();
}

void Scene::init() {
    resourceManager = ResourceManager::getInstance();

	this->terrainTreeManager.initTerrenVBO();
	this->terrainTreeManager.setGeomentryIndex(resourceManager->loadModel("Resources/Models/nodePlate.obj", TechniqueType::TerrainPhongBline));
	this->terrainTreeManager.setHeightMapIndex(resourceManager->loadTexture("Resources/Texture/Heightmap.dds"));

    auto& model = renderingQueue.addStaticModel(resourceManager->loadModel("Resources/Models/deer.obj"));
    model.setPosition(glm::vec3(2, 0, 2));
    model.rotate(30.0f, glm::vec3(0.0f, 1.0f, 0.0));

 //   auto& model2 = renderingQueue.addStaticModel(resourceManager->loadModel("Resources/Models/cube.obj"));
 //   model2.setPosition(glm::vec3(0, 0, -2));

 //   auto& model3 = renderingQueue.addStaticModel(resourceManager->loadModel("Resources/Models/Suzanne.obj"));
 //   model3.rotate(-90.0f, glm::vec3(0.0f, 1.0f, 0.0));
	//
 //   auto& deerModel = renderingQueue.addStaticModel(resourceManager->loadModel("Resources/Models/deer.obj"));
 //   deerModel.setPosition(glm::vec3(-3, 0, 2));
 //   deerModel.rotate(90.0f, glm::vec3(0.0f, 1.0f, 0.0));

 	//auto& planeModel = renderingQueue.addStaticModel(resourceManager->loadModel("Resources/Models/nodePlate.obj"));

}

void Scene::update(double dTime)
{
	mat4 newPos = camera.view;

	if (input->isPreeed(GLFW_KEY_W)) {
		newPos = glm::translate(newPos, vec3(0.0f, 0.0f, MOVING_FORCE * dTime));
	}

	if (input->isPreeed(GLFW_KEY_S)) {
		newPos = glm::translate(newPos, vec3(0.0f, 0.0f, -MOVING_FORCE * dTime));
	}

	if (input->isPreeed(GLFW_KEY_D)) {
		newPos = glm::translate(newPos, vec3(-MOVING_FORCE * dTime, 0.0f, 0.0f));
	}

	if (input->isPreeed(GLFW_KEY_A)) {
		newPos = glm::translate(newPos, vec3(MOVING_FORCE * dTime, 0.0f, 0.0f));
	}

	if (input->isPreeed(GLFW_KEY_R)) {
		newPos = glm::translate(newPos, vec3(0.0f, -MOVING_FORCE * dTime, 0.0f));
	}

	if (input->isPreeed(GLFW_KEY_F)) {
		newPos = glm::translate(newPos, vec3(0.0f, MOVING_FORCE * dTime, 0.0f));
	}
	if (input->isPreeed(GLFW_KEY_O)) {
		Statistic<StatisticEvent>::shareInstance()->createStatistic();
	}

	camera.view = newPos;
}


