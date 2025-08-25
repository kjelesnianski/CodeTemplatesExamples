#include <memory>
#include <iostream>

class B;

class A {
public:
    std::shared_ptr<B> b_ptr;

    A() {
        std::cout << "A constructor" << std::endl;
    }

    ~A() {
        std::cout << "A destructor" << std::endl;
    }
};

class B {
public:
    std::shared_ptr<A> a_ptr;

    B() {
        std::cout << "B constructor" << std::endl;
    }

    ~B() {
        std::cout << "B destructor" << std::endl;
    }
};

int main() {
    {
        std::shared_ptr<A> a = std::make_shared<A>();
        std::shared_ptr<B> b = std::make_shared<B>();

        a->b_ptr = b;
        b->a_ptr = a;
    }

    return 0;
}
