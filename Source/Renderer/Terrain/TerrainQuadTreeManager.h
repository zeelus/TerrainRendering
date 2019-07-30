//
// Created by Gilbert Gwizdala on 2019-03-09.
//

#ifndef TERRENRENDERING_TERRAINQUADTREEMANAGER_H
#define TERRENRENDERING_TERRAINQUADTREEMANAGER_H

#include <vector>
#include <string>
#include <glm/glm.hpp>

#include "../Renderer.h"

#include "TerrainTreeNode.h"

class TerrainQuadTreeManager {

    const short levels;
    const short maxSize;
	const short maxDistance = 50;
	const float terrenScale;

	gl::GLuint ubo_terrain_handle;

	int geometryIndex = -1;
	int heightMapIndex = -1;

    std::vector<TerrainTreeNode> buildNodes(const short levels);

    void setNodesPositionAndSizes();
    void setNodesPositionAndSizes(const unsigned int nodeIndex, const glm::vec3 position);
	void checkNodeVisibility(const int nodeIndex, const glm::vec3& cameraPosVec3);
	void hideNodeWithChildrens(const int nodeIndex);

public:
    std::vector<TerrainTreeNode> nodes;

    TerrainQuadTreeManager(const float terrenScale, const short levels, const short maxSize);

	void update(const glm::mat4& cameraPos);

	void setGeomentryIndex(const int index);

	void setHeightMapIndex(const int index);

	const int getGeometryIndex() const;

	const int getHeightMapTextureIndex() const;

	void initTerrenVBO();

	const gl::GLuint getTerrain_handle_ubo() const;

};


#endif //TERRENRENDERING_TERRAINQUADTREEMANAGER_H
