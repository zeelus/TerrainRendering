//
// Created by Gilbert Gwizdala on 2018-12-25.
//

#include "Renderer.h"
#define GLFW_INCLUDE_NONE
#include <glbinding/gl/gl.h>
#include <string>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>
#include "Shader.h"
#include "Technique.h"
#include "../ResourceManager.h"

using namespace gl;

Renderer::Renderer(): lightPos(-8.0f, 4.0f, 0.0f) {

}

void Renderer::init() {

    glGenVertexArrays(1, &vao);

    gl::glGenBuffers(1, &ubo_matrix_handle);
    glBindBuffer(GL_UNIFORM_BUFFER, ubo_matrix_handle);
    std::array<glm::mat4, 3u> matrices = { mat4(1.0), camera.view, camera.project};
    gl::glBufferData(GL_UNIFORM_BUFFER, 3 * sizeof(glm::mat4), matrices.data(), gl::GL_DYNAMIC_DRAW);
    glBindBuffer(GL_UNIFORM_BUFFER, 0);

    gl::glGenBuffers(1, &ubo_light_handle);
    glBindBuffer(GL_UNIFORM_BUFFER, ubo_light_handle);
    std::array<glm::vec4, 2u> light = {glm::vec4(lightPos.x, lightPos.y, lightPos.z, 0.0f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f)};
    gl::glBufferData(GL_UNIFORM_BUFFER, 2 * sizeof(glm::vec4), light.data(), gl::GL_DYNAMIC_DRAW);
    glBindBuffer(GL_UNIFORM_BUFFER, 0);

    resourceManager = ResourceManager::getInstance();
}

void Renderer::drawStaticModels(const std::vector<StaticModel> &staticModels) const {
    static short lastUsedTechnique = -2;
    static int lastUsedModelIndex = -2;
    static const Geometry* geometry;

    for(const auto& model: staticModels) {

        const unsigned int geometryIndex = model.getIndexGeometryIndex();

        if(geometryIndex < 0) continue;

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

        this->updateLightPosition();
        this->updateMatrices(model);

        glDrawElements(GL_TRIANGLES, geometry->getElementsSize() * sizeof(GLushort), GL_UNSIGNED_SHORT, nullptr);

    }
}

void Renderer::setShaderProgram(GLuint shader_programme) const {
    glUseProgram(shader_programme);
    glBindBufferBase(GL_UNIFORM_BUFFER, matricesBlockBinding, ubo_matrix_handle);
    glBindBufferBase(GL_UNIFORM_BUFFER, pointLightBinding, ubo_light_handle);
}

void Renderer::updateMatrices(const StaticModel &model) const {
    glBindBuffer(GL_UNIFORM_BUFFER, ubo_matrix_handle);
    gl::glBufferData(GL_UNIFORM_BUFFER, 3 * sizeof(glm::mat4), nullptr, gl::GL_DYNAMIC_DRAW);
    std::array<mat4, 3u> matrices = {model.getTransform(), camera.view, camera.project};
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

void Renderer::key_callback_static(GLFWwindow *window, int key, int scancode, int action, int mods) {
    auto rendererSystem = reinterpret_cast<Renderer*>(glfwGetWindowUserPointer(window));
    rendererSystem->key_callback(window, key, scancode, action, mods);
}

void Renderer::key_callback(GLFWwindow *window, int key, int scancode, int action, int mods) {
    auto pos = this->camera.view;
    mat4 newPos = pos;
    switch (key) {
        case GLFW_KEY_W:
            newPos = glm::translate(pos, vec3(-0.2f, 0.0f, 0.0f));
            break;
        case GLFW_KEY_S:
            newPos = glm::translate(pos, vec3(0.2f, 0.0f, 0.0));
            break;
        case GLFW_KEY_D:
            newPos = glm::translate(pos, vec3(0.0f, 0.0f, -0.2f));
            break;
        case GLFW_KEY_A:
            newPos = glm::translate(pos, vec3(0.0f, 0.0f, 0.2f));
            break;
        case GLFW_KEY_R:
            newPos = glm::translate(pos, vec3(0.0f, -0.2f, 0.0f));
            break;
        case GLFW_KEY_F:
            newPos = glm::translate(pos, vec3(0.0f, 0.2f, 0.0f));
            break;
    }

    this->camera.view = newPos;

//
//    switch (key) {
//        case GLFW_KEY_W:
//            lightPos += vec3(0.2f, 0.0f, 0.0f);
//            break;
//        case GLFW_KEY_S:
//            lightPos += vec3(-0.2f, 0.0f, 0.0);
//            break;
//        case GLFW_KEY_D:
//            lightPos += vec3(0.0f, 0.0f, 0.2f);
//            break;
//        case GLFW_KEY_A:
//            lightPos += vec3(0.0f, 0.0f, -0.2f);
//            break;
//        case GLFW_KEY_R:
//            lightPos += vec3(0.0f, 0.2f, 0.0f);
//            break;
//        case GLFW_KEY_F:
//            lightPos += vec3(0.0f, -0.2f, 0.0f);
//            break;
//        default:
//            break;
//    }

}

