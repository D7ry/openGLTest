#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "render_loop.h"

const int window_width = 1024;
const int window_height = 768;

void framebuffer_resize_callback(GLFWwindow* a_window, int a_width, int a_height)
{
	printf("Resize callback: %i, %i", a_width, a_height);
	glViewport(0, 0, a_width, a_height);
}



int main()
{
	
	printf("Initializing GLFW...");
	glfwInit();
	// configure openGL version(3.3)
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // core profile
	printf("...GLFW initialized");

	// create a window object
	printf("Creating window object...");
	GLFWwindow* new_window = glfwCreateWindow(window_width, window_height, "MyFirstWindow", nullptr, nullptr);

	if (!new_window) {
		printf("window object creation failed");
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(new_window);

	printf("...window object created");

	// initialize GLAD, which manages func pointers to openGL
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		printf("GLAD initialization failed");
		glfwTerminate();
		return -1;
	}
	glViewport(0, 0, window_width, window_height); // this needs to be equal to glfwCreatWindow's params
	glfwSetFramebufferSizeCallback(new_window, framebuffer_resize_callback); // so that openGL window resizes with glfw

	render_loop::start_render_loop(new_window); // enter render loop for actual rendering
	glfwTerminate();

	while (1) {
		
	}

	return 0;
}