#include "bonus.h"
#include "matrices.h"
#include "renderer.h"
#include "global.h"
#include <glm/gtc/matrix_transform.hpp>


#define BONUS_HEIGHT 1.0f
#define BONUS_FLOAT_AMPLITUDE 0.5f
#define BONUS_FLOAT_SPEED 2.0f

std::vector<Bonus> bonuses;

void InitializeBonuses()
{
    glm::vec3 positions[4] = {
        glm::vec3(-3.0f, BONUS_HEIGHT, -3.0f),
        glm::vec3(3.0f, BONUS_HEIGHT, -3.0f),
        glm::vec3(-3.0f, BONUS_HEIGHT, 3.0f),
        glm::vec3(3.0f, BONUS_HEIGHT, 3.0f)
    };

    for (int i = 0; i < 4; ++i)
    {
        Bonus bonus;
        bonus.position = positions[i];
        bonus.initialY = positions[i].y;
        bonuses.push_back(bonus);
    }
}

void UpdateBonuses(float elapsedTime)
{
    for (auto &bonus : bonuses)
    {
        bonus.position.y = bonus.initialY + BONUS_FLOAT_AMPLITUDE * sin(glfwGetTime() * BONUS_FLOAT_SPEED);
    }
}

void DrawBonuses()
{
    static GLuint last_texture_id = 0;
    for (const auto &bonus : bonuses)
    {
        glm::mat4 model = Matrix_Identity();
        model = glm::translate(glm::mat4(1.0f), bonus.position);

        GLuint current_texture_id = g_VirtualScene["the_pizza"].texture_id;
        if (last_texture_id != current_texture_id)
        {
            glActiveTexture(GL_TEXTURE5);
            glBindTexture(GL_TEXTURE_2D, current_texture_id);
            glUniform1i(g_texture4_uniform, 4);
            last_texture_id = current_texture_id;
            printf("Textura do bônus vinculada.\n");
        }
        RenderModel("the_pizza", model, BONUS);
    }
}
