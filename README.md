# tutorial
externpro tutorial

I came across this simple and straightforward video on YouTube
"C++ Package Management for Beginners: vcpkg and Conan Tutorial"
https://www.youtube.com/watch?v=8kiAklZGJJE

And I decided to create this tutorial repository that uses the same example CMakeLists.txt and main.cpp to show how simple, straightforward, and powerful externpro is to streamline your C++ projects.

1. fork https://github.com/externpro/tutorial into your github account/organization
   * deselect "Copy the `main` branch only" checkbox so your clone includes the `v1.0` tag
1. clone your fork to your local machine
   ```
   git clone https://github.com/your-username/tutorial
   ```
1. initialize externpro
   ```
   cd tutorial
   git remote add upstream https://github.com/externpro/tutorial
   git fetch --all # fetch all tags in case fork didn't include tags
   git checkout -b xpro v1.0
   git submodule add https://github.com/externpro/externpro .devcontainer
   git commit -m "add externpro as submodule" -m "git submodule add https://github.com/externpro/externpro .devcontainer"
   mkdir -p .github/workflows
   cp .devcontainer/.github/wf-templates/xpinit.yml .github/workflows/
   git add .github/workflows/xpinit.yml
   git commit -m "workflows: add xpinit" -m "cp .devcontainer/.github/wf-templates/xpinit.yml .github/workflows"
   git push origin xpro
   git push origin --tags # in case fork didn't include tags
   git fetch --all
   git branch --set-upstream-to=origin/xpro xpro
   ```
1. set xpro as default branch in github repo settings
1. run xpinit workflow
1. fetch and merge xpro branch
   ```
   git fetch --all
   git status
   git merge origin/xpro
   ```
1. make changes to CMakeLists.txt
   ```diff
   diff --git a/CMakeLists.txt b/CMakeLists.txt
   index 16c3f01..018a3d5 100644
   --- a/CMakeLists.txt
   +++ b/CMakeLists.txt
   @@ -1,5 +1,6 @@
    # CMakeLists.txt
    cmake_minimum_required(VERSION 3.31)
   +set(CMAKE_PROJECT_TOP_LEVEL_INCLUDES .devcontainer/cmake/xproinc.cmake)
    project(MyProject)

    # Find packages
   @@ -13,10 +14,15 @@ target_link_libraries(app PRIVATE
        fmt::fmt
        spdlog::spdlog
        nlohmann_json::nlohmann_json)
   -set_target_properties(app PROPERTIES DEBUG_POSTFIX -d)
   +set_target_properties(app PROPERTIES DEBUG_POSTFIX ${CMAKE_DEBUG_POSTFIX})

   -include(GNUInstallDirs)
   -set(CMAKE_INSTALL_CMAKEDIR ${CMAKE_INSTALL_DATADIR}/cmake)
    set(targetsFile ${PROJECT_NAME}-targets)
   +xpExternPackage(REPO_NAME tutorial NAMESPACE xp
   +  TARGETS_FILE ${targetsFile} EXE app
   +  BASE v1.0 XPDIFF "patch" PVT_DEPS fmt spdlog nlohmann_json
   +  WEB "https://github.com/smanders/tutorial" UPSTREAM "github.com/externpro/tutorial"
   +  DESC "A simple externpro tutorial project"
   +  LICENSE "[MIT](https://github.com/externpro/tutorial?tab=MIT-1-ov-file#readme 'MIT License')"
   +  )
    install(TARGETS app EXPORT ${targetsFile} DESTINATION ${CMAKE_INSTALL_BINDIR})
   -install(EXPORT ${targetsFile} DESTINATION ${CMAKE_INSTALL_CMAKEDIR} NAMESPACE bar::)
   +install(EXPORT ${targetsFile} DESTINATION ${CMAKE_INSTALL_CMAKEDIR} NAMESPACE xp::)
   ```
   ```
   git commit -m "cmake: include xproinc, call xpExternPackage()" CMakeLists.txt
   ```
1. make changes to main.cpp
   ```diff
   diff --git a/main.cpp b/main.cpp
   index bdaf760..31403d4 100644
   --- a/main.cpp
   +++ b/main.cpp
   @@ -5,11 +5,11 @@

    int main() {
      // Using fmt library
   -  fmt::print("Hello, {}!\n", "foo");
   +  fmt::print("Hello, {}!\n", "externpro");

      // Using nlohmann_json library
      nlohmann::json data = {
   -    {"name", "foo"},
   +    {"name", "externpro"},
        {"type", "package manager"}
      };
      fmt::print("{}\n", data.dump());
   ```
   ```
   git commit -m "main.cpp: foo -> externpro" main.cpp
   ```
