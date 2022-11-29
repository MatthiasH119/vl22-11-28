#include <iostream>
#include <CLI/CLI.hpp>

int main (int argc, char** argv){
    CLI::App app{"1","2"};
    try{
        app.parse(argc, argv);
    } catch(const CLI::ParseError& e){
        return app.exit(e);
    }
    std::cout << "Hello" << std::endl;
}