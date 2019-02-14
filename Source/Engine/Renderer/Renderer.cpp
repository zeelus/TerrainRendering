//
// Created by Gilbert Gwizdala on 2018-12-25.
//

#include "Renderer.h"

#include <string>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include "Shader.h"
#include "../ResourceManager.h"

Renderer::Renderer(): lightPos(-8.0f, 4.0f, 0.0f) {

}

void Renderer::init() {

    glGenVertexArrays(1, &vao);

    glGenBuffers(1, &ubo_matrix_handle);
    glBindBuffer(GL_UNIFORM_BUFFER, ubo_matrix_handle);
    glBufferData(GL_UNIFORM_BUFFER, 3 * sizeof(glm::mat4), nullptr, GL_DYNAMIC_DRAW);
    glBindBuffer(GL_UNIFORM_BUFFER, 0);

    glGenBuffers(1, &ubo_light_handle);
    glBindBuffer(GL_UNIFORM_BUFFER, ubo_light_handle);
    glBufferData(GL_UNIFORM_BUFFER, 2 * sizeof(glm::vec4), nullptr, GL_DYNAMIC_DRAW);
    glBindBuffer(GL_UNIFORM_BUFFER, 0);

    resourceManager = ResourceManager::getInstance();
}

void Renderer::draw() {
    drawStaticModels();
}

void Renderer::drawStaticModels() {
    auto* technique = ResourceManager::getInstance()->loadTechnique("phongBline");
    auto shader_programme = technique->getShader_programme();

    glUseProgram(shader_programme);

    unsigned int uniformMatricesBlockIndex = glGetUniformBlockIndex(shader_programme, "Matrices");
    unsigned int uniformPointLightIndex = glGetUniformBlockIndex(shader_programme, "PointLight");

    glUniformBlockBinding(shader_programme, uniformPointLightIndex, pointLight);
    glBindBufferBase(GL_UNIFORM_BUFFER, pointLight, ubo_light_handle);
    glBindBuffer(GL_UNIFORM_BUFFER, ubo_light_handle);
    std::array<glm::vec4, 2u> light = {glm::vec4(lightPos.x, lightPos.y, lightPos.z, 0.0f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f)};
    if(void *result = glMapBuffer(GL_UNIFORM_BUFFER, GL_WRITE_ONLY)) {
        std::memcpy(result, light.data(), 2 * sizeof(glm::vec4));
        glUnmapBuffer(GL_UNIFORM_BUFFER);
    }
    glBindBuffer(GL_UNIFORM_BUFFER, 0);

    for(auto& model: staticModels) {

        int index = model.getIndexMashPtr();
        if(index < 0) continue;
        auto& geometry = resourceManager->getGeometry(index);

        glUniformBlockBinding(shader_programme, uniformMatricesBlockIndex, matricesBlockBinding);
        glBindBufferBase(GL_UNIFORM_BUFFER, matricesBlockBinding, ubo_matrix_handle);
        glBindBuffer(GL_UNIFORM_BUFFER, ubo_matrix_handle);
        std::array<glm::mat4, 3u> matrices = { model.getTransform(), camera.view, camera.project};
        if(void *result = glMapBuffer(GL_UNIFORM_BUFFER, GL_WRITE_ONLY)) {
            std::memcpy(result, matrices.data(), sizeof(glm::mat4) * 3);
            glUnmapBuffer(GL_UNIFORM_BUFFER);
        }
        glBindBuffer(GL_UNIFORM_BUFFER, 0u);

        glBindVertexArray(geometry.vao);

        glDrawElements(GL_TRIANGLES, geometry.elementsSize * sizeof(GLushort), GL_UNSIGNED_SHORT, nullptr);

        glBindVertexArray(0u);
    }
}


Renderer::~Renderer() { }

void Renderer::key_callback_static(GLFWwindow *window, int key, int scancode, int action, int mods) {
    auto rendererSystem = reinterpret_cast<Renderer*>(glfwGetWindowUserPointer(window));
    rendererSystem->key_callback(window, key, scancode, action, mods);
}

void Renderer::key_callback(GLFWwindow *window, int key, int scancode, int action, int mods) {
//    auto pos = camera.view;
//    mat4 newPos = pos;
//    switch (key) {
//        case GLFW_KEY_W:
//            newPos = glm::translate(pos, vec3(-0.2f, 0.0f, 0.0f));
//            break;
//        case GLFW_KEY_S:
//            newPos = glm::translate(pos, vec3(0.2f, 0.0f, 0.0));
//            break;
//        case GLFW_KEY_D:
//            newPos = glm::translate(pos, vec3(0.0f, 0.0f, -0.2f));
//            break;
//        case GLFW_KEY_A:
//            newPos = glm::translate(pos, vec3(0.0f, 0.0f, 0.2f));
//            break;
//        case GLFW_KEY_R:
//            newPos = glm::translate(pos, vec3(0.0f, -0.2f, 0.0f));
//            break;
//        case GLFW_KEY_F:
//            newPos = glm::translate(pos, vec3(0.0f, 0.2f, 0.0f));
//            break;
//    }

//    camera.view = newPos;

    switch (key) {
        case GLFW_KEY_W:
            lightPos += vec3(0.2f, 0.0f, 0.0f);
            break;
        case GLFW_KEY_S:
            lightPos += vec3(-0.2f, 0.0f, 0.0);
            break;
        case GLFW_KEY_D:
            lightPos += vec3(0.0f, 0.0f, 0.2f);
            break;
        case GLFW_KEY_A:
            lightPos += vec3(0.0f, 0.0f, -0.2f);
            break;
        case GLFW_KEY_R:
            lightPos += vec3(0.0f, 0.2f, 0.0f);
            break;
        case GLFW_KEY_F:
            lightPos += vec3(0.0f, -0.2f, 0.0f);
            break;
        default:
            break;
    }

}

