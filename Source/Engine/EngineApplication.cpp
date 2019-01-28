//
// Created by Gilbert Gwizdala on 2019-01-26.
//

#include "EngineApplication.h"

EngineApplication::EngineApplication(float width, float height, std::string &name): width(width), height(height), name(name), rendererSystem(&registryEntt) {
}

int EngineApplication::setupWindow() {
    if (!glfwInit()) {
        fprintf(stderr, "ERROR: could not start GLFW3\n");
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(width, height, name.c_str(), NULL, NULL);

    if (!window) {
        fprintf(stderr, "ERROR: could not open window with GLFW3\n");
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    showOpenGLInformations();

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    GLenum err = glewInit();
    if (GLEW_OK != err)
    {
        /* Problem: glewInit failed, something is seriously wrong. */
        auto x = glewGetErrorString(err);
        fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
        return -1;
    }

    fprintf(stdout, "Status: Using GLEW %s\n", glewGetString(GLEW_VERSION));

    return 0;
}

void EngineApplication::showOpenGLInformations() {
    const GLubyte* renderer = glGetString(GL_RENDERER);
    const GLubyte* version = glGetString(GL_VERSION);
    printf("RendererSystem: %s\n", renderer);
    printf("OpenGL version supported %s\n", version);
}

int EngineApplication::run(int argc, char **argv) {

    if (this->setupWindow() == -1) {
        fprintf(stderr, "Setup window error! \n");
        return -1;
    }

    this->scene->createScene();

    while(!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        rendererSystem.drowing();

        glfwPollEvents();
        glfwSwapBuffers(window);
    }

    return 0;
}

void EngineApplication::setScene(AbstractScene& scene) {
    this->scene = &scene;
    this->scene->setRegistryEntt(&registryEntt);
}


