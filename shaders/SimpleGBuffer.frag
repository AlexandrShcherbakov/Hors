#version 330

in vec4 vertNormal;

layout(location = 0) out vec4 normal;

void main() {
	normal = vertNormal;
}