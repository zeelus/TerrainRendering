//
// Created by Gilbert Gwizdala on 2019-01-31.
//

#ifndef TERRENRENDERING_RESORCEMANAGER_HPP
#define TERRENRENDERING_RESORCEMANAGER_HPP

#include <string>
#include <map>
#include "../Renderer/Geometry.h"
#include "../Renderer/StaticModel.h"
#include "../Renderer/Technique.h"
#include "../Renderer/Texture.h"
#include <optional>
#include <vector>

class ResourceManager {

    const GLuint vertex_position_location = 0u;
    const GLuint vertex_normal_location = 1u;

    static ResourceManager* instance;

    std::vector<Geometry> loadsModel;
    std::map<std::string, int> modelIndexs;

    std::vector<Technique> loadsTechnique;

    std::vector<Texture> loadsTexture;
    std::map<std::string, int> textureIndexs;

    std::optional<Geometry> loadOBJModel(const std::string& path, const TechniqueType techniqueType);

	gl::GLuint loadTexFromFileAndCreateTO(const std::string &file_path);

    constexpr short getIndexTechnique(TechniqueType techniqueType);

    void loadTechniques();

    ResourceManager();

public:

    static ResourceManager* getInstance();

    const int loadModel(const std::string& path, const TechniqueType techniqueType = TechniqueType::PhongBline);

	const int loadTexture(const std::string& path);

    const Technique& loadTechnique(const unsigned int index) const;

    const Geometry& getGeometry(const unsigned int index) const;

	const Texture& getTexture(const unsigned int index) const;

    ~ResourceManager() = default;

};


#endif //TERRENRENDERING_RESORCEMANAGER_HPP

