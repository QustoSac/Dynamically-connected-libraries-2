#include <iostream>

extern "C" void TestHello(void);

int main() {
    std::cout << "Calling TestHello from shared library..." << std::endl;
    
    TestHello();
    
    return 0;
}
