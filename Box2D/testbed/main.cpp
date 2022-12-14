#include "main.h"

int main()
{
	// @TODO Enum으로 에러분류
	if (init() == -1) return -1;

	// @TODO glslVersion과 nullptr
	//createUI(g_mainWindow, nullptr);

	// @TODO ImGui
	//bool show_demo_window = true;
	//bool show_another_window = false;
	//ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);


	glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
	while (!glfwWindowShouldClose(g_mainWindow))
	{
		processInput(g_mainWindow);
		glfwGetWindowSize(g_mainWindow, &g_camera.m_width, &g_camera.m_height);
		glClear(GL_COLOR_BUFFER_BIT);

		// @TODO ImGui
		//ImGui_ImplOpenGL3_NewFrame();
		//ImGui_ImplGlfw_NewFrame();
		//ImGui::NewFrame();
		//ImGui::Render();
		//ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());


		glfwSwapBuffers(g_mainWindow);
		glfwPollEvents();
	}

	// @TODO ImGui
	//ImGui_ImplOpenGL3_Shutdown();
	//ImGui_ImplGlfw_Shutdown();
	//ImGui::DestroyContext();

	glfwDestroyWindow(g_mainWindow);
	glfwTerminate();

	return 0;
}