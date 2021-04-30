#pragma warning( disable : 4005 )
#pragma warning( disable : 4098 )
#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include "Window.h"
#include "Mesh.h"
#include "Shader.h"
#include "Texture.h"
#include "GuiWindow.h"
#include "Camera.h"
#include "MeshRenderer.h"
#include "IO.h"

#include <Windows.h>
#include <shobjidl.h> 

#ifndef UNICODE
#define UNICODE
#endif 

//Use a winmain application on release build, and console app on debug build
#if defined (VIEWER_CONSOLE_APP)
#define ENTRY_POINT int main(int argc, char** argv)
#else
#define ENTRY_POINT int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR lpCmdLine, INT nCmdShow)
#endif 

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "Vertices.h"

void InputCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

ENTRY_POINT
{	
	Window::Init(); //initialize

	//Create data for a cube
	Shader cubeShader;
	Mesh cube(vertices, 90);
	glm::mat4 model = glm::mat4(1.0f);

	////ENABLE WINDOWS "OPEN WITH" FUNCTIONALITY
	//If there are two cmd line arguments, and it isnt empty load the second as texture. This allows "open with" functionality in windows.
	//If you pass a texture to an EXE, it is the second cmd line argument. This allows loading it.
	Texture texture("");

#ifdef VIEWER_CONSOLE_APP
	for (int i = 0; i < argc; i++)
	{
		std::cout << argv[i] << "\n";
	}

	if (argc == 2)
	{
		if (argv[1] != "")
			texture.Reload(argv[1]); //load command line argument
	}
#else 
	//For some reason windows adds "" to the end of the command line argument when you use the "Open With" dialog.
	//This removes the "", so it can be loaded correctly.
	std::string filePath = lpCmdLine;
	filePath.erase(remove(filePath.begin(), filePath.end(), '"'), filePath.end()); //remove " from string

	//Log info to file
	std::ofstream log("output.log");
	log << "CMD LINE: " << filePath;
	log.close();

	texture.Reload(filePath.c_str()); //load command line argument	
#endif
	////////////

	//Setup camera and gui
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

		//Update Model Matrix
		model = glm::mat4(1.0f);
		model = glm::rotate(
			model,
			(float)glfwGetTime() * glm::radians(50.0f),
			glm::vec3(0.5f, 1.0f, 0.0f));

		//Update Perspective data, and render.
		camera.Run();

		cubeShader.SetMatrix4("view", camera.view);
		cubeShader.SetMatrix4("model", model);
		cubeShader.SetMatrix4("projection", camera.GetProjection());

		glBindTexture(GL_TEXTURE_2D, texture.Data());
		glBindVertexArray(cube.GetVAO());
		glUseProgram(cubeShader.ID);
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