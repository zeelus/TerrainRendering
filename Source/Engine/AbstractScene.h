//
// Created by Gilbert Gwizdala on 2019-01-26.
//

#ifndef TERRENRENDERING_ABSTACTSCENE_H
#define TERRENRENDERING_ABSTACTSCENE_H

#include "GameElement.h"

#include <entt/entt.hpp>
#include <string>
#include <vector>


class AbstractScene {

    std::vector<GameElement> gameElements;

private:
    entt::registry<> *registryEntt;

public:
    void virtual createScene() = 0;

    entt::registry<> *getRegistryEntt() const;

    void setRegistryEntt(entt::registry<> *registryEntt);

protected:
    GameElement& createGameElement(const std::string& name);
};


#endif //TERRENRENDERING_ABSTACTSCENE_H
