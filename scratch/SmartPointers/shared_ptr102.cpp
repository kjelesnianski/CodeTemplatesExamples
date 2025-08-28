#include <iostream>
#include <memory>

void printValue(std::shared_ptr<int> sharedInt) {
    std::cout << *sharedInt << std::endl; // 123
}

int main() {
    std::shared_ptr<int> sharedInt = std::make_shared<int>(123);
    printValue(sharedInt);
    return 0;
}
