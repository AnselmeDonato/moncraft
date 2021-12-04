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

//#include "shader.cpp"

void loadShader(GLuint _program, GLenum type, const std::string &_shaderFilename);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

int wireframeMode = 0;

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
    else {
        std::cout << "SHADER::" << _shaderFilename << "::COMPILATION_SUCCEEDED\n" <<std::endl;
    }
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
void processInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
    if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        if(wireframeMode){
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
            wireframeMode = 0;
        }
        else {
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            wireframeMode = 1;
        }
    }
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}

int main()
{
    // glfw: initialize and configure
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // glfw window creation
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // glad: load all OpenGL function pointers
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
    
    //Initialisation of meshes and shaders
    //Defining vertices for the triangle
    float vertices[] = {
        -0.5f, -0.5f, 0.0f,
        -0.5f,  0.5f, 0.0f,
         0.5f,  0.5f, 0.0f,
         0.5f, -0.5f, 0.0f
    };
    
    unsigned int indices[] = {
        0, 2, 1,
        0, 2, 3
    };
    
    //Bind Vertex Array Object
    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    
    //Storing the vertex data within memory on the graphics card, managed by a vertex buffer object named VBO
    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    
    //Storing the vertex data within memory on the graphics card, managed by an element buffer object named EBO
    unsigned int EBO;
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    
    //Specifing to OpenGL how it should interpret the vertex data
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    
    
    
    
    /* ---------------- Shaders -------------------*/
    /*
    
    //Creating vertex shader (actual code of the shader at the top of the file)
    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    
    //Checking if the compilation of the vertexShader was successful
    int successVertex;
    char infoLogVertex[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &successVertex);
    if(!successVertex){
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLogVertex);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLogVertex <<std::endl;
    }
    else {
        std::cout << "SHADER::VERTEX  ::COMPILATION_SUCCEEDED\n" <<std::endl;
    }
    
    //Creating fragment shader (actual code of the shader at the top of the file)
    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    
    //Checking if the compilation of the fragmentShader was successful
    int successFragment;
    char infoLogFragment[512];
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &successFragment);
    if(!successFragment){
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLogFragment);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLogFragment <<std::endl;
    }
    else {
        std::cout << "SHADER::FRAGMENT::COMPILATION_SUCCEEDED\n" <<std::endl;
    }
    
    //Creating the shader program
    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    
    //Checking if the compilation of the shader program was successful
    int successShader;
    char infoLogShader[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &successShader);
    if(!successShader){
        glGetShaderInfoLog(shaderProgram, 512, NULL, infoLogShader);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLogFragment <<std::endl;
    }
    else {
        std::cout << "SHADER::PROGRAM ::COMPILATION_SUCCEEDED\n" <<std::endl;
    }
    
    //Once we've linked the shaders into the program object, we no longer need them anymore
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
     */
    
    unsigned int _shaderProgram = glCreateProgram();
    loadShader(_shaderProgram, GL_VERTEX_SHADER, "/Users/anselmedonato/desktop/Pas Telecom/OpenGL/moncraft/moncraft/vertexShader.glsl");
    loadShader(_shaderProgram, GL_FRAGMENT_SHADER, "/Users/anselmedonato/desktop/Pas Telecom/OpenGL/moncraft/moncraft/fragmentShader.glsl");
    glLinkProgram(_shaderProgram);
    
    /* --------------------------------------------*/

    // render loop
    while (!glfwWindowShouldClose(window))
    {
        // input
        processInput(window);

        // render
        //glClearColor(0.94f, 0.59f, 0.71f, 1.0f);
        glClearColor(245.f/255, 214.f/255, 175.f/255, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        
        // Drawing the object
        glUseProgram(_shaderProgram);
        glBindVertexArray(VAO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // glfw: terminate, clearing all previously allocated GLFW resources.
    glfwDestroyWindow(window);
    glfwTerminate();
    return EXIT_SUCCESS;
}


