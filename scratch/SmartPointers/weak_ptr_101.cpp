#include <iostream>
#include <memory>

int main() {
    std::shared_ptr<int> sharedInt = std::make_shared<int>(42);
    std::weak_ptr<int> weakInt = sharedInt;

    std::cout << "Owners: " << sharedInt.use_count() << std::endl;

    if (auto shared = weakInt.lock()) {
        std::cout << "Value: " << *shared << std::endl;
    } else {
        std::cout << "Not available" << std::endl;
    }

    // freeing the shared pointer
    sharedInt.reset();

    if (auto shared = weakInt.lock()) {
        std::cout << "Value: " << *shared << std::endl;
    } else {
        std::cout << "Not available" << std::endl;
    }

    return 0;
}
