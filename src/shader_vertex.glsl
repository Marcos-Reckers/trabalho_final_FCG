#version 330 core

layout (location = 0) in vec4 model_coefficients;
layout (location = 1) in vec4 normal_coefficients;
layout (location = 2) in vec2 texture_coefficients;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec4 position_world;
out vec4 normal;
out vec3 position_model;
out vec2 tex_coords;

void main()
{
    gl_Position = projection * view * model * model_coefficients;
    position_world = model * model_coefficients;
    normal = normal_coefficients;
    position_model = model_coefficients.xyz;
    tex_coords = texture_coefficients;
}