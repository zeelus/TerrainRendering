//
// Created by Gilbert Gwizdala on 2018-12-19.
//

#include "Camera.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/constants.hpp>
#include <OpenGL/gl3.h>
#include <cstdio>

using namespace glm;

Camera::Camera() {

    model = mat4(1.0f);

    view = lookAt(
            vec3(-4.0f, 3.0f, 0.0f),
            vec3(0.0f, 0.0f, 0.0f),
            vec3(0.0f, 1.0f, 0.0f)
            );

    float fovy = quarter_pi<float>();
    project = perspective(fovy, 800.0f / 600.0f, 0.01f, 100.0f);


    updateMVP();

}

void Camera::updateMVP() { mvp = project * view * model; }

void Camera::update(GLuint program) {
    GLint uniMvp = glGetUniformLocation(program, "mvp");

    glUniformMatrix4fv(uniMvp, 1, GL_FALSE, value_ptr(mvp));
}

void Camera::setView(const mat4 &view) {
    Camera::view = view;
    updateMVP();
}

mat4 Camera::getView(){
    return view;
}
