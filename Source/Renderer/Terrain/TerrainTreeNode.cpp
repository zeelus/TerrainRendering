//
// Created by Gilbert Gwizdala on 2019-03-09.
//

#include "TerrainTreeNode.h"

#include "../../Engine/libs.h"

TerrainTreeNode::TerrainTreeNode(const short level): level(level) {

}

void TerrainTreeNode::setPosition(const glm::vec3 position) {

    this->transform = glm::translate(this->transform, position);

}

const glm::vec3 TerrainTreeNode::getPosition() const
{
	return this->transform[3];
}

void TerrainTreeNode::setScale(const glm::vec3 scale) {
    this->transform = glm::scale(this->transform, scale);
}

void TerrainTreeNode::setScale(const float scale) {
    this->setScale(glm::vec3(scale, scale, scale));
}


