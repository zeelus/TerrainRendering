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

class Renderer {
private:

	gl::GLuint vao = 0;
	gl::GLuint ubo_matrix_handle;
	gl::GLuint ubo_light_handle;
	gl::GLint ubo_terrain_handle = -1u;
    gl::GLuint ubo_terrain_tessellation_handle;

public:


private:
    gl::GLuint sampler_handle;

    glm::vec3 lightPos;

	Camera* camera = nullptr;

    ResourceManager* resourceManager;

private:

    void updateMatrices(const glm::mat4 & model) const;

    inline void setShaderProgram(GLuint shader_programme) const;

	inline void initSO(void);

public:

    void init();
	
    void drawStaticModel(const int geometryIndex, const glm::mat4& modelMatrix, const int textureIndex) const;

	void updateLightPosition() const;

    Renderer();

    ~Renderer() = default;

	void setCamera(Camera* camera);

	void setUbo_terrain_handle(const gl::GLint ubo_terrain_handle);
    void setUboTerrainTessellationHandle(GLuint uboTerrainTessellationHandle);

};


#endif //TESTGLEW_RENDERER_H


