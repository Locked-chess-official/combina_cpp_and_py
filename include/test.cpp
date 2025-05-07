#include "combine.h"
#include <iostream>

int main() {
    std::vector<std::pair<std::string, std::string>> cpp_filetypes = {
        {"C++ files", "*.c;*.cpp;*.h;*.hpp"},
        {"All files", "*.*"}
    };

    std::vector<std::pair<std::string, std::string>> py_filetypes = {
        {"Python files", "*.py;*.pyw;*.pyi"},
        {"All files", "*.*"}
    };

    std::vector<std::pair<std::string, std::string>> save_filetypes = {
        {"Python files", "*.py"},
        {"Python source files", "*.pyi"},
        {"Python file (no console)", "*.pyw"},
        {"C files", "*.c"},
        {"C++ files", "*.cpp"},                   
        {"C header files", "*.h"},
        {"C++ header files", "*.hpp"},
        {"All files", "*.*"}
   };

    std::cout << "Choose c file" << std::endl;
    std::string cpp_path = select_file("Choose c file", cpp_filetypes);
    if (cpp_path.empty()) {
        std::cerr << "No c file." << std::endl;
        return 1;
    }

    std::cout << "Choose python file" << std::endl;
    std::string py_path = select_file("Choose py file", py_filetypes);
    if (py_path.empty()) {
        std::cerr << "No python file." << std::endl;
        return 1;
    }

    std::string cpp_code = read_file(cpp_path);
    std::string py_code = read_file(py_path);
 
    if (cpp_code.empty() || py_code.empty()) {
        std::cerr << "Fail to read." << std::endl;
        return 1;
    }

    char choice;
    std::cout << "Use double?(Y/n): ";
    std::cin >> choice;
    bool use_double = (choice == 'Y' || choice == 'y');
 
    std::string combined_code = combine_cpp_and_py(cpp_code, py_code, use_double);
 
    std::cout << "Choose a path to save..." << std::endl;
    std::string save_path = save_file_dialog(save_filetypes);
    if (save_path.empty()) {
        std::cerr << "No saving path." << std::endl;
        return 1;
    }

    if (save_file(save_path, combined_code)) {
        std::cout << "Success to save the file: " << save_path << std::endl;
    } else {
        std::cerr << "Failure to save." << std::endl;
        return 1;
    }
        
    return 0;
}
