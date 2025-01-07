#include "projectile.h"
#include "renderer.h"
#include "matrices.h"
#include "global.h" // Inclua o arquivo global.h para acessar as variáveis globais
#define PROJECTILE 5

void UpdateProjectiles(std::vector<Projectile> &projectiles, float elapsedTime)
{
    for (auto &proj : projectiles)
    {
        proj.position += proj.direction * proj.speed * elapsedTime;
    }
}

void DrawProjectiles(const std::vector<Projectile> &projectiles)
{
    // static GLuint last_texture_id = 0;
    // for (const auto &proj : projectiles)
    // {
    //     glm::mat4 model = Matrix_Identity();
    //     model = Matrix_Translate(proj.position.x, proj.position.y, proj.position.z) * Matrix_Scale(0.1f, 0.1f, 0.1f);
    //     GLuint current_texture_id = g_VirtualScene["the_enemy"].texture_id;
    //     if (last_texture_id != current_texture_id)
    //     {
    //         glActiveTexture(GL_TEXTURE1);
    //         glBindTexture(GL_TEXTURE_2D, current_texture_id);
    //         glUniform1i(g_texture5_uniform, 5);
    //         last_texture_id = current_texture_id;
    //         printf("Textura do projétil vinculada.\n");
    //     }
        
    //     RenderModel("projectile", model, PROJECTILE);
    // }
    static GLuint last_texture_id = 0;
    for (const auto &projectile : projectiles)
    {
        glm::mat4 model = Matrix_Identity();
        model = glm::translate(glm::mat4(1.0f), projectile.position);
        model = glm::rotate(model, static_cast<float>(glfwGetTime()*10), glm::vec3(0.0f, 1.0f, 0.0f)); // Gira em volta do próprio eixo Y
        // model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f)); // Reduz o tamanho para 1/4

        GLuint current_texture_id = g_VirtualScene["shuriken"].texture_id;
        if (last_texture_id != current_texture_id)
        {
            glActiveTexture(GL_TEXTURE5);
            glBindTexture(GL_TEXTURE_2D, current_texture_id);
            glUniform1i(g_texture5_uniform, 5);
            last_texture_id = current_texture_id;
            printf("Textura do shuriken vinculada.\n");
        }
        RenderModel("shuriken", model, PROJECTILE);
    }
}
