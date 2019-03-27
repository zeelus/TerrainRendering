//
// Created by Gilbert Gwizdala on 2019-03-13.
//

#include "Scene.h"
#include "ResourceManager.h"
#include "Input.h"
#include "libs.h"
#include "../Renderer/Camera.h"

Scene::Scene(): terrainTreeManager(4, 40) {

}

void Scene::init() {
    resourceManager = ResourceManager::getInstance();

	this->terrainTreeManager.setGeomentryIndex(resourceManager->loadModel("Resources/Models/nodePlate.obj"));

 //   auto& model = renderingQueue.addStaticModel(resourceManager->loadModel("Resources/Models/tetrahedron.obj"));
 //   model.setPosition(glm::vec3(2, 0, 2));
 //   model.rotate(30.0f, glm::vec3(0.0f, 1.0f, 0.0));

 //   auto& model2 = renderingQueue.addStaticModel(resourceManager->loadModel("Resources/Models/cube.obj"));
 //   model2.setPosition(glm::vec3(0, 0, -2));

 //   auto& model3 = renderingQueue.addStaticModel(resourceManager->loadModel("Resources/Models/Suzanne.obj"));
 //   model3.rotate(-90.0f, glm::vec3(0.0f, 1.0f, 0.0));
	//
 //   auto& deerModel = renderingQueue.addStaticModel(resourceManager->loadModel("Resources/Models/deer.obj"));
 //   deerModel.setPosition(glm::vec3(-3, 0, 2));
 //   deerModel.rotate(90.0f, glm::vec3(0.0f, 1.0f, 0.0));

 	//auto& planeModel = renderingQueue.addStaticModel(resourceManager->loadModel("Resources/Models/nodePlate.obj"));


    Input::getInstance()->addFunction( [&camera = camera] (int key, int scancode, int action, int mods){
		auto pos = camera.view;
		mat4 newPos = pos;
		switch (key) {
			case GLFW_KEY_W:
				newPos = glm::translate(pos, vec3(0.0f, 0.0f, 0.2f));
				break;
			case GLFW_KEY_S:
				newPos = glm::translate(pos, vec3(0.0f, 0.0f, -0.2));
				break;
			case GLFW_KEY_D:
				newPos = glm::translate(pos, vec3(-0.2f, 0.0f, 0.0f));
				break;
			case GLFW_KEY_A:
				newPos = glm::translate(pos, vec3(0.2f, 0.0f, 0.0f));
				break;
			case GLFW_KEY_R:
				newPos = glm::translate(pos, vec3(0.0f, -0.2f, 0.0f));
				break;
			case GLFW_KEY_F:
				newPos = glm::translate(pos, vec3(0.0f, 0.2f, 0.0f));
				break;
		}

		camera.view = newPos;
    });

}

void Scene::update()
{

}


