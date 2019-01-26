//
// Created by Gilbert Gwizdala on 2019-01-26.
//

#ifndef TERRENRENDERING_ABSTACTSCENE_H
#define TERRENRENDERING_ABSTACTSCENE_H

#include "GameElement.h"
#include <entt/entity/registry.hpp>
#include <string>
#include <vector>

class AbstractScene {

    std::vector<GameElement> gameelements;



public:
    void virtual createScene() = 0;

protected:
    GameElement& createGameElement(const std::string& name);
};


#endif //TERRENRENDERING_ABSTACTSCENE_H
