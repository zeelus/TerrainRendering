//
// Created by Gilbert Gwizdala on 2019-01-31.
//

#ifndef TERRENRENDERING_TECHNIQUE_HPP
#define TERRENRENDERING_TECHNIQUE_HPP

#include <glbinding/gl/gl.h>
#include "Shader.h"
using namespace gl;

const GLuint MatricesBlockBinding = 0u;
const GLuint PointLightBinding = 1u;
const GLuint TerrainBinding = 2u;
const GLuint TerrainTessellationBinding = 3u;

enum class TechniqueType {
    PhongBline,
    TerrainPhongBline,
    TerrainTessellation,
    SampleTessellation
};

class Technique {

    GLuint shader_programme;

public:

    GLuint getShader_programme() const;

    Technique(Shader vertex, Shader fragment);

	Technique(Shader vertex, Shader fragment, Shader geometry);

    Technique(Shader vertex, Shader fragment, Shader tControl, Shader tEval);

    Technique(Shader vertex, Shader fragment, Shader geometry, Shader tControl, Shader tEval);

};


#endif //TERRENRENDERING_TECHNIQUE_HPP
