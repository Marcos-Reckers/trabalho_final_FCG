#include "camera.h"
#include "global.h"
#include "matrices.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

void UpdatePlayerPos(glm::vec3 horizontal_direction, glm::vec3 camera_right){
    // Atualiza a posição do jogador com base nas teclas pressionadas
        if (front)
            g_PlayerPosition += g_PlayerSpeed * horizontal_direction;
        if (back)
            g_PlayerPosition -= g_PlayerSpeed * horizontal_direction;
        if (left)
            g_PlayerPosition -= g_PlayerSpeed * camera_right;
        if (right)
            g_PlayerPosition += g_PlayerSpeed * camera_right;

        // Atualiza a orientação do jogador.
        glm::vec3 player_forward = -horizontal_direction; // Direção horizontal da câmera
        float angle = atan2(player_forward.z, player_forward.x);
        g_PlayerRotation = glm::rotate(glm::mat4(1.0f), (-angle - 1.6f), glm::vec3(0.0f, 1.0f, 0.0f));
}

void UpdateCamera(){
    // Abaixo definimos as varáveis que efetivamente definem a câmera virtual.
        glm::vec4 camera_lookat_l = glm::vec4(g_PlayerPosition, 1.0f); // Ponto "l", para onde a câmera (look-at) estará sempre olhando
        float radius = g_CameraDistance;
        float x = g_PlayerPosition.x + radius * -cos(g_CameraPhi) * cos(g_CameraTheta);
        float y = g_PlayerPosition.y + radius * sin(g_CameraPhi);
        float z = g_PlayerPosition.z + radius * cos(g_CameraPhi) * sin(g_CameraTheta);
        glm::vec4 camera_position_c = glm::vec4(x, y, z, 1.0f);
        glm::vec4 camera_view_vector = camera_lookat_l - camera_position_c; // Vetor "view", sentido para onde a câmera está virada
        glm::vec4 camera_up_vector = glm::vec4(0.0f, 1.0f, 0.0f, 0.0f);     // Vetor "up" fixado para apontar para o "céu" (eito Y global)
        // Computamos a matriz "View" utilizando os parâmetros da câmera para
        // definir o sistema de coordenadas da câmera.
        glm::mat4 view = Matrix_Camera_View(camera_position_c, camera_view_vector, camera_up_vector);
        
        // Definição de vetores utilizados no controle da câmera.
        glm::vec3 camera_direction = glm::normalize(glm::vec3(camera_view_vector));
        glm::vec3 horizontal_direction = glm::normalize(glm::vec3(camera_direction.x, 0.0f, camera_direction.z));
        glm::vec3 camera_right = glm::normalize(glm::cross(camera_direction, glm::vec3(0.0f, 1.0f, 0.0f)));


        UpdatePlayerPos(horizontal_direction, camera_right);
        
        // Atualiza posição da camera após movimento do jogador.
        glm::vec3 camera_position = g_PlayerPosition - camera_direction * g_CameraDistance;
        camera_position.y = g_CameraHeight; // Mantém a altura constante

        // Agora computamos a matriz de Projeção.
        glm::mat4 projection;

        // Note que, no sistema de coordenadas da câmera, os planos near e far
        // estão no sentido negativo! Veja slides 176-204 do documento Aula_09_Projecoes.pdf.
        float nearplane = -0.1f;  // Posição do "near plane"
        float farplane = -100.0f; // Posição do "far plane"

        // Projeção Perspectiva.
        // Para definição do field of view (FOV), veja slides 205-215 do documento Aula_09_Projecoes.pdf.
        float field_of_view = 3.141592 / 3.0f;
        projection = Matrix_Perspective(field_of_view, g_ScreenRatio, nearplane, farplane);

        // Enviamos as matrizes "view" e "projection" para a placa de vídeo
        // (GPU). Veja o arquivo "shader_vertex.glsl", onde estas são
        // efetivamente aplicadas em todos os pontos.
        glUniformMatrix4fv(g_view_uniform, 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(g_projection_uniform, 1, GL_FALSE, glm::value_ptr(projection));
}