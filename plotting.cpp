#include <iostream>
#include <cstdlib>
#include <stdexcept>
#include <string>

void plotting (std::string name) {
    std::cout << "Running python code: " << std::endl;
    std::string command{
        ".venv\\Scripts\\python.exe plotting.py \"" + name + "\""
    };
    int result = system(command.c_str());

    if (result == 0) {
        std::cout << "Succefully ran plotting and saved gif" << std::endl;
    }
    else {
        throw std::runtime_error("Error running python programme");
    }
}