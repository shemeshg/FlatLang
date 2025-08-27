#include <iostream>
#include <nlohmann/json.hpp>
#include <inja.hpp>
using json = nlohmann::json;

int main(int, char**){

    /*
    assume:
    # External hardware bindings
    gpio_in: external int[4] hw_gpio_in    
    gpio_out: external int[4] hw_gpio_out
    tick_counter: external int clock

    toggle_start_stop: alias gpio_in[0]
    */

    nlohmann::json externalParams = nlohmann::json::array({
        {
            {"name", "gpio_in"},
            {"datatype", "std::span<int,4>"},
        },
        {
            {"name", "gpio_out"},
            {"datatype", "std::span<int,4>"},
        },
        {
            {"name", "clockTick"},
            {"datatype", "int&"},
        }
    });



    std::string t = R"(
    #include <span>

    void myRealTimeLoop(
    {% for var in params %}   
     {{ var.datatype }} {{ var.name }}{% if not loop.is_last %},{% endif %}    
    {% endfor %}
    ) {
        {% include "impl" %}
    }
    )";

    inja::Environment env;
    inja::Template implTemplate = env.parse("    // Implementation goes here");
    env.include_template("impl", implTemplate);


nlohmann::json data;
data["params"] = externalParams;

    
    std::cout << env.render(t, data);
}
