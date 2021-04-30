#pragma once
#include "glad/glad.h"
#include "stb_image.h"
#include <iostream>
#include "Shader.h"
#include "Window.h"

class Texture
{
public:
	Texture(const char* path, bool genMipMaps);
	void Reload(const char* path);
	~Texture();

	const unsigned int& Data() { return texture; }
private:
	unsigned int texture;
};

