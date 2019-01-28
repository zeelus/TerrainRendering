//
// Created by Gilbert Gwizdala on 2019-01-26.
//

#include "AbstractScene.h"

GameElement& AbstractScene::createGameElement(const std::string &name) {
    GameElement& ref = this->gameElements.emplace_back(GameElement(name, registryEntt));
    return ref;
}

entt::registry<uint32_t> *AbstractScene::getRegistryEntt() const {
    return registryEntt;
}

void AbstractScene::setRegistryEntt(entt::registry<uint32_t> *registryEntt) {
    AbstractScene::registryEntt = registryEntt;
}
