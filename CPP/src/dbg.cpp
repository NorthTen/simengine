#include <string>
#include <iostream>
#include <tuple>
#include "simengine.hpp"
int main() {
    std::string fp = "cube.obj";
    std::cout << "is it just this one function";
    std::tuple<bool,Simengine::Mesh> mesh = Simengine::Dataloaders::loadobj(fp);
    return 0;
}
