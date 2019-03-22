//
// Created by Gilbert Gwizdala on 2019-03-06.
//

#ifndef TERRENRENDERING_RENDERINGQUEUE_H
#define TERRENRENDERING_RENDERINGQUEUE_H

#include "StaticModel.h"

class RenderingQueue {

    std::vector<StaticModel> staticModels;

public:

    const std::vector<StaticModel> &getStaticModels() const;

    StaticModel& addStaticModel(const int modelIndex);


};


#endif //TERRENRENDERING_RENDERINGQUEUE_H
