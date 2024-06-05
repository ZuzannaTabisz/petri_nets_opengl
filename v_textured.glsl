#version 330

uniform mat4 P;
uniform mat4 V;
uniform mat4 M;
uniform vec4 color;
uniform vec4 lightDir1;
uniform vec4 lightDir2;
uniform vec4 lightColor1;
uniform vec4 lightColor2;
uniform mat4 lightSpaceMatrix;


layout(location = 0) in vec4 vertex;
layout(location = 1) in vec4 normal;
layout(location = 2) in vec2 texCoord;


out vec4 FragPosLightSpace;
out vec2 i_tc;
out vec4 ic;
out vec4 i_lightColor1;
out vec4 i_lightColor2;
out vec4 l1;
out vec4 l2;
out vec4 n;
out vec4 v;

void main(void) {
    l1 = normalize(V * (lightDir1 - M * vertex));
    l2 = normalize(V * (lightDir2 - M * vertex));
    n = normalize(V * M * normal);
    v = normalize(vec4(0, 0, 0, 1) - V * M * vertex);

    gl_Position = P * V * M * vertex;
    i_tc = vec2(texCoord.x, 1.0 - texCoord.y);
    ic = color;
    i_lightColor1 = lightColor1;
    i_lightColor2 = lightColor2; 
    FragPosLightSpace = lightSpaceMatrix * M * vertex;
}
