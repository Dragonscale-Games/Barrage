layout (location = 0) in vec2 vertex;
layout (location = 1) in vec2 uv;
layout (location = 2) in vec2 position;
layout (location = 3) in vec2 scale;
layout (location = 4) in float rotation;
layout (location = 5) in vec4 texCoords;

uniform mat4 projection;

out FS_DATA
{
  vec2 uv;
} vs_out;

void main(void)
{
  // Apply the transformation for the geometry.
  vec2 v = scale * vertex;
  v = vec2( v.x * cos(rotation) - v.y * sin(rotation), v.x * sin(rotation) + v.y * cos(rotation) );
  v += position;
  gl_Position = projection * vec4(v, 0.0, 1.0);
  // Send over data over to the fragment shader.
  vs_out.uv = texCoords.zw * uv + texCoords.xy;
}
