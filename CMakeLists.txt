# CMakeLists.txt
cmake_minimum_required(VERSION 3.31)
project(MyProject)

# Find packages
find_package(fmt REQUIRED)
find_package(nlohmann_json REQUIRED)

# Link libraries
add_executable(app main.cpp)
target_link_libraries(app PRIVATE
    fmt::fmt
    nlohmann_json::nlohmann_json)
