//
// Created by Gilbert Gwizdala on 2019-03-09.
//

#include "TerrainTreeNode.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

TerrainTreeNode::TerrainTreeNode(const short level, const int parentIndex): level(level), parentIndex(parentIndex) {

}

void TerrainTreeNode::setPosition(const glm::vec3 position) {

    this->transform = glm::translate(this->transform, position);

}


