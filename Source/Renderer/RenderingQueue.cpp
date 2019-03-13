//
// Created by Gilbert Gwizdala on 2019-03-06.
//

#include <vector>
#include <algorithm>
#include "RenderingQueue.h"
#include "StaticModel.h"

using namespace std;

const std::vector<StaticModel> &RenderingQueue::getStaticModels() const {
    return staticModels;
}

StaticModel& RenderingQueue::addStaticModel(const StaticModel &staticModel) {
    auto& staticModelOnVector = this->staticModels.emplace_back(move(staticModel));
    sort(this->staticModels.begin(), this->staticModels.end(), [] (const StaticModel& staticModel1, const StaticModel& staticModel2) {
        return staticModel1.getIndexGeometryIndex() < staticModel2.getIndexGeometryIndex();
    });

    return staticModelOnVector;
}
