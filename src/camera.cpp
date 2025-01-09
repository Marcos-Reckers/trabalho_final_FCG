#include "camera.h"
#include "global.h"
#include "matrices.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "projectile.h"
#include <iostream>
#include "collisions.h"

glm::vec4 camera_view_vector;

void UpdatePlayerPos(glm::vec3 horizontal_direction, glm::vec3 camera_right, float elapsedTime)
{
    int keys_pressed = front + back + left + right;
    float player_speed = g_PlayerSpeed;
    if (keys_pressed > 1)
        player_speed /= sqrt(2.0f);
    // Atualiza a posição do jogador com base nas teclas pressionadas
    if (front)
        g_PlayerPosition += player_speed * horizontal_direction * elapsedTime;
    if (back)
        g_PlayerPosition -= player_speed * horizontal_direction * elapsedTime;
    if (left)
        g_PlayerPosition -= player_speed * camera_right * elapsedTime;
    if (right)
        g_PlayerPosition += player_speed * camera_right * elapsedTime;

    // Atualiza a orientação do jogador.
    glm::vec3 player_forward = -horizontal_direction; // Direção horizontal da câmera
    float angle = atan2(player_forward.z, player_forward.x);
    g_PlayerRotation = glm::rotate(glm::mat4(1.0f), (-angle - 1.6f), glm::vec3(0.0f, 1.0f, 0.0f));

    if (g_PlayerPosition.y < 0.0f)
        g_PlayerPosition.y = 0.0f;
}

glm::vec3 BezierCurve(glm::vec3 p0, glm::vec3 p1, glm::vec3 p2, glm::vec3 p3, float t)
{
    float u = 1.0f - t;
    float tt = t * t;
    float uu = u * u;
    float uuu = uu * u;
    float ttt = tt * t;

    glm::vec3 p = uuu * p0; // (1-t)^3 * p0
    p += 5 * uu * t * p1;   // 3 * (1-t)^2 * t * p1
    p += 5 * u * tt * p2;   // 3 * (1-t) * t^2 * p2
    p += ttt * p3;          // t^3 * p3

    return p;
}

extern std::vector<Projectile> projectiles;
extern float lastShotTime;

