//
// Created by Gilbert Gwizdala on 2018-12-25.
//

#ifndef TESTGLEW_RENDERER_H
#define TESTGLEW_RENDERER_H

#include <string>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "../Camera.h"

class RendererSystem {
private:

    Camera camera;
    
public:
    void drowing();
};


#endif //TESTGLEW_RENDERER_H
