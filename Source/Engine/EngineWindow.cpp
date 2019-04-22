//
// Created by Gilbert Gwizdala on 2019-01-26.
//

#include "EngineWindow.h"
#include <iostream>
#include "libs.h"

#include "../Renderer/Terrain/TerrainTreeManager.h"
#include "Input.h"

using namespace gl;

EngineWindow::EngineWindow(int width, int height, std::string &name, Scene& scene): width(width), height(height), name(name), scene(scene) {

}

int EngineWindow::setupWindow() {
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

    int widthBufferSize, heightBufferSize;

    glfwGetFramebufferSize(window, &widthBufferSize, &heightBufferSize);

    glfwMakeContextCurrent(window);

    glbinding::initialize(glfwGetProcAddress);

    gl::glViewport(0, 0, widthBufferSize, heightBufferSize);

    showOpenGLInformation();

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    setupErrorCallback();

    glfwSetWindowUserPointer(window, Input::getInstance());
    glfwSetKeyCallback(window, Input::key_callback_static);

    return 0;
}

void EngineWindow::setupErrorCallback() const {
    glbinding::setCallbackMaskExcept(glbinding::CallbackMask::After | glbinding::CallbackMask::ParametersAndReturnValue, {"glGetError" });
    glbinding::setAfterCallback([](const glbinding::FunctionCall &call)
                                {
                                    const auto error = gl::glGetError();
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

void EngineWindow::showOpenGLInformation() const {
    const GLubyte* renderer = glGetString(GL_RENDERER);
    const GLubyte* version = glGetString(GL_VERSION);
    printf("Renderer: %s\n", renderer);
    printf("OpenGL version supported %s\n", version);
}

void EngineWindow::drowStaticModelQueue() const
{
	for (auto& model : this->scene.renderingQueue.getStaticModels()) {
		renderer.drawStaticModel(model.getIndexGeometryIndex(), model.getTransform(), NO_TEXTURE);
	}
}

void EngineWindow::drowTerrainTree() const
{
	auto& terrainTreeManger = this->scene.terrainTreeManager;
	const int geometry = terrainTreeManger.getGeometryIndex();
	const int heightMapTextureIndex = terrainTreeManger.getHeightMapTextureIndex();

	for (auto& node : terrainTreeManger.nodes) {
		if (node.isShowing) {
			renderer.drawStaticModel(geometry, node.transform, heightMapTextureIndex);
		}
	}
}

int EngineWindow::run(int argc, char **argv) {

    if (this->setupWindow() == -1) {
        fprintf(stderr, "Setup window error! \n");
        return -1;
    }

    scene.init();
    renderer.init();
	renderer.setCamera(&scene.camera);
	renderer.setUbo_terrain_handle(scene.terrainTreeManager.getTerrain_handle_ubo());

    while(!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		scene.terrainTreeManager.update(scene.camera.view);
        //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

		renderer.updateLightPosition();
		drowStaticModelQueue();
		drowTerrainTree();

        //glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        
        glfwPollEvents();
		scene.update();

        glfwSwapBuffers(window);
    }

    return 0;
}

