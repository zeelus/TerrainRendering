#version 410

layout(location = 0) in vec4 position;
uniform sampler2D terrain;

void main(void){
    vec2 texcoord = position.xy;
    float height = texture(terrain, texcoord).r;
    vec4 displaced = vec4(position.x, position.y, height, 1.0);
    gl_Position = displaced;
}