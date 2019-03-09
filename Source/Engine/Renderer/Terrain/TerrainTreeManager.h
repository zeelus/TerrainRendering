//
// Created by Gilbert Gwizdala on 2019-03-09.
//

#ifndef TERRENRENDERING_TERRAINTREEMANAGER_H
#define TERRENRENDERING_TERRAINTREEMANAGER_H

#include <vector>
#include "TerrainTreeNode.h"

class TerrainTreeManager {

    const short levels;

    std::vector<TerrainTreeNode> nodes;

    std::vector<TerrainTreeNode> buildNodes(const short levels);

public:

    TerrainTreeManager(const short levels);

};


#endif //TERRENRENDERING_TERRAINTREEMANAGER_H
