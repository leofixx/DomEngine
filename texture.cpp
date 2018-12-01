#include "stdafx.h"
#include "texture.h"
#include "stb_image.h"
#include <cassert>

Texture::Texture(const std::string& filename)
{
	int width, height, numComponenets;
	unsigned char* imagedata = stbi_load((filename).c_str(), &width, &height, &numComponenets, 4);

	if (imagedata == NULL)
		std::cerr << "Texture loading failed for texture:" << filename << std::endl;
	
	glGenTextures(1, &m_texture);
	glBindTexture(GL_TEXTURE_2D, m_texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imagedata);
	stbi_image_free(imagedata);


}


Texture::~Texture()
{
	glDeleteTextures(1, &m_texture);
}


void Texture::Bind(unsigned int unit)
{
	assert(unit >= 0 && unit <= 31);

	glActiveTexture(GL_TEXTURE0 + unit);
	glBindTexture(GL_TEXTURE_2D, m_texture);
}