#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "Renderer.h"
#include "IndexBuffer.h"
#include "VertexBuffer.h"

GLFWwindow* initWindow();


static unsigned int CompileShader(unsigned int type, const std::string& source) {

    unsigned int id = glCreateShader(type);

    const char* src = source.c_str();
    // &source[0];
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);


    int result; 
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);

    if (result == GL_FALSE) {
        int len;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &len);

        //Dynamic allocation on stack - alloca
        char* message = (char*)alloca(len * sizeof(char));

        std::cout << "[ERROR] Failed compiling"  << 
            (type == GL_VERTEX_SHADER? "vertex" : "fragment")
            <<  " shader!";

        glGetShaderInfoLog(id, len, &len, message);
        std::cout << message << std::endl;

        glDeleteShader(id);
        return 0;
    }


    return id;
}

static unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader) {
    unsigned int program = glCreateProgram();
   
    unsigned int vs = CompileShader( GL_VERTEX_SHADER, vertexShader );
    unsigned int fs = CompileShader( GL_FRAGMENT_SHADER, fragmentShader );

    glAttachShader(program, vs);
    glAttachShader(program, fs);

    glLinkProgram(program);
    glValidateProgram(program);

    //glDetachShader
    glDeleteShader(vs);
    glDeleteShader(fs);

    return program;
}

unsigned int initShader(const std::string& filepath) {
  
    std::stringstream ss[2];


    enum class ShaderType {
        NONE = -1, VERTEX = 0, FRAGMENT = 1
    } type = ShaderType::NONE;

    std::ifstream stream(filepath);

    std::string line;
    while (getline(stream, line)) {
        if (line.find("#shader") != std::string::npos) {

            if (line.find("vertex") != std::string::npos)
                type = ShaderType::VERTEX;
            else if (line.find("fragment") != std::string::npos)
                type = ShaderType::FRAGMENT;
        }
        else {
            ss[static_cast<int>(type)] << line << '\n';
        }

    }

    unsigned int shader = CreateShader(ss[0].str(), ss[1].str());
    glUseProgram(shader);


    int location = glGetUniformLocation(shader, "u_Color");
    ASSERT(location != -1);
 
    glUniform4f(location, 1.0, 0.0, 0.0, 1.f);

    return shader;
}

void initTriangle() {
    unsigned int buffer;
    float positions[6] = {
        -0.5f,-0.5f,
         0.0f, 0.5f,
         0.5f,-0.5f
    };
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), positions, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);
    glEnableVertexAttribArray(0);
}


int main(void) {
  
    GLFWwindow* window = initWindow();
  
    //initTriangle();
 
    unsigned int shader = initShader("res/shaders/basic.shader");
    int location = glGetUniformLocation(shader, "u_Color");



    {
        float positions[8] = {
            -0.5f, -0.5f, //0
             0.5f, -0.5f, //1
             0.5f,  0.5f, //2
            -0.5f,  0.5f  //3
        };

        // INDEX BUFFER
        unsigned int indices[6] = {
            0, 1, 2,
            2, 3, 0
        };


        unsigned int vao;
        GLCall(glGenVertexArrays(1, &vao));
        GLCall(glBindVertexArray(vao));

        VertexBuffer vb(positions, 4 * 2 * sizeof(float));


        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);

        IndexBuffer ib(indices, 6);





        float r = 0.f, increment = 0.01f;

        /* Loop until the user closes the window */
        while (!glfwWindowShouldClose(window)) {
            /* Render here */
            glClear(GL_COLOR_BUFFER_BIT);

            if (r > 1.0f || r < 0.f)
                increment = -increment;

            r += increment;

            glUniform4f(location, r, cos(r * r), sin(increment * r), 1.f);
            //glDrawArrays(GL_TRIANGLES, 0, 6);
            GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));





            /* Swap front and back buffers */
            glfwSwapBuffers(window);

            /* Poll for and process events */
            glfwPollEvents();
        }












        glDeleteProgram(shader);
    }
    glfwTerminate();
    return 0;
}

GLFWwindow* initWindow() {

    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        throw std::runtime_error("GLFW_INIT");


    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);





    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(800, 800, "Hello World", NULL, NULL);
    if (!window) {
        glfwTerminate();
        throw std::runtime_error("WINDOW" );
    }
    /* Make the window's context current */
    glfwMakeContextCurrent(window);


    glfwSwapInterval(1);

    if (glewInit() != GLEW_OK)
        throw std::runtime_error("GLEW_INIT");

    std::cout << glGetString(GL_VERSION) << std::endl;

    return window;
}