//
// Created by Gilbert Gwizdala on 2019-01-26.
//

#ifndef TERRENRENDERING_ENGINEAPPLICATION_H
#define TERRENRENDERING_ENGINEAPPLICATION_H

#include <string>
#include <glbinding/gl/gl.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <memory>
#include "Renderer/Renderer.h"
#include "ResourceManager.h"

using namespace gl;

class EngineApplication {

    int width;
    int height;
    std::string name;

    Renderer renderer;
    ResourceManager* resourceManager;

    GLFWwindow* window;

private:
    int setupWindow();
    void showOpenGLInformations();
    void init();

public:
    EngineApplication(float width, float height, std::string &name);
    int run(int argc,  char** argv);

    void setupErrorCallback() const;
};


#endif //TERRENRENDERING_ENGINEAPPLICATION_H
