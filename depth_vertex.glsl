#version 330 core

layout (location = 0) in vec4 vertex;

uniform mat4 lightSpaceMatrix;
uniform mat4 model;

void main() {
    gl_Position = lightSpaceMatrix * model * vertex;
}
