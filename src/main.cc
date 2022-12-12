#include <iostream>
#include <CLI/CLI.hpp>
#include <nlohmann/json.hpp>

int main (int argc, char** argv){

    std::cout << "Hello" << std::endl;

    CLI::App app{"Dies ist ein Programm, mit dem der Umgang mit CMake, CLI11 und der nlohmann/json lib getestet werden soll","Testprogramm"};

    std::string filepath;
    app.add_option("-r,--read", filepath, "Path to config file")
        ->required()
        ->check(CLI::ExistingFile);

    try{
        app.parse(argc, argv);
    } catch(const CLI::ParseError& e){
        return app.exit(e);
    }

    std::ifstream file{filepath};
    if(!file.is_open()){
        std::cout << "Error opening File!" << std::endl;
        exit(0);
    }
    nlohmann::json FileToJson;

    file >> FileToJson;

    std::cout << FileToJson.dump() << "\n";

    /*
    nlohmann::json database_object;
    try
    {
        database_object = nlohmann::json::parse(file);
    }
    catch (nlohmann::json::parse_error& ex)
    {
        std::cerr << "parse error at byte" << ex.byte << std::endl;
    }

    for (auto& element : database_object["Regale"]){
        std::cout << "Anzahl Lagerplätze" << element["Anzahl Lagerplätze"] << std::endl;
    }
    
    */
    return 0;   
}