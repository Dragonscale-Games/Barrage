layout (location = 0) in vec2 vertex;
layout (location = 2) in vec2 position;
layout (location = 3) in vec2 scale;
layout (location = 4) in float rotation;
uniform mat4 projection;
void main(void)
{
  vec2 v = scale * vertex;
  v = vec2( v.x * cos(rotation) - v.y * sin(rotation), v.x * sin(rotation) + v.y * cos(rotation) );
  v += position;
  gl_Position = projection * vec4(v, 0.0, 1.0);
}
