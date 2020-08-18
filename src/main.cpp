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
#include "ConfigReader.h"
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

Camera* camera;
Shader* shader;
Texture* texture;
Mesh* cube;
MeshRenderer* renderer;
glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);


int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
	Window::Init();
	shader = new Shader("shaders/Standard.vert", "shaders/Standard.frag");
	texture = new Texture("assets/error.jpg", false);
	cube = new Mesh(vertices, NULL, 180, 0, false);

	camera = new Camera(
		cameraPos,
		glm::vec3(0.0f, 0.0f, 0.0f),
		Perspective);

	renderer = new MeshRenderer(cube, texture, shader, camera);

	GuiWindow sceneWin(Window::Instance().GetWidth(), Window::Instance().GetHeight(), 0, 0, "Scene Window");

	//Input
	glfwSetKeyCallback(Window::Instance().GetWindow(), InputCallback);

	//Subscribe to events
	sceneWin.onNewTexLoad.AddHandler([](GetTextureFileArgs args) { texture->Reload(args.texturePath.c_str()); });

	while (!glfwWindowShouldClose(Window::Instance().GetWindow()))
	{
		Window::Instance().BeforeRender();
		sceneWin.BeginDraw();

		//FPS
		std::string output("FPS: ");
		output += std::to_string(Window::Instance().GetFrameCount());
		ImGui::Text(output.c_str());

		//Update Shaders
		shader->Update();

		//Update Model Matrix
		renderer->model = glm::mat4(1.0f);
		renderer->model = glm::rotate(
			renderer->model,
			(float)glfwGetTime() * glm::radians(50.0f),
			glm::vec3(0.5f, 1.0f, 0.0f));

		//Update Perspective data, and render.
		camera->Run();
		shader->SetMatrix4("view", camera->view);
		renderer->Render();

		sceneWin.EndDraw();
		Window::Instance().AfterRender();
	}

	delete shader;
	return 0;
}	

void InputCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	camera->Input();
}