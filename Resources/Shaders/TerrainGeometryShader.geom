#version 410

layout(triangles) in;
layout(triangle_strip, max_vertices = 3) out;


vec3 Normal[];
vec3 FragPos[];

in vData
{
    vec3 FragPos;
}vertices[];

out fData
{
    vec3 Normal;
    vec3 FragPos;
} frag;

void main() {

	vec3 VecA = vec3(gl_in[1].gl_Position - gl_in[0].gl_Position);
	vec3 VecB = vec3(gl_in[2].gl_Position - gl_in[0].gl_Position);
	vec3 normal = normalize(cross(VecB, VecA));

	for(int i = 0; i < 3; i++) {
		gl_Position = gl_in[i].gl_Position;
		frag.Normal = normal;
		frag.FragPos = vertices[i].FragPos;
		EmitVertex();
	}

	EndPrimitive();

}