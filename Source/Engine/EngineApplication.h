//
// Created by Gilbert Gwizdala on 2019-01-26.
//

#ifndef TERRENRENDERING_ENGINEAPPLICATION_H
#define TERRENRENDERING_ENGINEAPPLICATION_H

#include <string>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <memory>
#include "Renderer/Renderer.h"
#include "ResourceManager.h"

class EngineApplication {

    int width;
    int height;
    std::string name;

    Renderer renderer;
    ResourceManager resourceManager;

    GLFWwindow* window;

private:
    int setupWindow();
    void showOpenGLInformations();
    void init();

public:
    EngineApplication(float width, float height, std::string &name);
    int run(int argc,  char** argv);
};


#endif //TERRENRENDERING_ENGINEAPPLICATION_H
