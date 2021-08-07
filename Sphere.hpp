//
//  Sphere.hpp
//  CSE167 Starter
//
//  Created by yueqi liao on 11/18/20.
//  Copyright © 2020 YueqiLiao. All rights reserved.
//

#ifndef Sphere_hpp
#define Sphere_hpp

#ifdef __APPLE__
#include <OpenGL/gl3.h>
#else
#include <GL/glew.h>
#endif

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "shader.h"
#include "Object.h"

class Sphere {
    public:
        GLuint shader;

        GLuint vao = 0, vbo = 0, vbo_n = 0, ebo = 0;
        glm::vec3 _minVal, _maxVal, _center;
        
        glm::mat4 model = glm::mat4(2);
        int stackCount = 40;
        int sectorCount = 40;
        int numsToDraw;
        Sphere();
        void draw(const glm::mat4& world, const glm::mat4& projection, const glm::mat4& view, const glm::vec3& eye);
        void useShader(GLuint s) { shader = s; }
        void spin(float deg);
};

#endif /* Sphere_hpp */
