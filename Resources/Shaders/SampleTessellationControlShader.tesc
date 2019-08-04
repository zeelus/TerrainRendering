#version 410

layout(vertices = 4) out;
//
////    void main(){
////        if (gl_InvocationID == 0)
////        {
////            gl_TessLevelInner[0] = 9.0;
////            gl_TessLevelInner[1] = 7.0;
////            gl_TessLevelOuter[0] = 3.0;
////            gl_TessLevelOuter[1] = 5.0;
////            gl_TessLevelOuter[2] = 3.0;
////            gl_TessLevelOuter[3] = 5.0;
////        }
////
////        gl_out[gl_InvocationID].gl_Position = gl_in[gl_InvocationID].gl_Position;
////    }
//
layout (std140) uniform Matrices
{
    mat4 model;
    mat4 view;
    mat4 projection;
} matrices;

float lod_factor = 32.0;

bool offscreen(vec4 vertex){
    if(vertex.z < -0.5){
        return true;
    }
    return any(lessThan(vertex.xy, vec2(-1.7))) || any(greaterThan(vertex.xy, vec2(1.7)));

}

vec4 project(vec4 vertex){
    vec4 result = matrices.projection * matrices.view * matrices.model * vertex;
    result /= result.w;
    return result;
}

vec2 screen_space(vec4 vertex){
    vec2 screen_size = vec2(1280.0, 960.0);
    return (clamp(vertex.xz, -1.3, 1.3)+1) * (screen_size * 0.5);
}

float level(vec2 v0, vec2 v1){
    return clamp(distance(v0, v1)/lod_factor, 1, 64);
}

void main(){

    if(gl_InvocationID == 0){
        vec4 v0 = project(gl_in[0].gl_Position);
        vec4 v1 = project(gl_in[1].gl_Position);
        vec4 v2 = project(gl_in[2].gl_Position);
        vec4 v3 = project(gl_in[3].gl_Position);

        if(all(bvec4(offscreen(v0), offscreen(v1), offscreen(v2), offscreen(v3)))){
            gl_TessLevelInner[0] = 0;
            gl_TessLevelInner[1] = 0;
            gl_TessLevelOuter[0] = 0;
            gl_TessLevelOuter[1] = 0;
            gl_TessLevelOuter[2] = 0;
            gl_TessLevelOuter[3] = 0;
        }
        else{
            vec2 ss0 = screen_space(v0);
            vec2 ss1 = screen_space(v1);
            vec2 ss2 = screen_space(v2);
            vec2 ss3 = screen_space(v3);

            float e0 = level(ss1, ss2);
            float e1 = level(ss0, ss1);
            float e2 = level(ss3, ss0);
            float e3 = level(ss2, ss3);

            gl_TessLevelInner[0] = mix(e1, e2, 0.5);
            gl_TessLevelInner[1] = mix(e0, e3, 0.5);
            gl_TessLevelOuter[0] = e0;
            gl_TessLevelOuter[1] = e1;
            gl_TessLevelOuter[2] = e2;
            gl_TessLevelOuter[3] = e3;

//                        gl_TessLevelInner[0] = 2.0;
//                        gl_TessLevelInner[1] = 2.0;
//                        gl_TessLevelOuter[0] = 3.0;
//                        gl_TessLevelOuter[1] = 3.0;
//                        gl_TessLevelOuter[2] = 3.0;
//                        gl_TessLevelOuter[3] = 3.0;
        }
    }
    gl_out[gl_InvocationID].gl_Position = gl_in[gl_InvocationID].gl_Position;
}