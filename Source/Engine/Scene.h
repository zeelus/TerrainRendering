//
// Created by Gilbert Gwizdala on 2019-03-13.
//

#ifndef TERRENRENDERING_SCENE_H
#define TERRENRENDERING_SCENE_H


#include "ResourceManager.h"
#include "../Renderer/Terrain/TerrainTreeManager.h"
#include "../Renderer/RenderingQueue.h"

class Scene {

public:

    RenderingQueue renderingQueue;
    TerrainTreeManager terrainTreeManager;
    ResourceManager* resourceManager;

    Scene();
    void init();

};


#endif //TERRENRENDERING_SCENE_H
