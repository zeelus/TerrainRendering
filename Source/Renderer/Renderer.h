//
// Created by Gilbert Gwizdala on 2018-12-25.
//

#ifndef TESTGLEW_RENDERER_H
#define TESTGLEW_RENDERER_H

#include <string>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Camera.h"

class Renderer {
private:

    float width;
    float height;
    std::string name;

    GLFWwindow* window;

    Camera camera;
public:
    GLFWwindow *getWindow() const;

private:

    void showOpenGLInformations();

    static void key_callback_static(GLFWwindow* window, int key, int scancode, int action, int mods);
    void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

public:

    Renderer(float width, float height, std::string &name);

    int setupWindow();

    void drowing();
};


#endif //TESTGLEW_RENDERER_H
