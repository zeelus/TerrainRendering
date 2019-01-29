//
// Created by Gilbert Gwizdala on 2018-12-19.
//

#include "CameraComponent.h"
#include <GL/glew.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/constants.hpp>
#include <cstdio>

using namespace glm;

CameraComponent::CameraComponent() {

    model = mat4(1.0f);

    view = mat4(1.0f);/*lookAt(
            vec3(-4.0f, 3.0f, 0.0f),
            vec3(0.0f, 0.0f, 0.0f),
            vec3(0.0f, 1.0f, 0.0f)
            );*/

    float fovy = quarter_pi<float>();
    project = perspective(fovy, 800.0f / 600.0f, 0.01f, 100.0f);


    updateMVP();

}

void CameraComponent::updateMVP() { mvp = project * view * model; }

void CameraComponent::update(GLuint program) {
    GLint uniMvp = glGetUniformLocation(program, "mvp");

    glUniformMatrix4fv(uniMvp, 1, GL_FALSE, value_ptr(mvp));
}

void CameraComponent::setView(const mat4 &view) {
    CameraComponent::view = view;
    updateMVP();
}

mat4 CameraComponent::getView(){
    return view;
}
