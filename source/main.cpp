//
//  MIT License
//
//  Copyright (c) 2024 unique-ones
//
//  Permission is hereby granted, free of charge, to any person obtaining a copy
//  of this software and associated documentation files (the "Software"), to deal
//  in the Software without restriction, including without limitation the rights
//  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//  copies of the Software, and to permit persons to whom the Software is
//  furnished to do so, subject to the following conditions:
//
//  The above copyright notice and this permission notice shall be included in all
//  copies or substantial portions of the Software.
//
//  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
//  SOFTWARE.

#include "types.h"

#include <GLFW/glfw3.h>
#include <iostream>

namespace {

const char *opengl_severity(u32 severity) {
    switch (severity) {
        case GL_DEBUG_SEVERITY_HIGH: {
            return "HIGH";
        }
        case GL_DEBUG_SEVERITY_MEDIUM: {
            return "MEDIUM";
        }
        case GL_DEBUG_SEVERITY_LOW: {
            return "LOW";
        }
        case GL_DEBUG_SEVERITY_NOTIFICATION: {
            return "NOTIFICATION";
        }
        default: {
            return "UNKNOWN";
        }
    }
}

void opengl_error_callback(u32 source, u32 type, u32 severity, s32 length, const char *message, const void *args) {
    // Do not care for messages that are just notifications
    if (severity == GL_DEBUG_SEVERITY_NOTIFICATION) {
        return;
    }

    if (auto *severity_text = opengl_severity(severity); type == GL_DEBUG_TYPE_ERROR) {
        std::fprintf(stderr, "ERROR: %d, severity = %s, message = %s\n", type, severity_text, message);
    } else {
        std::fprintf(stderr, "OTHER: %d, severity = %s, message = %s\n", type, severity_text, message);
    }
}

}// namespace

int main(int argc, char **argv) {
    if (not glfwInit()) {
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    auto *window = glfwCreateWindow(800, 400, "Application", nullptr, nullptr);
    if (not window) {
        glfwTerminate();
        return -2;
    }

    glfwMakeContextCurrent(window);
    if (not gladLoadGLLoader((GLADloadproc) (glfwGetProcAddress))) {
        glfwDestroyWindow(window);
        glfwTerminate();
        return -3;
    }

    while (not glfwWindowShouldClose(window)) {
        glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
