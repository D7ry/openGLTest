#version 330 core
out vec4 FragColor;
  
in vec4 vertexColor; // the input variable from the vertex shader (same name and same type)  

uniform vec4 customColor; // sth we set from the C++ code

void main()
{
    FragColor = customColor;
} 