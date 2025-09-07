#include <iostream>
#include <vector>
#include <FlatLangConfig.h>
#include "MyRealTimeLoop.h"

int main(int, char **)
{
    FlatLangConfig flatLangConfig;
    ExternalHwBinding gpio_in("gpio_in","int",4,  true);
    flatLangConfig.externalHwBindings.push_back(gpio_in);

    ExternalHwBinding gpio_out("gpio_out","int",4,  false);    
    flatLangConfig.externalHwBindings.push_back(gpio_out);

    ExternalHwBinding tick_counter("tick_counter","int",1,  true);
    flatLangConfig.externalHwBindings.push_back(tick_counter);

    auto cTrue = std::make_unique<FixedValue>("cTrue", "bool", "true");
    auto cFalse = std::make_unique<FixedValue>("cFalse", "bool", "false");
    flatLangConfig.semanticNodes.push_back(cTrue.get());
    flatLangConfig.semanticNodes.push_back(cFalse.get());
    
    
    SemanticGroup usedInputes;
    usedInputes.tag = "usedInputs";
    SemanticGroupItem i0(&tick_counter);
    SemanticGroupItem i1(&gpio_in);
    i1.fromIdx =0;
    i1.toIdx = 2;
    usedInputes.semanticGroups.emplace_back(i0);
    usedInputes.semanticGroups.emplace_back(i1);
    flatLangConfig.semanticGroups.emplace_back(usedInputes);
    
   auto thisIsAnd = std::make_unique<LogicalGateAnd>(gpio_out.signalPorts.at(0).tag, 
                            usedInputes.tagAt(0), 
                            gpio_in.signalPorts.at(1).tag);   
    auto thisIsAnd2 = std::make_unique<LogicalGateAnd>(gpio_out.signalPorts.at(1).tag, 
                            gpio_in.signalPorts.at(1).tag, 
                            gpio_in.signalPorts.at(2).tag);    
    flatLangConfig.semanticNodes.push_back(thisIsAnd.get());
    flatLangConfig.semanticNodes.push_back(thisIsAnd2.get());


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
