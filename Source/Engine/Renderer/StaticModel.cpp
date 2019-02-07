//
// Created by Gilbert Gwizdala on 2019-02-03.
//

#include "StaticModel.h"

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

void StaticModel::setPosition(const glm::vec3 postition) {
    this->transform[3] = glm::vec4(postition, 1.0f);
}

const glm::vec3 StaticModel::getPosition() const {
    return glm::vec3(this->transform[3]);
}


