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

    void updateLightPosition() const;

    void updateMatrices(const StaticModel &model) const;

    inline void setShaderProgram(GLuint shader_programme) const;

public:

    void init();

    void drawStaticModels(const std::vector<StaticModel> &staticModels) const;

    Renderer();

    ~Renderer() = default;

	void setCamera(Camera* camera);


};


#endif //TESTGLEW_RENDERER_H

