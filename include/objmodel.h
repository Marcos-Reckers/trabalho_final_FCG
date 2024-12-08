#ifndef OBJMODEL_H
#define OBJMODEL_H

#include <tiny_obj_loader.h>
#include <string>
#include <vector>
#include <stdexcept>
#include <cstdio> // Para printf e fprintf

// Estrutura que representa um modelo geométrico carregado a partir de um
// arquivo ".obj". Veja https://en.wikipedia.org/wiki/Wavefront_.obj_file .
struct ObjModel
{
public:
    tinyobj::attrib_t attrib;
    std::vector<tinyobj::shape_t> shapes;
    std::vector<tinyobj::material_t> materials;

    // Construtor que carrega o modelo
    ObjModel(const char *filename, const char *basepath = nullptr, bool triangulate = true);
};

// Computa normais de um ObjModel, caso não existam.
void ComputeNormals(ObjModel *model);

// Função para debugging
void PrintObjModelInfo(ObjModel *model);

// Constrói triângulos para futura renderização a partir de um ObjModel.
void BuildTrianglesAndAddToVirtualScene(ObjModel *model);

#endif // OBJMODEL_H
