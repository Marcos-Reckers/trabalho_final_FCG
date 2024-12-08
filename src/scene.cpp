#include <cmath>
#include <cstdio>
#include <cstdlib>

// Headers das bibliotecas OpenGL
#include <glad/glad.h>  // Criação de contexto OpenGL 3.3
#include <GLFW/glfw3.h> // Criação de janelas do sistema operacional

#include "scene.h"
#include "utils.h"
#include "global.h"
#include "renderer.h"

void LoadModels(int argc, char *argv[]) {
    ObjModel spheremodel("../../data/wall.obj");
    ComputeNormals(&spheremodel);
    BuildTrianglesAndAddToVirtualScene(&spheremodel);

    ObjModel bunnymodel("../../data/bunny.obj");
    ComputeNormals(&bunnymodel);
    BuildTrianglesAndAddToVirtualScene(&bunnymodel);

    ObjModel planemodel("../../data/plane.obj");
    ComputeNormals(&planemodel);
    BuildTrianglesAndAddToVirtualScene(&planemodel);

    if (argc > 1) {
        ObjModel model(argv[1]);
        BuildTrianglesAndAddToVirtualScene(&model);
    }
}