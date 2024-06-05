#version 330

//Zmienne jednorodne
uniform mat4 P;
uniform mat4 V;
uniform mat4 M;
uniform vec4 lp;

//cwiczenie 1 i 2
uniform vec4 color=vec4(0.3,1.0,0.2,1);
uniform vec4 lightDir=vec4(0,0,1,0);

layout (location=0) in vec4 vertex; 
//layout (location=1) in vec4 normal; 


out vec4 iC;
out vec4 l;
out vec4 n;
out vec4 v;


void main(void) {

    //cwiczenie 1 oraz 2
    // normalne œcian i wierzcho³ka s¹ ju¿ wylicznone dla myTeapot, wystarczy je zmieniæ w main_file.cpp (oko³o linii 50, linia 54,55,56)
    gl_Position=P*V*M*vertex;

    //mat4 G=mat4(inverse(transpose(mat3(M))));
    //vec4 n=normalize(V*G*normal);

    //float nl=clamp(dot(n,lightDir),0,1);

    //iC=vec4(color.rgb*nl,color.a);
    iC = color;
}