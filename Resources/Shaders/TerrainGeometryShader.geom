#version 410

layout(triangles) in;
layout(triangle_strip, max_vertices = 3) out;

vec3 Normal;
vec3 FragPos;

in VS_OUT
{
    vec3 Normal;
	vec3 FragPos;
}  gs_in[];

out GS_OUT
{
    vec3 Normal;
	vec3 FragPos;
} gs_out;

void main() {

	for(int i = 0; i < 3; i++) {
		gl_Position = gl_in[i].gl_Position;
		gs_out.Normal = gs_in[i].Normal;
		gs_out.FragPos = gs_in[i].FragPos;
		EmitVertex();
	}

	EndPrimitive();

}