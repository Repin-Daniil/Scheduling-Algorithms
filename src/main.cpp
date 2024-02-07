#include <iostream>
#include "Application/Application.h"

namespace {

Algorithm GetAlgorithmFromUser() {
  std::string input;

  std::cout << "Algorithm: ";
  std::cin >> input;

  return string_to_algo.at(input);
}

}  // namespace

int main() {
  try {
    app::Application app(GetAlgorithmFromUser());
    app.Start();
  }
  catch (const std::exception &ex) {
    std::cerr << ex.what() << std::endl;
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
