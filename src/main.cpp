#include <cmath>
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif
#include <cstdio>
#include <cstdlib>

// Headers abaixo são específicos de C++
#include <map>
#include <stack>
#include <string>
#include <vector>
#include <limits>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <algorithm>

// Headers das bibliotecas OpenGL
#include <glad/glad.h>  // Criação de contexto OpenGL 3.3
#include <GLFW/glfw3.h> // Criação de janelas do sistema operacional

// Headers da biblioteca GLM: criação de matrizes e vetores.
#include <glm/mat4x4.hpp>
#include <glm/vec4.hpp>
#include <glm/gtc/type_ptr.hpp>

// Headers da biblioteca para carregar modelos obj
#include <tiny_obj_loader.h>

// Headers locais, definidos na pasta "include/"
#include "global.h"
#include "utils.h"
#include "matrices.h"
#include "objmodel.h"
#include "scene.h"
#include "shaders.h"
#include "textrendering.h"
#include "callbacks.h"
#include "renderer.h"
#include <math.h>

int main(int argc, char *argv[])
{
    // Inicializamos a biblioteca GLFW, utilizada para criar uma janela do
    // sistema operacional, onde poderemos renderizar com OpenGL.
    int success = glfwInit();
    if (!success)
    {
        fprintf(stderr, "ERROR: glfwInit() failed.\n");
        std::exit(EXIT_FAILURE);
    }

    // Definimos o callback para impressão de erros da GLFW no terminal
    glfwSetErrorCallback(ErrorCallback);

    // Pedimos para utilizar OpenGL versão 3.3 (ou superior)
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // Pedimos para utilizar o perfil "core", isto é, utilizaremos somente as
    // funções modernas de OpenGL.
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Criamos uma janela do sistema operacional, com 800 colunas e 600 linhas
    // de pixels, e com título "INF01047 ...".
    GLFWwindow *window;
    window = glfwCreateWindow(800, 600, "INF01047 - Ninja Survival", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        fprintf(stderr, "ERROR: glfwCreateWindow() failed.\n");
        std::exit(EXIT_FAILURE);
    }
    
    SetCallbacks(window);
    // Define o ângulo incial da câmera para ser o mesmo que o do cursor.
    glfwGetCursorPos(window, &g_LastCursorPosX, &g_LastCursorPosY);

    // Indicamos que as chamadas OpenGL deverão renderizar nesta janela
    glfwMakeContextCurrent(window);

    // Carregamento de todas funções definidas por OpenGL 3.3, utilizando a
    // biblioteca GLAD.
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

    // Definimos a função de callback que será chamada sempre que a janela for redimensionada.
    glfwSetFramebufferSizeCallback(window, FramebufferSizeCallback);
    FramebufferSizeCallback(window, 800, 600);

    // Imprimimos no terminal informações sobre a GPU do sistema
    const GLubyte *vendor = glGetString(GL_VENDOR);
    const GLubyte *renderer = glGetString(GL_RENDERER);
    const GLubyte *glversion = glGetString(GL_VERSION);
    const GLubyte *glslversion = glGetString(GL_SHADING_LANGUAGE_VERSION);

    printf("GPU: %s, %s, OpenGL %s, GLSL %s\n", vendor, renderer, glversion, glslversion);

    // Carregamos os shaders de vértices e de fragmentos que serão utilizados
    // para renderização. Veja slides 180-200 do documento Aula_03_Rendering_Pipeline_Grafico.pdf.
    //
    LoadShadersFromFiles();

    // Construímos a representação de objetos geométricos através de malhas de triângulos
    LoadModels(argc, argv);

    // Inicializamos o código para renderização de texto.
    TextRendering_Init();

    // Habilitamos o Z-buffer. Veja slides 104-116 do documento Aula_09_Projecoes.pdf.
    glEnable(GL_DEPTH_TEST);

    // Habilitamos o Backface Culling. Veja slides 8-13 do documento Aula_02_Fundamentos_Matematicos.pdf, slides 23-34 do documento Aula_13_Clipping_and_Culling.pdf e slides 112-123 do documento Aula_14_Laboratorio_3_Revisao.pdf.
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glFrontFace(GL_CCW);

    // Configuramos o modo do cursor para desabilitado
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // Ficamos em um loop infinito, renderizando, até que o usuário feche a janela
    while (!glfwWindowShouldClose(window))
    {
        // Aqui executamos as operações de renderização

        // Definimos a cor do "fundo" do framebuffer como branco.  Tal cor é
        // definida como coeficientes RGBA: Red, Green, Blue, Alpha; isto é:
        // Vermelho, Verde, Azul, Alpha (valor de transparência).
        // Conversaremos sobre sistemas de cores nas aulas de Modelos de Iluminação.
        //
        //           R     G     B     A
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

        // "Pintamos" todos os pixels do framebuffer com a cor definida acima,
        // e também resetamos todos os pixels do Z-buffer (depth buffer).
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Pedimos para a GPU utilizar o programa de GPU criado acima (contendo
        // os shaders de vértice e fragmentos).
        glUseProgram(g_GpuProgramID);

        // Abaixo definimos as varáveis que efetivamente definem a câmera virtual.
        glm::vec4 camera_lookat_l = glm::vec4(g_BunnyPosition, 1.0f); // Ponto "l", para onde a câmera (look-at) estará sempre olhando
        float radius = g_CameraDistance;
        float x = g_BunnyPosition.x + radius * -cos(g_CameraPhi) * cos(g_CameraTheta);
        float y = g_BunnyPosition.y + radius * sin(g_CameraPhi);
        float z = g_BunnyPosition.z + radius * cos(g_CameraPhi) * sin(g_CameraTheta);
        glm::vec4 camera_position_c = glm::vec4(x, y, z, 1.0f);
        glm::vec4 camera_view_vector = camera_lookat_l - camera_position_c; // Vetor "view", sentido para onde a câmera está virada
        glm::vec4 camera_up_vector = glm::vec4(0.0f, 1.0f, 0.0f, 0.0f);     // Vetor "up" fixado para apontar para o "céu" (eito Y global)
        // Computamos a matriz "View" utilizando os parâmetros da câmera para
        // definir o sistema de coordenadas da câmera.
        glm::mat4 view = Matrix_Camera_View(camera_position_c, camera_view_vector, camera_up_vector);

        // Atualiza a posição do coelho com base nas teclas pressionadas
        glm::vec3 camera_direction = glm::normalize(glm::vec3(camera_view_vector));
        glm::vec3 horizontal_direction = glm::normalize(glm::vec3(camera_direction.x, 0.0f, camera_direction.z));
        glm::vec3 camera_right = glm::normalize(glm::cross(camera_direction, glm::vec3(0.0f, 1.0f, 0.0f)));

        if (front)
            g_BunnyPosition += g_BunnySpeed * horizontal_direction;
        if (back)
            g_BunnyPosition -= g_BunnySpeed * horizontal_direction;
        if (left)
            g_BunnyPosition -= g_BunnySpeed * camera_right;
        if (right)
            g_BunnyPosition += g_BunnySpeed * camera_right;

        glm::vec3 bunny_forward = -horizontal_direction; // Direção horizontal da câmera
        float angle = atan2(bunny_forward.z, bunny_forward.x);
        glm::mat4 bunny_rotation = glm::rotate(glm::mat4(1.0f), (-angle - 1.6f), glm::vec3(0.0f, 1.0f, 0.0f));
        glm::vec3 camera_position = g_BunnyPosition - camera_direction * g_CameraDistance;
        camera_position.y = g_CameraHeight; // Mantém a altura constante

        // Agora computamos a matriz de Projeção.
        glm::mat4 projection;

        // Note que, no sistema de coordenadas da câmera, os planos near e far
        // estão no sentido negativo! Veja slides 176-204 do documento Aula_09_Projecoes.pdf.
        float nearplane = -0.1f;  // Posição do "near plane"
        float farplane = -100.0f; // Posição do "far plane"

        // Projeção Perspectiva.
        // Para definição do field of view (FOV), veja slides 205-215 do documento Aula_09_Projecoes.pdf.
        float field_of_view = 3.141592 / 3.0f;
        projection = Matrix_Perspective(field_of_view, g_ScreenRatio, nearplane, farplane);
        glm::mat4 model = Matrix_Identity(); // Transformação identidade de modelagem

        // Enviamos as matrizes "view" e "projection" para a placa de vídeo
        // (GPU). Veja o arquivo "shader_vertex.glsl", onde estas são
        // efetivamente aplicadas em todos os pontos.
        glUniformMatrix4fv(g_view_uniform, 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(g_projection_uniform, 1, GL_FALSE, glm::value_ptr(projection));

        #define WALL 0
        #define BUNNY 1
        #define PLANE 2

        g_BunnyPosition.y = 1.0f; // Mantém o coelho no chão

        // Desenhamos o modelo do coelho
        model = glm::translate(glm::mat4(1.0f), g_BunnyPosition) * bunny_rotation;
        glUniformMatrix4fv(g_model_uniform, 1, GL_FALSE, glm::value_ptr(model));
        glUniform1i(g_object_id_uniform, BUNNY);
        DrawVirtualObject("the_bunny");

        // Desenhamos o modelo do plano (chão)
        model = Matrix_Scale(40.0, 1.0, 40.0) * Matrix_Translate(0.0f, -1.0f, 0.0f) * Matrix_Rotate_Z(g_AngleZ) * Matrix_Rotate_Y(g_AngleY) * Matrix_Rotate_X(g_AngleX);
        glUniformMatrix4fv(g_model_uniform, 1, GL_FALSE, glm::value_ptr(model));
        glUniform1i(g_object_id_uniform, PLANE);
        DrawVirtualObject("the_plane");

        // Desenhamos o modelo da parede
        model = Matrix_Scale(1.0, 20.0, 50.0) * Matrix_Translate(32.0f, 0.5f, 0.0f) * Matrix_Rotate_Z(g_AngleZ) * Matrix_Rotate_Y(g_AngleY) * Matrix_Rotate_X(g_AngleX);
        glUniformMatrix4fv(g_model_uniform, 1, GL_FALSE, glm::value_ptr(model));
        glUniform1i(g_object_id_uniform, WALL);
        DrawVirtualObject("the_wall");
        // Desenhamos o modelo da parede
        model = Matrix_Scale(1.0, 20.0, 50.0) * Matrix_Translate(-32.0f, 0.5f, 0.0f) * Matrix_Rotate_Z(g_AngleZ) * Matrix_Rotate_Y(-M_PI) * Matrix_Rotate_X(g_AngleX);
        glUniformMatrix4fv(g_model_uniform, 1, GL_FALSE, glm::value_ptr(model));
        glUniform1i(g_object_id_uniform, WALL);
        DrawVirtualObject("the_wall");
        // Desenhamos o modelo da parede
        model = Matrix_Scale(50.0, 20.0, 1.0) * Matrix_Translate(0.0f, 0.5f, 35.0f) * Matrix_Rotate_Z(g_AngleZ) * Matrix_Rotate_Y(-M_PI / 2) * Matrix_Rotate_X(g_AngleX);
        glUniformMatrix4fv(g_model_uniform, 1, GL_FALSE, glm::value_ptr(model));
        glUniform1i(g_object_id_uniform, WALL);
        DrawVirtualObject("the_wall");
        // Desenhamos o modelo da parede
        model = Matrix_Scale(50.0, 20.0, 1.0) * Matrix_Translate(0.0f, 0.5f, -35.0f) * Matrix_Rotate_Z(g_AngleZ) * Matrix_Rotate_Y(M_PI / 2) * Matrix_Rotate_X(g_AngleX);
        glUniformMatrix4fv(g_model_uniform, 1, GL_FALSE, glm::value_ptr(model));
        glUniform1i(g_object_id_uniform, WALL);
        DrawVirtualObject("the_wall");

        // Imprimimos na tela informação sobre o número de quadros renderizados
        // por segundo (frames per second).
        TextRendering_ShowFramesPerSecond(window);

        // O framebuffer onde OpenGL executa as operações de renderização não
        // é o mesmo que está sendo mostrado para o usuário, caso contrário
        // seria possível ver artefatos conhecidos como "screen tearing". A
        // chamada abaixo faz a troca dos buffers, mostrando para o usuário
        // tudo que foi renderizado pelas funções acima.
        // Veja o link: https://en.wikipedia.org/w/index.php?title=Multiple_buffering&oldid=793452829#Double_buffering_in_computer_graphics
        glfwSwapBuffers(window);

        // Verificamos com o sistema operacional se houve alguma interação do
        // usuário (teclado, mouse, ...). Caso positivo, as funções de callback
        // definidas anteriormente usando glfwSet*Callback() serão chamadas
        // pela biblioteca GLFW.
        glfwPollEvents();
    }

    // Finalizamos o uso dos recursos do sistema operacional
    glfwTerminate();

    // Fim do programa
    return 0;
}

// set makeprg=cd\ ..\ &&\ make\ run\ >/dev/null
// vim: set spell spelllang=pt_br :