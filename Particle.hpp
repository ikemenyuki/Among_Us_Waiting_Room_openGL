////
////  Particle.hpp
////  CSE167
////
////  Created by yueqi liao on 12/13/20.
////  Copyright © 2020 YueqiLiao. All rights reserved.
////
//
//#ifndef Particle_hpp
//#define Particle_hpp
//
//#include <stdio.h>
//#ifdef __APPLE__
//#include <OpenGL/gl3.h>
//#else
//#include <GL/glew.h>
//#endif
//
//#include "shader.h"
//#include <iostream>
//#include <fstream>
//#include <string>
//#include <stdio.h>
//#include <glm/glm.hpp>
//#include <glm/gtc/matrix_transform.hpp>
//#include <glm/gtx/transform.hpp>
//#include "BoundSphere.hpp"
//#include "Window.h"
//
//// Represents a single particle and its state
//struct Particle {
//    glm::vec3 Position;
//    glm::vec2 Velocity;
//    glm::vec4 Color;
//    float     Life;
//
//    Particle() : Position(0.0f), Velocity(glm::vec2(0.f)), Color(0.0f), Life(0.0f) { }
//};
//
//// ParticleGenerator acts as a container for rendering a large number of
//// particles by repeatedly spawning and updating particles and killing
//// them after a given amount of time.
//class ParticleGenerator
//{
//public:
//    // constructor
//    ParticleGenerator(GLuint shader, unsigned int amount);
//    // update all particles
//    void Update(float dt, BoundingSphere* object, unsigned int newParticles, glm::vec3 offset = glm::vec3(0.0f));
//    // render all particles
//    void Draw();
//private:
//    // state
//    glm::mat4 model = glm::mat4(1.f);
//    std::vector<Particle> particles;
//    unsigned int amount;
//    // render state
//    GLuint shader;
//    unsigned int VAO;
//    // initializes buffer and vertex attributes
//    void init();
//    // returns the first Particle index that's currently unused e.g. Life <= 0.0f or 0 if no particle is currently inactive
//    unsigned int firstUnusedParticle();
//    // respawns particle
//    void respawnParticle(Particle &particle, BoundingSphere* object, glm::vec3 offset = glm::vec3(0.0f));
//};
//
//#endif /* Particle_hpp */
