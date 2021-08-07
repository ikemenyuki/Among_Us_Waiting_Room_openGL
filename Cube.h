#ifndef _CUBE_H_
#define _CUBE_H_

#include "Object.h"

#include <vector>
#include <string>

using namespace std;

class ParticleSystem : public Object
{
private:
    std::vector<glm::vec3> points;
    
    GLuint VAO, VBO;

public:
    struct Particle {
        glm::vec3 position, velocity;
        float life = 3.f;
        glm::vec3 color = glm::vec3(1.f, 1.f, 1.f);
        GLuint VAO, VBO;
        std::vector<glm::vec3> points = {
            glm::vec3(0.f, 0.f, 0.f)
        };
        
        void initialize(){
            // Generate a Vertex Array (VAO) and Vertex Buffer Object (VBO)
            
            glGenVertexArrays(1, &VAO);
            glGenBuffers(1, &VBO);

            // Bind VAO
            glBindVertexArray(VAO);

            // Bind VBO to the bound VAO, and store the point data
            glBindBuffer(GL_ARRAY_BUFFER, VBO);
            glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * points.size(), points.data(), GL_STATIC_DRAW);
            // Enable Vertex Attribute 0 to pass point data through to the shader
            glEnableVertexAttribArray(0);
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), 0);

            // Unbind the VBO/VAO
            glBindBuffer(GL_ARRAY_BUFFER, 0);
            glBindVertexArray(0);
        }

        
        void draw(const glm::mat4& view, const glm::mat4& projection, GLuint shader, glm::mat4 model){
            
            cout << glm::to_string(position) << endl;
            //glm::mat4 model = glm::rotate(glm::mat4(1), glm::radians(90.f), glm::vec3(0.0f,1.0f,0.0f));
//            glm::mat4 model = glm::translate(glm::mat4(1), position);
//            cout << glm::to_string(model) << endl;
//            cout << endl;
            glUniformMatrix4fv(glGetUniformLocation(shader, "view"), 1, false, glm::value_ptr(view));
            glUniformMatrix4fv(glGetUniformLocation(shader, "projection"), 1, false, glm::value_ptr(projection));
            glUniformMatrix4fv(glGetUniformLocation(shader, "model"), 1, GL_FALSE, glm::value_ptr(model));
            glUniform3fv(glGetUniformLocation(shader, "offset"), 1, glm::value_ptr(position));
            glUniform3fv(glGetUniformLocation(shader, "color"), 1, glm::value_ptr(color));

            // Bind the VAO
            glBindVertexArray(VAO);

            // Set point size
            glPointSize(10.f);

            // Draw the points
            glDrawArrays(GL_POINTS, 0, points.size());

            // Unbind the VAO and shader program
            glBindVertexArray(0);
            glUseProgram(0);
        }
        
        void update(float deltaTime);
    };
    float scale1;
    float scale2;
    float scale3;
    static const int MAX_PARTICLES = 100;
    static const int PARTICLE_LIFE = 3;
    glm::vec3 center;
    Particle particles[MAX_PARTICLES];
    glm::vec3 position_data[MAX_PARTICLES];
    
    ParticleSystem(glm::vec3 center);
    ~ParticleSystem();
    
    void draw(const glm::mat4& view, const glm::mat4& projection, GLuint shader);
    void update(float deltaTime);
    void update();

    void spin(float deg);
    void respawnParticles(Particle &particle, glm::vec3 center, glm::vec3 offset=glm::vec3(0.f));
};

#endif
