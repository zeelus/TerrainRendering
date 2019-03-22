//
// Created by Gilbert Gwizdala on 2018-12-25.
//

#ifndef TESTGLEW_RENDERER_H
#define TESTGLEW_RENDERER_H

#define GLFW_INCLUDE_NONE

#include "../Engine/libs.h"
#include <string>

#include "Camera.h"
#include "Technique.h"
#include "Shader.h"
#include "StaticModel.h"
#include "../Engine/ResourceManager.h"

using namespace gl;

class Renderer {
private:

    GLuint vao = 0;
    GLuint ubo_matrix_handle;
    GLuint ubo_light_handle;

    glm::vec3 lightPos;

	Camera* camera = nullptr;

    ResourceManager* resourceManager;

private:

    void updateMatrices(const glm::mat4 & model) const;

    inline void setShaderProgram(GLuint shader_programme) const;

public:

    void init();
	
	
    void drawStaticModel(const int geometryIndex, const glm::mat4& modelMatrix) const;

	void updateLightPosition() const;

    Renderer();

    ~Renderer() = default;

	void setCamera(Camera* camera);


};


#endif //TESTGLEW_RENDERER_H


