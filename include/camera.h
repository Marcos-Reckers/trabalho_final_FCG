#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

void UpdatePlayerPos(glm::vec3 horizontal_direction, glm::vec3 camera_right);
void UpdateCamera(float elapsedTime);

#endif // CAMERA_H