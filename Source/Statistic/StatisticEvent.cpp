//
// Created by Gilbert Gwizdala on 2019-07-11.
//

#include "StatisticEvent.h"

StatisticEvent::StatisticEvent(double msFr, gl::GLint memUsage) : msFr(msFr), memUsage(memUsage) {

}

std::ostream &operator<<(std::ostream &os, const StatisticEvent &event) {
    os << "msFr: " << event.msFr << " memUsage: " << event.memUsage;
    return os;
}
