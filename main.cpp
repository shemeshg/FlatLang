#include <iostream>
#include <vector>
#include <FlatLangConfig.h>
#include "MyRealTimeLoop.h"

int main(int, char **)
{
    FlatLangConfig flatLangConfig;
    ExternalHwBindingIn gpio_in("gpio_in","int",4,  true);
    flatLangConfig.externalHwBindings.push_back(gpio_in);

    ExternalHwBindingOut gpio_out("gpio_out","int",4,  false);
    flatLangConfig.externalHwBindings.push_back(gpio_out);

    ExternalHwBindingIn tick_counter("tick_counter","int",1,  true);
    flatLangConfig.externalHwBindings.push_back(tick_counter);

    // flatLangConfig.getFixedValue("cTrue", "bool", "true") => TagOut
    // it is
    //     TagOut getTagAt(int idx){
    //return TagOut( signalPorts.at(0).tag );
    //}
    auto cTrue = FixedValue("cTrue", "bool", "true");
    auto cFalse = FixedValue("cFalse", "bool", "false");
    flatLangConfig.semanticNodes.push_back(&cTrue);
    flatLangConfig.semanticNodes.push_back(&cFalse);
    
    
    SemanticGroupIn usedInputes("usedInputs");

    SemanticGroupItemIn i0(&tick_counter);
    SemanticGroupItemIn i1(&gpio_in);
    i1.fromIdx =0;
    i1.toIdx = 2;
    usedInputes.addSemanticNode(i0);
    usedInputes.addSemanticNode(i1);
    flatLangConfig.semanticGroups.emplace_back(usedInputes);
    
    const TagOut result = gpio_out.getTagAt(0);
    const TagIn val1(usedInputes.tagAt(0));
    const TagIn val2(usedInputes.tagAt(1));

   auto thisIsAnd = std::make_unique<LogicalGateAnd>(result,
                            val1,
                            val2);
    /*
    auto thisIsAnd2 = std::make_unique<LogicalGateAnd>(gpio_out.signalPorts.at(1).tag, 
                            gpio_in.signalPorts.at(1).tag, 
                            gpio_in.signalPorts.at(2).tag);
    flatLangConfig.semanticNodes.push_back(thisIsAnd2.get());
    */
    flatLangConfig.semanticNodes.push_back(thisIsAnd.get());



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
