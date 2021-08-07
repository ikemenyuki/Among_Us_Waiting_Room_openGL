//
//  Geometry.cpp
//  CSE167 Starter
//
//  Created by yueqi liao on 11/19/20.
//  Copyright © 2020 YueqiLiao. All rights reserved.
//
#include <cstdio>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <limits>
#include <cmath>
#include "Geometry.hpp"
#include "Window.h"

glm::vec3 lightPos = glm::vec3(5,5,5);
glm::vec3 lightColor = glm::vec3(211.0f/255.0f, 211.0f/255.0f, 211.0f/255.0f);
glm::vec3 eyePos = glm::vec3(0, 40, 20);

Geometry::Geometry(std::string filepath, GLuint shaderProgram){
    shader = shaderProgram;
    fileName = filepath;
    if ((filepath.find("teapot") != std::string::npos) || (fileName.find("sphere") != std::string::npos) || ((filepath.find("torus") != std::string::npos))) {
        loadFileSimple(filepath);
    }
    else {
        loadFileComplex(filepath);
    }
    
}

void Geometry::draw(glm::mat4 C){
    modelM = modelM * C;
//    glm::mat4 view = Window::view * modelM;
    
//    std::cout << glm::to_string(glm::rotate(glm::mat4(1.0f), 0.3f / 180.0f * glm::pi<float>(), glm::vec3(0.0f, 1.0f, 0.0f))) << std::endl;
    glm::mat4 view = Window::view;
    glUseProgram(shader);
    glm::mat4 modelview = Window::view * modelM;
    glUniformMatrix4fv(glGetUniformLocation(shader, "view"), 1, false, glm::value_ptr(view));
    glUniformMatrix4fv(glGetUniformLocation(shader, "projection"), 1, false, glm::value_ptr(Window::projection));
    glUniformMatrix4fv(glGetUniformLocation(shader, "model"), 1, GL_FALSE, glm::value_ptr(modelM));
    glUniform3fv(glGetUniformLocation(shader, "color"), 1, glm::value_ptr(color));
    glUniform3fv(glGetUniformLocation(shader, "direction"), 1, glm::value_ptr(glm::vec3(-0.2f, -1.0f, -0.3f)));
    glUniform3fv(glGetUniformLocation(shader, "lightColor"), 1, glm::value_ptr(lightColor));
    glUniform1i(glGetUniformLocation(shader, "objType"), 2.0f);
    glUniform3fv(glGetUniformLocation(shader, "viewpos"), 1, glm::value_ptr(eyePos));
    glUniform1i(glGetUniformLocation(shader, "isphong"), 1.0f);
    glUniform1i(glGetUniformLocation(shader, "islight"), 0);
    // Bind the VAO
    glBindVertexArray(VAO);
    // Set point size
    if ((fileName.find("teapot") != std::string::npos)  || (fileName.find("sphere") != std::string::npos) || ((fileName.find("torus") != std::string::npos))){
        glDrawElements(GL_TRIANGLES, sizeof(glm::ivec3) * indices.size(), GL_UNSIGNED_INT, 0);
    }
    else{
       glDrawArrays(GL_TRIANGLES, 0, vertices.size());
    }

//    if ((fileName.find("sphere") != std::string::npos)){
//        std::cout << glm::to_string(modelM) << std::endl;
//    }
    
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
    // spin(0.3f);
}

void Geometry::loadFileSimple(std::string filepath){
        
    FILE* fp;     // file pointer
    float x, y, z;  // vertex coordinates
    unsigned int f_1_n, f_2_n, f_3_n;
    unsigned int f_1_t, f_2_t, f_3_t;
    unsigned int f_1, f_2, f_3;
    float r, g, b;  // vertex color
    int c1, c2, c3;    // characters read from file
    int v_count = 0;
    int n_count = 0;
    int f_count = 0;
    const char* fpath = filepath.c_str();
    fp = fopen(fpath, "rb");  // make the file name configurable so you can load other files

    indices.push_back(0);
    indices.push_back(1);
    indices.push_back(2);

    while (!feof(fp)) {
        c1 = fgetc(fp);
        c2 = fgetc(fp);
        char line[150];
        if ((c1 == 'v') && (c2 == ' ')) {
            fscanf(fp, "%f %f %f", &x, &y, &z);
            glm::vec3 vertex_pos(x, y, z);
            vertices.push_back(vertex_pos);
            v_count++;
        }
        else if ((c1 == 'v') && (c2 == 'n')) {
            c3 = fgetc(fp);
            if (c3 == ' ') {
                fscanf(fp, "%f %f %f", &x, &y, &z);
                glm::vec3 vertex_pos(x, y, z);
                normals.push_back(glm::normalize(vertex_pos));
            }
            n_count++;
        }
        else if ((c1 == 'f') && (c2 == ' ')) {
            fscanf(fp, "%u//%u %u//%u %u//%u", &f_1, &f_1_n, &f_2, &f_2_n, &f_3, &f_3_n);
            indices.push_back(f_1 - 1);
            indices.push_back(f_2 - 1);
            indices.push_back(f_3 - 1);
        }
        fgets(line, 300, fp);
    }

    fclose(fp);   // make sure you don't forget to close the file when done

    float x_max = std::numeric_limits<float>::min();
    float x_min = std::numeric_limits<float>::max();
    float y_max = std::numeric_limits<float>::min();
    float y_min = std::numeric_limits<float>::max();
    float z_max = std::numeric_limits<float>::min();
    float z_min = std::numeric_limits<float>::max();

    for (unsigned int i = 0; i < vertices.size(); ++i)
    {
        if (vertices[i].x > x_max) {
            x_max = vertices[i].x;
        }
        if (vertices[i].x < x_min) {
            x_min = vertices[i].x;
        }
        if (vertices[i].y > y_max) {
            y_max = vertices[i].y;
        }
        if (vertices[i].y < y_min) {
            y_min = vertices[i].y;
        }
        if (vertices[i].z > z_max) {
            z_max = vertices[i].z;
        }
        if (vertices[i].z < z_max) {
            z_min = vertices[i].z;
        }
    }

    float x_center = (x_max + x_min) / 2;
    float y_center = (y_max + y_min) / 2;
    float z_center = (z_max + z_min) / 2;


    std::vector<glm::vec3> ver;
    for (auto&& v : vertices) {
        v = v - glm::vec3(x_center, y_center, z_center);
        ver.push_back(v);
    }
    vertices = ver;
    
//    modelM *= glm::scale(glm::mat4(1), glm::vec3(5));
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), vertices.data(), GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void *)0);
    glGenBuffers(1, &VBO_N);
    glBindBuffer(GL_ARRAY_BUFFER, VBO_N);
    glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(glm::vec3), normals.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(1, 3, GL_FLOAT,  GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(1);
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), indices.data(), GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}
    
