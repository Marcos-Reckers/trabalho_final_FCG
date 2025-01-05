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

out vec4 color;

#define M_PI   3.14159265358979323846
#define M_PI_2 1.57079632679489661923

void main()
{
    vec4 origin = vec4(0.0, 0.0, 0.0, 1.0);
    vec4 camera_position = inverse(view) * origin;
    vec4 p = position_world;
    vec4 n = normalize(normal);
    vec4 l = normalize(vec4(1.0,1.0,0.5,0.0));
    vec4 v = normalize(camera_position - p);
    vec4 r = -l + 2*n*(dot(n,l));

    vec3 Kd;
    vec3 Ks;
    vec3 Ka;
    float q;

    if ( object_id == WALL )
    {
        Kd = vec3(0.8,0.4,0.08);
        Ks = vec3(0.0,0.0,0.0);
        Ka = vec3(0.4,0.2,0.04);
        q = 1.0;
    }
    else if ( object_id == PLAYER )
    {
        float minx = bbox_min.x;
        float maxx = bbox_max.x;
        float miny = bbox_min.y;
        float maxy = bbox_max.y;
        float U = (position_model.x - minx) / (maxx - minx);
        float V = (position_model.y - miny) / (maxy - miny);
        Kd = vec3(0.08,0.4,0.8);
        Ks = vec3(0.8,0.8,0.8);
        Ka = vec3(0.04,0.2,0.4);
        q = 32.0;
        vec3 Kd0 = texture(TextureImage0, tex_coords).rgb;
        float lambert = max(0,dot(n,l));
        color.rgb = Kd0 * (lambert + 0.01);
        color.a = 1;
        color.rgb = pow(color.rgb, vec3(1.0,1.0,1.0)/2.2);
    }
    else if ( object_id == PLANE )
    {
        Kd = vec3(0.2,0.2,0.2);
        Ks = vec3(0.3,0.3,0.3);
        Ka = vec3(0.0,0.0,0.0);
        q = 20.0;
    }
    else if ( object_id == ENEMY )
    {
        Kd = vec3(0.8, 0.8, 0.7);
        Ks = vec3(0.3, 0.3, 0.3);
        Ka = vec3(0.4, 0.4, 0.35);
        q = 10.0;
    }
    else
    {
        Kd = vec3(0.0,0.0,0.0);
        Ks = vec3(0.0,0.0,0.0);
        Ka = vec3(0.0,0.0,0.0);
        q = 1.0;
    }

    vec3 I = vec3(1.0,1.0,1.0);
    vec3 Ia = vec3(0.2,0.2,0.2);
    vec3 lambert_diffuse_term = Kd * I * max(0, dot(n,l));
    vec3 ambient_term = Ka * Ia;
    vec3 phong_specular_term  = Ks * I * pow(max(0, dot(r,v)), q);
    color.a = 1;
    color.rgb = lambert_diffuse_term + ambient_term + phong_specular_term;
    color.rgb = pow(color.rgb, vec3(1.0,1.0,1.0)/2.2);
}