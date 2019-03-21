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


