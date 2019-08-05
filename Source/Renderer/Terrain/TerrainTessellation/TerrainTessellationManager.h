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

    gl::GLuint ubo_terrain_tessellation_handle;

    float screenWidth;
public:
    TerrainTessellationManager(float screenWidth, float screenHeight, float lodFactor, const int textureIndex);

private:
    float screenHeight;
    float lodFactor;

public:

    TerrainTessellationManager();

    ~TerrainTessellationManager();

    void drowIn(Renderer &renderer) const;
private:

    void init();

    void initUBO();

    std::pair<std::vector<glm::vec3>, std::vector<GLushort>> make_plane(const int dX, const int dZ) const;



};


#endif //TERRENRENDERING_TERRAINTESSELLATIONMANAGER_H
