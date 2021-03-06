#pragma once
#include <cfloat>
#include <string>
#include "imgui.h"
#include "Window.h"

/// <summary>
/// This is a legacy test file from the first version of Viewer.
/// 
/// You can ignore this.
/// </summary>
class Calculator 
{
public:
	Calculator(GLFWwindow* window);

	float Multiply(float num1, float num2) 
	{
		float result = num1 * num2;
		resultText = "Result " + std::to_string(result);

		return result;
	}
	float Add(float num1, float num2) 
	{
		float result = num1 + num2;
		resultText = "Result " + std::to_string(result);

		return result;	
	}
	float Subtract(float num1, float num2) 
	{
		float result = num1 - num2;
		resultText = "Result " + std::to_string(result);

		return result;
	}

	//Divide num1 by num2. Returns NULL if num2 is 0.
	float Divide(float num1, float num2) 
	{
		if (num2 == 0) 
		{
			resultText = "Error! Cannot divide by 0!";
			return NULL;
		}

		float result = num1 / num2;
		resultText = "Result " + std::to_string(result);

		return result;
	}
	//Gets the result of the most recent calculation in a string
	const char* GetResultText() const { return resultText.c_str(); }
	void Run();

private:
	//Verifies if two given numbers do not go over floating point limits.
	static bool SanitizeSize (float num1, float num2) 
	{
		return !(num1 >= FLT_MAX || num2 >= FLT_MAX);
	}

	std::string resultText = "Result";
	float num1 = 0, num2 = 0;
	bool* active = false;

	unsigned int WIDTH = 300, HEIGHT = 200;
};

