#ifndef COLLISIONS_H
#define COLLISIONS_H

#include <glm/vec3.hpp>

struct AABB {
    glm::vec3 min;
    glm::vec3 max;
};

struct Plane {
    glm::vec3 normal;
    float distance;
};

AABB CreateBoundingBox(const glm::vec3 &center, float halfSize);
bool CheckDotSphereCollision(const glm::vec3 &playerPos, const glm::vec3 &bonusCenter, float bonusRadius, float deltaTime, float &playerVelocity);
bool CheckCubeCubeCollision(const AABB &a, const AABB &b, float &A_Velocity, float &B_Velocity, float deltaTime);
bool CheckCubePlaneCollision(const AABB &box, const Plane &plane, float &velocity, float deltaTime);
void UpdateBaundingBox(AABB &box, const glm::vec3 &center, float halfSize);
void DrawBoundingBox(const AABB &box); // Adicionar a declaração da função DrawBoundingBox

#endif // COLLISIONS_H
