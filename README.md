# Code Template Examples

The purpose of this repository is to have a place to have commonly
used code in practice. In essence, a C/C++ toolbox that I can get practice
while creating and a place to look back to once it is implemented.

Things such as:

- Demo C++ classes
- opening, reading, modifying binary files
- working with smart pointers
  - std::unique_ptr<Type>()  -- std::make_unique<Type>()
  - std::shared_ptr<Type>()  -- std::make_shared<Type>()
  - std::weak_ptr<Type>()    -- std::make_shared<Type>()
- Using standard library functions (std::strcmp, std::memcpy, std::forward)
- Implementing lambda functions
  - Using lambdas in class initializer as a wrapper for an actual callback
- Initializer lists
- Callbacks

My questions:
- what is std::move for? How should it be used?

TUI ncurses demo
