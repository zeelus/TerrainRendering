#version 410

layout(location = 0) in vec3 v;
uniform sampler2D terrain;

void main(void){
    vec2 texcoord = v.xz;
    float height = texture(terrain, texcoord).r;
    vec4 displaced = vec4(v.x, height, v.z, 1.0);
    gl_Position = displaced;
}