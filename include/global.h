#ifndef GLOBAL_H
#define GLOBAL_H

#include <map>
#include <stack>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/mat4x4.hpp>
#include "scene.h"

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

#define WALL 0
#define PLAYER 1
#define PLANE 2
#define ENEMY 3

// Definição de variáveis globais
extern std::map<std::string, SceneObject> g_VirtualScene;
extern std::stack<glm::mat4> g_MatrixStack;

extern float g_ScreenRatio;
extern float g_AngleX;
extern float g_AngleY;
extern float g_AngleZ;

extern bool g_LeftMouseButtonPressed;
extern bool g_RightMouseButtonPressed;
extern bool g_MiddleMouseButtonPressed;

extern float g_CameraTheta;
extern float g_CameraPhi;
extern float g_CameraDistance;

extern float g_ForearmAngleZ;
extern float g_ForearmAngleX;

extern float g_TorsoPositionX;
extern float g_TorsoPositionY;

extern bool g_UsePerspectiveProjection;
extern bool g_ShowInfoText;

extern GLuint g_GpuProgramID;
extern GLint g_model_uniform;
extern GLint g_view_uniform;
extern GLint g_projection_uniform;
extern GLint g_object_id_uniform;
extern GLint g_NumLoadedTextures;

extern GLint g_texture0_uniform;
extern GLint g_texture1_uniform;

extern GLint g_bbox_min_uniform;
extern GLint g_bbox_max_uniform;

extern bool front;
extern bool back;
extern bool left;
extern bool right;

extern glm::vec3 g_PlayerPosition;
extern glm::mat4 g_PlayerRotation;
extern float g_PlayerSpeed;
extern float g_CameraHeight;

extern double g_LastCursorPosX, g_LastCursorPosY;

#endif // GLOBAL_H
