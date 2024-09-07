#version 460 core

layout (location = 0) in vec3 v_position;
layout (location = 1) in vec2 v_texCoord;
layout (location = 2) in vec4 v_light;

out vec4 a_color;
out vec2 a_texCoord;

uniform mat4 model;
uniform mat4 projview;

void main() {
	a_color = vec4(v_light.r, v_light.g, v_light.b, 1);
	a_color.rgb += v_light.a;
	a_texCoord = v_texCoord;
	gl_Position = projview * model * vec4(v_position, 1);
}