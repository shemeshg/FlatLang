#include <iostream>
#include <vector>
#include <FlatLangConfig.h>
#include "MyRealTimeLoop.h"

int main(int, char **)
{
    FlatLangConfig flatLangConfig;
    auto gpio_in = flatLangConfig.addExternalHwBindingIn("gpio_in","int",4,  true);
    auto gpio_out = flatLangConfig.addExternalHwBindingOut("gpio_out","int",4,  false);
    auto tick_counter = flatLangConfig.addExternalHwBindingIn("tick_counter","int",1,  true);

    auto cTrue = flatLangConfig.addFixedValue("cTrue", "bool", "true");
    auto cFalse = flatLangConfig.addFixedValue("cFalse", "bool", "false");

        
    auto usedInputes = flatLangConfig.addSemanticGroupIn ("usedInputs");
    usedInputes->addSemanticGroupItemIn(tick_counter);
    usedInputes->addSemanticGroupItemIn(gpio_in,0,2);

    
    //TODO Here, isUsed, if not set to true,
    //TODO If true, throw exception
    //TODO getTagAt, should always return the same TagOut
    const TagOut result = gpio_out->getTagAt(0);
    //BUG THIS SHOULD RETURN TagIn using getTagAt
    const TagIn val1 = usedInputes->getTagAt(0);
    const TagIn val2 = usedInputes->getTagAt(1);

    flatLangConfig.addLogicalGate<LogicalGateAnd>(result,
                            val1,
                            val2);

    //ERROR result can not be assigned twice !!!!!!!!!!
    //TODO Can I make any TagOutSemanticGroup and TagInSemanticGroup
    flatLangConfig.addLogicalGate<LogicalGateAnd>(result,
                                                      cTrue->getTag(),
                                                      cFalse->getTag());




    std::cout<<flatLangConfig.getConfig();

    //gpio_in.signalPorts[1].aliases= std::vector<std::string>{"aa","bb"};
    //gpio_in.printAllAliases();
    //usedInputes.printAllAliases();
    

    std::vector<int> ins{4};
    std::vector<int> outs{4}; 
    int tick=0;
    myRealTimeLoop(std::span<const int, 4>(ins.data(), 4),
                 std::span< int, 4>(outs.data(), 4), 
                 tick);

    const int v_false = false;
    const int v_true = true;
     /*
    assume:
    # External hardware bindings
    gpio_in: external int[4] hw_gpio_in
    gpio_out: external int[4] hw_gpio_out
    tick_counter: external int clock

    toggle_start_stop: alias gpio_in[0]
    */
}
