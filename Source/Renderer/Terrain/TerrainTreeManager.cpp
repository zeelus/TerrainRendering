//
// Created by Gilbert Gwizdala on 2019-03-09.
//

#include "TerrainTreeManager.h"
#include "TerrainTreeNode.h"

#include <vector>
#include <string>
#include <glm/glm.hpp>
#include "../../Engine/ResourceManager.h"

TerrainTreeManager::TerrainTreeManager(const short levels, const short maxSize): 
	levels(levels), 
	maxSize(maxSize)
{
    nodes = buildNodes(levels);
    setNodesPositionAndSizes();
}

void TerrainTreeManager::update(const glm::mat4& cameraPos)
{
	const glm::vec3 cameraPosVec3 = glm::vec3(cameraPos[3]) * glm::vec3(-1.0f, -1.0f, -1.0f);
	
	if (!nodes.empty()) {
		checkNodeVisibility(0, cameraPosVec3);
	}

}

void TerrainTreeManager::setGeomentryIndex(const int index)
{
	this->geometryIndex = index;
}

int TerrainTreeManager::getGeometryIndex() const
{
	return geometryIndex;
}

std::vector<TerrainTreeNode> TerrainTreeManager::buildNodes(const short levels) {

    std::vector<TerrainTreeNode> nodes;

	int nextElementBaseIndex = 0;

	auto& rootNode = nodes.emplace_back(0);
	rootNode.firstChildIndexs = 1;

	for (int level = 1; level < levels; level++) {

		const int elements = static_cast<int>(pow(4, level));

		const int elementsInArray = nodes.size();

		for(int j = 0; j < elements; j++) {
          auto& newNode = nodes.emplace_back(level);

		  if ((level + 1) < levels) {
			  const int offset = (nodes.size() - 1) - elementsInArray;
			  const int childNodeIndex = elementsInArray + elements + (offset * 4);
			  newNode.firstChildIndexs = childNodeIndex;
		  }
		}
	}

    return nodes;
}

void TerrainTreeManager::setNodesPositionAndSizes() {

    if(this->nodes.empty()) {
        return;
    }

    glm::vec3 rootPosition(0.0f, 0.0f, 0.0f);

    setNodesPositionAndSizes(0, rootPosition);

}

void TerrainTreeManager::setNodesPositionAndSizes(const unsigned int nodeIndex, const glm::vec3 position) {

    auto& node = this->nodes[nodeIndex];

    const int sizeFactor = this->maxSize / (pow(2,node.level));
    const int childSizeFactor = sizeFactor / 2;

    node.setPosition(position);

	for (int i = 0; i < 4; i++) {
		if (node.firstChildIndexs != -1) {
			const glm::vec3 childPosition = position + glm::vec3(((i % 2)? -1 : 1) * childSizeFactor, 0.0f, ((i < 2) ? -1 : 1) * childSizeFactor);
			setNodesPositionAndSizes(node.firstChildIndexs + i, childPosition);
		}
	}
}

void TerrainTreeManager::checkNodeVisibility(const int nodeIndex, const glm::vec3& cameraPosVec3)
{
	auto& node = this->nodes[nodeIndex];
	
	const glm::vec3 nodePos = node.transform[3];
	const float distance = glm::distance(cameraPosVec3, nodePos);

	if (distance < (maxDistance / (node.level + 1))) {
		node.isShowing = false;

		for (int i = 0; i < 4; i++) {
			if (node.firstChildIndexs != -1) {
				checkNodeVisibility(node.firstChildIndexs + i, cameraPosVec3);
			}
			else {
				node.isShowing = true;
			}
		}
	}
	else {
		node.isShowing = true;
		for (int i = 0; i < 4; i++) {
			if (node.firstChildIndexs != -1) {
				hideNodeWithChildrens(node.firstChildIndexs + i);
			}
		}
	}
}

void TerrainTreeManager::hideNodeWithChildrens(const int nodeIndex)
{
	auto& node = nodes[nodeIndex];
	node.isShowing = false;

	if (node.firstChildIndexs != -1) {
		for (int i = 0; i < 4; i++) {
			hideNodeWithChildrens(node.firstChildIndexs + i);
		}
	}
	
}
