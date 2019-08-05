//
// Created by Gilbert Gwizdala on 2018-12-25.
//

#include "Renderer.h"

#include "../Engine/libs.h"
#include <string>
#include <vector>

#include "Shader.h"
#include "Technique.h"
#include "../Engine/ResourceManager.h"

using namespace gl;

Renderer::Renderer(): lightPos(-8.0f, 4.0f, 0.0f) {
    ubo_terrain_tessellation_handle = 0;
}

void Renderer::init() {

	initSO();

    glGenVertexArrays(1, &vao);

    gl::glGenBuffers(1, &ubo_matrix_handle);
    glBindBuffer(GL_UNIFORM_BUFFER, ubo_matrix_handle);
    std::array<glm::mat4, 3u> matrices = { mat4(1.0), mat4(1.0), mat4(1.0) };
    gl::glBufferData(GL_UNIFORM_BUFFER, 3 * sizeof(glm::mat4), matrices.data(), gl::GL_DYNAMIC_DRAW);
    glBindBuffer(GL_UNIFORM_BUFFER, 0);

    gl::glGenBuffers(1, &ubo_light_handle);
    glBindBuffer(GL_UNIFORM_BUFFER, ubo_light_handle);
    std::array<glm::vec4, 2u> light = {glm::vec4(lightPos.x, lightPos.y, lightPos.z, 0.0f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f)};
    gl::glBufferData(GL_UNIFORM_BUFFER, 2 * sizeof(glm::vec4), light.data(), gl::GL_DYNAMIC_DRAW);
    glBindBuffer(GL_UNIFORM_BUFFER, 0);

    resourceManager = ResourceManager::getInstance();
}

void Renderer::drawStaticModel(const int geometryIndex, const glm::mat4& modelMatrix, const int textureIndex) const {
    static short lastUsedTechnique = -2;
    static int lastUsedModelIndex = -2;
	static int lastUsedTextureIndex = -2;
    static const Geometry* geometry;

    if(geometryIndex < 0) return;

	if (lastUsedTextureIndex != textureIndex) {

		lastUsedTextureIndex = textureIndex;

		if (textureIndex < 0) {
			gl::glBindSampler(0, 0u);
			gl::glBindTexture(gl::GL_TEXTURE_2D, 0u);
		}
		else {
			gl::glBindSampler(0, sampler_handle);
			gl::glActiveTexture(gl::GL_TEXTURE0);

			auto& texture = this->resourceManager->getTexture(textureIndex);
			gl::glBindTexture(gl::GL_TEXTURE_2D, texture.getTextureHandler());
		}
	}

    if(geometryIndex != lastUsedModelIndex) {
        lastUsedModelIndex = geometryIndex;
        geometry = &resourceManager->getGeometry(geometryIndex);

        const short techniqueIndex = geometry->getTechniqueIndex();
        if(lastUsedTechnique != techniqueIndex) {
            lastUsedTechnique = techniqueIndex;
            const auto& technique = this->resourceManager->loadTechnique(techniqueIndex);
            const auto shader_programme = technique.getShader_programme();
            this->setShaderProgram(shader_programme);
        }

        glBindVertexArray(0u);

        glBindVertexArray(geometry->getVao());

    }

    this->updateMatrices(modelMatrix);

    glPatchParameteri(GL_PATCH_VERTICES, 4);
	glDrawElements(geometry->getOpenGLRenderingType(), geometry->getElementsSize() * sizeof(GLushort), GL_UNSIGNED_SHORT, nullptr);

}

void Renderer::setShaderProgram(GLuint shader_programme) const {
    glUseProgram(shader_programme);
    glBindBufferBase(GL_UNIFORM_BUFFER, MatricesBlockBinding, ubo_matrix_handle);
    glBindBufferBase(GL_UNIFORM_BUFFER, PointLightBinding, ubo_light_handle);
	glBindBufferBase(GL_UNIFORM_BUFFER, TerrainBinding, ubo_terrain_handle);
	if(ubo_terrain_tessellation_handle > 0 ) {
        glBindBufferBase(GL_UNIFORM_BUFFER, TerrainTessellationBinding, ubo_terrain_tessellation_handle);
    }
}

inline void Renderer::initSO(void)
{
	gl::glGenSamplers(1, &sampler_handle);

	gl::glSamplerParameteri(sampler_handle, gl::GL_TEXTURE_WRAP_S, gl::GL_REPEAT);
	gl::glSamplerParameteri(sampler_handle, gl::GL_TEXTURE_WRAP_T, gl::GL_REPEAT);
	gl::glSamplerParameteri(sampler_handle, gl::GL_TEXTURE_WRAP_R, gl::GL_REPEAT);
	gl::glSamplerParameteri(sampler_handle, gl::GL_TEXTURE_MIN_FILTER, gl::GL_LINEAR_MIPMAP_LINEAR);
	gl::glSamplerParameteri(sampler_handle, gl::GL_TEXTURE_MAG_FILTER, gl::GL_LINEAR);
}

void Renderer::updateMatrices(const glm::mat4 & model) const {
    glBindBuffer(GL_UNIFORM_BUFFER, ubo_matrix_handle);
    gl::glBufferData(GL_UNIFORM_BUFFER, 3 * sizeof(glm::mat4), nullptr, gl::GL_DYNAMIC_DRAW);
    std::array<mat4, 3u> matrices = {model, camera->view, camera->project};
    if(void *result = gl::glMapBuffer(GL_UNIFORM_BUFFER, gl::GL_WRITE_ONLY)) {
            memcpy(result, matrices.data(), sizeof(mat4) * 3);
            glUnmapBuffer(GL_UNIFORM_BUFFER);
        }
    glBindBuffer(GL_UNIFORM_BUFFER, 0u);
}

void Renderer::updateLightPosition() const {
    glBindBuffer(GL_UNIFORM_BUFFER, ubo_light_handle);
    gl::glBufferData(GL_UNIFORM_BUFFER, 2 * sizeof(vec4), nullptr, gl::GL_DYNAMIC_DRAW);
    std::array<vec4, 2u> light = {vec4(lightPos.x, lightPos.y, lightPos.z, 0.0f), vec4(1.0f, 1.0f, 1.0f, 1.0f)};
    if(void *result = gl::glMapBuffer(GL_UNIFORM_BUFFER, gl::GL_WRITE_ONLY)) {
        memcpy(result, light.data(), 2 * sizeof(vec4));
        glUnmapBuffer(GL_UNIFORM_BUFFER);
    }
    glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

void Renderer::setCamera(Camera* camera)
{
	this->camera = camera;
}

void Renderer::setUbo_terrain_handle(const gl::GLint ubo_terrain_handle)
{
	this->ubo_terrain_handle = ubo_terrain_handle;
}

void Renderer::setUboTerrainTessellationHandle(GLuint uboTerrainTessellationHandle) {
    ubo_terrain_tessellation_handle = uboTerrainTessellationHandle;
}