void UpdateCamera(float elapsedTime)
{
    static bool animationComplete = false;
    static float animationTime = 0.0f;
    static glm::vec3 initialPosition = glm::vec3(0.0f, 10.0f, 0.0f);                                       // Posição inicial da câmera
    static glm::vec3 controlPoint1 = glm::vec3(5.0f, 7.0f, 5.0f);                                          // Primeiro ponto de controle
    static glm::vec3 controlPoint2 = glm::vec3(-5.0f, 3.0f, -5.0f);                                        // Segundo ponto de controle
    static glm::vec3 finalPosition = g_PlayerPosition + glm::vec3(0.0f, g_CameraHeight, g_CameraDistance); // Posição final da câmera

    if (!animationComplete)
    {
        animationTime += elapsedTime;
        float t = animationTime / 5.0f; // Normaliza o tempo para 3 segundos

        if (t >= 1.0f)
        {
            t = 1.0f;
            animationComplete = true;
            g_enemySpeed = 4.0f;
        }

        glm::vec3 camera_position = BezierCurve(initialPosition, controlPoint1, controlPoint2, finalPosition, t);
        glm::vec4 camera_lookat_l = glm::vec4(g_PlayerPosition, 1.0f);                                // Ponto "l", para onde a câmera (look-at) estará sempre olhando
        glm::vec4 camera_view_vector = glm::vec4(camera_lookat_l - glm::vec4(camera_position, 1.0f)); // Vetor "view", sentido para onde a câmera está virada
        glm::vec4 camera_up_vector = glm::vec4(0.0f, 1.0f, 0.0f, 0.0f);                               // Vetor "up" fixado para apontar para o "céu" (eito Y global)
        glm::mat4 view = Matrix_Camera_View(glm::vec4(camera_position, 1.0f), camera_view_vector, camera_up_vector);

        // Agora computamos a matriz de Projeção.
        glm::mat4 projection;
        float nearplane = -0.1f;  // Posição do "near plane"
        float farplane = -200.0f; // Posição do "far plane"
        float field_of_view = 3.141592 / 3.0f;
        projection = Matrix_Perspective(field_of_view, g_ScreenRatio, nearplane, farplane);

        // Enviamos as matrizes "view" e "projection" para a placa de vídeo (GPU).
        glUniformMatrix4fv(g_view_uniform, 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(g_projection_uniform, 1, GL_FALSE, glm::value_ptr(projection));
    }
    else
    {
        // Limite o ângulo vertical da câmera para estar entre -π/3 e π/3
        float max_vertical_angle = glm::pi<float>() / 3.0f; // 60º em radianos
        if (g_CameraPhi > max_vertical_angle)
            g_CameraPhi = max_vertical_angle;
        if (g_CameraPhi < -max_vertical_angle)
            g_CameraPhi = -max_vertical_angle;

        // Abaixo definimos as varáveis que efetivamente definem a câmera virtual.
          // Definição de vetores utilizados no controle da câmera.
        glm::vec3 camera_direction = glm::normalize(glm::vec3(camera_view_vector));
        glm::vec3 horizontal_direction = glm::normalize(glm::vec3(camera_direction.x, 0.0f, camera_direction.z));
        glm::vec3 camera_right = glm::normalize(glm::cross(camera_direction, glm::vec3(0.0f, 1.0f, 0.0f)));
        UpdatePlayerPos(horizontal_direction, camera_right, elapsedTime);
        glm::vec4 camera_lookat_l = glm::vec4(g_PlayerPosition, 1.0f); // Ponto "l", para onde a câmera (look-at) estará sempre olhando
        float radius = g_CameraDistance;
        float x = g_PlayerPosition.x + radius * -cos(g_CameraPhi) * cos(g_CameraTheta);
        float y = g_PlayerPosition.y + radius * sin(g_CameraPhi);
        float z = g_PlayerPosition.z + radius * cos(g_CameraPhi) * sin(g_CameraTheta);
        glm::vec4 camera_position_c = glm::vec4(x, y, z, 1.0f);
        camera_view_vector = camera_lookat_l - camera_position_c;       // Vetor "view", sentido para onde a câmera está virada
        glm::vec4 camera_up_vector = glm::vec4(0.0f, 1.0f, 0.0f, 0.0f); // Vetor "up" fixado para apontar para o "céu" (eito Y global)
        glm::mat4 view = Matrix_Camera_View(camera_position_c, camera_view_vector, camera_up_vector);

        // Agora computamos a matriz de Projeção.
        glm::mat4 projection;

        // Note que, no sistema de coordenadas da câmera, os planos near e far
        // estão no sentido negativo! Veja slides 176-204 do documento Aula_09_Projecoes.pdf.
        float nearplane = -0.1f;  // Posição do "near plane"
        float farplane = -200.0f; // Posição do "far plane"

        // Projeção Perspectiva.
        // Para definição do field of view (FOV), veja slides 205-215 do documento Aula_09_Projecoes.pdf.
        float field_of_view = 3.141592 / 3.0f;
        projection = Matrix_Perspective(field_of_view, g_ScreenRatio, nearplane, farplane);

        // Enviamos as matrizes "view" e "projection" para a placa de vídeo
        // (GPU). Veja o arquivo "shader_vertex.glsl", onde estas são
        // efetivamente aplicadas em todos os pontos.
        glUniformMatrix4fv(g_view_uniform, 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(g_projection_uniform, 1, GL_FALSE, glm::value_ptr(projection));

        UpdateBaundingBox(g_Playerbbox, g_PlayerPosition, 1.5f); // Atualizar a bounding box do jogador
        DrawBoundingBox(g_Playerbbox); // Desenhar a bounding box do jogador
    }

    if (g_LeftMouseButtonPressed && (glfwGetTime() - lastShotTime) >= 1.0f)
    {
        glm::vec3 direction = glm::normalize(glm::vec3(camera_view_vector));
        direction.y = 0.0f;

        projectiles.push_back(Projectile(g_PlayerPosition, direction, 25.0f, 3.0f));
        lastShotTime = glfwGetTime();
    }
}