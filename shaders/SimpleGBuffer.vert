#version 330

layout(location = 0) in vec4 point;
layout(location = 1) in vec4 normal;

uniform mat4 CameraMatrix;

out vec4 vertNormal;

void main() {
	gl_Position = CameraMatrix * point;
	vertNormal = normal;
}