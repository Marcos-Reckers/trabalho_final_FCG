#include <glad/glad.h>  // Include glad before any other OpenGL headers
#include <GLFW/glfw3.h> // Include GLFW after glad

#include "renderer.h"
#include "global.h"
#include <glm/gtc/type_ptr.hpp>
#include "matrices.h"

void RenderInit() {
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glFrontFace(GL_CCW);

    LoadShadersFromFiles();
}

void ClearBuffers(){
    // Definimos a cor do "fundo" do framebuffer como branco.
    //           R     G     B     A
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    // "Pintamos" os pixels do framebuffer com a cor definida acima,
    // e também resetamos todos os pixels do Z-buffer (depth buffer).
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

}

// Enviamos as matrizes "view" e "projection" para a GPU.
// Veja o arquivo "shader_vertex.glsl", onde estas são
void SendMatricesToGPU(const glm::mat4& view, const glm::mat4& projection, const glm::mat4& model)
{
    glUniformMatrix4fv(g_view_uniform, 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(g_projection_uniform, 1, GL_FALSE, glm::value_ptr(projection));
}
void RenderModel(const char* model_name, const glm::mat4& model_matrix, int object_id)
{
    glUniformMatrix4fv(g_model_uniform, 1, GL_FALSE, glm::value_ptr(model_matrix));
    glUniform1i(g_object_id_uniform, object_id);

    static GLuint last_texture_id = 0;
    GLuint current_texture_id = g_VirtualScene[model_name].texture_id;

    // Bind the appropriate texture based on the object ID
    if (object_id == PLAYER)
    {
        if (last_texture_id != current_texture_id)
        {
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, current_texture_id);
            glUniform1i(g_texture0_uniform, 0);
            last_texture_id = current_texture_id;
        }
    }
    else if (object_id == ENEMY)
    {
        if (last_texture_id != current_texture_id)
        {
            glActiveTexture(GL_TEXTURE1);
            glBindTexture(GL_TEXTURE_2D, current_texture_id);
            glUniform1i(g_texture1_uniform, 1);
            last_texture_id = current_texture_id;
        }
    }
    else if (object_id == WALL)
    {
        if (last_texture_id != current_texture_id)
        {
            glActiveTexture(GL_TEXTURE3);
            glBindTexture(GL_TEXTURE_2D, current_texture_id);
            glUniform1i(g_texture3_uniform, 3);
            last_texture_id = current_texture_id;
        }
    }
    else if (object_id == PLANE)
    {
        if (last_texture_id != current_texture_id)
        {
            glActiveTexture(GL_TEXTURE2);
            glBindTexture(GL_TEXTURE_2D, current_texture_id);
            glUniform1i(g_texture2_uniform, 2);
            last_texture_id = current_texture_id;
        }
    }
    else if (object_id == BONUS)
    {
        if (last_texture_id != current_texture_id)
        {
            glActiveTexture(GL_TEXTURE4);
            glBindTexture(GL_TEXTURE_2D, current_texture_id);
            glUniform1i(g_texture4_uniform, 4);
            last_texture_id = current_texture_id;
        }
    }
    else if (object_id == PROJECTILE)
    {
        if (last_texture_id != current_texture_id)
        {
            glActiveTexture(GL_TEXTURE5);
            glBindTexture(GL_TEXTURE_2D, current_texture_id);
            glUniform1i(g_texture5_uniform, 5);
            last_texture_id = current_texture_id;
        }
    }
    else
    {
        printf("ERRO: ID de objeto desconhecido.\n");
    }
    
    DrawVirtualObject(model_name);
}

void DrawVirtualObject(const char* object_name)
{
    // "Ligamos" o VAO. Informamos que queremos utilizar os atributos de
    // vértices apontados pelo VAO criado pela função BuildTrianglesAndAddToVirtualScene(). Veja
    // comentários detalhados dentro da definição de BuildTrianglesAndAddToVirtualScene().
    glBindVertexArray(g_VirtualScene[object_name].vertex_array_object_id);

    // Setamos as variáveis "bbox_min" e "bbox_max" do fragment shader
    // com os parâmetros da axis-aligned bounding box (AABB) do modelo.
    glm::vec3 bbox_min = g_VirtualScene[object_name].bbox_min;
    glm::vec3 bbox_max = g_VirtualScene[object_name].bbox_max;
    glUniform4f(g_bbox_min_uniform, bbox_min.x, bbox_min.y, bbox_min.z, 1.0f);
    glUniform4f(g_bbox_max_uniform, bbox_max.x, bbox_max.y, bbox_max.z, 1.0f);

    // Pedimos para a GPU rasterizar os vértices dos eixos XYZ
    // apontados pelo VAO como linhas. Veja a definição de
    // g_VirtualScene[""] dentro da função BuildTrianglesAndAddToVirtualScene(), e veja
    // a documentação da função glDrawElements() em
    // http://docs.gl/gl3/glDrawElements.
    glDrawElements(
        g_VirtualScene[object_name].rendering_mode,
        g_VirtualScene[object_name].num_indices,
        GL_UNSIGNED_INT,
        (void*)(g_VirtualScene[object_name].first_index * sizeof(GLuint))
    );

    // "Desligamos" o VAO, evitando assim que operações posteriores venham a
    // alterar o mesmo. Isso evita bugs.
    glBindVertexArray(0);
}