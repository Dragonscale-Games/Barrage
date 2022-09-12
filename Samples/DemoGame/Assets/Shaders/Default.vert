#version 330 core

layout (location = 0) in vec3 a_position;
layout (location = 1) in vec2 a_tex_coord;

uniform mat4 proj_matrix;
uniform mat4 view_matrix;
uniform mat4 transform_matrix;

out vec2 tex_coord;

void main()
{
  gl_Position = proj_matrix * view_matrix * transform_matrix * vec4(a_position, 1.0f);
  
  tex_coord = a_tex_coord;
}