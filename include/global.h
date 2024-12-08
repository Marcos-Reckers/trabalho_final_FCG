#ifndef GLOBAL_H
#define GLOBAL_H

#include <map>
#include <stack>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/mat4x4.hpp>
#include "scene.h"

// Declaration of global variables
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

extern bool front;
extern bool back;
extern bool left;
extern bool right;

extern glm::vec3 g_BunnyPosition;
extern float g_BunnySpeed;
extern float g_CameraHeight;

extern double g_LastCursorPosX, g_LastCursorPosY;

#endif // GLOBAL_H
