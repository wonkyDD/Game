#include "main.h"

int main()
{
	// @TODO Enum으로 에러분류
	if (init() == -1) return -1;

	glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
	while (!glfwWindowShouldClose(g_mainWindow))
	{
		processInput(g_mainWindow);
		glClear(GL_COLOR_BUFFER_BIT);
		glfwSwapBuffers(g_mainWindow);
		glfwPollEvents();
	}
	return 0;
}