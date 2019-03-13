//
// Created by Gilbert Gwizdala on 2019-01-26.
//

#ifndef TERRENRENDERING_ENGINEAPPLICATION_H
#define TERRENRENDERING_ENGINEAPPLICATION_H

#include <string>
#include "libs.h"
#include "Renderer/Renderer.h"
#include "Renderer/RenderingQueue.h"
#include "ResourceManager.h"
#include "Renderer/Terrain/TerrainTreeManager.h"


class EngineApplication {

    int width;
    int height;
    std::string name;

    RenderingQueue renderingQueue;

    TerrainTreeManager terrainTreeManager;

    Renderer renderer;

    ResourceManager* resourceManager;

    GLFWwindow* window;

private:
    int setupWindow();
    void showOpenGLInformation() const;
    void init();

public:
    EngineApplication(int width, int height, std::string &name);
    int run(int argc,  char** argv);

    void setupErrorCallback() const;
};


#endif //TERRENRENDERING_ENGINEAPPLICATION_H
