#include <iostream>                                                                                                                         
#include <fstream>
#include <vector>
#include <memory>
#include <string>
#include <algorithm>
#include <numeric>
#include <stdexcept>
#include <functional>

#include "FileProcessor_cj.hpp"

int main() {
  try {
    FileProcessor processor;
    processor.readFile("input.bin");

    //TODO lamda

    processor.writeFile("output.bin");

    processor.printSummary();

    std::cout << "Sorted:" << std::endl;
    processor.displaySorted();

  } catch(const std::exception& e){
    std::cerr << "Error: " << e.what() << std::endl;
    return 1;
  }
  return 0;
}
