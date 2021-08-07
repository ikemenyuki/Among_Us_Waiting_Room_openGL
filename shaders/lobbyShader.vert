#version 330 core
// NOTE: Do NOT use any version older than 330! Bad things will happen!

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;

// Uniform variables can be updated by fetching their location and passing values to that location
uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;
uniform int objType;
uniform vec3 viewpos;
uniform int isphong;
uniform int islight;

// Outputs of the vertex shader are the inputs of the same name of the fragment shader.
// The default output, gl_Position, should be assigned something. You can define as many
// extra outputs as you need.
out float sampleExtraOutput;
out vec3 Normal;
out vec3 FragPos;
out vec3 viewPos;
out float type;
out float isPhong;
out float isLight;

void main()
{
    // OpenGL maintains the D matrix so you only need to multiply by P, V (aka C inverse), and M
    gl_Position = projection * view * model * vec4(position, 1.0);
    sampleExtraOutput = 1.0f;
    Normal = normalize(normal);
    FragPos = vec3(model * vec4(position, 1.0));
    viewPos = viewpos;
    type = objType;
    isPhong = isphong;
    isLight = islight;
}
