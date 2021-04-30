#pragma once
#include "glad/glad.h"

class Mesh 
{
public:
	Mesh(
		float* vertices, 
		size_t numOfVertices);
	~Mesh();

	const unsigned int VertexCount() const { return m_numOfVertices; }
	const unsigned int GetVAO() const { return VAO; }
	
private:
	unsigned int VBO, VAO;

	float* m_vertices;
	unsigned int m_numOfVertices;
};
