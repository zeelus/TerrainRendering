//
// Created by Gilbert Gwizdala on 2019-07-30.
//

#ifndef TERRENRENDERING_TERRAINTESSELLATIONMANAGER_H
#define TERRENRENDERING_TERRAINTESSELLATIONMANAGER_H

#include <glm/glm.hpp>
#include <vector>
#include <utility>
#include "../../StaticModel.h"
#include "../../Renderer.h"

class TerrainTessellationManager {

    StaticModel *staticModel = nullptr;

    const int textureIndex;

public:

    TerrainTessellationManager();

    ~TerrainTessellationManager();

    void drowIn(const Renderer &renderer) const;
private:

    void init();

    std::pair<std::vector<glm::vec3>, std::vector<GLushort>> make_plane(const int dX, const int dZ) const;



};


#endif //TERRENRENDERING_TERRAINTESSELLATIONMANAGER_H
