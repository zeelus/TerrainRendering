#version 410

layout(quads, fractional_odd_spacing, ccw) in;

layout (std140) uniform Matrices
{
    mat4 model;
    mat4 view;
    mat4 projection;
} matrices;

out vData
{
    vec3 FragPos;
} vertex;

uniform sampler2D terrain;

void main(){
    float u = gl_TessCoord.x;
    float v = gl_TessCoord.y;

    vec4 a = mix(gl_in[1].gl_Position, gl_in[0].gl_Position, u);
    vec4 b = mix(gl_in[2].gl_Position, gl_in[3].gl_Position, u);
    vec4 position = mix(a, b, v);
    vec2 texcoord = position.xy;
    float height = texture(terrain, texcoord).a;
    gl_Position = matrices.model * matrices.view * matrices.projection * vec4(texcoord, height, 1.0);
    vertex.FragPos = vec3(gl_Position);
}