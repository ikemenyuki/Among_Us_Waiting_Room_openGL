#include "Cube.h"

ParticleSystem::ParticleSystem(glm::vec3 c){
    /*
     * TODO: Section 2: Currently, all the points are hard coded below.
     * Modify this to read points from an obj file.
     */
//    srand(time(NULL));
    scale1 = static_cast<float>(rand() % 200) / 100 - 1;
    scale2 = static_cast<float>(rand() % 200) / 100 - 1;
    scale3 = static_cast<float>(rand() % 200) / 100 - 1;
    this->center = c;
    
    points = {
        glm::vec3(-1, 1, 1),
        glm::vec3(-1, -1, 1),
        glm::vec3(1, -1, 1),
        glm::vec3(1, 1, 1),
        glm::vec3(-1, 1, -1),
        glm::vec3(-1, -1, -1),
        glm::vec3(1, -1, -1),
        glm::vec3(1, 1, -1)
    };

    /*
     * TODO: Section 4, you will need to normalize the object to fit in the
     * screen.
     */

    // Set the model matrix to an identity matrix.
    model = glm::mat4(1);

    // Set the color.
    color = glm::vec3(0, 1, 0);

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
    
    for (int i = 0; i < MAX_PARTICLES; i++){
        particles[i] = Particle();
        particles[i].initialize();
        this->respawnParticles(particles[i], this->center);
    }
}

ParticleSystem::~ParticleSystem()
{
    // Delete the VBO and the VAO.
    glDeleteBuffers(1, &VBO);
    glDeleteVertexArrays(1, &VAO);
}

void ParticleSystem::draw(const glm::mat4& view, const glm::mat4& projection, GLuint shader)
{
    // Actiavte the shader program
    glUseProgram(shader);
    //model = glm::translate(glm::mat4(1), particles[0].position);
    for (Particle particle: this->particles){
        // Get the shader variable locations and send the uniform data to the shader
        if (particle.life > 0.f){
            glUniformMatrix4fv(glGetUniformLocation(shader, "view"), 1, false, glm::value_ptr(view));
            glUniformMatrix4fv(glGetUniformLocation(shader, "projection"), 1, false, glm::value_ptr(projection));
            glUniformMatrix4fv(glGetUniformLocation(shader, "model"), 1, GL_FALSE, glm::value_ptr(model));
            glUniform3fv(glGetUniformLocation(shader, "offset"), 1, glm::value_ptr(particle.position));
            glUniform3fv(glGetUniformLocation(shader, "color"), 1, glm::value_ptr(color));

            // Bind the VAO
            glBindVertexArray(VAO);

            // Set point size
            glPointSize(5.f);

            // Draw the points
            glDrawArrays(GL_POINTS, 0, points.size());

            // Unbind the VAO and shader program
            glBindVertexArray(0);
            glUseProgram(0);
        }

    }
}

void ParticleSystem::update(float deltaTime)
{
    for (unsigned int i = 0; i < MAX_PARTICLES; i++){
        Particle &particle = particles[i];
        // cout << particle.life << endl;
        particle.life -= deltaTime * 4;
        if (particle.life > 0.f){
            particle.position += particle.velocity * deltaTime;
        }
    }
}

void ParticleSystem::spin(float deg)
{
    // Update the model matrix by multiplying a rotation matrix
    model = model * glm::rotate(glm::radians(deg), glm::vec3(0.0f, 1.0f, 0.0f));
}

void ParticleSystem::respawnParticles(Particle &particle, glm::vec3 center, glm::vec3 offset){
//    cout << scale1 << " " << scale2 << " " << scale3 << endl;
    float random = rand() % 20 / 10.f - 0.5f;
    particle.position = center;
    float sign1 = rand() % 2;
    sign1 == 0 ? sign1 = -1 : sign1 = 1;
    float sign2 = rand() % 2;
    sign2 == 0 ? sign2 = -1 : sign2 = 1;
    float sign3 = rand() % 2;
    sign3 == 0 ? sign3 = -1 : sign3 = 1;
    particle.velocity = glm::vec3(5.f * sign1 * scale1, 5.f * sign2 * scale2, 5.f * sign3 * scale3);
    particle.life = PARTICLE_LIFE;
}

void ParticleSystem::update(){

}
