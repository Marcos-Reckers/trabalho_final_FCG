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
    ObjModel wallmodel("../../data/wall.obj");
    ComputeNormals(&wallmodel);
    BuildTrianglesAndAddToVirtualScene(&wallmodel);

    ObjModel playermodel("../../data/player.obj");
    ComputeNormals(&playermodel);
    BuildTrianglesAndAddToVirtualScene(&playermodel);

    ObjModel planemodel("../../data/plane.obj");
    ComputeNormals(&planemodel);
    BuildTrianglesAndAddToVirtualScene(&planemodel);

    ObjModel enemymodel("../../data/enemy.obj");
    ComputeNormals(&enemymodel);
    BuildTrianglesAndAddToVirtualScene(&enemymodel);

    ObjModel bonusmodel("../../data/Pizza.obj");
    ComputeNormals(&bonusmodel);
    BuildTrianglesAndAddToVirtualScene(&bonusmodel);

    ObjModel projectilemodel("../../data/shuriken.obj");
    ComputeNormals(&projectilemodel);
    BuildTrianglesAndAddToVirtualScene(&projectilemodel);

    if (argc > 1) {
        ObjModel model(argv[1]);
        BuildTrianglesAndAddToVirtualScene(&model);
    }
}