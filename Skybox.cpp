//
//  Skybox.cpp
//  CSE167 Starter
//
//  Created by yueqi liao on 11/16/20.
//  Copyright © 2020 YueqiLiao. All rights reserved.
//
#include "Skybox.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <limits>
#include <cmath>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

Skybox::Skybox()
    : pointSize(pointSize)
{
    GLfloat skyboxVertices[] = {
        // Positions
        -100.0f,  100.0f, -100.0f,
        -100.0f, -100.0f, -100.0f,
        100.0f, -100.0f, -100.0f,
        100.0f, -100.0f, -100.0f,
        100.0f,  100.0f, -100.0f,
        -100.0f,  100.0f, -100.0f,

        -100.0f, -100.0f,  100.0f,
        -100.0f, -100.0f, -100.0f,
        -100.0f,  100.0f, -100.0f,
        -100.0f,  100.0f, -100.0f,
        -100.0f,  100.0f,  100.0f,
        -100.0f, -100.0f,  100.0f,

        100.0f, -100.0f, -100.0f,
        100.0f, -100.0f,  100.0f,
        100.0f,  100.0f,  100.0f,
        100.0f,  100.0f,  100.0f,
        100.0f,  100.0f, -100.0f,
        100.0f, -100.0f, -100.0f,

        -100.0f, -100.0f,  100.0f,
        -100.0f,  100.0f,  100.0f,
        100.0f,  100.0f,  100.0f,
        100.0f,  100.0f,  100.0f,
        100.0f, -100.0f,  100.0f,
        -100.0f, -100.0f,  100.0f,

        -100.0f,  100.0f, -100.0f,
        100.0f,  100.0f, -100.0f,
        100.0f,  100.0f,  100.0f,
        100.0f,  100.0f,  100.0f,
        -100.0f,  100.0f,  100.0f,
        -100.0f,  100.0f, -100.0f,

        -100.0f, -100.0f, -100.0f,
        -100.0f, -100.0f,  100.0f,
        100.0f, -100.0f, -100.0f,
        100.0f, -100.0f, -100.0f,
        -100.0f, -100.0f,  100.0f,
        100.0f, -100.0f,  100.0f
    };
    // skybox VAO
    glGenVertexArrays(1, &skyboxVAO);
    glGenBuffers(1, &skyboxVBO);
    glBindVertexArray(skyboxVAO);
    glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
}

unsigned int Skybox::loadCubemap(std::vector<std::string> faces)
{
    unsigned int textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

    int width, height, nrChannels;
    for (unsigned int i = 0; i < faces.size(); i++)
    {
        unsigned char *data = stbi_load(faces[i].c_str(), &width, &height, &nrChannels, 0);
        if (data)
        {
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
                         0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data
            );
            stbi_image_free(data);
        }
        else
        {
            std::cout << "Cubemap tex failed to load at path: " << faces[i] << std::endl;
            stbi_image_free(data);
        }
    }
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    return textureID;
}

Skybox::~Skybox()
{
    // Delete the VBO and the VAO.
    glDeleteBuffers(1, &VBO);
    glDeleteVertexArrays(1, &VAO);
}

void Skybox::draw(const glm::mat4& view, const glm::mat4& projection, GLuint shader)
{
    // Actiavte the shader program
    glUseProgram(shader);

    // Get the shader variable locations and send the uniform data to the shader
    std::vector<std::string> faces{
        "shaders/skybox/posx.jpg",
        "shaders/skybox/negx.jpg",
        "shaders/skybox/posy.jpg",
        "shaders/skybox/negy.jpg",
        "shaders/skybox/negz.jpg",
        "shaders/skybox/posz.jpg"
    };
    unsigned int cubemapTexture = loadCubemap(faces);
    glUniformMatrix4fv(glGetUniformLocation(shader, "view"), 1, false, glm::value_ptr(view));
    glUniformMatrix4fv(glGetUniformLocation(shader, "projection"), 1, false, glm::value_ptr(projection));
    // glUniformMatrix4fv(glGetUniformLocation(shader, "model"), 1, GL_FALSE, glm::value_ptr(model));
    // Bind the VAO
//    glBindVertexArray(VAO);
    // Set point size
    // glPointSize(pointSize);

     // draw skybox as last
    glDepthFunc(GL_LEQUAL);
    // skybox cube
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glBindVertexArray(skyboxVAO);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
    // Make sure no bytes are padded:
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    // Use bilinear interpolation:
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Use clamp to edge to hide skybox edges:
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindVertexArray(0);
    glDepthFunc(GL_LESS); // set depth function back to default
    // Unbind the VAO and shader program
    glBindVertexArray(0);
    glUseProgram(0);
}
