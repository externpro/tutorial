# CMakeLists.txt
cmake_minimum_required(VERSION 3.31)
project(MyProject)

# Find packages
find_package(fmt REQUIRED)
find_package(spdlog REQUIRED)
find_package(nlohmann_json REQUIRED)

# Link libraries
add_executable(app main.cpp)
target_link_libraries(app PRIVATE
    fmt::fmt
    spdlog::spdlog
    nlohmann_json::nlohmann_json)
set_target_properties(app PROPERTIES DEBUG_POSTFIX -d)

include(GNUInstallDirs)
set(CMAKE_INSTALL_CMAKEDIR ${CMAKE_INSTALL_DATADIR}/cmake)
set(targetsFile ${PROJECT_NAME}-targets)
install(TARGETS app EXPORT ${targetsFile} DESTINATION ${CMAKE_INSTALL_BINDIR})
install(EXPORT ${targetsFile} DESTINATION ${CMAKE_INSTALL_CMAKEDIR} NAMESPACE bar::)
