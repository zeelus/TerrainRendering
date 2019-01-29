//
// Created by Gilbert Gwizdala on 2018-12-19.
//

#ifndef TESTGLEW_CAMERA_H
#define TESTGLEW_CAMERA_H

#include <GL/glew.h>
#include <glm/glm.hpp>
#include "Component.h"


using namespace glm;

class CameraComponent: public Component {

    mat4 model;
    mat4 view;
    mat4 project;

    mat4 mvp;


public:
    CameraComponent();

    void update(GLuint program);

    mat4 getView();
    void setView(const mat4 &view);

    void updateMVP();
};


#endif //TESTGLEW_CAMERA_H
