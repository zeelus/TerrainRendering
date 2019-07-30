//
// Created by Gilbert Gwizdala on 2019-01-26.
//

#include "EngineWindow.h"
#include <iostream>
#include <stdio.h>
#include <string.h>
#include "libs.h"

#include "../Renderer/Terrain/TerrainQuadTreeManager.h"
#include "Input.h"

using namespace gl;


EngineWindow::EngineWindow(int width, int height, std::string &name, Scene& scene): width(width), height(height), name(name), scene(scene) {
	input = Input::getInstance();
}

int EngineWindow::setupWindow() {
    if (!glfwInit()) {
        fprintf(stderr, "ERROR: could not start GLFW3\n");
        return -1;
    }
    statistic = Statistic<StatisticEvent>::shareInstance();

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

    glfwSetWindowUserPointer(window, input);
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

void EngineWindow::showOpenGLInformation() {
    const char* vendor = reinterpret_cast<const char*>(glGetString(GL_VENDOR));
    const GLubyte* renderer = glGetString(GL_RENDERER);
    const GLubyte* version = glGetString(GL_VERSION);
    printf("Vendor: %s\n", vendor);
    printf("Renderer: %s\n", renderer);
    printf("OpenGL version supported %s\n", version);

    isNvidia = (strcmp(vendor, "NVIDIA Corporation") == 0);

}

void EngineWindow::drowStaticModelQueue() const
{
	for (auto& model : this->scene.renderingQueue.getStaticModels()) {
		renderer.drawStaticModel(model.getIndexGeometryIndex(), model.getTransform(), NO_TEXTURE);
	}
}

void EngineWindow::drowTerrainTree() const
{
	auto& terrainTreeManger = this->scene.renderingQueue.terrainTreeManager;
	const int geometry = terrainTreeManger->getGeometryIndex();
	const int heightMapTextureIndex = terrainTreeManger->getHeightMapTextureIndex();

	for (auto& node : terrainTreeManger->nodes) {
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
    glfwSwapInterval(0);

    lastTime = glfwGetTime();
    lastTimeStatistic = glfwGetTime();

    scene.init();
    renderer.init();
	renderer.setCamera(&scene.camera);
	renderer.setUbo_terrain_handle(scene.renderingQueue.terrainTreeManager->getTerrain_handle_ubo());

    while(!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        double currentTime = glfwGetTime();
        double dTime = currentTime - lastTime;
		lastTime = currentTime;

		if constexpr (REDERING_QUAD_TREE) scene.renderingQueue.terrainTreeManager->update(scene.camera.view);

        if constexpr (SHOW_MASH) glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

		renderer.updateLightPosition();
		drowStaticModelQueue();
		drowTerrainTree();

        glfwPollEvents();
		scene.update(dTime);

        glfwSwapBuffers(window);

        if constexpr (CALCULATE_STATISTIC) calculateStatistic(currentTime);

    }

    return 0;
}

void EngineWindow::calculateStatistic(double currentTime) { 
    nbFrames++;
    if ( currentTime - lastTimeStatistic >= 1.0) {
        double msFr = 1000.0 / double(nbFrames);
        printf("%f ms/frame\n", msFr);
        nbFrames = 0;
        lastTimeStatistic += 1.0;

        const GLint memUsage = calculateGPUMemoryUsage();

        StatisticEvent event(msFr, memUsage);
        statistic->addElement(std::move(event));
    }
}

const GLint EngineWindow::calculateGPUMemoryUsage() const{

    if(isNvidia) {

	#ifdef _WIN32
			GLint total_mem_kb = 0;
			glGetIntegerv(GL_GPU_MEMORY_INFO_TOTAL_AVAILABLE_MEMORY_NVX, &total_mem_kb);

			GLint cur_avail_mem_kb = 0;
			glGetIntegerv(GL_GPU_MEMORY_INFO_CURRENT_AVAILABLE_VIDMEM_NVX, &cur_avail_mem_kb);

			return total_mem_kb - cur_avail_mem_kb;
	#endif // _WIN32

    }

    return -1;
}

