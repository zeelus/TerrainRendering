//
// Created by Gilbert Gwizdala on 2019-01-31.
//

#ifndef TERRENRENDERING_RESORCEMANAGER_HPP
#define TERRENRENDERING_RESORCEMANAGER_HPP

#include <string>
#include <map>
#include "Renderer/MashPtr.h"
#include "Renderer/StaticModel.h"
#include "Renderer/Technique.h"
#include <optional>

class ResourceManager {

    const GLuint vertex_position_loction = 0u;
    const GLuint vertex_normal_loction = 1u;

    static ResourceManager* instance;

    std::vector<MashPtr> loadsModel;
    std::map<std::string, unsigned int> modelIndexs;

    std::vector<Technique> loadsTechnique;

    std::optional<MashPtr> loadOBJModel(const std::string& path);

    void loadTechniques();

    ResourceManager();

public:

    static ResourceManager* getInstance();

    StaticModel loadModel(const std::string& path);

    Technique& loadTechnique(const unsigned int index);

    MashPtr& getGeometry(const unsigned int index);

    ~ResourceManager();

};


#endif //TERRENRENDERING_RESORCEMANAGER_HPP

