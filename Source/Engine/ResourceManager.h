//
// Created by Gilbert Gwizdala on 2019-01-31.
//

#ifndef TERRENRENDERING_RESORCEMANAGER_HPP
#define TERRENRENDERING_RESORCEMANAGER_HPP

#include <string>
#include <map>
#include "Renderer/MashPtr.h"
#include "Renderer/StaticModel.h"

class ResourceManager {

    static ResourceManager* instance;

    std::map<std::string, MashPtr*> loadsModel;

    MashPtr* loadOBJModel(const std::string& path);

    ResourceManager();

public:

    static ResourceManager* getInstance();

    StaticModel loadModel(const std::string& path);

    ~ResourceManager();

};


#endif //TERRENRENDERING_RESORCEMANAGER_HPP

