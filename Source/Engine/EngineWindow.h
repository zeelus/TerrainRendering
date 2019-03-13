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
#include "Scene.h"


class EngineWindow {

    Scene& scene;

    int width;
    int height;
    std::string name;

    Renderer renderer;

    GLFWwindow* window;

private:
    int setupWindow();
    void showOpenGLInformation() const;

public:
    EngineWindow(int width, int height, std::string &name, Scene& scene);
    int run(int argc,  char** argv);

    void setupErrorCallback() const;
};


#endif //TERRENRENDERING_ENGINEAPPLICATION_H
