//
//  Particlez.hpp
//  CSE167
//
//  Created by yueqi liao on 12/13/20.
//  Copyright © 2020 YueqiLiao. All rights reserved.
//

#ifndef Particlez_hpp
#define Particlez_hpp

#include <stdio.h>
#include "Object.h"

#include <vector>
#include <string>

using namespace std;

class Particlez : public Object
{
private:
    std::vector<glm::vec3> points;

    GLuint VAO, VBO;
    GLfloat pointSize;

public:
    Particlez();
    ~Particlez();
    
    void draw(const glm::mat4& view, const glm::mat4& projection, GLuint shader);
    void update();

    void updatePointSize(GLfloat size);
    void spin(float deg);
};

#endif /* Particlez_hpp */
