
#include "enemy.h"
#include "matrices.h"
#include "renderer.h"

#define ENEMY 3
#define ENEMY_HEIGHT 1.0f

// Declare the DrawCube function
void DrawCube()
{
    // Implement the cube drawing logic here
    // For example, you can use OpenGL functions to draw a cube
    // This is a placeholder implementation
    glBegin(GL_QUADS);
    // Front face
    glVertex3f(-0.5f, -0.5f, 0.5f);
    glVertex3f(0.5f, -0.5f, 0.5f);
    glVertex3f(0.5f, 0.5f, 0.5f);
    glVertex3f(-0.5f, 0.5f, 0.5f);
    // Other faces...
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
        } while (glm::distance(enemy.position, playerPosition) < 20.0f);
        enemies.push_back(enemy);
    }
}
void UpdateEnemies(float elapsedTime, const glm::vec3 &g_PlayerPosition)
{
    float enemySpeed = 4.0f; // Velocidade dos inimigos
    for (auto &enemy : enemies)
    {
        glm::vec3 direction = glm::normalize(g_PlayerPosition - enemy.position);
        enemy.position += direction * enemySpeed * elapsedTime;
        enemy.position.y = ENEMY_HEIGHT;

        // Calcula ângulo de rotação do inimigo para olhar para o jogador
        enemy.rotation = -atan2(direction.z, direction.x);
    }
}
void DrawEnemies()
{
    for (const auto &enemy : enemies)
    {
        glm::mat4 model = Matrix_Identity();
        // Aplica translação e rotação ao modelo
        model = glm::translate(glm::mat4(1.0f), enemy.position);
        model = glm::rotate(model, enemy.rotation, glm::vec3(0.0f, 1.0f, 0.0f));

        // Renderiza o modelo do inimigo
        RenderModel("the_enemy", model, ENEMY);
    }
}