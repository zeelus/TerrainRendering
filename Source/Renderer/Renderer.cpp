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

}

void Renderer::init() {

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

void Renderer::drawStaticModel(const unsigned int geometryIndex, const glm::mat4& modelMatrix) const {
    static short lastUsedTechnique = -2;
    static int lastUsedModelIndex = -2;
    static const Geometry* geometry;

    if(geometryIndex < 0) return;

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

	glDrawElements(GL_TRIANGLES, geometry->getElementsSize() * sizeof(GLushort), GL_UNSIGNED_SHORT, nullptr);

    
}

void Renderer::setShaderProgram(GLuint shader_programme) const {
    glUseProgram(shader_programme);
    glBindBufferBase(GL_UNIFORM_BUFFER, matricesBlockBinding, ubo_matrix_handle);
    glBindBufferBase(GL_UNIFORM_BUFFER, pointLightBinding, ubo_light_handle);
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