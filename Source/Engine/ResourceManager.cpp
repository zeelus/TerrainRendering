//
// Created by Gilbert Gwizdala on 2019-01-31.
//
#include <glbinding/gl/gl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <glm/glm.hpp>
#include <boost/algorithm/string.hpp>
#include <exception>
#include <optional>

#include "ResourceManager.h"
#include "../Renderer/Shader.h"

using namespace std;

ResourceManager::ResourceManager() { }

optional<Geometry> ResourceManager::loadOBJModel(const std::string& path, const TechniqueType techniqueType) {

    vector<glm::vec3> vertices;
    vector<glm::vec3> normals;
    vector<glm::vec3> faceNormals;
    vector<GLushort> elements;
    vector<GLushort> elementsNormals;

    ifstream file(path);

    if(!file.is_open()) {
        return {};
    }

    string line;
    while (getline(file, line)) {
        if (line.substr(0, 2) == "v ") {

            istringstream lineString(line.substr(2));
            glm::vec3 v;
            lineString >> v.x;
            lineString >> v.y;
            lineString >> v.z;
            vertices.push_back(v);

        } else if(line.substr(0, 3) == "vn " ) {

            istringstream lineString(line.substr(3));
            glm::vec3 n;
            lineString >> n.x;
            lineString >> n.y;
            lineString >> n.z;
            faceNormals.push_back(n);

        } else if (line.substr(0, 2) == "f ") {

            auto newLine = line.substr(2);
            vector<string> strs;
            std::vector<std::string> elementsString;
            boost::algorithm::split(elementsString, newLine, boost::is_any_of(" "));

            for (auto &element: elementsString) {
                if (element.empty()) continue;

                std::vector<std::string> partString;
                boost::algorithm::split(partString, element, boost::is_any_of("/"));

                GLushort e, p, n = 0;

                if(!partString[0].empty()) {
                    e = std::stoi(partString[0]);
                }

                if(!partString[1].empty()) {
                    p = std::stoi(partString[1]);
                }

                if(!partString[2].empty()) {
                    n = std::stoi(partString[2]);
                }

                elements.push_back(--e);
                elementsNormals.push_back(--n);
            }

        }
    }

    normals.resize(vertices.size());

    for(int i = 0; i < elements.size(); i++) {
        normals[elements[i]] += faceNormals[elementsNormals[i]];
    }

    file.close();

    vector<glm::vec3> vboData;
    for(int i = 0; i < vertices.size(); i++) {
		vboData.push_back(vertices[i]);
		vboData.push_back(normals[i]);
    }

    gl::GLuint vao = 0;
	gl::glGenVertexArrays(1, &vao);
	gl::glBindVertexArray(vao);

		gl::GLuint vbo = 0;
		gl::glGenBuffers(1, &vbo);
		gl::glEnableVertexAttribArray(vertex_position_location);
		gl::glBindBuffer(GL_ARRAY_BUFFER, vbo);
		gl::glBufferData(GL_ARRAY_BUFFER, vboData.size() * sizeof(glm::vec3), vboData.data(), GL_STATIC_DRAW);
		gl::glVertexAttribPointer(vertex_position_location, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), nullptr);

		gl::glEnableVertexAttribArray(vertex_normal_location);
		gl::glVertexAttribPointer(vertex_normal_location, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), reinterpret_cast<void*>(3 * sizeof(GLfloat)));

		gl::GLuint index_buffer = 0;
		gl::glGenBuffers(1, &index_buffer);
		gl::glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer);
		gl::glBufferData(GL_ELEMENT_ARRAY_BUFFER, elements.size() * sizeof(GLushort), elements.data(), GL_STATIC_DRAW);

	gl::glBindVertexArray(0u);

	gl::glBindBuffer(GL_ARRAY_BUFFER, 0u);
	gl::glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0u);

    return Geometry(vao, vbo, index_buffer, static_cast<unsigned int>(elements.size()), getIndexTechnique(techniqueType), RenderingType::Triangles);
}

