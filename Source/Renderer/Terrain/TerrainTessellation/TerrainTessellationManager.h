//
// Created by Gilbert Gwizdala on 2019-07-30.
//

#ifndef TERRENRENDERING_TERRAINTESSELLATIONMANAGER_H
#define TERRENRENDERING_TERRAINTESSELLATIONMANAGER_H

#include <glm/glm.hpp>
#include <vector>
#include <utility>

class TerrainTessellationManager {

public:

    TerrainTessellationManager();

private:

    void init();

    std::pair<std::vector<glm::vec3>, std::vector<int>> make_plane() const;

};


#endif //TERRENRENDERING_TERRAINTESSELLATIONMANAGER_H
