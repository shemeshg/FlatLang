#include <iostream>

#include <FlatLangConfig.h>


int main(int, char **)
{
    FlatLangConfig flatLangConfig;
    ExternalHwBinding ehb;
    ehb.tag = "gpio_in";
    ehb.datatype = "int";
    ehb.dataLen = 4;
    ehb.isConst = true;
    flatLangConfig.externalHwBindings.push_back(ehb);
    ehb.tag = "gpio_out";
    ehb.isConst = false;
    flatLangConfig.externalHwBindings.push_back(ehb);
    ehb.tag = "tick_counter";
    ehb.isConst = true;
    ehb.dataLen = 1;
    flatLangConfig.externalHwBindings.push_back(ehb);

    std::cout<<flatLangConfig.getConfig();
     /*
    assume:
    # External hardware bindings
    gpio_in: external int[4] hw_gpio_in
    gpio_out: external int[4] hw_gpio_out
    tick_counter: external int clock

    toggle_start_stop: alias gpio_in[0]
    */
}