gl::GLuint ResourceManager::loadTexFromFileAndCreateTO(const std::string & file_path) {

	gli::texture texture = gli::load(file_path);

	if (texture.empty())
		return 0u;

	gli::gl GL(gli::gl::PROFILE_GL33);
	gli::gl::format const format = GL.translate(texture.format(), texture.swizzles());
	gl::GLenum target = static_cast<gl::GLenum>(GL.translate(texture.target()));

	gl::GLuint texture_handle = 0u;
	gl::glGenTextures(1, &texture_handle);
	gl::glBindTexture(target, texture_handle);
	glTexParameteri(target, gl::GL_TEXTURE_BASE_LEVEL, 0);
	glTexParameteri(target, gl::GL_TEXTURE_MAX_LEVEL, static_cast<gl::GLint>(texture.levels() - 1));
	glTexParameteri(target, gl::GL_TEXTURE_SWIZZLE_R, format.Swizzles[0]);
	glTexParameteri(target, gl::GL_TEXTURE_SWIZZLE_G, format.Swizzles[1]);
	glTexParameteri(target, gl::GL_TEXTURE_SWIZZLE_B, format.Swizzles[2]);
	glTexParameteri(target, gl::GL_TEXTURE_SWIZZLE_A, format.Swizzles[3]);

	glm::tvec3<gl::GLsizei> const extent(texture.extent());
	gl::GLsizei const face_total = static_cast<gl::GLsizei>(texture.layers() * texture.faces());

	switch (texture.target())
	{
	case gli::TARGET_1D:
		gl::glTexStorage1D(
			target, static_cast<gl::GLint>(texture.levels()), static_cast<gl::GLenum>(format.Internal), extent.x);
		break;
	case gli::TARGET_1D_ARRAY:
	case gli::TARGET_2D:
	case gli::TARGET_CUBE:
		gl::glTexStorage2D(
			target, static_cast<gl::GLint>(texture.levels()), static_cast<gl::GLenum>(format.Internal),
			extent.x, texture.target() == gli::TARGET_2D ? extent.y : face_total);
		break;
	case gli::TARGET_2D_ARRAY:
	case gli::TARGET_3D:
	case gli::TARGET_CUBE_ARRAY:
		gl::glTexStorage3D(
			target, static_cast<gl::GLint>(texture.levels()), static_cast<gl::GLenum>(format.Internal),
			extent.x, extent.y,
			texture.target() == gli::TARGET_3D ? extent.z : face_total);
		break;
	default:
		assert(0);
		break;
	}

	for (std::size_t layer = 0; layer < texture.layers(); ++layer)
		for (std::size_t face = 0; face < texture.faces(); ++face)
			for (std::size_t level = 0; level < texture.levels(); ++level)
			{
				gl::GLsizei const layer_GL = static_cast<gl::GLsizei>(layer);
				glm::tvec3<gl::GLsizei> extent(texture.extent(level));
				target = gli::is_target_cube(texture.target())
					? static_cast<gl::GLenum>(gl::GL_TEXTURE_CUBE_MAP_POSITIVE_X + face)
					: target;

				switch (texture.target())
				{
				case gli::TARGET_1D:
					if (gli::is_compressed(texture.format()))
						gl::glCompressedTexSubImage1D(
							target, static_cast<gl::GLint>(level), 0, extent.x,
							static_cast<gl::GLenum>(format.Internal), static_cast<gl::GLsizei>(texture.size(level)),
							texture.data(layer, face, level));
					else
						gl::glTexSubImage1D(
							target, static_cast<gl::GLint>(level), 0, extent.x,
							static_cast<gl::GLenum>(format.External), static_cast<gl::GLenum>(format.Type),
							texture.data(layer, face, level));
					break;
				case gli::TARGET_1D_ARRAY:
				case gli::TARGET_2D:
				case gli::TARGET_CUBE:
					if (gli::is_compressed(texture.format()))
						gl::glCompressedTexSubImage2D(
							target, static_cast<gl::GLint>(level),
							0, 0,
							extent.x,
							texture.target() == gli::TARGET_1D_ARRAY ? layer_GL : extent.y,
							static_cast<gl::GLenum>(format.Internal), static_cast<gl::GLsizei>(texture.size(level)),
							texture.data(layer, face, level));
					else
						gl::glTexSubImage2D(
							target, static_cast<gl::GLint>(level),
							0, 0,
							extent.x,
							texture.target() == gli::TARGET_1D_ARRAY ? layer_GL : extent.y,
							static_cast<gl::GLenum>(format.External), static_cast<gl::GLenum>(format.Type),
							texture.data(layer, face, level));
					break;
				case gli::TARGET_2D_ARRAY:
				case gli::TARGET_3D:
				case gli::TARGET_CUBE_ARRAY:
					if (gli::is_compressed(texture.format()))
						gl::glCompressedTexSubImage3D(
							target, static_cast<gl::GLint>(level),
							0, 0, 0,
							extent.x, extent.y,
							texture.target() == gli::TARGET_3D ? extent.z : layer_GL,
							static_cast<gl::GLenum>(format.Internal), static_cast<gl::GLsizei>(texture.size(level)),
							texture.data(layer, face, level));
					else
						gl::glTexSubImage3D(
							target, static_cast<gl::GLint>(level),
							0, 0, 0,
							extent.x, extent.y,
							texture.target() == gli::TARGET_3D ? extent.z : layer_GL,
							static_cast<gl::GLenum>(format.External), static_cast<gl::GLenum>(format.Type),
							texture.data(layer, face, level));
					break;
				default: assert(0); break;
				}
			}
	return texture_handle;
}

