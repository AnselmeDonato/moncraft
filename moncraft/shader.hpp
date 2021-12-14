//
//  shader.hpp
//  moncraft
//
//  Created by Anselme Donato on 04/12/2021.
//

#ifndef SHADER_HPP
#define SHADER_HPP

#include <glad/glad.h>

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

class Shader {
public:
    //the program ID
    unsigned int ID;
    
    //constructor reads and builds the shader
    Shader(const char* vertexPath, const char* fragmentPath){
        
        // 1. retrieve the vertex/fragment source code from filePath
        /*--------------------------------------------------------*/
        std::string vertexCode;
        std::string fragmentCode;
        std::ifstream vShaderFile;
        std::ifstream fShaderFile;
        //ensure ifstream objects can throw exceptions:
        vShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
        fShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
        try{
            //open file
            vShaderFile.open(vertexPath);
            fShaderFile.open(fragmentPath);
            std::stringstream vShaderStream, fShaderStream;
            //read file's buffer contents into streams
            vShaderStream << vShaderFile.rdbuf();
            fShaderStream << fShaderFile.rdbuf();
            //close file handlers
            vShaderFile.close();
            fShaderFile.close();
            //convert stream into string
            vertexCode = vShaderStream.str();
            fragmentCode = fShaderStream.str();
        }
        catch(std::ifstream::failure e)
        {
            std::cout<<"ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ" <<std::endl;
        }
        const char* vShaderCode = vertexCode.c_str();
        const char* fShaderCode = fragmentCode.c_str();
        /*--------------------------------------------------------*/
        
        // 2. compile shaders
        /*--------------------------------------------------------*/
        unsigned int vertex, fragment ;
        int success;
        char infoLog[512];
        
        //vertex Shader
        vertex = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertex, 1, &vShaderCode, NULL);
        glCompileShader(vertex);
        // print compile error if any
        glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
        if(!success) {
            glGetShaderInfoLog(vertex, 512, NULL, infoLog);
            std::cout<< "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n"<<infoLog<<std::endl;
        }
        //fragment Shader
        fragment = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragment, 1, &fShaderCode, NULL);
        glCompileShader(fragment);
        // print compile error if any
        glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
        if(!success) {
            glGetShaderInfoLog(fragment, 512, NULL, infoLog);
            std::cout<< "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n"<<infoLog<<std::endl;
        }
        
        //shader Program
        ID = glCreateProgram();
        glAttachShader(ID, vertex);
        glAttachShader(ID, fragment);
        glLinkProgram(ID);
        // print compile errors if any
        glGetProgramiv(ID, GL_LINK_STATUS, &success);
        if(!success)
        {
            glGetProgramInfoLog(ID, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n"<<infoLog<<std::endl;
        }
        
        //delete shaders; they're linked into our program and no longer necessary
        glDeleteShader(vertex);
        glDeleteShader(fragment);
    }
    //use or activate the shader
    void use(){
        glUseProgram(ID);
    }
    //utilisty uniform functions
    void setBool(const std::string &name, bool value) const{
        glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
    }
    void setInt(const std::string &name, int value) const{
        glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
    }
    void setFloat(const std::string &name, float value) const{
        glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
    }
    void setMatrix4fv(const std::string &name, const GLfloat* value_ptr) const{
        glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, value_ptr);
    }
    void setVec3f(const std::string &name, float v0, float v1, float v2) const{
        glUniform3f(glGetUniformLocation(ID, name.c_str()), v0, v1, v2);
    }
    void setVec3f(const std::string &name, const GLfloat* value_ptr) const{
        glUniform3fv(glGetUniformLocation(ID, name.c_str()), 1, value_ptr);
    }
};
#endif /* shader_hpp */
