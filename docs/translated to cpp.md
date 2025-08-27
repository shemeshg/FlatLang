cpp converted

```
#include <span>

void myRealTimeLoop(std::span<int, 4> hw_gpio_in,
	std::span<int, 4>  gpio_out,
int& clockTick) {
    // Implementation goes here
}

````



```
using Predicate = std::function<bool()>;
std::unordered_map<std::string, Predicate> conditions;

conditions["is_system_start"] = [&clockTick]() { return clockTick == 0; };
conditions["toggle_triggered"] = [&hw_gpio_in]() { return hw_gpio_in[0] == 1; };

// Usage
if (conditions["is_system_start"]()) {
    reset_all_gpios();
}

```

```
auto is_system_start = [&clockTick]() -> bool {
    return clockTick == 0;
};
```
`

```
[
  {
	"name": "gpio_in",
    "type": "external",    
    "datatype": "int[]",
    "size": 4,
    "source": "hw_gpio_in"
  },
  {
	"name": "toggle_start_stop",
    "type": "alias",    
    "datatype": "int",
    "target": "gpio_in",
	"targetDatatype": "int[]",
	"targetIdx": 0
  },
  {
	"name": "gpio_out",
    "type": "external",    
    "datatype": "int[]",
    "size": 4,
  },
  {
	"name": "tick_counter",
    "type": "external",    
    "datatype": "int",
  },
  {
	"name": "is_system_start",
    "type": "compare",    
    "param1": "tick_counter",
    "param2": "==",
    "param3": "0"
  }
]


````

```
[
  {
    "name": "voltage_select",
    "type": "mod",
    "param1": "tick_counter",
    "param2": 3
  },
  {
    "name": "reset_all_gpios",
    "type": "function",
    "body": [
      {
        "name": "gpio_out",
        "type": "set_all",
        "value": 0
      },
      {
        "name": "gpio_in",
        "type": "set_all",
        "value": 0
      },
      {
        "name": "is_running",
        "type": "const",
        "value": 0
      }
    ]
  }
]

```

```
void reset_all_gpios(std::span<int, 4> gpio_out, std::span<int, 4> gpio_in, bool& is_running) {
    for (int& v : gpio_out) v = 0;
    for (int& v : gpio_in) v = 0;
    is_running = false;
}


void myRealTimeLoop(std::span<int, 4> hw_gpio_in,
                    std::span<int, 4> gpio_out,
                    int& clockTick) {
    int toggle_start_stop = hw_gpio_in[0];

    bool is_system_start = (clockTick == 0);

    if (is_system_start) {
        gpio_out[0] = 1; 
    } else {
        gpio_out[0] = 0; 
    }
    
    if (toggle_start_stop) {
        gpio_out[1] ^= 1; 
    }

	int voltage_select = clockTick % 3;
}

```


runtime registry
```
std::unordered_map<std::string, std::function<int()>> runtime_nodes;

```
