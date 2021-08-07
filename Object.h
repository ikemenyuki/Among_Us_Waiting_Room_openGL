#ifndef _OBJECT_H_
#define _OBJECT_H_

#ifdef __APPLE__
#include <OpenGL/gl3.h>
#else
#include <GL/glew.h>
#endif

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <stdlib.h>
#include <glm/gtx/string_cast.hpp>

//#include <string>
//#include <vector>

class Object
{
protected:
    glm::vec3 lightPos = glm::vec3(5,5,5);
    glm::vec3 lightColor = glm::vec3(1, 0.3, 0.3);
    glm::vec3 eyePos = glm::vec3(0, 0, 20);
    glm::vec3 origin = glm::vec3(0, 0, 0);

public:
    glm::mat4 model;
    glm::vec3 color = glm::vec3(0.3f, 0.3f, 0.7f);
    int objType;
    bool isPhong = 1;
    bool islight = 0;
    // glm::mat4 model_s = glm::translate(lightPos) * model_s;
    glm::mat4 model_s = glm::mat4(1);
	glm::mat4 getModel() { return model; }
	glm::vec3 getColor() { return color; }
    void scaleModel (float scale){
        //model = glm::mat4(1);
        model = model * glm::scale(glm::mat4(1.0f), glm::vec3(scale, scale, scale));
    }
    
    void rotateModel (float omega, glm::vec3 axis){
        model = glm::rotate(model, omega, axis);
    }
    
    void rotateSphere (float omega, glm::vec3 axis){
        glm::mat4 translate = glm::translate(glm::mat4(1), origin);
        lightPos = glm::vec3(translate * glm::rotate(glm::mat4(1), omega, axis) * inverse(translate) *
                             glm::vec4(lightPos, 1));
        model_s = translate * glm::rotate(glm::mat4(1), omega, axis) * inverse(translate) * model_s;
    }
    
    void moveToCenter (float yoffset){
        if (lightPos.x < 0.01){
            if (yoffset > 0){
                std::cout << yoffset << std::endl;
                glm::mat4 translate = glm::translate(glm::mat4(1), origin);
                lightPos = glm::vec3(translate * glm::scale(glm::vec3(1 + yoffset/50)) * inverse(translate) * glm::vec4(lightPos, 1));
                model_s = translate * glm::scale(glm::vec3(1 + yoffset/50)) * inverse(translate) * model_s;
            }
        }
        else{
            glm::mat4 translate = glm::translate(glm::mat4(1), origin);
            lightPos = glm::vec3(translate * glm::scale(glm::vec3(1 + yoffset/50)) * inverse(translate) *
            glm::vec4(lightPos, 1));
            model_s = translate * glm::scale(glm::vec3(1 + yoffset/50)) * inverse(translate) * model_s;
        }
    }
    
	virtual void draw(const glm::mat4& view, const glm::mat4& projection, GLuint shader) = 0;
	virtual void update() = 0;
};

#endif

