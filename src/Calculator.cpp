#include "Calculator.h"

void CalculatorInput(GLFWwindow* window, int key, int scancode, int action, int mods);

Calculator::Calculator(GLFWwindow* window)
{
	//Register input callback
	glfwSetKeyCallback(window, CalculatorInput);
}

void Calculator::Run()
{
	// Create a window called "My First Tool", with a menu bar.
	ImGui::Begin("Calculator", active, ImGuiWindowFlags_NoResize);

	ImGui::SetWindowSize(ImVec2((float)WIDTH, (float)HEIGHT));
	//ImGui::SetWindowPos(ImVec2(0, 0));
	ImGui::Text(resultText.c_str());

	ImGui::NewLine();

	ImGui::PushItemWidth(100);
	ImGui::InputFloat("Number 1", &num1);
	ImGui::InputFloat("Number 2", &num2);

	ImGui::NewLine();
	//Operators
	if (ImGui::Button("*", ImVec2(50, 50)))
	{
		resultText = "Result: " + std::to_string(Calculator::Multiply(num1, num2));
	}
	ImGui::SameLine();

	if (ImGui::Button("+", ImVec2(50, 50)))
	{
		resultText = "Result: " + std::to_string(Calculator::Add(num1, num2));
	}
	ImGui::SameLine();

	if (ImGui::Button("-", ImVec2(50, 50)))
	{
		resultText = "Result: " + std::to_string(Calculator::Subtract(num1, num2));
	}
	ImGui::SameLine();

	if (ImGui::Button("/", ImVec2(50, 50)))
	{
		//Prevent 0 division
		if (num2 == 0) { resultText = "Error! Cannot divide by 0."; }
		else { resultText = "Result: " + std::to_string(Calculator::Divide(num1, num2)); }
	}
	ImGui::SameLine();

	ImGui::End();
}

void CalculatorInput(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_E && action == GLFW_PRESS)
	{
		std::cout << "Calculator Input Dispatched: " << std::endl;
	}
}
