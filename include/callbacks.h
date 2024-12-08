#ifndef CALLBACKS_H
#define CALLBACKS_H

#include <GLFW/glfw3.h>

// Funções callback para comunicação com o sistema operacional e interação do
// usuário.
void SetCallbacks(GLFWwindow *window);
void FramebufferSizeCallback(GLFWwindow *window, int width, int height);
void ErrorCallback(int error, const char *description);
void KeyCallback(GLFWwindow *window, int key, int scancode, int action, int mode);
void MouseButtonCallback(GLFWwindow *window, int button, int action, int mods);
void CursorPosCallback(GLFWwindow *window, double xpos, double ypos);
void ScrollCallback(GLFWwindow *window, double xoffset, double yoffset);

#endif