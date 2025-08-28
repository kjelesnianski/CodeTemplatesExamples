#include <iostream>
#include <memory>

int main() {
    std::shared_ptr<int> sharedInt = std::make_shared<int>(12);

    std::cout << *sharedInt << std::endl; // 12

    std::shared_ptr<int> sharedInt2 = sharedInt;

    *sharedInt = 100;

    std::cout << *sharedInt << std::endl; // 100
    std::cout << *sharedInt2 << std::endl; // 100

    return 0;
}
