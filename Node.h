//
//  Node.h
//  CSE167 Starter
//
//  Created by yueqi liao on 11/19/20.
//  Copyright © 2020 YueqiLiao. All rights reserved.
//

#ifndef _NODE_H_
#define _NODE_H_

#define GLFW_INCLUDE_GLEXT
#ifdef __APPLE__
#define GLFW_INCLUDE_GLCOREARB
#else
#include <GL/glew.h>
#endif
#include <GLFW/glfw3.h>
#ifndef GLM_FORCE_RADIANS
#define GLM_FORCE_RADIANS
#endif
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>

class Node{
public:
    virtual void draw(glm::mat4 C) = 0;
    virtual void update() = 0;
    virtual glm::mat4 getMatrix() = 0;
    virtual void setMatrix(glm::mat4 mat) = 0;
};

#endif
