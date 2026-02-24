cmake_minimum_required(VERSION 3.10)

# #Sets to new boost policty if using a cringe version of cmake (mine)
# if(POLICY CMP0167)
#     cmake_policy(SET CMP0167 OLD)
# endif()

project(MyGLFWProject LANGUAGES CXX C)

set(CMAKE_CXX_COMPILER clang++)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
#For LSP support!!
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

#Dependencies 

find_package(Threads REQUIRED)
find_package(glfw3 3.3 REQUIRED)
find_package(PkgConfig REQUIRED)

pkg_check_modules(WAYLAND_LIBS REQUIRED 
    wayland-client 
    wayland-cursor 
    wayland-egl 
    xkbcommon
)

#Source Files
file(GLOB_RECURSE SOURCES "src/*.cpp")
set(GLAD_SOURCE "include/glad/src/glad.c")

add_executable(${PROJECT_NAME} ${SOURCES} ${GLAD_SOURCE})

#Includes
target_include_directories(${PROJECT_NAME} PRIVATE
    "include/glad/include"   
    "src"                    
    ${WAYLAND_LIBS_INCLUDE_DIRS}
)

#Linking
target_link_libraries(${PROJECT_NAME} PRIVATE 
    glfw
    GL 
    ${WAYLAND_LIBS_LIBRARIES}
    pthread 
    dl
)

set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
