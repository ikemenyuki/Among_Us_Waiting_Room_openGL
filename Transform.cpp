//
//  Transform.cpp
//  CSE167 Starter
//
//  Created by yueqi liao on 11/19/20.
//  Copyright © 2020 YueqiLiao. All rights reserved.
//

#include <stdio.h>
#include "Transform.hpp"
#include <stdio.h>
#include <vector>
#include <iostream>

void Transform::addChild(Node* node){
    ptrs.push_back(node);
}

//void Transform::removeChild(Node* childNode){
//    nodeList.pop_back();
//}

void Transform::draw(glm::mat4 C) {
    for (int i = 0; i < ptrs.size(); i++)
    {
        auto node = ptrs[i];
        // node->draw(C*M);
        node->draw(C*M);
    }
}

glm::mat4 Transform::getMatrix() {
    return M;
}

void Transform::setMatrix(glm::mat4 mat) {
    M = mat;
}

void Transform::update() {
}

