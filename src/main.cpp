#include <cmath>
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
#include "camera.h"
#include "enemy.h"
#include <math.h>
#include <stb_image.h>
#include "bonus.h"

void LoadTextureImage(const char *filename);                                                 // Função que carrega imagens de textura
void DrawFloor(const glm::vec3 &scale, const glm::vec3 &translate, float rotateY, int type); // Função que desenha o chão
void DrawWall(const glm::vec3 &scale, const glm::vec3 &translate, float rotateY, int type);  // Função que desenha as paredes

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
    window = glfwCreateWindow(1024, 768, "INF01047 - Ninja Survival", NULL, NULL);
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
    FramebufferSizeCallback(window, 1024, 768);

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
    // Carregamos duas imagens para serem utilizadas como textura
    LoadTextureImage("../../data/Donatello_Ulti_Props_Leo_BaseColor-resources.assets-7492.png"); // TextureImage0
    LoadTextureImage("../../data/Splinter_BaseColor.png");                                       // TextureImage1
    LoadTextureImage("../../data/chao.png");                                                     // TextureImage2
    LoadTextureImage("../../data/paredes.png");                                                  // TextureImage3
    LoadTextureImage("../../data/Pizza_Diffuse_Color.png");                                      // TextureImage5

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
    float lastTime = glfwGetTime();

    // Inicializamos os inimigos
    InitializeEnemies(5, g_PlayerPosition);

    // Inicializamos os bônus
    InitializeBonuses();

    // Ficamos em um loop infinito, renderizando, até que o usuário feche a janela
    while (!glfwWindowShouldClose(window))
    {
        float currentTime = glfwGetTime();
        float elapsedTime = currentTime - lastTime;
        lastTime = currentTime;

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

        UpdateCamera(elapsedTime);

        g_PlayerPosition.y = 1.0f; // Mantém o jogador no chão

        glm::mat4 model = Matrix_Identity(); // Transformação identidade de modelagem

        // Desenhamos o modelo do jogador
        DrawPlayer();

        // Desenhamos o modelo do plano (chão)
        DrawFloor(glm::vec3(40.0, 1.0, 40.0), glm::vec3(0.0f, -1.0f, 0.0f), g_AngleY, PLANE);

        // Desenhamos os modelos das paredes
        DrawWall(glm::vec3(1.0, 20.0, 50.0), glm::vec3(32.0f, 0.5f, 0.0f), g_AngleY, WALL);
        DrawWall(glm::vec3(1.0, 20.0, 50.0), glm::vec3(-32.0f, 0.5f, 0.0f), -M_PI, WALL);
        DrawWall(glm::vec3(50.0, 20.0, 1.0), glm::vec3(0.0f, 0.5f, 35.0f), -M_PI / 2, WALL);
        DrawWall(glm::vec3(50.0, 20.0, 1.0), glm::vec3(0.0f, 0.5f, -35.0f), M_PI / 2, WALL);

        // Atualizamos a posição dos inimigos
        UpdateEnemies(elapsedTime, g_PlayerPosition);

        // Atualizamos a posição dos bônus
        UpdateBonuses(elapsedTime);

        // Desenhamos os inimigos
        DrawEnemies();

        // Desenhamos os bônus
        DrawBonuses();

        // Imprimimos na tela informação sobre o número de quadros renderizados
        // por segundo (frames per second).

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

void LoadTextureImage(const char *filename)
{
    printf("Carregando imagem \"%s\"... ", filename);

    // Primeiro fazemos a leitura da imagem do disco
    stbi_set_flip_vertically_on_load(true);
    int width;
    int height;
    int channels;
    unsigned char *data = stbi_load(filename, &width, &height, &channels, 3);

    if (data == NULL)
    {
        fprintf(stderr, "ERROR: Cannot open image file \"%s\".\n", filename);
        std::exit(EXIT_FAILURE);
    }

    GLuint texture_id;
    GLuint sampler_id;
    glGenTextures(1, &texture_id);
    glGenSamplers(1, &sampler_id);

    // Veja slides 95-96 do documento Aula_20_Mapeamento_de_Texturas.pdf
    glSamplerParameteri(sampler_id, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glSamplerParameteri(sampler_id, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    // Parâmetros de amostragem da textura.
    glSamplerParameteri(sampler_id, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glSamplerParameteri(sampler_id, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Agora enviamos a imagem lida do disco para a GPU
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
    glPixelStorei(GL_UNPACK_SKIP_PIXELS, 0);
    glPixelStorei(GL_UNPACK_SKIP_ROWS, 0);

    GLuint textureunit = g_NumLoadedTextures;
    glActiveTexture(GL_TEXTURE0 + textureunit);
    glBindTexture(GL_TEXTURE_2D, texture_id);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_SRGB8, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
    glBindSampler(textureunit, sampler_id);

    stbi_image_free(data);

    g_NumLoadedTextures += 1;

    printf("Imagem \"%s\" carregada com sucesso.\n", filename);
}

void DrawPlayer()
{
    static GLuint last_texture_id = 0;
    glm::mat4 model = Matrix_Identity();
    model = Matrix_Translate(g_PlayerPosition.x, g_PlayerPosition.y, g_PlayerPosition.z) * g_PlayerRotation * Matrix_Translate(0.0f, -2.0f, 0.0f) * Matrix_Scale(0.02f, 0.02f, 0.02f);

    GLuint current_texture_id = g_VirtualScene["the_player"].texture_id;
    if (last_texture_id != current_texture_id)
    {
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, current_texture_id);
        glUniform1i(g_texture0_uniform, 0);
        last_texture_id = current_texture_id;
        printf("Textura do jogador vinculada.\n");
    }
    RenderModel("the_player", model, PLAYER);
}

void DrawFloor(const glm::vec3 &scale, const glm::vec3 &translate, float rotateY, int type)
{
    static GLuint last_texture_id = 0;
    glm::mat4 model = Matrix_Identity();
    model = Matrix_Scale(scale.x, scale.y, scale.z) * Matrix_Translate(translate.x, translate.y, translate.z) * Matrix_Rotate_Z(g_AngleZ) * Matrix_Rotate_Y(rotateY) * Matrix_Rotate_X(g_AngleX);

    GLuint current_texture_id = g_VirtualScene["the_plane"].texture_id;
    if (last_texture_id != current_texture_id)
    {
        glActiveTexture(GL_TEXTURE2);
        glBindTexture(GL_TEXTURE_2D, current_texture_id);
        glUniform1i(g_texture2_uniform, 2);
        last_texture_id = current_texture_id;
        printf("Textura do the_plane vinculada.\n");
    }
    RenderModel("the_plane", model, type);
}

void DrawWall(const glm::vec3 &scale, const glm::vec3 &translate, float rotateY, int type)
{
    static GLuint last_texture_id = 0;
    glm::mat4 model = Matrix_Identity();
    model = Matrix_Scale(scale.x, scale.y, scale.z) * Matrix_Translate(translate.x, translate.y, translate.z) * Matrix_Rotate_Z(g_AngleZ) * Matrix_Rotate_Y(rotateY) * Matrix_Rotate_X(g_AngleX);

    GLuint current_texture_id = g_VirtualScene["the_wall"].texture_id;
    if (last_texture_id != current_texture_id)
    {
        glActiveTexture(GL_TEXTURE3);
        glBindTexture(GL_TEXTURE_2D, current_texture_id);
        glUniform1i(g_texture3_uniform, 3);
        last_texture_id = current_texture_id;
        printf("Textura do the_wall vinculada.\n");
    }
    RenderModel("the_wall", model, type);
}