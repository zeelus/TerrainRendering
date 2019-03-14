//
// Created by Gilbert Gwizdala on 2019-02-03.
//

#include "StaticModel.h"
#include <glm/gtc/matrix_transform.hpp>

StaticModel::StaticModel(const int indexMashPtr): indexMashPtr(indexMashPtr) {
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

void StaticModel::scale(const glm::vec3 &scale) {
    this->transform = glm::scale(this->transform, scale);
}

const int StaticModel::getIndexGeometryIndex() const {
    return indexMashPtr;
}

StaticModel &StaticModel::operator=(const StaticModel &&staticModel) noexcept{
    this->indexMashPtr = staticModel.indexMashPtr;
    this->transform = staticModel.transform;
    return *this;
}

StaticModel::StaticModel(const StaticModel &&staticModel) noexcept{
    this->indexMashPtr = staticModel.indexMashPtr;
    this->transform = staticModel.transform;
}

StaticModel::StaticModel(const StaticModel &staticModel) noexcept{
    this->indexMashPtr = staticModel.indexMashPtr;
    this->transform = staticModel.transform;
}

StaticModel &StaticModel::operator=(const StaticModel &staticModel) noexcept{
    this->indexMashPtr = staticModel.indexMashPtr;
    this->transform = staticModel.transform;
    return *this;
}
