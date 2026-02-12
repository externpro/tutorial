// main.cpp
#include <fmt/core.h>
#include <spdlog/spdlog.h>
#include <nlohmann/json.hpp>

int main() {
  // Using fmt library
  fmt::print("Hello, {}!\n", "foo");

  // Using nlohmann_json library
  nlohmann::json data = {
    {"name", "foo"},
    {"type", "package manager"}
  };
  fmt::print("{}\n", data.dump());

  // Using spdlog library
  spdlog::info("Closing app");

  return 0;
}
