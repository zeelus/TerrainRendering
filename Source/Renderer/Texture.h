//
// Created by Gilbert Gwizdala on 18.04.2019.
//

#ifndef TERRENRENDERING_TEXTURE_H
#define TERRENRENDERING_TEXTURE_H

#include "../Engine/libs.h"

class Texture {

    const gl::GLuint texture_handler;

public:

    Texture(gl::GLuint texture_handler);

	const gl::GLuint getTextureHandler() const;

};


#endif //TERRENRENDERING_TEXTURE_H
