#pragma once
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <iostream>
#include <Windows.h>
#include <string>
#include "delegate.h"
#include "Debug.h"

class Window
{
public:
	~Window();

	void SetSize(int width, int height) { SCR_WIDTH = width; SCR_HEIGHT = height; }
	ImVec2 GetSize() { return ImVec2(SCR_WIDTH, SCR_HEIGHT); }

	int GetWidth() { return SCR_WIDTH; }
	int GetHeight() { return SCR_HEIGHT; }

	void BeforeRender();
	void AfterRender();

	GLFWwindow* GetWindow() { return m_window; }

	static void Init() { Instance(); }

	const int GetFrameCount() { return frameCount; }
private:
	GLFWwindow* m_window;

	int SCR_WIDTH = 800;
	int SCR_HEIGHT = 600;

	//FPS data
	double previousTime = 0;
	int frameCount = 0; //This is updated every second.

//SINGLETON//
public:
	static Window& Instance()
	{
		static Window instance;
		return instance;
	}

	Window(Window const&) = delete;
	void operator=(Window const&) = delete;
private:
	Window();
};