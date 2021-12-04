//
//  shader.hpp
//  moncraft
//
//  Created by Anselme Donato on 04/12/2021.
//

#ifndef shader_hpp
#define shader_hpp

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <cmath>
#include <memory>

#include <stdio.h>

std::string file2String(const std::string &_filename);

void loadShader(GLuint _program, GLenum _type, const std::string &_shaderFilename);

#endif /* shader_hpp */
