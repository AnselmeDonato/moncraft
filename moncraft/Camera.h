//
//  Camera.h
//  moncraft
//
//  Created by Anselme Donato on 07/12/2021.
//

#ifndef Camera_h
#define Camera_h

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include <iostream>

// Defines several possible options for camera movement. Used as abstraction to stay away from window-system specific input methods
enum Camera_Movement {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT,
    UP,
    DOWN
};

//Defalut values
float LAST_X = 800.0f/ 2.0;
float LAST_Y = 600.0 / 2.0;
float YAW = -90.0f;
float PITCH =  0.0f;
float SPEED = 5.0f;

class Camera {
    
private:
    
    glm::vec3 m_position;
    glm::vec3 m_front;
    glm::vec3 m_up;
    
    float m_speed;
    bool m_firstMouse;
    float m_lastX;
    float m_lastY;
    float m_yaw;
    float m_pitch;
    
public:
    
    Camera() {};
    Camera(glm::vec3 _cameraPos = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 _cameraUp = glm::vec3(0.0f, 1.0f, 0.0f)) : m_front(glm::vec3(0.0f, 0.0f, -1.0f)), m_lastX(LAST_X), m_lastY(LAST_Y), m_yaw(YAW), m_pitch(PITCH), m_speed(SPEED){
        m_position = _cameraPos;
        m_up = _cameraUp;
        m_firstMouse = true;
    }
        
    void processKey(Camera_Movement direction, float deltaTime){
        float _speed = SPEED * deltaTime;
        glm::vec3 planar_front;
        planar_front.x = m_front.x;
        planar_front.z = m_front.z;
        
        if(direction == FORWARD) {
            m_position += _speed * glm::normalize(planar_front);
        }
        if(direction == LEFT) {
            m_position -= glm::normalize(glm::cross(planar_front, m_up)) * _speed;
        }
        if(direction == BACKWARD) {
            m_position -= _speed * glm::normalize(planar_front);
        }
        if(direction == RIGHT) {
            m_position += glm::normalize(glm::cross(planar_front, m_up)) * _speed;
        }
        if(direction == UP) {
            m_position += _speed * glm::vec3(0.0f, 1.0f, 0.0f);
        }
        if(direction == DOWN) {
            m_position -= _speed * glm::vec3(0.0f, 1.0f, 0.0f);
        }
    }
    
    void processLook(double _xpos, double _ypos){
        if (m_firstMouse)
        {
            m_lastX = _xpos;
            m_lastY = _ypos;
            m_firstMouse = false;
        }

        float xoffset = _xpos - m_lastX;
        float yoffset = m_lastY - _ypos; // reversed since y-coordinates go from bottom to top
        m_lastX = _xpos;
        m_lastY = _ypos;

        float sensitivity = 0.1f; // change this value to your liking
        xoffset *= sensitivity;
        yoffset *= sensitivity;

        m_yaw += xoffset;
        m_pitch += yoffset;

        // make sure that when pitch is out of bounds, screen doesn't get flipped
        if (m_pitch > 89.0f) {
            m_pitch = 89.0f;
        }
        if (m_pitch < -89.0f) {
            m_pitch = -89.0f;
        }
            
        glm::vec3 _front;
        _front.x = cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
        _front.y = sin(glm::radians(m_pitch));
        _front.z = sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
        m_front = glm::normalize(_front);
    }
    
    glm::mat4 getView(){
        return glm::lookAt(m_position, m_position + m_front, m_up);
    }
    

};
#endif /* Camera_h */
