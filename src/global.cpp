#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "global.h"
#include <glm/trigonometric.hpp>

// Definição de variáveis globais
std::map<std::string, SceneObject> g_VirtualScene;
std::stack<glm::mat4> g_MatrixStack;

float g_ScreenRatio = 1.0f;
float g_AngleX = 0.0f;
float g_AngleY = 0.0f;
float g_AngleZ = 0.0f;

bool g_LeftMouseButtonPressed = false;
bool g_RightMouseButtonPressed = false;
bool g_MiddleMouseButtonPressed = false;

float g_CameraTheta = glm::radians(0.0f);
float g_CameraPhi = glm::radians(0.0f);
float g_CameraDistance = 8.0f;

float g_ForearmAngleZ = 0.0f;
float g_ForearmAngleX = 0.0f;

float g_TorsoPositionX = 0.0f;
float g_TorsoPositionY = 0.0f;

bool g_UsePerspectiveProjection = true;
bool g_ShowInfoText = true;

GLuint g_GpuProgramID = 0;
GLint g_model_uniform;
GLint g_view_uniform;
GLint g_projection_uniform;
GLint g_object_id_uniform;
GLint g_bbox_min_uniform;
GLint g_bbox_max_uniform;

GLint g_texture0_uniform;
GLint g_texture1_uniform;

GLint g_NumLoadedTextures = 0;

bool front = false;
bool back = false;
bool left = false;
bool right = false;

glm::vec3 g_PlayerPosition(1.0f, 0.0f, 0.0f);
glm::mat4  g_PlayerRotation = glm::mat4(1.0f);

float g_PlayerSpeed = 10.0f;
float g_CameraHeight = 1.0f;

double g_LastCursorPosX = 0;
double g_LastCursorPosY = 0;