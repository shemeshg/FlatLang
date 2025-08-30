#include <span>

void myRealTimeLoop(std::span<const int, 4> gpio_in, 
    std::span<int, 4> gpio_out, 
    const int &tick_counter)
{
    std::vector<std::reference_wrapper<const int>> _usedInputs{};
    _usedInputs.push_back(std::ref(tick_counter));
    _usedInputs.push_back(std::ref(gpio_in[0]));
    _usedInputs.push_back(std::ref(gpio_in[1]));
    _usedInputs.push_back(std::ref(gpio_in[2]));
    const std::vector<std::reference_wrapper<const int>> usedInputs = std::move(_usedInputs);
}