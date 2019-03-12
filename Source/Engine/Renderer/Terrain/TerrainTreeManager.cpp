//
// Created by Gilbert Gwizdala on 2019-03-09.
//

#include "TerrainTreeManager.h"
#include "TerrainTreeNode.h"

#include <vector>
#include <glm/glm.hpp>

TerrainTreeManager::TerrainTreeManager(const short levels, const short maxSize): levels(levels), maxSize(maxSize) {
    nodes = buildNodes(levels);
    setNodesPositionAndSizes();
}

std::vector<TerrainTreeNode> TerrainTreeManager::buildNodes(const short levels) {

    std::vector<TerrainTreeNode> nodes;

    int nextElementBaseIndex = 0;

    for(int level = (levels - 1); level >= 0; level--) {

        int elements = static_cast<int>(pow(4, level));
        nextElementBaseIndex += elements;

        int offset = nodes.size();

        if(elements == 1) {
            nodes.emplace_back(level, -1);
            continue;
        }

        for(int j = 0; j < elements; j++) {

            int nodeIndex = nodes.size();

            int parentIndex = nextElementBaseIndex + ((nodeIndex - offset) / 4);

            nodes.emplace_back(level, parentIndex);
        }
    }


    for(int z = 0; z < nodes.size(); z += 4 ) {
        auto& parentNode = nodes[nodes[z].parentIndex];
        parentNode.childIndexs[0] = z;
        parentNode.childIndexs[1] = z + 1;
        parentNode.childIndexs[2] = z + 2;
        parentNode.childIndexs[3] = z + 3;
    }


    return nodes;
}

void TerrainTreeManager::setNodesPositionAndSizes() {

    if(this->nodes.empty()) {
        return;
    }

    const unsigned int rootNodeIndex = this->nodes.size() - 1;

    glm::vec3 rootPosition(0.0f, 0.0f, 0.0f);

    setNodesPositionAndSizes(rootNodeIndex, rootPosition);

}

void TerrainTreeManager::setNodesPositionAndSizes(const unsigned int nodeIndex, const glm::vec3 position) {

    auto& node = this->nodes[nodeIndex];

    const int sizeFactor = this->maxSize / (pow(2,node.level));
    const int childSizeFactor = sizeFactor / 2;

    node.setPosition(position);

    if(node.childIndexs[0] != -1) {
        const glm::vec3 childPosition = position + glm::vec3(-childSizeFactor, 0.0f, -childSizeFactor);
        setNodesPositionAndSizes(node.childIndexs[0], childPosition);
    }

    if(node.childIndexs[1] != -1) {
        const glm::vec3 childPosition = position + glm::vec3(childSizeFactor, 0.0f, -childSizeFactor);
        setNodesPositionAndSizes(node.childIndexs[1], childPosition);
    }

    if(node.childIndexs[2] != -1) {
        const glm::vec3 childPosition = position + glm::vec3(-childSizeFactor, 0.0f, childSizeFactor);
        setNodesPositionAndSizes(node.childIndexs[2], childPosition);
    }

    if(node.childIndexs[3] != -1) {
        const glm::vec3 childPosition = position + glm::vec3(childSizeFactor, 0.0f, childSizeFactor);
        setNodesPositionAndSizes(node.childIndexs[3], childPosition);
    }


}
