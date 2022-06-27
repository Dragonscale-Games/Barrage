#version 330 core

layout (location = 0) in vec3 a_position;
layout (location = 1) in vec2 a_tex_coord;

layout (location = 2) in vec2 a_translation;
layout (location = 3) in vec2 a_scale;
layout (location = 4) in float a_rotation;

uniform mat4 proj_matrix;
uniform mat4 view_matrix;

out vec2 tex_coord;

void main()
{
  float cos_result = cos(a_rotation);
  float sin_result = sin(a_rotation);
  
  mat4 transform_matrix = mat4( a_scale[0] * cos_result, a_scale[0] * sin_result, 0.0, 0.0,
                               a_scale[1] * -sin_result, a_scale[1] * cos_result, 0.0, 0.0,
                                                    0.0,                     0.0, 1.0, 0.0,
                                       a_translation[0],        a_translation[1], 0.0, 1.0);

  gl_Position = proj_matrix * view_matrix * transform_matrix * vec4(a_position, 1.0f);
  
  tex_coord = a_tex_coord;
}