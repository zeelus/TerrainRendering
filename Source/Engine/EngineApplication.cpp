//
// Created by Gilbert Gwizdala on 2019-01-26.
//

#include "EngineApplication.h"
#include <glbinding/Version.h>
#include <glbinding/Binding.h>
#include <glbinding/FunctionCall.h>
#include <glbinding/CallbackMask.h>
#include <glbinding/gl/gl.h>
#include <glbinding/gl/extension.h>
#include <glbinding/glbinding.h>
#include <glbinding-aux/types_to_string.h>
#include <iostream>

#include "Renderer/Terrain/TerrainTreeManager.h"


using namespace gl;

EngineApplication::EngineApplication(int width, int height, std::string &name): width(width), height(height), name(name) {

}

int EngineApplication::setupWindow() {
    if (!glfwInit()) {
        fprintf(stderr, "ERROR: could not start GLFW3\n");
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, true);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(width, height, name.c_str(), NULL, NULL);

    if (!window) {
        fprintf(stderr, "ERROR: could not open window with GLFW3\n");
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    glbinding::initialize(glfwGetProcAddress);

    showOpenGLInformation();

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    setupErrorCallback();

    resourceManager = ResourceManager::getInstance();

    return 0;
}

void EngineApplication::setupErrorCallback() const {
    glbinding::setCallbackMaskExcept(glbinding::CallbackMask::After | glbinding::CallbackMask::ParametersAndReturnValue, {"glGetError" });
    glbinding::setAfterCallback([](const glbinding::FunctionCall &call)
                                {
                                    const auto error = glGetError();
                                    if(error != gl::GL_NO_ERROR)
                                    {
                                        std::cerr << "OpenGL error in function call:" << std::endl;
                                        std::cerr << call.function->name() << "(";
                                        for(size_t i = 0u; i < call.parameters.size(); ++i)
                                        {
                                            std::cerr << call.parameters[i].get();
                                            if(i < call.parameters.size() - 1)
                                                std::cerr << ", ";
                                        }
                                        std::cerr << ");";

                                        if(call.returnValue)
                                            std::cerr << " -> " << call.returnValue.get();
                                        std::cerr << std::endl;
                                        std::cerr << "Error: " << error << std::endl;
                                        throw error;
                                    }
                                });
}

void EngineApplication::showOpenGLInformation() const {
    const GLubyte* renderer = glGetString(GL_RENDERER);
    const GLubyte* version = glGetString(GL_VERSION);
    printf("Renderer: %s\n", renderer);
    printf("OpenGL version supported %s\n", version);
}

int EngineApplication::run(int argc, char **argv) {

    if (this->setupWindow() == -1) {
        fprintf(stderr, "Setup window error! \n");
        return -1;
    }

    this->init();
    renderer.init();

    glfwSetWindowUserPointer(window, &renderer);
    glfwSetKeyCallback(window, Renderer::key_callback_static);

    while(!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        renderer.drawStaticModels(this->renderingQueue.getStaticModels());

        glfwPollEvents();
        glfwSwapBuffers(window);
    }

    return 0;
}

void EngineApplication::init() {

    auto& model = renderingQueue.addStaticModel(resourceManager->loadModel("Resources/Models/tetrahedron.obj"));
    model.setPosition(glm::vec3(2, 0, 2));
    model.rotate(30.0f, glm::vec3(0.0f, 1.0f, 0.0));

    auto& model2 = renderingQueue.addStaticModel(resourceManager->loadModel("Resources/Models/cube.obj"));
    model2.setPosition(glm::vec3(0, 0, -2));

    auto& model3 = renderingQueue.addStaticModel(resourceManager->loadModel("Resources/Models/Suzanne.obj"));
    model3.rotate(-90.0f, glm::vec3(0.0f, 1.0f, 0.0));

    auto& deerModel = renderingQueue.addStaticModel(resourceManager->loadModel("Resources/Models/deer.obj"));
    deerModel.setPosition(glm::vec3(-3, 0, 2));
    deerModel.rotate(90.0f, glm::vec3(0.0f, 1.0f, 0.0));

    TerrainTreeManager terrainTreeManager(3);

}
