#pragma once
#include "stb_image.h"
#include "imgui.h"
#include <string>
#include <iostream>
#include <Windows.h>
#include <shobjidl.h> 
#include <stdlib.h>
#include <fstream>
#include <sstream>

class File
{
public:
	static std::string GetFile();

private:
};

//Contains the filepaths retrieved from the picker.
struct GetFileArgs 
{
	size_t numOfFiles;
	std::string* filePaths;
};

//Contains the filepaths retrieved from the picker.
struct GetTextureFileArgs
{
	std::string texturePath;
};