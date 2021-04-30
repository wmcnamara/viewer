#include "Camera.h"

void Camera::UpdateProjectionData()
{
	//Get information about the viewport, to make sure the projection is configured correctly.
	//https://www.khronos.org/registry/OpenGL-Refpages/es2.0/xhtml/glViewport.xml
	float viewportDat[4] = { 0, 0, 0, 0 };
	glGetFloatv(GL_VIEWPORT, viewportDat);

	if (m_projType == Projection::Perspective)
	{
		projection = glm::perspective(
			glm::radians(60.0f),
			viewportDat[2] / viewportDat[3], //The first 2 elements of GL_VIEWPORT are irrelevant here.
			0.1f,
			100.0f);
	}
	else if (m_projType == Projection::Orthographic)
	{
		projection = glm::ortho(
			glm::radians(60.0f),
			viewportDat[2] / viewportDat[3], //The first 2 elements of GL_VIEWPORT are irrelevant here.
			0.1f,
			100.0f);
	}
}
