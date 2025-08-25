#include <iostream>
#include <memory>

class MyClass {
public:
    MyClass(int value) : value(value) {}

    ~MyClass() {}

private:
    int value;
};

/* std::use_count Returns the number of different shared_ptr instances (*this
 * included) managing the current object. If there is no managed object,
 * ​0​ is returned.
 * In multithreaded environment, use_count atomically retrieves the number of
 * instances (typical implementations use a memory_order_relaxed load).
 */

int main() {
    std::shared_ptr<MyClass> sharedObj = std::make_shared<MyClass>(42);
    std::shared_ptr<MyClass> sharedObj2 = sharedObj;

    std::cout << sharedObj.use_count()  << std::endl; // 2
    std::cout << sharedObj2.use_count() << std::endl; // 2

    sharedObj.reset();

    std::cout << sharedObj.use_count()  << std::endl; // 0
    std::cout << sharedObj2.use_count() << std::endl; // 1

    sharedObj2.reset();

    std::cout << sharedObj.use_count()  << std::endl; // 0
    std::cout << sharedObj2.use_count() << std::endl; // 0

    return 0;
}
