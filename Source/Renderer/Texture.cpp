//
// Created by Gilbert Gwizdala on 18.04.2019.
//

#include "Texture.h"
#include "../Engine/libs.h"

Texture::Texture(gl::GLuint texture_handler): texture_handler(texture_handler) {

}

const gl::GLuint Texture::getTextureHandler() const {
	return this->texture_handler;
}
