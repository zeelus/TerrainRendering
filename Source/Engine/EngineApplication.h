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

class EngineApplication {

    float width;
    float height;
    std::string name;

    Renderer renderer;

    GLFWwindow* window;

private:
    int setupWindow();
    void showOpenGLInformations();

public:
    EngineApplication(float width, float height, std::string &name);
    int run(int argc,  char** argv);
};


#endif //TERRENRENDERING_ENGINEAPPLICATION_H
