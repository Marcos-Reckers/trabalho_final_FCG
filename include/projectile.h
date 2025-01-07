#ifndef PROJECTILE_H
#define PROJECTILE_H

#include <vector>
#include <cstdlib>
#include <ctime>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glad/glad.h>

struct Projectile
{
    glm::vec3 position;
    glm::vec3 direction;
    float speed;

    Projectile(glm::vec3 pos, glm::vec3 dir, float spd)
        : position(pos), direction(dir), speed(spd) {}
};

void UpdateProjectiles(std::vector<Projectile> &projectiles, float elapsedTime);
void DrawProjectiles(const std::vector<Projectile> &projectiles);

#endif // PROJECTILE_H
