//
// Created by aurailus on 27/11/18.
//

#ifndef GLPROJECT_CAMERA_H
#define GLPROJECT_CAMERA_H

#include <GL/glew.h>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <GLFW/glfw3.h>

class Camera {
public:
//    Camera();
    Camera(glm::vec3 position, glm::vec3 up, GLfloat yaw, GLfloat pitch, GLfloat moveSpeed, GLfloat turnSpeed);

    void keyControl(bool* keys, GLfloat delta);
    void mouseControl(double deltaX, double deltaY);

    glm::mat4 calculateViewMatrix();

    ~Camera();

private:
    glm::vec3 position;

    glm::vec3 front;
    glm::vec3 up;
    glm::vec3 right;
    glm::vec3 worldUp;

    double yaw;
    double pitch;

    GLfloat moveSpeed;
    GLfloat turnSpeed;

    void update();
};


#endif //GLPROJECT_CAMERA_H
