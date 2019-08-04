#version 410

layout(location = 0) in vec3 v;

void main(void){
    gl_Position = vec4(v, 1.0);
}