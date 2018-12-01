#pragma once
#ifndef TEXTURE_H
#define TEXTURE_H

#include <string>
#include <GL/glew.h>


class Texture
{
public:
	Texture(const std::string& filename);

	void Bind(unsigned int unit);

	virtual ~Texture();
	
private:
	Texture(const Texture& other) {}
	void operator=(const Texture& other) {}

	GLuint m_texture;

protected:
};

#endif // !TEXTURE_H