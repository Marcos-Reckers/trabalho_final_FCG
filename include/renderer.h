#ifndef RENDERER_H
#define RENDERER_H

#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>
#include <string>
#include "shaders.h"
#include "objmodel.h"

// Initialize the rendering context (OpenGL settings, shaders, etc.)
void RenderInit();

// Clear the buffers (color and depth buffers)
void ClearBuffers();

// Function to send the "view" and "projection" matrices to the GPU
void SendMatricesToGPU(const glm::mat4& view, const glm::mat4& projection, const glm::mat4& model); 

// Renderiza um modelo específico com sua transformação e ID de objeto
void RenderModel(const char* model_name, const glm::mat4& model_matrix, int object_id);

// Função que desenha um objeto armazenado em g_VirtualScene.
void DrawVirtualObject(const char *object_name);

// Funções para desenhar objetos específicos
void DrawPlayer();

#endif // RENDERER_H
