#include <iostream>

#include <FlatLangConfig.h>


int main(int, char **)
{
    FlatLangConfig flatLangConfig;
    ExternalHwBinding gpio_in;
    gpio_in.tag = "gpio_in";
    gpio_in.datatype = "int";
    gpio_in.dataLen = 4;
    gpio_in.isConst = true;

    ExternalHwBinding gpio_out;
    flatLangConfig.externalHwBindings.push_back(gpio_out);
    gpio_out.tag = "gpio_out";
    gpio_in.datatype = "int";
    gpio_in.dataLen = 4;    
    gpio_out.isConst = false;

    ExternalHwBinding tick_counter;
    flatLangConfig.externalHwBindings.push_back(tick_counter);
    tick_counter.tag = "tick_counter";
    tick_counter.isConst = true;
    tick_counter.dataLen = 1;
    flatLangConfig.externalHwBindings.push_back(tick_counter);

    std::cout<<flatLangConfig.getConfig();

    SemanticGroup usedInputes;
    SemanticGroupItem i0(&tick_counter);
    SemanticGroupItem i1(&gpio_in);
    i1.fromIdx =0;
    i1.toIdx = 2;
    usedInputes.semanticGroups.emplace_back(i0);
    usedInputes.semanticGroups.emplace_back(i1);


     /*
    assume:
    # External hardware bindings
    gpio_in: external int[4] hw_gpio_in
    gpio_out: external int[4] hw_gpio_out
    tick_counter: external int clock

    toggle_start_stop: alias gpio_in[0]
    */
}
