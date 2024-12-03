#ifndef SCENE_H
#define SCENE_H

//#include <string>
#include <GLFW/glfw3.h>
#include "objmodel.h"

// Definimos uma estrutura que armazenará dados necessários para renderizar
// cada objeto da cena virtual.
struct SceneObject
{
    std::string name;              // Nome do objeto
    size_t first_index;            // Índice do primeiro vértice dentro do vetor indices[] definido em BuildTrianglesAndAddToVirtualScene()
    size_t num_indices;            // Número de índices do objeto dentro do vetor indices[] definido em BuildTrianglesAndAddToVirtualScene()
    GLenum rendering_mode;         // Modo de rasterização (GL_TRIANGLES, GL_TRIANGLE_STRIP, etc.)
    GLuint vertex_array_object_id; // ID do VAO onde estão armazenados os atributos do modelo
};

// Funções relacionadas à cena
void BuildTrianglesAndAddToVirtualScene(ObjModel *model);
void DrawVirtualObject(const char *object_name);

#endif