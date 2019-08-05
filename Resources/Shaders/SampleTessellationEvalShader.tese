#version 410

layout(quads, fractional_odd_spacing, ccw) in;

layout (std140) uniform Matrices
{
    mat4 model;
    mat4 view;
    mat4 projection;
} matrices;

uniform sampler2D terrain;

out vData
{
    vec3 FragPos;
} vertex;

void main(){

    vec4 p1 = mix(gl_in[0].gl_Position,
    gl_in[1].gl_Position,
    gl_TessCoord.x);

    vec4 p2 = mix(gl_in[2].gl_Position,
    gl_in[3].gl_Position,
    gl_TessCoord.x);

    vec4 position = mix(p1, p2, gl_TessCoord.y);
    vec2 texcoord = position.xz;

    float height = texture(terrain, texcoord).r;
    gl_Position = matrices.projection * matrices.view * matrices.model * vec4(texcoord.x, height, texcoord.y, 1.0);

    vertex.FragPos = vec3(gl_Position);
}