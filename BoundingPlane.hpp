//
//  BoundingPlane.hpp
//  CSE167
//
//  Created by yueqi liao on 12/9/20.
//  Copyright © 2020 YueqiLiao. All rights reserved.
//

#ifndef BoundingPlane_hpp
#define BoundingPlane_hpp

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

class BoundingPlane {
public:
    glm::vec3 origin;
    glm::vec3 normal;
    string name;
    BoundingPlane(glm::vec3 o, glm::vec3 n, string na){
        origin = o;
        normal = n;
        name = na;
    }
};

#endif /* BoundingPlane_hpp */
