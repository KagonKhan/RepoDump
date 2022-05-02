#include "Renderer.h"
#include <iostream>

bool GLLogCall(const char* function, const char* file, int line) {
    while (GLenum  error = glGetError()) {
        std::cout << "[OpenGL Error] (" << error << "): " << function <<
            "\n\t\t\t" << file << " : " << line << '\n';

        return false;
    }
    return true;
}

void GLClearError() {
    while (glGetError() != GL_NO_ERROR);
}
