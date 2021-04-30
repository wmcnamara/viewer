#include "GuiWindow.h"

GuiWindow::GuiWindow(int width, int height, int posx, int posy, const char* name) :
	m_name(name)
{
	glGenFramebuffers(1, &FBO);
	glGenTextures(1, &renderTexture);

	ImGui::SetNextWindowSize(ImVec2(width, height));
	ImGui::SetNextWindowPos(ImVec2(posx, posy));

	glEnable(GL_DEPTH_TEST);
	glClearColor(.2, .4, .56, .8);
}

bool open = true;
void GuiWindow::BeginDraw()
{
	ImGui::SetNextWindowSize(Window::Instance().GetSize());
	ImGui::SetNextWindowPos(ImVec2(0, 0));
	ImGui::Begin(m_name, false, 
		ImGuiWindowFlags_MenuBar | 
		ImGuiWindowFlags_NoTitleBar | 
		ImGuiWindowFlags_NoResize);

	//draw menu
	if (ImGui::BeginMenuBar())
	{
		if (ImGui::BeginMenu("File"))
		{
			if (ImGui::MenuItem("Load Texture..."))
			{
				GetTextureFileArgs args =
				{
					File::GetFile().c_str(),
				};

				OnNewTexLoad.Invoke(args);
			}
			ImGui::EndMenu();
		}
		if (ImGui::MenuItem("Exit"))
		{
			glfwSetWindowShouldClose(Window::Instance().GetWindow(), true);
		}
	}
	ImGui::EndMenuBar();

	//If the screen can be rendered to, render to texture
	if (Renderable())
	{
		glViewport(0, 0, RenderSpace().x, RenderSpace().y);
		glBindFramebuffer(GL_FRAMEBUFFER, FBO);
		glBindTexture(GL_TEXTURE_2D, renderTexture);

		//Color
		glTexImage2D(
			GL_TEXTURE_2D,
			0,
			GL_RGBA,
			RenderSpace().x,
			RenderSpace().y,
			0,
			GL_RGBA,
			GL_UNSIGNED_BYTE,
			NULL
		);


		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		//Color attachment
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, renderTexture, 0);

		//Depth and stencil renderbuffer attachment
		glGenRenderbuffers(1, &RBO);
		glBindRenderbuffer(GL_RENDERBUFFER, RBO);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, RenderSpace().x, RenderSpace().y);
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, RBO);
																									  
		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
			std::cout << "Framebuffer not complete error\n";
	}
	else 
	{
		glViewport(0, 0, Window::Instance().GetWidth(), Window::Instance().GetHeight());
	}

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

}

void GuiWindow::EndDraw()
{
	//get the mouse position
	ImVec2 pos = ImGui::GetCursorScreenPos();

	ImGui::GetWindowDrawList()->AddImage(
		(void *)renderTexture,
		ImVec2(ImGui::GetCursorScreenPos()),
		ImVec2(ImGui::GetCursorScreenPos().x + ImGui::GetContentRegionAvail().x,
			ImGui::GetCursorScreenPos().y + ImGui::GetContentRegionAvail().y), ImVec2(0, 1), ImVec2(1, 0));
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	glDeleteRenderbuffers(1, &RBO);
	ImGui::End();
}

GuiWindow::~GuiWindow()
{
	glDeleteFramebuffers(1, &FBO);
	glDeleteTextures(1, &renderTexture);
}