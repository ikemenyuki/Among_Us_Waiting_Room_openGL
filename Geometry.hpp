//
//  Geometry.hpp
//  CSE167 Starter
//
//  Created by yueqi liao on 11/19/20.
//  Copyright © 2020 YueqiLiao. All rights reserved.
//

#ifndef Geometry_h
#define Geometry_h

#ifdef __APPLE__
#include <OpenGL/gl3.h>
#else
#include <GL/glew.h>
#endif

#include "Node.h"
#include "shader.h"
#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include "BoundSphere.hpp"

using namespace std;
class Geometry : public Node {
public:
    float angle = 0.0f;
    std::string fileName;
    glm::mat4 modelM = glm::mat4(1);
    std::vector<unsigned int> indices;
    std::vector<glm::vec3> vertices;
    std::vector<glm::vec3> normals;
    std::vector < glm::vec3 > uvs;
    glm::vec3 color;
    int direction = 2; // 0 for up, 1 for right, 2 for down, 3 for left
    float npc_dir = 0.f;
    GLuint shader;
    bool sphere = false;
    BoundingSphere* boundingSphere;
    GLuint VBO, VAO, VBO_N, EBO;
    GLuint uProjection, uModelview, uModel;
    void spin(float degree){
        this->angle += degree;
        if (this->angle > 360.0f || this->angle < -360.0f) this->angle = 0.0f;
        angle = degree;
        this->modelM = this->modelM * glm::rotate(glm::mat4(1.0f), this->angle / 180.0f * glm::pi<float>(), glm::vec3(0.0f, 1.0f, 0.0f));
    }
    void draw(glm::mat4 C);
    void update();
    glm::mat4 getMatrix();
    void setMatrix(glm::mat4 M);
    void loadFileSimple(std::string filepath);
    void loadFileComplex(std::string filepath);
    Geometry(std::string filepath, GLuint shaderProgram);
    void setColor(glm::vec3 c){
        color = c;
    }
    void setSphere(BoundingSphere* s){
        boundingSphere = s;
    }
//    ~Geometry(){}
};

#endif /* Geometry_h */
