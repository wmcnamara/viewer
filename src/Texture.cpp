#include "Texture.h"

Texture::Texture(const char* path, bool genMipMaps)
{
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	// set the texture wrapping/filtering options (on the currently bound texture object)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

	// load and generate the texture
	int width, height, nrChannels;

	unsigned char *data = stbi_load(path, &width, &height, &nrChannels, 4);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);

		if (genMipMaps)
			glGenerateMipmap(GL_TEXTURE_2D);

		//Debug logging
		std::stringstream output;
		output << "TEXTURE: "<< path << " successfully loaded!" << std::endl;

		Debug::Log(output);
	}
	else
	{
		std::stringstream output;
		output << "Failed to load texture from " << path << "\n";
		Debug::Log(output);
	}
	stbi_image_free(data);
}

void Texture::Reload(const char * path)
{
	glDeleteTextures(1, &texture); //Delete old memory

	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	// set the texture wrapping/filtering options (on the currently bound texture object)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

	// load and generate the texture
	int width, height, nrChannels;

	std::stringstream output;

	unsigned char *data = stbi_load(path, &width, &height, &nrChannels, 4);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		//Debug logging
		output << "TEXTURE: " << path << " successfully loaded!";
		Debug::Log(output);
	}
	else
	{
		output << "Failed to load texture from " << path;
		Debug::Log(output);
	}
	stbi_image_free(data);
}

Texture::~Texture()
{
	glDeleteTextures(1, &texture);
}
