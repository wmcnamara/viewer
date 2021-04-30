#pragma once

#include <glad/glad.h> 
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include "GLFW/glfw3.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


class Shader
{
public:
	// the program ID
	unsigned int ID;

	Shader();
	~Shader();

	// use/activate the shader
	void Use();

	// utility uniform functions
	void SetBool(const char* name, bool value) const;
	void SetInt(const char* name, int value) const;
	void SetFloat(const char* name, float value) const;
	void SetMatrix4(const char* name, glm::mat4 matrix) const;
	
private:
	void ShaderCompileLog(unsigned int vertexShader, unsigned int fragmentShader);
	void ShaderLinkLog(unsigned int shaderProgram);
};

