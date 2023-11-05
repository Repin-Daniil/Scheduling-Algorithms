#include <iostream>
#include "Application/Application.h"

int main() {
  try {
    app::Application app({ApplicationConstants::WIDTH,
                          ApplicationConstants::HEIGHT,
                          Algorithm::FCFS});

    app.Start();
  }
  catch (const std::exception &ex) {
    std::cerr << ex.what() << std::endl;
  }
}