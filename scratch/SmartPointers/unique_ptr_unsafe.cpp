#include <iostream>
#include <memory>

int main() {
    std::unique_ptr<int> uniqueInt(new int(42));
    std::cout << *uniqueInt << std::endl; // 42

    int* rawPtr = uniqueInt.release();
    std::cout << *rawPtr << std::endl; // 42

    if (!uniqueInt) {
        std::cout << "no longer owns the memory." << std::endl;
    }

    delete rawPtr;

    return 0;
}
