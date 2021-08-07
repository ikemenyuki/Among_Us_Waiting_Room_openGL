//
//  BoundSphere.hpp
//  CSE167
//
//  Created by yueqi liao on 12/9/20.
//  Copyright © 2020 YueqiLiao. All rights reserved.
//

#ifndef BoundSphere_hpp
#define BoundSphere_hpp

#ifdef __APPLE__
#include <OpenGL/gl3.h>
#else
#include <GL/glew.h>
#endif

#include "shader.h"
#include "Object.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>

using namespace std;
class BoundingSphere{
public:
    std::vector<unsigned int> indices;
    float radius;
    glm::vec3 center;
    string name;
    bool isMoving = true;
    float direction;
    
    BoundingSphere(float r, glm::vec3 c, string n) {
        radius = r;
        center = c;
        name = n;
    }
//    glm::mat4 modelM = glm::mat4(1);
//    GLuint shader;
//    bool sphere = false;
//    GLuint VBO, VAO, VBO_N, EBO;
//    GLuint uProjection, uModelview, uModel;
//    void draw(glm::mat4 C);
//    void update();
//    void collisionDetection(BoundingSphere* b);
};

#endif /* BoundSphere_hpp */
