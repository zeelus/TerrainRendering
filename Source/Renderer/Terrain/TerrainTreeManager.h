//
// Created by Gilbert Gwizdala on 2019-03-09.
//

#ifndef TERRENRENDERING_TERRAINTREEMANAGER_H
#define TERRENRENDERING_TERRAINTREEMANAGER_H

#include <vector>
#include <glm/glm.hpp>

#include "TerrainTreeNode.h"

class TerrainTreeManager {

    const short levels;
    const short maxSize;



    std::vector<TerrainTreeNode> buildNodes(const short levels);

    void setNodesPositionAndSizes();
    void setNodesPositionAndSizes(const unsigned int nodeIndex, const glm::vec3 position);

public:
    std::vector<TerrainTreeNode> nodes;

    TerrainTreeManager(const short levels, const short maxSize);

	void update(const glm::mat4& cameraPos);

};


#endif //TERRENRENDERING_TERRAINTREEMANAGER_H
