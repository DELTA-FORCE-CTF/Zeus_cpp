//
// Created by aurailus on 26/11/18.
//

#ifndef GLPROJECT_WINDOW_H
#define GLPROJECT_WINDOW_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vec2.hpp>
#include <cstdio>
#include "InputManager.h"

class Window {
public:
    Window();
    Window(GLint windowWidth, GLint windowHeight);

    int initialize();

    void update();

    glm::vec2 getSize();
    bool resized;

    bool shouldClose();

    double getDeltaX();
    double getDeltaY();

    void swapBuffers();

    ~Window();

    InputManager input;
private:
    GLFWwindow *mainWindow;

    GLint width, height;
    GLint centerX, centerY;
    bool mouseLocked;

    bool keys[1024];

    GLint bufferWidth, bufferHeight;

    //Static so that GLFW can run callback
    static void handleKeys(GLFWwindow* glfwWindow, int key, int code, int action, int mode);
    static void handleResize(GLFWwindow* glfwWindow, int width, int height);

    double deltaX;
    double deltaY;
};


#endif //GLPROJECT_WINDOW_H
