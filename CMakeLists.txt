cmake_minimum_required(VERSION 3.20)

project(DotEngine)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
add_definitions(-DGL_SILENCE_DEPRECATION)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -frtti")

# Find GLFW package
find_package(PkgConfig REQUIRED)
find_package(GLFW3 REQUIRED)

# AngelScript paths
set(ANGELSCRIPT_DIR ${CMAKE_SOURCE_DIR}/angelscript/sdk/angelscript)
set(ANGELSCRIPT_ADDON_DIR ${CMAKE_SOURCE_DIR}/angelscript/sdk/add_on)
set(ANGELSCRIPT_INCLUDE_DIR ${ANGELSCRIPT_DIR}/include)
set(ANGELSCRIPT_SRC_DIR ${ANGELSCRIPT_DIR}/source)
set(ANGELSCRIPT_LIB_DIR ${ANGELSCRIPT_DIR}/projects/cmake/build)

# Include directories
include_directories(${ANGELSCRIPT_INCLUDE_DIR})
include_directories(${ANGELSCRIPT_ADDON_DIR}/scriptbuilder)
include_directories(${ANGELSCRIPT_ADDON_DIR}/scriptstdstring)
include_directories(${ANGELSCRIPT_ADDON_DIR}/scriptarray)
include_directories(${CMAKE_SOURCE_DIR}/header)
include_directories(${CMAKE_SOURCE_DIR}/header/Math_C)
include_directories(${CMAKE_SOURCE_DIR}/header/Objects_C)

# Check if AngelScript is built as static or shared
if(EXISTS ${ANGELSCRIPT_LIB_DIR}/libangelscript.a)
    set(ANGELSCRIPT_LIB ${ANGELSCRIPT_LIB_DIR}/libangelscript.a)
elseif(EXISTS ${ANGELSCRIPT_LIB_DIR}/libangelscript.so)
    set(ANGELSCRIPT_LIB ${ANGELSCRIPT_LIB_DIR}/libangelscript.so)
else()
    message(FATAL_ERROR "AngelScript library not found in ${ANGELSCRIPT_LIB_DIR}. Please build AngelScript first.")
endif()

# Add AngelScript sources (.cpp) and headers (.h)
file(GLOB_RECURSE ANGELSCRIPT_SOURCES
    ${ANGELSCRIPT_SRC_DIR}/*.cpp
)
file(GLOB_RECURSE ANGELSCRIPT_HEADERS
    ${ANGELSCRIPT_SRC_DIR}/*.h
)

# Add the scriptbuilder.cpp from AngelScript's add_on folder
file(GLOB ADDON_SOURCES
    ${ANGELSCRIPT_ADDON_DIR}/scriptbuilder/scriptbuilder.cpp
    ${ANGELSCRIPT_ADDON_DIR}/scriptstdstring/scriptstdstring.cpp
    ${ANGELSCRIPT_ADDON_DIR}/scriptarray/scriptarray.cpp
)

# Collect all source files from the project
file(GLOB_RECURSE SOURCE_FILES
    "source/*.cpp"
    "source/Math_C/*.cpp"
    "source/Objects_C/*.cpp"
)

# Add the executable, using all the source files in the "source" folder, including AngelScript if required
add_executable(DotEngine source/main.cpp ${SOURCE_FILES} ${ADDON_SOURCES})

# Link libraries for DotEngine executable (using GLFW, GLM, and AngelScript)
target_link_libraries(DotEngine glfw ${ANGELSCRIPT_LIB})

# Include AngelScript headers in the target for better IDE integration
target_include_directories(DotEngine PRIVATE ${ANGELSCRIPT_INCLUDE_DIR} ${ANGELSCRIPT_SRC_DIR} ${CMAKE_SOURCE_DIR}/glm)

# MacOS Specific settings for DotEngine
if(APPLE)
    target_link_libraries(DotEngine "-framework Cocoa" "-framework OpenGL" "-framework IOKit" "-framework CoreVideo")
endif()

# Optional: Add AngelScript source files directly to the project if you want to build AngelScript with your project
# Uncomment this if you want to compile AngelScript with your project
# target_sources(DotEngine PRIVATE ${ANGELSCRIPT_SOURCES})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
