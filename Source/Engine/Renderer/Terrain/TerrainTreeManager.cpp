//
// Created by Gilbert Gwizdala on 2019-03-09.
//

#include "TerrainTreeManager.h"
#include "TerrainTreeNode.h"

#include <vector>

TerrainTreeManager::TerrainTreeManager(const short levels): levels(levels) {
    nodes = buildNodes(levels);
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
