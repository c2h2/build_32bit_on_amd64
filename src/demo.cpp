#include <iostream>
#include <vector>
#include <memory>
#include <string>

class Demo {
private:
    std::string name;
    int value;
    
public:
    Demo(const std::string& n, int v) : name(n), value(v) {}
    
    void display() const {
        std::cout << "Name: " << name << ", Value: " << value << std::endl;
    }
    
    int getValue() const { return value; }
};

int main() {
    std::cout << "C++ Cross-compilation Demo" << std::endl;
    std::cout << "Size of long: " << sizeof(long) << " bytes" << std::endl;
    std::cout << "Size of pointer: " << sizeof(void*) << " bytes" << std::endl;
    std::cout << "Size of int: " << sizeof(int) << " bytes" << std::endl;
    
    std::vector<std::unique_ptr<Demo>> demos;
    demos.push_back(std::make_unique<Demo>("Test1", 42));
    demos.push_back(std::make_unique<Demo>("Test2", 100));
    
    std::cout << "\nDemo objects:" << std::endl;
    for (const auto& demo : demos) {
        demo->display();
    }
    
    return 0;
}