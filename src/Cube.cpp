#include "Cube.h"

Cube::Cube() :
	m_shader("shaders/Standard.vert", "shaders/Standard.frag"),
	m_texture("assets/crate.jpg", false),
	m_mesh(vertices, 90),

	m_camera(glm::vec3(0.0f, 0.0f, 3.0f), Projection::Perspective)
{
	//Subscribe to events
	GuiWindow::OnNewTexLoad.AddHandler([&](GetTextureFileArgs args) { std::cout << "New Texture Loaded\n";  m_texture.Reload(args.texturePath.c_str()); });
}

void Cube::Render()
{	
	//Update Shaders
	m_shader.Update();

	//Update Model Matrix
	m_model = glm::mat4(1.0f);
	m_model = glm::rotate(
		m_model,
		(float)glfwGetTime() * glm::radians(50.0f),
		glm::vec3(0.5f, 1.0f, 0.0f));
	
	m_shader.Use();



	//Update Perspective data, and render.
	m_camera.Run();

	m_shader.SetMatrix4("model", m_model);
	m_shader.SetMatrix4("projection", m_camera.GetProjection());
	m_shader.SetMatrix4("view", m_camera.view);

	glBindVertexArray(m_mesh.GetVAO());
	glBindTexture(GL_TEXTURE_2D, m_texture.Data());
	
	glDrawArrays(GL_TRIANGLES, 0, m_mesh.VertexCount());
}