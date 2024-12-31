
#include "enemy.h"



// Declare the DrawCube function
void DrawCube()
{
    // Implement the cube drawing logic here
    // For example, you can use OpenGL functions to draw a cube
    // This is a placeholder implementation
    glBegin(GL_QUADS);
    // Front face
    glVertex3f(-0.5f, -0.5f,  0.5f);
    glVertex3f( 0.5f, -0.5f,  0.5f);
    glVertex3f( 0.5f,  0.5f,  0.5f);
    glVertex3f(-0.5f,  0.5f,  0.5f);
    // Other faces...
    glEnd();
}

std::vector<Enemy> enemies;

void InitializeEnemies(int numEnemies)
{
    srand(static_cast<unsigned int>(time(0)));
    for (int i = 0; i < numEnemies; ++i)
    {
        Enemy enemy;
        enemy.position = glm::vec3(
            static_cast<float>(rand() % 20 - 10), // X posição aleatória entre -10 e 10
            1.0f,                                 // Y posição fixa no chão
            static_cast<float>(rand() % 20 - 10)  // Z posição aleatória entre -10 e 10
        );
        enemies.push_back(enemy);
    }
}
void UpdateEnemies(float elapsedTime, const glm::vec3& g_PlayerPosition)
{
    float enemySpeed = 0.5f; // Velocidade dos inimigos
    for (auto &enemy : enemies)
    {
        glm::vec3 direction = glm::normalize(g_PlayerPosition - enemy.position);
        enemy.position += direction * enemySpeed * elapsedTime;
    }
}
void DrawEnemies()
{
    for (const auto &enemy : enemies)
    {
        glm::mat4 model = glm::translate(glm::mat4(1.0f), enemy.position);
        glUniformMatrix4fv(g_model_uniform, 1, GL_FALSE, glm::value_ptr(model));
        DrawCube(); // Supondo que você tenha uma função para desenhar um cubo
    }
}