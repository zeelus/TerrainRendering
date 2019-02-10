//
// Created by Gilbert Gwizdala on 2019-02-03.
//

#include "StaticModel.h"
#include <glm/gtc/matrix_transform.hpp>

StaticModel::StaticModel(MashPtr *mashPtr): mashPtr(mashPtr) {
}

MashPtr *StaticModel::getMashPtr() const {
    return mashPtr;
}

const glm::mat4 &StaticModel::getTransform() const {
    return transform;
}

void StaticModel::setTransform(const glm::mat4 &transform) {
    StaticModel::transform = transform;
}

void StaticModel::setPosition(const glm::vec3 &position) {
    this->transform = glm::translate(this->transform, position);;
}

const glm::vec3 StaticModel::getPosition() const {
    return glm::vec3(this->transform[3]);
}

void StaticModel::rotate(GLfloat angle, glm::vec3 vector) {
    glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f), angle, vector);
    this->transform = this->transform * rotationMatrix;
}


