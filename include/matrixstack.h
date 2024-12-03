#ifndef MATRIXSTACK_H
#define MATRIXSTACK_H

#include <glm/mat4x4.hpp>

// Declarações de funções de pilha de matrizes
void PushMatrix(glm::mat4 M);
void PopMatrix(glm::mat4 &M);

#endif