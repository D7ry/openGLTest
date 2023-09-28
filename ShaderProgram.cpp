#include <fstream>
#include <sstream>
#include <iostream>
#include <glad/glad.h>

#include "ShaderProgram.h"
ShaderProgram::ShaderProgram(std::string& a_vertex_path, std::string& a_fragment_path)
{
	this->_vertex_path = a_vertex_path;
	this->_fragment_path = a_fragment_path;
}

void ShaderProgram::build()
{
	// https://learnopengl.com/Getting-started/Shaders
	std::string vertex_shader_source = "";
	std::string fragment_shader_source = "";
	std::ifstream fd_vertex;
	std::ifstream fd_fragment;

	// ensure ifstream objects can throw exceptions:
	fd_vertex.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fd_fragment.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	try {
		fd_vertex.open(this->_vertex_path);
		fd_fragment.open(this->_fragment_path);
		std::stringstream vertex_shader_stream, fragment_shader_stream;
		vertex_shader_stream << fd_vertex.rdbuf();
		fragment_shader_stream << fd_fragment.rdbuf();

		// close fd
		fd_vertex.close();
		fd_fragment.close();

		vertex_shader_source = vertex_shader_stream.str();
		fragment_shader_source = fragment_shader_stream.str();
	}
	catch (std::ifstream::failure e) {
		printf("Error:Shader:Bad file: \n %s \n", e.what());
	}
	
	const char* vertex_shader_src_ptr = vertex_shader_source.c_str();
	const char* fragment_shader_src_ptr = fragment_shader_source.c_str();

	unsigned int vertex_shader_id = this->create_gl_shader(vertex_shader_src_ptr, GL_VERTEX_SHADER);
	unsigned int fragment_shader_id = this->create_gl_shader(fragment_shader_src_ptr, GL_FRAGMENT_SHADER);

	if (vertex_shader_id != 0 && fragment_shader_id != 0) {
		printf("Vertex and fragment shader compiled. \n");
	}
	// create shader program
	this->ID = glCreateProgram();

	// link compiled shaders to shader program
	glAttachShader(this->ID, vertex_shader_id);
	glAttachShader(this->ID, fragment_shader_id);
	glLinkProgram(this->ID);


	// check linking status
	int success;
	char infoLog[512];
	glGetProgramiv(ID, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(ID, 512, NULL, infoLog);
		std::cout << "ShaderProgram::build: linking failed.\n" << infoLog << std::endl;
	}
	printf("Shader program linked.\n");

	// delete the shaders as they're linked into our program now and no longer necessary
	glDeleteShader(vertex_shader_id);
	glDeleteShader(fragment_shader_id);
	
}

void ShaderProgram::use()
{
	if (this->ID == -1) {
		throw std::exception("Shader::use(): Shader not build");
		return;
	}
	glUseProgram(this->ID);
}

void ShaderProgram::set_uniform_4f(const char* a_uniform_name, float a_x, float a_y, float a_z, float a_w)
{
	this->use(); // must be using the program before setting uniform TODO: can queue uniform set until next use.
	unsigned int uniform_location = glGetUniformLocation(this->ID, a_uniform_name);
	if (uniform_location == -1) {
		throw std::exception(std::string("ShaderProgram::set_uniform_4f: Uniform not found for " + std::string(a_uniform_name)).data());
	}
	glUniform4f(uniform_location, a_x, a_y, a_z, a_w);
}

void ShaderProgram::set_uniform_4f(std::string& a_uniform_name, float a_x, float a_y, float a_z, float a_w)
{
	this->set_uniform_4f(a_uniform_name.data(), a_x, a_y, a_z, a_w);
}

unsigned int ShaderProgram::create_gl_shader(const char* a_src, unsigned int a_shader_type)
{
	
	int success;
	char infoLog[512];

	// vertex Shader
	unsigned int shader_id = glCreateShader(a_shader_type); // create new shader
	glShaderSource(shader_id, 1, &a_src, NULL); // replace shader sourcecode
	glCompileShader(shader_id); // compile sourcecode
	// print compile errors if any
	glGetShaderiv(shader_id, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(shader_id, 512, NULL, infoLog);
		std::cout << "ShaderProgram::create_gl_shader: compilation failed.\n" << infoLog << std::endl;
		return -1;
	};

	
	return shader_id;
}
