//
// Created by Gilbert Gwizdala on 2019-07-08.
//

#ifndef TERRENRENDERING_STATISTIC_H
#define TERRENRENDERING_STATISTIC_H

#include <deque>
#include <iostream>
#include <fstream>

template<typename T>
class Statistic {

    std::deque<T> deque;

    static Statistic<T>* instance;

    Statistic<T>() {

    }

    const std::string currentDateTime() const {

        time_t     now = time(0);
        struct tm  tstruct;
        char       buf[80];
        tstruct = *localtime(&now);
        strftime(buf, sizeof(buf), "%FT%TZ", &tstruct);

        return std::string(buf);

    }

public:

    void addElement(T&& element) {
        deque.push_back(element);
    }

    static Statistic<T>* shareInstance() {
        if(!instance) {
            instance = new Statistic<T>();
        }
        return instance;
    }

    void createStatistic() {
        for(const T& element: deque) {
            std::cout << element << std::endl;
        }
    }

    void createStatisticFile() const {

        std::string fileNameString = std::string("statistic_") + currentDateTime() + std::string(".csv");
        std::fstream file;
        file.open(fileNameString.c_str(), std::ios::out);
        int num = 0;
        if(file.is_open()) {
            for(const T& element: deque) {
                file << num << "," << element << std::endl;
                num++;
            }
        }

        file.close();
    }



};

template<typename T>
Statistic<T>* Statistic<T>::instance = nullptr;


#endif //TERRENRENDERING_STATISTIC_H
