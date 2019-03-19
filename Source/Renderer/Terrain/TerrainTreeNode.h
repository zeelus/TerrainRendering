//
// Created by Gilbert Gwizdala on 2019-03-09.
//

#ifndef TERRENRENDERING_TERRAINTREENODE_H
#define TERRENRENDERING_TERRAINTREENODE_H

#include <glm/glm.hpp>
#include <array>

class TerrainTreeNode {

public:

    const short level;

    const int parentIndex;

    std::array<int, 4u> childIndexs = {-1, -1, -1, -1};

    TerrainTreeNode(const short level, const int parentIndex);

    glm::mat4 transform = glm::mat4(1.0f);

    void setPosition(const glm::vec3 position);

	const glm::vec3 getPosition() const;

};


#endif //TERRENRENDERING_TERRAINTREENODE_H
