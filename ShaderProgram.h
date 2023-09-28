#pragma once
#include <iostream>
class ShaderProgram
{
public:
	unsigned int ID = -1;
	
	ShaderProgram() = delete;

	ShaderProgram(std::string& a_vertex_path, std::string& a_fragment_path);

	void build();

	/// <summary>
	/// Use this ShaderProgram, must be called before drawing in the render loop.
	/// </summary>
	void use();
	
	void set_uniform_4f(const char* a_uniform_name, float a_x, float a_y, float a_z, float a_w);
	void set_uniform_4f(std::string& a_uniform_name, float a_x, float a_y, float a_z, float a_w);

private:
	std::string _vertex_path;
	std::string _fragment_path;

	unsigned int create_gl_shader(const char* a_src, unsigned int a_shader_type);
};