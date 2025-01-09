#include "enemy.h"
#include "matrices.h"
#include "renderer.h"
#include "global.h" // Inclua o arquivo global.h para acessar as variáveis globais

#define ENEMY 3
#define ENEMY_HEIGHT 1.0f

// Declare the DrawCube function
void DrawCube()
{
    glBegin(GL_QUADS);
    glVertex3f(-0.5f, -0.5f, 0.5f);
    glVertex3f(0.5f, -0.5f, 0.5f);
    glVertex3f(0.5f, 0.5f, 0.5f);
    glVertex3f(-0.5f, 0.5f, 0.5f);
    glEnd();
}

std::vector<Enemy> enemies;

void InitializeEnemies(int numEnemies, const glm::vec3 &playerPosition)
{
    srand(static_cast<unsigned int>(time(0)));
    for (int i = 0; i < numEnemies; ++i)
    {
        Enemy enemy;
        do
        {
            enemy.position = glm::vec3(
                static_cast<float>(rand() % 60 - 30), // X posição aleatória entre -30 e 30
                ENEMY_HEIGHT,                         // Y posição fixa no chão
                static_cast<float>(rand() % 60 - 30)  // Z posição aleatória entre -30 e 30
            );
        } while (glm::distance(enemy.position, playerPosition) < 30.0f);

        enemy.bbox = CreateBoundingBox(enemy.position, 1.5f); // Ajuste o tamanho da bounding box
        enemies.push_back(enemy);
    }
}

void UpdateEnemies(float elapsedTime, const glm::vec3 &g_PlayerPosition)
{
    for (auto &enemy : enemies)
    {
        glm::vec3 direction = glm::normalize(g_PlayerPosition - enemy.position);
        enemy.position += direction * g_enemySpeed * elapsedTime;
        enemy.position.y = ENEMY_HEIGHT;
        UpdateBaundingBox(enemy.bbox, enemy.position, 1.5f); // Ajuste o tamanho da bounding box

        // Calcula ângulo de rotação do inimigo para olhar para o jogador
        enemy.rotation = -atan2(direction.z, direction.x);
    }
}

void DrawEnemies()
{
    static GLuint last_texture_id = 0;
    for (const auto &enemy : enemies)
    {
        glm::mat4 model = Matrix_Identity();
        // Aplica translação e rotação ao modelo
        model = glm::translate(glm::mat4(1.0f), enemy.position);
        model = glm::rotate(model, enemy.rotation, glm::vec3(0.0f, 1.0f, 0.0f));

        // Renderiza o modelo do inimigo
        GLuint current_texture_id = g_VirtualScene["the_enemy"].texture_id;
        if (last_texture_id != current_texture_id)
        {
            glActiveTexture(GL_TEXTURE1);
            glBindTexture(GL_TEXTURE_2D, current_texture_id);
            glUniform1i(g_texture1_uniform, 1);
            last_texture_id = current_texture_id;
            printf("Textura do inimigo vinculada.\n");
        }
        RenderModel("the_enemy", model, ENEMY);
        DrawBoundingBox(enemy.bbox); // Desenhar a bounding box
    }
}