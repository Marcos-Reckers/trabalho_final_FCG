#include "projectile.h"
#include "renderer.h"
#include "matrices.h"
#include "global.h" // Inclua o arquivo global.h para acessar as variáveis globais
#include "collisions.h"
#define PROJECTILE 5

void UpdateProjectiles(std::vector<Projectile> &projectiles, float elapsedTime)
{
    for (auto &proj : projectiles)
    {
        proj.position += proj.direction * proj.speed * elapsedTime;
        UpdateBaundingBox(proj.bbox, proj.position, 0.5f);
    }
}

void DrawProjectiles(const std::vector<Projectile> &projectiles)
{
    static GLuint last_texture_id = 0;
    for (const auto &projectile : projectiles)
    {
        glm::mat4 model = Matrix_Identity();
        model = glm::translate(glm::mat4(1.0f), projectile.position);
        model = glm::rotate(model, static_cast<float>(glfwGetTime()*10), glm::vec3(0.0f, 1.0f, 0.0f)); // Gira em volta do próprio eixo Y

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
