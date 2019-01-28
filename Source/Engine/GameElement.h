//
// Created by Gilbert Gwizdala on 2019-01-26.
//

#ifndef TERRENRENDERING_GAMEELEMENT_H
#define TERRENRENDERING_GAMEELEMENT_H

#include <string>
#include <entt/entity/registry.hpp>
#include <entt/entt.hpp>

class GameElement {
    std::string name;
    entt::registry<>* registryEntt;
    unsigned int entity;
public:
    GameElement(std::string name, entt::registry<>* registryEntt);

    template<typename T> T& createComponent() {
        return registryEntt->assign<T>(entity);
    }
};


#endif //TERRENRENDERING_GAMEELEMENT_H
