//
// Created by Gilbert Gwizdala on 2019-01-31.
//

#ifndef TERRENRENDERING_TECHNIQUE_HPP
#define TERRENRENDERING_TECHNIQUE_HPP

#include <GL/glew.h>
#include "Shader.h"


class Technique {

    GLuint shader_programme;

public:

    GLuint getShader_programme() const;

    Technique(Shader vertex, Shader fragment);

};


#endif //TERRENRENDERING_TECHNIQUE_HPP
