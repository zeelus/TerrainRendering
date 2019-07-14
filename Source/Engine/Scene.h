//
// Created by Gilbert Gwizdala on 2019-03-13.
//

#ifndef TERRENRENDERING_SCENE_H
#define TERRENRENDERING_SCENE_H


#include "ResourceManager.h"
#include "../Renderer/RenderingQueue.h"
#include "../Renderer/Camera.h"
#include "../Renderer/Renderer.h"
#include "Input.h"

class Scene {

public:

    RenderingQueue renderingQueue;
    ResourceManager* resourceManager;
	Camera camera;
	Input* input;

    Scene();
    void init();
	void update(double dTime);

};


#endif //TERRENRENDERING_SCENE_H