const int ResourceManager::loadModel(const std::string &path, const TechniqueType techniqueType) {
    int index = -1;
    auto modelIndexInVector = modelIndexs.find(path);
    if(modelIndexInVector == modelIndexs.end()) {

        optional<Geometry> modelMashOpt = loadOBJModel(path, techniqueType);
        if(modelMashOpt) {
            Geometry modelMash = *modelMashOpt;
            loadsModel.push_back(modelMash);
            index = static_cast<int>(loadsModel.size() - 1);
            modelIndexs[path] = index;
        }

    } else {
        index = modelIndexInVector->second;
    }

    return index;
}

const int ResourceManager::loadTexture(const std::string & path)
{
    int index = -1;
    auto modelTextureInVector = textureIndexs.find(path);

    if(modelTextureInVector == textureIndexs.end()) {
        gl::GLuint texture_handler = loadTexFromFileAndCreateTO(path);
        loadsTexture.emplace_back(texture_handler);
        index = static_cast<int>(loadsTexture.size() - 1);
        textureIndexs[path] = index;
    } else {
        index = modelTextureInVector->second;
    }

	return index;
}


ResourceManager* ResourceManager::instance = nullptr;

ResourceManager *ResourceManager::getInstance() {
    if(ResourceManager::instance == nullptr) {
        ResourceManager::instance = new ResourceManager();
        ResourceManager::instance->loadTechniques();
    }

    return ResourceManager::instance;
}

void ResourceManager::loadTechniques() {
    {
        Shader vertex(VertexShader, "Resources/Shaders/VertexShader.vert");
        Shader fragment(FragmentShader, "Resources/Shaders/FragmentShader.frag");
        this->loadsTechnique.emplace_back(vertex, fragment);
    }

    {
        Shader vertex(VertexShader, "Resources/Shaders/TerrainVertexShader.vert");
		Shader geometry(GeometryShader, "Resources/Shaders/TerrainGeometryShader.geom");
        Shader fragment(FragmentShader, "Resources/Shaders/TerrainFragmentShader.frag");
		this->loadsTechnique.emplace_back(vertex, fragment, geometry);
    }

    {
        Shader vertex(VertexShader, "Resources/Shaders/TerrainTessellationVertexShader.vert");
        Shader tesControl(TessellationControlShader, "Resources/Shaders/TerrainTessellationControlShader.tesc");
        Shader tesEval(TessellationEvalShader, "Resources/Shaders/TerrainTessellationEvalShader.tese");
        Shader geometry(GeometryShader, "Resources/Shaders/TerrainGeometryShader.geom");
        Shader fragment(FragmentShader, "Resources/Shaders/TerrainFragmentShader.frag");
        this->loadsTechnique.emplace_back(vertex, fragment, geometry, tesControl, tesEval);
    }
}

const Technique& ResourceManager::loadTechnique(const unsigned int index) const {
    return this->loadsTechnique[index];
}

const Geometry& ResourceManager::getGeometry(const unsigned int index) const {
    return loadsModel[index];
}

const Texture & ResourceManager::getTexture(const unsigned int index) const
{
	return this->loadsTexture[index];
}

constexpr short ResourceManager::getIndexTechnique(TechniqueType techniqueType) {
    switch (techniqueType) {
        case TechniqueType::PhongBline:
            return 0;
        case TechniqueType::TerrainPhongBline:
            return 1;
        case TechniqueType::TerrainTessellation:
            return 2;
        default:
            return -1;
    }
}


