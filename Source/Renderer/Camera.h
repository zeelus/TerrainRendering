//
// Created by Gilbert Gwizdala on 2018-12-19.
//

#ifndef TESTGLEW_CAMERA_H
#define TESTGLEW_CAMERA_H

#include "../Engine/libs.h"

using namespace glm;

struct Camera {

public:
    mat4 view;
    mat4 project;

    Camera();

};


#endif //TESTGLEW_CAMERA_H
