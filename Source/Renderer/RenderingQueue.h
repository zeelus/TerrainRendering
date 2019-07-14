//
// Created by Gilbert Gwizdala on 2019-03-06.
//

#ifndef TERRENRENDERING_RENDERINGQUEUE_H
#define TERRENRENDERING_RENDERINGQUEUE_H

#include "StaticModel.h"
#include "Terrain/TerrainTreeManager.h"

class RenderingQueue {

    std::vector<StaticModel> staticModels;

public:

    std::unique_ptr<TerrainTreeManager> terrainTreeManager;

    const std::vector<StaticModel> &getStaticModels() const;

    StaticModel& addStaticModel(const int modelIndex);

    void addTerrainTreeManager(TerrainTreeManager* terrainTreeManager);

};


#endif //TERRENRENDERING_RENDERINGQUEUE_H
