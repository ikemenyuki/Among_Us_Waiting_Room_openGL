//
//  Skybox.hpp
//  CSE167 Starter
//
//  Created by yueqi liao on 11/16/20.
//  Copyright © 2020 YueqiLiao. All rights reserved.
//

#ifndef _POINT_CLOUD_H_
#define _POINT_CLOUD_H_

#include "Object.h"
#include <vector>
#include <string>

using namespace std;

class Skybox
{
private:
    GLuint VAO, VBO, EBO;
    GLuint VBO2;
    GLuint VAO_s, VBO_s, VBO_s2, EBO_s;
    GLfloat pointSize;
    //xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
//    GLuint cubeVAO, cubeVBO;
    GLuint skyboxVAO, skyboxVBO;
    GLuint textureID;
public:
    Skybox();
    ~Skybox();
    
    void draw(const glm::mat4& view, const glm::mat4& projection, GLuint shader);
    unsigned int loadCubemap(vector<std::string> faces);
};

#endif
