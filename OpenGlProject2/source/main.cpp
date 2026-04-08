#include <stdio.h>
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>


void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);
int main(void)
{
    //library init
    glfwInit();
    //setting up the settings
    //major.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);
    //3.minor
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,3);
    //setting up the core
    glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);
    
    //Window
    GLFWwindow* window = glfwCreateWindow(1980, 1080, "Hello World", NULL, NULL);
    if(window == nullptr){
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    
    //glad initialization
    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        return -1;
    }
    
    glViewport(0,0,1980,1080);
    //setting up callback for window's resize handling
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glClearColor(0.2f, 0.3f, 0.2f, 0.1f);
    
    
    //hello triangle
    float vertices[] = {
        -0.5f,-0.5f,0.0f,//bottom left
        0.5f, -0.5f, 0.0f,//bottom right
        0.5f, 0.5f, 0.0f,//top right
        -0.5f, 0.5f, 0.0f, // top left
        0.75f, 0.75f,0.0f,
        0.75f, 0.5f, 0.0f,
        1.0f, 0.5f, 0.0f,
        1.0f, 0.0f, 0.0f
        
    };
    //5.8.2
    float vertices2[] = {
        -1.0f, -1.0f, 0.0f,
        -0.75f, -0.75f, 0.0f,
        -0.75f, -1.0f, 0.0f
    };
    unsigned int indices2[] ={
        0,1,2
    };
    
    
    unsigned int indices[] = {
        0,1,2,
        2,3,0,
        4,2,5,
        5,6,7
        
    };
    
    const char* vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main (){\n"
        "gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";
    const char* fragmentShaderSource = "#version 330 core\n"
    "out vec4 fragColor;\n"
    "void main(){\n"
        "fragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
    "}\0";
    const char* fragmentShaderSource2 = "#version 330 core\n"
    "out vec4 fragColor;\n"
    "void main(){\n"
        "fragColor = vec4(0.89f, 0.125f, 0.522f,1.0f);\n"
    "}\0";
    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader,1, &vertexShaderSource,NULL);
    glCompileShader(vertexShader);
    
    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    
    unsigned int fragmentShader2;
    fragmentShader2 = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader2,1, &fragmentShaderSource2, NULL);
    glCompileShader(fragmentShader2);
    
   
    
    unsigned int shaderProgram,shaderProgram2 ;
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    
    shaderProgram2 =glCreateProgram();
    glAttachShader(shaderProgram2, vertexShader);
    glAttachShader(shaderProgram2, fragmentShader2);
    glLinkProgram(shaderProgram2);

    //after linkinng we can delete the shaders
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    glDeleteShader(fragmentShader2);
    
    unsigned int VAO, VBO, EBO;
    glGenVertexArrays(1,&VAO);
    glGenBuffers(1,&VBO);
    glGenBuffers(1,&EBO);
    
    //bind VAO first
    glBindVertexArray(VAO);
    //filling and binding of vbo
    glBindBuffer(GL_ARRAY_BUFFER,VBO);
    glBufferData(GL_ARRAY_BUFFER,sizeof(vertices), vertices, GL_STATIC_DRAW);
    //bind and fill ebo
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    
    glVertexAttribPointer(0,3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    
    unsigned int VAO2,VBO2,EBO2;
    glGenVertexArrays(1,&VAO2);
    glGenBuffers(1,&VBO2);
    glGenBuffers(1,&EBO2);
    
    glBindVertexArray(VAO2);
    
    glBindBuffer(GL_ARRAY_BUFFER, VBO2);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_STATIC_DRAW);
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO2);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(indices2), indices2, GL_STATIC_DRAW);
    glVertexAttribPointer(0,3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    
    while(!glfwWindowShouldClose(window)){
        glClear(GL_COLOR_BUFFER_BIT);
        processInput(window);
        glfwPollEvents();
        glUseProgram(shaderProgram);
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES,12,GL_UNSIGNED_INT, 0);
        glUseProgram(shaderProgram2);
        glBindVertexArray(VAO2);
        glDrawElements(GL_TRIANGLES,3, GL_UNSIGNED_INT,0);
        glfwSwapBuffers(window);
       
    }
    glfwTerminate();
    return 0;
}


void framebuffer_size_callback(GLFWwindow* window, int width, int height){
    glViewport(0,0,width,height);
}
void processInput(GLFWwindow* window){
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS){
        glfwSetWindowShouldClose(window, 1);
    }
}
