in FS_DATA
{
  vec2 uv;
} fs_in;

uniform sampler2D colorTex;

out vec4 color;

void main(void)
{
  color = texture(colorTex, fs_in.uv).rgba;
};