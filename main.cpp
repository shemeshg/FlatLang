#include <iostream>
#include <nlohmann/json.hpp>
#include <inja.hpp>
using json = nlohmann::json;

int main(int, char**){
    std::cout << "Hello, from FlatLang!\n";

    json ex1 = json::parse(R"(
    {
        "pi": 3.141,
        "happy": true
    }
    )");
    
    std::cout << inja::render("Hello {{ pi }} \n!", ex1);
}
