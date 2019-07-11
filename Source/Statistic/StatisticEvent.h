//
// Created by Gilbert Gwizdala on 2019-07-11.
//

#ifndef TERRENRENDERING_STATISTICEVENT_H
#define TERRENRENDERING_STATISTICEVENT_H

#include <ostream>
#include "../Engine/libs.h"

class StatisticEvent {

    double msFr;
    gl::GLint memUsage;

public:
    StatisticEvent(double msFr, gl::GLint memUsage);

    friend std::ostream &operator<<(std::ostream &os, const StatisticEvent &event);

};


#endif //TERRENRENDERING_STATISTICEVENT_H
