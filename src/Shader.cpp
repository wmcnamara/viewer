#include "Shader.h"

Shader::Shader()
{
	#include "ShaderSrc.h" //contains shadercode data

	unsigned int vertex, fragment;
	int success;
	char infoLog[512];

	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vertSrc, NULL);
	glCompileShader(vertex);

	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fragSrc, NULL);
	glCompileShader(fragment);

	ID = glCreateProgram();
	glAttachShader(ID, vertex);
	glAttachShader(ID, fragment);
	glLinkProgram(ID);

	ShaderLinkLog(ID);
	ShaderCompileLog(vertex, fragment);
}

void Shader::ShaderLinkLog(unsigned int shaderProgram)
{
	int success;
	char infoLog[512];

	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);

	if (!success)
	{
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);

		std::cout << "Error. Shader linking failed.\n" << infoLog << "\n";
	}
	else
	{
		std::cout << "Shader Program Linked Successfully\n";
	}
}

void Shader::ShaderCompileLog(unsigned int vertexShader, unsigned int fragmentShader)
{
	int success;
	char infoLog[512];

	//Vertex Shader
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);

		std::cout << "Vertex Compilation Failed\n" << infoLog << "\n";
	}
	else
		std::cout << "Vertex Shader Compiled Successfully\n";

	//Fragment Shader
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);

		std::cout << "Fragment Compilation Failed\n" << infoLog << std::endl;
	}
	else
		std::cout << "Fragment Shader Compiled Successfully\n";
}

void Shader::SetBool(const char* name, bool value) const
{
	glUniform1i(glGetUniformLocation(ID, name), (int)value);
}

void Shader::SetInt(const char* name, int value) const
{
	glUniform1i(glGetUniformLocation(ID, name), value);
}

void Shader::SetFloat(const char* name, float value) const
{
	glUniform1f(glGetUniformLocation(ID, name), value);
}

void Shader::SetMatrix4(const char* name, glm::mat4 matrix) const
{
	glUniformMatrix4fv(glGetUniformLocation(ID, name), 1, GL_FALSE, glm::value_ptr(matrix));
}

void Shader::Use() { glUseProgram(ID); }

Shader::~Shader()
{
	glDeleteProgram(ID);
}