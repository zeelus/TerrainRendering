//
// Created by Gilbert Gwizdala on 2019-03-09.
//

#ifndef TERRENRENDERING_TERRAINTREEMANAGER_H
#define TERRENRENDERING_TERRAINTREEMANAGER_H

#include <vector>
#include <glm/glm.hpp>

#include "TerrainTreeNode.h"

class TerrainTreeManager {

private:
    const short levels;
    const short maxSize;
	const short maxDistance = 50;

    std::vector<TerrainTreeNode> buildNodes(const short levels);

    void setNodesPositionAndSizes();
    void setNodesPositionAndSizes(const unsigned int nodeIndex, const glm::vec3 position);
	void checkNodeVisibility(const int nodeIndex, const glm::vec3& cameraPosVec3);
	void hideNodeWithChildrens(const int nodeIndex);

public:
    std::vector<TerrainTreeNode> nodes;

    TerrainTreeManager(const short levels, const short maxSize);

	void update(const glm::mat4& cameraPos);

};


#endif //TERRENRENDERING_TERRAINTREEMANAGER_H
