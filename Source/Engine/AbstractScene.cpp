//
// Created by Gilbert Gwizdala on 2019-01-26.
//

#include "AbstractScene.h"

GameElement& AbstractScene::createGameElement(const std::string &name) {
    GameElement& ref = this->gameelements.emplace_back(GameElement(name));
    return ref;
}
