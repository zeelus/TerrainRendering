//
// Created by Gilbert Gwizdala on 2019-01-26.
//

#ifndef TERRENRENDERING_ENGINEAPPLICATION_H
#define TERRENRENDERING_ENGINEAPPLICATION_H

#include <string>
#include "libs.h"
#include "../Renderer/Renderer.h"
#include "../Renderer/RenderingQueue.h"
#include "ResourceManager.h"
#include "../Renderer/Terrain/QuadTree/TerrainQuadTreeManager.h"
#include "Scene.h"
#include "../Statistic/Statistic.h"
#include "../Statistic/StatisticEvent.h"
#include "Input.h"

const int NO_TEXTURE = -1;
const bool CALCULATE_STATISTIC = true;
const bool SHOW_MASH = true;

const static bool REDERING_QUAD_TREE = false;

class EngineWindow {

    Scene& scene;

    int width;
    int height;
    std::string name;

    Renderer renderer;

    GLFWwindow* window;

    Statistic<StatisticEvent> *statistic = nullptr;
	Input* input;

    double lastTime = 0.0;
    double lastTimeStatistic = 0.0;
    int nbFrames = 0;

    bool isNvidia = false;

private:
    int setupWindow();
    void showOpenGLInformation();
	void drowStaticModelQueue() const;
	void drawTerrainTree() const;
	void calculateStatistic(double currentTime);
	const GLint calculateGPUMemoryUsage() const;

public:
    EngineWindow(int width, int height, std::string &name, Scene& scene);
    int run(int argc,  char** argv);

    void setupErrorCallback() const;
};


#endif //TERRENRENDERING_ENGINEAPPLICATION_H
