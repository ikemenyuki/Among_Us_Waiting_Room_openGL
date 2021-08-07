////
////  Particle.cpp
////  CSE167
////
////  Created by yueqi liao on 12/13/20.
////  Copyright © 2020 YueqiLiao. All rights reserved.
////
//
//#include "Particle.hpp"
//
//ParticleGenerator::ParticleGenerator(GLuint shader, unsigned int amount)
//    : shader(shader), amount(amount)
//{
//    this->init();
//}
//
//void ParticleGenerator::Update(float dt, BoundingSphere* object, unsigned int newParticles, glm::vec3 offset)
//{
//    // add new particles
//    for (unsigned int i = 0; i < newParticles; ++i)
//    {
//        int unusedParticle = this->firstUnusedParticle();
//        this->respawnParticle(this->particles[unusedParticle], object, offset);
//    }
//    // update all particles
//    for (unsigned int i = 0; i < this->amount; ++i)
//    {
//        Particle &p = this->particles[i];
//        p.Life -= dt; // reduce life
//        if (p.Life > 0.0f)
//        {    // particle is alive, thus update
//            p.Position -= glm::vec3(p.Velocity.x, 0.f, p.Velocity.y) * dt;
//            p.Position -= glm::vec3(p.Velocity.x, 0.f, p.Velocity.y) * dt;
//            p.Color.a -= dt * 2.5f;
//        }
//    }
//}
//
//// render all particles
//void ParticleGenerator::Draw()
//{
//    // use additive blending to give it a 'glow' effect
//    glBlendFunc(GL_SRC_ALPHA, GL_ONE);
//    glUseProgram(shader);
//    for (Particle particle : this->particles)
//    {
//        if (particle.Life > 0.0f)
//        {
//            
//            glUniform3fv(glGetUniformLocation(shader, "offset"), 1, glm::value_ptr(particle.Position));
//            glUniform4fv(glGetUniformLocation(shader, "color"), 1, glm::value_ptr(particle.Color));
//            glBindVertexArray(this->VAO);
//            glDrawArrays(GL_TRIANGLES, 0, 6);
//            glBindVertexArray(0);
//        }
//    }
//    // don't forget to reset to default blending mode
//    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
//}
//
//void ParticleGenerator::init()
//{
//    // set up mesh and attribute properties
//    unsigned int VBO;
//    float particle_quad[] = {
//        0.0f, 1.0f, 0.0f, 1.0f,
//        1.0f, 0.0f, 1.0f, 0.0f,
//        0.0f, 0.0f, 0.0f, 0.0f,
//
//        0.0f, 1.0f, 0.0f, 1.0f,
//        1.0f, 1.0f, 1.0f, 1.0f,
//        1.0f, 0.0f, 1.0f, 0.0f
//    };
//    glGenVertexArrays(1, &this->VAO);
//    glGenBuffers(1, &VBO);
//    glBindVertexArray(this->VAO);
//    // fill mesh buffer
//    glBindBuffer(GL_ARRAY_BUFFER, VBO);
//    glBufferData(GL_ARRAY_BUFFER, sizeof(particle_quad), particle_quad, GL_STATIC_DRAW);
//    // set mesh attributes
//    glEnableVertexAttribArray(0);
//    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
//    glBindVertexArray(0);
//
//    // create this->amount default particle instances
//    for (unsigned int i = 0; i < this->amount; ++i)
//        this->particles.push_back(Particle());
//}
//
//// stores the index of the last particle used (for quick access to next dead particle)
//unsigned int lastUsedParticle = 0;
//unsigned int ParticleGenerator::firstUnusedParticle()
//{
//    // first search from last used particle, this will usually return almost instantly
//    for (unsigned int i = lastUsedParticle; i < this->amount; ++i){
//        if (this->particles[i].Life <= 0.0f){
//            lastUsedParticle = i;
//            return i;
//        }
//    }
//    // otherwise, do a linear search
//    for (unsigned int i = 0; i < lastUsedParticle; ++i){
//        if (this->particles[i].Life <= 0.0f){
//            lastUsedParticle = i;
//            return i;
//        }
//    }
//    // all particles are taken, override the first one (note that if it repeatedly hits this case, more particles should be reserved)
//    lastUsedParticle = 0;
//    return 0;
//}
//
//void ParticleGenerator::respawnParticle(Particle &particle, BoundingSphere* object, glm::vec3 offset)
//{
//    float random = ((rand() % 100) - 50) / 10.0f;
//    float rColor = 0.5f + ((rand() % 100) / 100.0f);
//    particle.Position = object->center + glm::vec3(random) + offset;
//    particle.Color = glm::vec4(rColor, rColor, rColor, 1.0f);
//    particle.Life = 1.0f;
//    particle.Velocity = glm::vec2(0.2f);
//}
