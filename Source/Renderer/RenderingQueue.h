//
// Created by Gilbert Gwizdala on 2019-03-06.
//

#ifndef TERRENRENDERING_RENDERINGQUEUE_H
#define TERRENRENDERING_RENDERINGQUEUE_H

#include "StaticModel.h"
#include "Terrain/QuadTree/TerrainQuadTreeManager.h"
#include "Terrain/TerrainTessellation/TerrainTessellationManager.h"

class RenderingQueue {

    std::vector<StaticModel> staticModels;

public:

    std::unique_ptr<TerrainQuadTreeManager> terrainQuadTreeManager;
    std::unique_ptr<TerrainTessellationManager> terrainTessellationManager;

    const std::vector<StaticModel> &getStaticModels() const;

    StaticModel& addStaticModel(const int modelIndex);

    void addTerrainQuadTreeManager(TerrainQuadTreeManager *terrainTreeManager);
    void addTerrainTessellationManager(TerrainTessellationManager *terrainTessellationManager);
};


#endif //TERRENRENDERING_RENDERINGQUEUE_H
