//
// Created by sebas on 09/01/2025.
//

#ifndef SHADER_H
#define SHADER_H

#include <string>

#include "glm.hpp"

#include "glFunctions.h"

#define MAX_SHADER_SIZE 4096

class Shader {
public:
    explicit Shader(const std::string& shaderName);
    ~Shader();
    void use() const;
    void setFloat(const std::string& name, float value) const;
    void setMat4(const std::string& name, glm::mat4 value) const;
private:
    GLuint programID;
};



#endif //SHADER_H
