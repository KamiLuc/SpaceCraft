#version 330

layout(location = 0) in vec3 pos;

out vec3 texCoord;

uniform mat4 projection;
uniform mat4 view;

void main()
{
	texCoord = pos;
	gl_Position = projection * view * vec4(pos, 1.0);
}