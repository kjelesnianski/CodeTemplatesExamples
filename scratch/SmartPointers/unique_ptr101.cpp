#include <iostream>
#include <memory>

int main() {
    std::unique_ptr<int> u1(new int(1));
    std::unique_ptr<int> u2(new int(2));
    std::unique_ptr<int> u3 = std::move(u1);
    // std::unique_ptr<int> u4 = u2; // error

    if(u1) {
        // will not be printed as u1 is null
        std::cout << "unique_ptr 1: " << *u1 << std::endl;
    }
    if(u2 != nullptr) {
        std::cout << "unique_ptr 2: " << *u2 << std::endl;
    }
    if(u3) {
        std::cout << "unique_ptr 3: " << *u3 << std::endl;
    }

    return 0;
}
