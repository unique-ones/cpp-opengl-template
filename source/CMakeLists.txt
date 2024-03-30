#
# MIT License
#
# Copyright (c) 2024 unique-ones
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.

# Project source files
file(GLOB PROJECT_SOURCES 
    "${CMAKE_CURRENT_SOURCE_DIR}/*.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
)

# Fetch glfw and glm from github
include(FetchContent)
FetchContent_Declare(glfw GIT_REPOSITORY https://github.com/glfw/glfw.git)
FetchContent_Declare(glm GIT_REPOSITORY https://github.com/g-truc/glm.git)
FetchContent_MakeAvailable(glfw glm)

# Executable definition with the project sources and extern sources
add_executable("${PROJECT_NAME}"
    "${PROJECT_SOURCES}"
    "${CMAKE_SOURCE_DIR}/extern/glad/glad.c"
    "${CMAKE_SOURCE_DIR}/extern/glad/glad.h"
    "${CMAKE_SOURCE_DIR}/extern/glad/khrplatform.h"
)

# Add include path of extern folder to project executable
target_include_directories("${PROJECT_NAME}" PUBLIC "${CMAKE_SOURCE_DIR}/extern")

# Link glfw and glm with project executable
target_link_libraries("${PROJECT_NAME}" glfw glm::glm)
