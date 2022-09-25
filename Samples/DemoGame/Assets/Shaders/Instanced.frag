#version 330 core

out vec4 color;

in vec2 tex_coord;

uniform sampler2D tex_sampler;

void main()
{
  color = texture(tex_sampler, tex_coord);
}