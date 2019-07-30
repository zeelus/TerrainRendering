//
// Created by Gilbert Gwizdala on 2019-03-06.
//

#ifndef TERRENRENDERING_RENDERINGQUEUE_H
#define TERRENRENDERING_RENDERINGQUEUE_H

#include "StaticModel.h"
#include "Terrain/TerrainQuadTreeManager.h"

class RenderingQueue {

    std::vector<StaticModel> staticModels;

public:

    std::unique_ptr<TerrainQuadTreeManager> terrainTreeManager;

    const std::vector<StaticModel> &getStaticModels() const;

    StaticModel& addStaticModel(const int modelIndex);

    void addTerrainTreeManager(TerrainQuadTreeManager* terrainTreeManager);

};


#endif //TERRENRENDERING_RENDERINGQUEUE_H
