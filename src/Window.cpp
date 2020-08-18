#include "Window.h"

//TODO Fix
void SizeCallback(GLFWwindow* window, int width, int height) 
{
	Window::Instance().SetSize(width, height);
}

Window::~Window()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
	glfwDestroyWindow(m_window);
	glfwTerminate();
}

//Processes input, runs glClear and creates an IMGUI frame.
void Window::BeforeRender()
{
	//Setup polling, new frames and clear buffers
	glfwPollEvents();

	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Measure speed
	double currentTime = glfwGetTime();
	static int internalFrameCount;
	internalFrameCount++;

	// If a second has passed.
	if (currentTime - previousTime >= 1.0)
	{
		// Display the frame count here any way you want.
		frameCount = internalFrameCount;
		internalFrameCount = 0;
		previousTime = currentTime;
	}
}

//Called after rendering code. Ends IMGUI frames, swaps buffers, and polls events.
void Window::AfterRender()
{
	// Render dear imgui into screen
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	glfwSwapBuffers(m_window);
}

Window::Window()
{
	Debug::ClearOutputLogs();
	Debug::Log(std::stringstream("Viewer Debug Started"));
	//Glfw
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_SAMPLES, 4);

	//Window //TODO
	m_window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "WestMac Texture Viewer", NULL, NULL);
	if (m_window == NULL)
	{
		Debug::Log("Failed to create GLFW window");
		glfwTerminate();
		return;
	}
	glfwMakeContextCurrent(m_window);

	//Glad
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		Debug::Log("Failed to initialize GLAD");
		return;
	}

	//glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);
	glfwSetFramebufferSizeCallback(m_window, SizeCallback);

	//Init IMGUI
	// Setup Dear ImGui context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO &io = ImGui::GetIO();
	ImGui::GetIO().ConfigFlags |= ImGuiConfigFlags_None;
	// Setup Platform/Renderer bindings
	ImGui_ImplGlfw_InitForOpenGL(m_window, true);
	ImGui_ImplOpenGL3_Init("#version 330 core");
	// Setup Dear ImGui style
	ImGui::StyleColorsDark();

	//Setup logging and create a log file.
	//TODO
}
