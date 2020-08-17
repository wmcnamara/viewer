#pragma once
#include "glad/glad.h"
#include "stb_image.h"
#include <filesystem>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <cmath>

#define LOGERR() std::cout << glGetError() << std::endl;

class Mesh 
{
public:
	Mesh(
		float* vertices, 
		unsigned int* indices, 
		size_t numOfVertices, 
		size_t numOfIndices,
		bool useEBO);
	~Mesh();

	const unsigned int VertexCount() const { return m_numOfVertices; }
	const unsigned int IndexCount() const { return m_numOfIndices; }

	const unsigned int GetVAO() const { return VAO; }
	
	const bool indexed() const { return m_useEBO; }

private:
	unsigned int VBO, VAO, EBO;

	float* m_vertices;
	unsigned int* m_indices;

	unsigned int m_numOfVertices;
	unsigned int m_numOfIndices;

	bool m_useEBO;
};
