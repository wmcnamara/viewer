#include "glad/glad.h"
#include "stb_image.h"
#include "GLFW/glfw3.h"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "Window.h"
#include "Mesh.h"
#include "Shader.h"
#include "Texture.h"
#include "GuiWindow.h"
#include "Camera.h"
#include "MeshRenderer.h"
#include "IO.h"

#include <memory>
#include <iostream>
#include <string>

#include <Windows.h>
#include <shobjidl.h> 

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#ifndef UNICODE
#define UNICODE
#endif 

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

float vertices[] = {
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
	 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
};

void InputCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
	Window::Init();

	Shader shader("shaders/Standard.vert", "shaders/Standard.frag");
	Texture texture("assets/error.jpg", false);
	Mesh cube(vertices, 90);
	glm::mat4 model = glm::mat4(1.0f);

	Camera camera(glm::vec3(0.0f, 0.0f, 3.0f), Projection::Perspective);

	GuiWindow sceneWin(Window::Instance().GetWidth(), Window::Instance().GetHeight(), 0, 0, "Scene Window");

	//Input
	glfwSetKeyCallback(Window::Instance().GetWindow(), InputCallback);

	//Subscribe to events
	GuiWindow::OnNewTexLoad.AddHandler([&](GetTextureFileArgs args) { texture.Reload(args.texturePath.c_str()); });

	while (!glfwWindowShouldClose(Window::Instance().GetWindow()))
	{
		Window::Instance().BeforeRender();
		sceneWin.BeginDraw();

		//FPS
		std::string output("FPS: ");
		output += std::to_string(Window::Instance().GetFrameCount());
		ImGui::Text(output.c_str());

		//Update Shaders
		shader.Update();

		//Update Model Matrix
		model = glm::mat4(1.0f);
		model = glm::rotate(
			model,
			(float)glfwGetTime() * glm::radians(50.0f),
			glm::vec3(0.5f, 1.0f, 0.0f));

		//Update Perspective data, and render.
		camera.Run();
		shader.SetMatrix4("view", camera.view);

		shader.SetMatrix4("model", model);
		shader.SetMatrix4("projection", camera.GetProjection());
		glBindTexture(GL_TEXTURE_2D, texture.Data());
		glBindVertexArray(cube.GetVAO());
		glUseProgram(shader.ID);
		glDrawArrays(GL_TRIANGLES, 0, cube.VertexCount());
		sceneWin.EndDraw();
		Window::Instance().AfterRender();
	}

	return 0;
}

void InputCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}