#ifndef BONUS_H
#define BONUS_H

#include <vector>
#include <glm/glm.hpp>
#include <glad/glad.h>

// Structure to represent a bonus
struct Bonus {
    glm::vec3 position;
    float initialY;
    glm::vec3 center;
    float radius;
};

// Vector to store bonuses
extern std::vector<Bonus> bonuses;

// Function to initialize bonuses at the corners of the screen
void InitializeBonuses();

// Function to update the position of bonuses to float up and down
void UpdateBonuses(float elapsedTime);

// Function to draw bonuses on the screen
void DrawBonuses();

#endif // BONUS_H