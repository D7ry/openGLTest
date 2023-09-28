#include <stdio.h>
#include <iostream>
#include <fstream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "render_loop.h"
#include <exception>

#include "ShaderProgram.h"


const std::string shader_path = "C://Users//Ty//repo//openGLTest//";
const std::string shader_vertex_name = "shader_vertex.glsl";
const std::string shader_fragment_name = "shader_fragment.glsl";


void render_loop::start_render_loop(GLFWwindow* a_window)
{
	int  success;
	char infoLog[512];
	const float vertices_triangle[] = {
		-0.5f, -0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		 0.0f,  0.5f, 0.0f
	};

	const float vertices_rectancle[] = {
		 0.5f,  0.5f, 0.0f,  // top right
		 0.5f, -0.5f, 0.0f,  // bottom right
		-0.5f, -0.5f, 0.0f,  // bottom left
		-0.5f,  0.5f, 0.0f   // top left 
	};
	
	unsigned int vertices_rectancle_draw_indices[] = {
		0, 1, 3, // first triangle
		1, 2, 3  // second triangle
	};
	
	std::string vertex_path = (shader_path + shader_vertex_name);
	std::string fragment_path = (shader_path + shader_fragment_name);
	ShaderProgram shader_program(vertex_path, fragment_path);
	shader_program.build();
	shader_program.use();

	// set up objects to render
	unsigned int VBO, VAO1, VAO2;
	glGenVertexArrays(1, &VAO1);
	glGenVertexArrays(1, &VAO2);
	glGenBuffers(1, &VBO);
	
	unsigned int EBO;
	glGenBuffers(1, &EBO);
	
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAO1);
	glBindBuffer(GL_ARRAY_BUFFER, VBO); // bind the buffer to the GL_ARRAY_BUFFER target
	// from this point on, all buffer calls made to GL_ARRAY_BUFFER will configure VBO
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_triangle), vertices_triangle, GL_STATIC_DRAW); // copy the data to the buffer
	// vertex attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindVertexArray(VAO2);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);  // Rebind the same VBO
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_rectancle), vertices_rectancle, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(vertices_rectancle_draw_indices), vertices_rectancle_draw_indices, GL_STATIC_DRAW);
	// vertex attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// unbind VAO
	glBindVertexArray(0);

	printf("Starting render loop...");
	
	float i = 0.01;
	while (!glfwWindowShouldClose(a_window)) {
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		
		
		i += 0.01;
		if (i >= 1) {
			i = 0.01;
		}
		shader_program.set_uniform_4f("customColor", 0.0f, i, 1.0f, 1.0f);
		
		glBindVertexArray(VAO1);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glBindVertexArray(VAO2);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		glfwSwapBuffers(a_window);
		glfwPollEvents();
	}
	

}