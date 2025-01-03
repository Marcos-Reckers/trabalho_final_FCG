#ifndef ENEMY_H
#define ENEMY_H
#include <vector>
#include <cstdlib>
#include <ctime>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glad/glad.h>

// Declare the uniform location variable
extern GLint g_model_uniform;

// Declare the DrawCube function
void DrawCube();


// Structure to represent an enemy
struct Enemy {
    glm::vec3 position;
    float rotation;
};

// Vector to store enemies
extern std::vector<Enemy> enemies;

// Function to initialize enemies with random positions
void InitializeEnemies(int numEnemies, const glm::vec3& playerPosition);

// Function to update the position of enemies to follow the player
void UpdateEnemies(float elapsedTime, const glm::vec3& g_PlayerPosition);

// Function to draw enemies on the screen
void DrawEnemies();

#endif // ENEMY_HPP