#version 410

layout(location = 0) in vec3 vp;
layout(location = 1) in vec3 normal;

layout (std140) uniform Matrices
{
    mat4 model;
    mat4 view;
    mat4 projection;
} matrices;

layout (std140) uniform Terrain
{
    float size;
	float scale;
	vec2 p;
} terrain;

out vData
{
    vec3 FragPos;
} vertex;

uniform sampler2D color_tex;

void main() {
	vec3 fragPos = vec3(matrices.model * vec4(vp, 1.0));
	vec2 textureCord = vec2( (((fragPos.x / terrain.size) + 1.0f)) / 2.0f, (((fragPos.z / terrain.size) + 1.0f)) / 2.0f);

	float height = texture(color_tex, textureCord).r;

	vec3 heightVector = vec3(0.0f, height * terrain.scale , 0.0f);

	vec3 Pos = vp + heightVector;

    gl_Position = matrices.projection * matrices.view * matrices.model * vec4(Pos, 1.0f);
    vertex.FragPos = fragPos + heightVector;
}