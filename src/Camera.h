#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "Window.h"

using namespace glm;

enum struct Projection
{
	Orthographic,
	Perspective
};

class Camera
{
public:
	Camera(vec3 _position, Projection projType) :
		m_projType(projType)
	{
		view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f)); //TODO

		UpdateProjectionData();	
	}

    mat4 GetProjection() const { return projection; }
	mat4 view = mat4(1.0f);

	void Run() { UpdateProjectionData(); }
private:
	mat4 projection;
	Projection m_projType;

	void UpdateProjectionData();
};

