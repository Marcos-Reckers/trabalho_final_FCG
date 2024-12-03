#include "global.h"

// Definição das variáveis globais
std::map<std::string, SceneObject> g_VirtualScene;
std::stack<glm::mat4> g_MatrixStack;

float g_ScreenRatio = 1.0f;
float g_AngleX = 0.0f;
float g_AngleY = 0.0f;
float g_AngleZ = 0.0f;

bool g_LeftMouseButtonPressed = false;
bool g_RightMouseButtonPressed = false;
bool g_MiddleMouseButtonPressed = false;

float g_CameraTheta = 0.0f;
float g_CameraPhi = 0.0f;
float g_CameraDistance = 3.5f;

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

bool front = false;
bool back = false;
bool left = false;
bool right = false;

glm::vec3 g_BunnyPosition(1.0f, 0.0f, 0.0f);
float g_BunnySpeed = 0.05f;
float g_CameraHeight = 1.0f;
