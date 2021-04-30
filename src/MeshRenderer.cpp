#include "MeshRenderer.h"

void MeshRenderer::Render()
{
	m_shader->SetMatrix4("model", model);
	m_shader->SetMatrix4("projection", m_camera->GetProjection());
	if (active)
	{
		glBindTexture(GL_TEXTURE_2D, m_texture->Data());
		glBindVertexArray(m_mesh->GetVAO());
		glUseProgram(m_shader->ID);
		glDrawArrays(GL_TRIANGLES, 0, m_mesh->VertexCount());	
	}
}