void Geometry::update() {
}

glm::mat4 Geometry::getMatrix(){
    return modelM;
}
void Geometry::setMatrix(glm::mat4 M){
    modelM = M;
}

void Geometry::loadFileComplex(std::string filepath) {
    std::vector< unsigned int > vertexIndices, uvIndices, normalIndices;
    std::vector< glm::vec3 > temp_vertices;
    std::vector< glm::vec3 > temp_uvs;
    std::vector< glm::vec3 > temp_normals;
    
    float xmax = -16.4804;
    
    FILE * file = fopen(filepath.c_str(), "r");
    if( file == NULL ){
        printf("Impossible to open the file !\n");
        return;
    }
    while( 1 ){
        char lineHeader[128];
        // read the first word of the line
        int res = fscanf(file, "%s", lineHeader);
        if (res == EOF)
            break;
        if ( strcmp( lineHeader, "v" ) == 0 ){
            glm::vec3 vertex;
            fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z );
            temp_vertices.push_back(vertex);
        } else if ( strcmp( lineHeader, "vt" ) == 0 ){
            glm::vec3 uv;
            fscanf(file, "%f %f\n", &uv.x, &uv.y );
            temp_uvs.push_back(uv);
        } else if ( strcmp( lineHeader, "vn" ) == 0 ){
            glm::vec3 normal;
            fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z );
            temp_normals.push_back(normal);
        } else if ( strcmp( lineHeader, "f" ) == 0 ){
            std::string vertex1, vertex2, vertex3;
            unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
            int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2] );
            if (matches != 9){
                printf("File can't be read by our simple parser : ( Try exporting with other options\n");
                return;
            }
            vertexIndices.push_back(vertexIndex[0]);
            vertexIndices.push_back(vertexIndex[1]);
            vertexIndices.push_back(vertexIndex[2]);
            uvIndices    .push_back(uvIndex[0]);
            uvIndices    .push_back(uvIndex[1]);
            uvIndices    .push_back(uvIndex[2]);
            normalIndices.push_back(normalIndex[0]);
            normalIndices.push_back(normalIndex[1]);
            normalIndices.push_back(normalIndex[2]);
        }
    }
    
    for (unsigned int i=0; i<vertexIndices.size(); i++ ){
        unsigned int vertexIndex = vertexIndices[i];
        glm::vec3 vertex = temp_vertices[ vertexIndex-1 ];
        vertices.push_back(vertex);
    }
//    for (unsigned int i=0; i<uvIndices.size(); i++ ){
//           unsigned int uvIndex = uvIndices[i];
//           glm::vec3 uv = temp_uvs[ uvIndex-1 ];
//           uvs.push_back(uv);
//    }
    
    for (unsigned int i=0; i<normalIndices.size(); i++ ){
        unsigned int normalIndex = normalIndices[i];
        glm::vec3 normal = temp_normals[ normalIndex-1 ];
//        if(glm::normalize(normal) == glm::vec3(1.f, 0.f, 0.f)){
////            if (fileName.find("lobby") != std::string::npos){
////                std::cout << "iamhere" << std::endl;
////            }
//            if (vertices[i].x > xmax || vertices[i].x < 0) xmax = vertices[i].x;
//        }
        normals.push_back(normal);
    }
    
    for (unsigned int i=0; i < vertices.size(); i++){
        if (vertices[i].x > xmax && vertices[i].x < -16 && glm::normalize(normals[i]) == glm::vec3(1.f, 0.f, 0.f)){
//            std::cout << glm::to_string(vertices[i]) << std::endl;
//            xmax = vertices[i].x;
            
        }
    }
    
//    std::cout << xmax << std::endl;
    
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), vertices.data(), GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void *)0);
    glGenBuffers(1, &VBO_N);
    glBindBuffer(GL_ARRAY_BUFFER, VBO_N);
    glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(glm::vec3), normals.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(1, 3, GL_FLOAT,  GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(1);
//    glGenBuffers(1, &EBO);
//    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
//    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), indices.data(), GL_STATIC_DRAW);
//    glBindBuffer(GL_ARRAY_BUFFER, 0);
//    glBindVertexArray(0);
}
