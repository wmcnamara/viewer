#pragma once
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include <iostream>
#include "Window.h"
#include "imgui.h"
#include "delegate.h"
#include "IO.h"

class GuiWindow
{
public:
	//GuiWindow(int width, int height, const char* name, EventHandler&& renderHandler, size_t numOfHandlers);
	GuiWindow(int width, int height, int posx, int posy, const char* name);
	~GuiWindow();

	void BeginDraw();
	void EndDraw();

	unsigned int GetRenderTexture() const& { return renderTexture; }

	ImVec2 GetContentRegion() const { return ImGui::GetContentRegionAvail(); }

	bool Renderable() const { 
		return 
			ImGui::GetContentRegionAvail().x > 10 
			&& 
			ImGui::GetContentRegionAvail().y > 10; 
	}

	ImVec2 RenderSpace() const 
	{
		return ImGui::GetContentRegionAvail();
	}

	int ContentRegionAspectRatio () 
	{ 
		return ImGui::GetContentRegionAvail().x / ImGui::GetContentRegionAvail().y;
	}

	inline static Delegate<GetTextureFileArgs> OnNewTexLoad; //Called when user loads a new file.
private:
	unsigned int FBO = 0, RBO = 0;
	unsigned int renderTexture;
	const char* m_name;
};

