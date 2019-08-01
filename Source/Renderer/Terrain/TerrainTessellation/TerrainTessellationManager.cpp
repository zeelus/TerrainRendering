//
// Created by Gilbert Gwizdala on 2019-07-30.
//

#include "TerrainTessellationManager.h"

TerrainTessellationManager::TerrainTessellationManager() {
    this->init();
}

void TerrainTessellationManager::init() {

    std::pair<std::vector<glm::vec3>, std::vector<int>> model = make_plane();


}

std::pair<std::vector<glm::vec3>, std::vector<int>> TerrainTessellationManager::make_plane() const {
    std::vector<glm::vec3> vertecs = {glm::vec3(0,0,0), glm::vec3(1,0,0), glm::vec3(1,1,0), glm::vec3(0,1,0)};
    std::vector<int> elements = {0, 1, 2, 3};

    return std::pair(vertecs, elements);
}
