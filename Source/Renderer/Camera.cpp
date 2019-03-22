//
// Created by Gilbert Gwizdala on 2018-12-19.
//

#include "Camera.h"
#include "../Engine/libs.h"

using namespace glm;

Camera::Camera() {

	view = lookAt(
            vec3(0.0f, 4.0f, 8.0f),
            vec3(0.0f, 0.0f, 0.0f),
            vec3(0.0f, 1.0f, 0.0f)
            );

    float fovy = quarter_pi<float>();
    project = perspective(fovy, 800.0f / 600.0f, 0.01f, 100.0f);

}

