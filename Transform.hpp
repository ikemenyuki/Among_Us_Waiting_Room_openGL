//
//  Transform.hpp
//  CSE167 Starter
//
//  Created by yueqi liao on 11/19/20.
//  Copyright © 2020 YueqiLiao. All rights reserved.
//

#ifndef Transform_hpp
#define Transform_hpp

#define GLFW_INCLUDE_GLEXT
#ifdef __APPLE__
#define GLFW_INCLUDE_GLCOREARB
#else
#include <GL/glew.h>
#endif
#include "Node.h"
#include <GLFW/glfw3.h>
// Use of degrees is deprecated. Use radians instead.
#ifndef GLM_FORCE_RADIANS
#define GLM_FORCE_RADIANS
#endif
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>

class Transform : public Node {

public:
    glm::mat4 M = glm::mat4(1.0f);
    std::vector<Node*> ptrs;

    void addChild(Node* node);
//    void removeChild(Node* node);
    void draw(glm::mat4 C);
    void update();
    glm::mat4 getMatrix();
    void setMatrix(glm::mat4 mat);

};
#endif /* Transform_hpp */
