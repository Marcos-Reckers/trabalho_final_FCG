#version 330 core

in vec4 position_world;
in vec4 normal;
in vec3 position_model;
in vec2 tex_coords;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

#define WALL 0
#define PLAYER  1
#define PLANE  2
#define ENEMY 3
uniform int object_id;

uniform vec4 bbox_min;
uniform vec4 bbox_max;

uniform sampler2D TextureImage0;
uniform sampler2D TextureImage1;
uniform sampler2D TextureImage2;
uniform sampler2D TextureImage3;

out vec4 color;

void main()
{
    vec4 origin = vec4(0.0, 0.0, 0.0, 1.0);
    vec4 camera_position = inverse(view) * origin;
    vec4 p = position_world;
    vec4 n = normalize(normal);
    vec4 l = normalize(vec4(0.5, 1.0, 0.5, 0.0));
    vec4 v = normalize(camera_position - p);
    vec4 r = -l + 2 * n * (dot(n, l));

    vec3 Kd;
    vec3 Ks;
    vec3 Ka;
    float q;

    vec3 textureColor = vec3(1.0, 1.0, 1.0); // Default white color

    if (object_id == WALL)
    {
        Kd = vec3(0.8, 0.4, 0.08);
        Ks = vec3(0.2, 0.2, 0.2); // Refletividade especular
        Ka = vec3(0.5, 0.3, 0.1); // Refletividade ambiente
        q = 10.0;
        textureColor = texture(TextureImage3, tex_coords * 0.1).rgb;
    }
    else if (object_id == PLAYER)
    {
        float minx = bbox_min.x;
        float maxx = bbox_max.x;
        float miny = bbox_min.y;
        float maxy = bbox_max.y;
        float U = (position_model.x - minx) / (maxx - minx);
        float V = (position_model.y - miny) / (maxy - miny);
        Kd = vec3(0.08, 0.4, 0.8);
        Ks = vec3(0.8, 0.8, 0.8);
        Ka = vec3(0.04, 0.2, 0.4);
        q = 32.0;
        textureColor = texture(TextureImage0, tex_coords).rgb;
    }
    else if (object_id == PLANE)
    {
        Kd = vec3(0.3, 0.3, 0.3); // Refletividade difusa
        Ks = vec3(0.2, 0.2, 0.2); // Refletividade especular
        Ka = vec3(0.2, 0.2, 0.2); // Refletividade ambiente
        q = 20.0;
        textureColor = texture(TextureImage2, tex_coords * 0.0).rgb;
    }
    else if (object_id == ENEMY)
    {
        Kd = vec3(0.8, 0.8, 0.7);
        Ks = vec3(0.3, 0.3, 0.3);
        Ka = vec3(0.4, 0.4, 0.35);
        q = 10.0;
        textureColor = texture(TextureImage1, tex_coords).rgb;
    }
    else
    {
        Kd = vec3(0.0, 0.0, 0.0);
        Ks = vec3(0.0, 0.0, 0.0);
        Ka = vec3(0.0, 0.0, 0.0);
        q = 1.0;
    }

    vec3 I = vec3(2.0, 2.0, 2.0); // Intensidade da luz
    vec3 Ia = vec3(0.5, 0.5, 0.5); // Intensidade da luz ambiente global
    vec3 lambert_diffuse_term = Kd * I * max(0, dot(n, l));
    vec3 ambient_term = Ka * Ia;
    vec3 phong_specular_term = Ks * I * pow(max(0, dot(r, v)), q);

    vec3 finalColor = (lambert_diffuse_term + ambient_term + phong_specular_term) * textureColor;

    color = vec4(finalColor, 1.0);

    // Debugging output
    // Cor vermelha indica que textura não foi aplicada
    if (textureColor == vec3(0.0, 0.0, 0.0)) {
        color.rgb = vec3(1.0, 0.0, 0.0); 
    }
}