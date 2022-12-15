#include <iostream>
#include <CLI/CLI.hpp>
#include <nlohmann/json.hpp>

int main (int argc, char** argv){

    std::cout << "Hello" << std::endl;
    CLI::App app{"Dies ist ein Programm, mit dem der Umgang mit CMake, CLI11 und der nlohmann/json lib getestet werden soll","Testprogramm"};

/*  
    #   Einführung der option r (read), eingabe wird als string in 'filepath' geschrieben
    #   "->required" wird als erste Flag bei dieser Notation immer benötigt; wird beim Programmaufruf nicht -r <filepath> eingegeben, gibt das Programm einen entsprechenden Fehler aus.
    #   "->check(...)" überprüft, ob das File existiert
*/
    std::string filepath;
    app.add_option("-r,--read", filepath, "Path to config file")
        ->required()
        ->check(CLI::ExistingFile);

/*  
    #########################################################################################################################################
    #   Simple Ein-/Ausgabe mit CLI11

    std::string operation="+";
    int zahl_a=0, zahl_b=0;

    app.add_option("-a,--zahl_a", zahl_a, "Eingabe Zahl: a (int: 0)");
    app.add_option("-b,--zahl_b", zahl_b, "Eingabe Zahl: a (int: 0)");
    app.add_option("-o,--operation", operation, "Eingabe: Rechenoperation (int: +)");

    #########################################################################################################################################
*/
  
//  #   mit der try-catch Strategie wird hier die argc/argv Mechanik ausgeführt. Ohne diese stehen die "app.add_option" zeilen ohne Funktion im Programm
    try{
        app.parse(argc, argv);
    } catch(const CLI::ParseError& e){
        return app.exit(e);
    }

//  #   Hier wird das File geöffnet und anschließend überprüft, ob es richtig geöffnet ist. Wenn nicht, wird das Programm mit dem exit Wert 0 beendet.
    std::ifstream file{filepath};
    if(!file.is_open()){
        std::cout << "Error opening File!" << std::endl;
        exit(0);
    }

/*  
    #########################################################################################################################################
    #   Simple Ein-/Ausgabe mit CLI11

    if(operation=="+"){
        std::cout << zahl_a << " " << operation << " " << zahl_b << " = " << zahl_a + zahl_b << std::endl;
    }
    else if(operation=="x"){
        std::cout << zahl_a << " " << operation << " " << zahl_b << " = " << zahl_a * zahl_b << std::endl;
    }
    else{
        std::cout << "incorrect Input !" << std::endl;
    }
    #########################################################################################################################################
*/
/*
    #########################################################################################################################################
    #   Hier wird aus dem nlohmann namespace 'FileToJson' als json initialisiert. 'json' ist dabei der Datentyp.
    #   Anschließend wird das geöffnete File in diesen instantiierten Datentyp hineingeschoben.
    #   Danach wird die Variable 'FileToJson' mit der dump() Funktion ausgegeben.

    nlohmann::json FileToJson;

    file >> FileToJson;

    std::cout << FileToJson.dump() << "\n";
    #########################################################################################################################################
*/
    
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

    std::cout << "\033[1;31mDEBUG\033[0m"   << std::endl;
    std::cout << database_object.dump()     << std::endl;
    std::cout << "\033[1;31mDEBUG\033[0m"   << std::endl;



    


    
    return 0;   
}