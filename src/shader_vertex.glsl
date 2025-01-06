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
    normal = inverse(transpose(model)) * normal_coefficients;
    normal.w = 0.0;
    tex_coords = texture_coefficients;
    position_model = vec3(model_coefficients);

    // Debugging output
    if (tex_coords == vec2(0.0, 0.0)) {
        tex_coords = vec2(1.0, 0.0);
    }
}