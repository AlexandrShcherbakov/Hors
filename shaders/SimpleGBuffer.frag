#version 330

in vec4 vertPos;
in vec4 vertNormal;

layout(location = 0) out vec4 pos;
layout(location = 1) out vec4 normal;

void main() {
    pos = vertPos;
	normal = vertNormal;
}