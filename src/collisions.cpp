#include "collisions.h"
#include <glm/glm.hpp>
#include <vector>
#include <iostream>
#include "enemy.h"
#include "renderer.h"

AABB CreateBoundingBox(const glm::vec3 &center, float halfSize)
{
    AABB box;
    box.min = glm::vec3(center.x - halfSize, center.y - halfSize, center.z - halfSize);
    box.max = glm::vec3(center.x + halfSize, center.y + halfSize, center.z + halfSize);
    std::cout << "Created bounding box. Box min: " << box.min.x << " " << box.min.y << " " << box.min.z << std::endl;
    return box;
}

bool CheckDotSphereCollision(const glm::vec3 &dot_Pos, const glm::vec3 &sphereCenter, float sphereRadius, float deltaTime, float &playerVelocity)
{
    // Calcula a nova posição do jogador.
    glm::vec3 newdot_Pos = dot_Pos + playerVelocity * deltaTime;

    // Calcula a distância entre jogador e bonus
    float distance = glm::distance(newdot_Pos, sphereCenter);

    // Verifica se a distancia é menor que o raio da esfera bônus.
    bool teveColisao = distance <= sphereRadius;
    return teveColisao;
}

bool CheckCubeCubeCollision(const AABB &a, const AABB &b, float &A_Velocity, float &B_Velocity, float deltaTime)
{
    // Calcula a nova posição dos cubos.
    AABB newA = a;
    newA.min += A_Velocity * deltaTime;
    newA.max += A_Velocity * deltaTime;

    AABB newB = b;
    newB.min += B_Velocity * deltaTime;
    newB.max += B_Velocity * deltaTime;

    // Verifica se houve colisão.
    bool teveColisao = newA.min.x <= newB.max.x && newA.max.x >= newB.min.x &&
                       newA.min.y <= newB.max.y && newA.max.y >= newB.min.y &&
                       newA.min.z <= newB.max.z && newA.max.z >= newB.min.z;
    return teveColisao;
}

bool CheckCubePlaneCollision(const AABB &box, const Plane &plane, float &velocity, float deltaTime)
{
    // Ponto mais distante ao longo da normal
    glm::vec3 farCorner(
        (plane.normal.x >= 0) ? box.max.x : box.min.x,
        (plane.normal.y >= 0) ? box.max.y : box.min.y,
        (plane.normal.z >= 0) ? box.max.z : box.min.z);

    // Distância do ponto mais distante até o plano
    float dist = glm::dot(farCorner, plane.normal) - plane.distance;

    // Se estiver “atrás” do plano, há colisão
    if (dist >= 0.0f)
    {
        return true;
    }
    return false;
}

void UpdateBaundingBox(AABB &box, const glm::vec3 &center, float halfSize)
{
    box.min = glm::vec3(center.x - halfSize, center.y - halfSize, center.z - halfSize);
    box.max = glm::vec3(center.x + halfSize, center.y + halfSize, center.z + halfSize);

}