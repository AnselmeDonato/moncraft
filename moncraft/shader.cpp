//
//  shader.cpp
//  moncraft
//
//  Created by Anselme Donato on 04/12/2021.
//

#include "shader.hpp"

// Loads the content of an ASCII file in a standard C++ string
std::string file2String(const std::string &_filename) {
    std::ifstream _inputFile(_filename.c_str());
    std::stringstream _buffer;
    _buffer << _inputFile.rdbuf();
    return _buffer.str();
}

void loadShader(GLuint _program, GLenum _type, const std::string &_shaderFilename){
    GLuint _shader = glCreateShader(_type);
    std::string _shaderSourceString = file2String(_shaderFilename);
    const GLchar *_shaderSource = (const GLchar*)_shaderSourceString.c_str();
    glShaderSource(_shader, 1, &_shaderSource, NULL);
    glCompileShader(_shader);
    glAttachShader(_program, _shader);
    glDeleteShader(_shader);
    
    //Checking if the compilation of the vertexShader was successful
    int _success;
    char infoLog[512];
    glGetShaderiv(_shader, GL_COMPILE_STATUS, &_success);
    if(!_success){
        glGetShaderInfoLog(_shader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::"<< _shaderFilename << "::COMPILATION_FAILED \n" << infoLog <<std::endl;
    }
}
