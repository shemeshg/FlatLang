Node Graph for Timed GPIO Cycling

# Basic example
```
# External hardware bindings
gpio_in: external int[4] hw_gpio_in
gpio_out: external int[4] hw_gpio_out
tick_counter: external int clock

# System startup detection
is_system_start: compare tick_counter == 0
.: call_if is_system_start reset_all_gpios

# Function to reset GPIOs at startup
function reset_all_gpios:
  gpio_in: const 0
  gpio_out: const 0

# Voltage selector cycles through 0, 1, 2 based on tick_counter
voltage_select: mod tick_counter 3
.: call set_led_light_voltage

# Function to set LED voltage based on selector
function set_led_light_voltage:
  is_0v: compare voltage_select == 0
  is_1v: compare voltage_select == 1
  is_2v: compare voltage_select == 2

  gpio_out[0]: call_if is_0v const 0
  gpio_out[0]: call_if is_1v const 1
  gpio_out[0]: call_if is_2v const 2

```

## Improvements
Match
```
gpio_out[0]: match voltage_select {
  0 -> const 0
  1 -> const 1
  2 -> const 2
}

```

## Step 2
```
# library function
function not $x:
  is_zero: compare $x == 0
  .: call_if is_zero const 1
  .: call_if (not is_zero) const 0


# External hardware bindings
gpio_in: external int[4] hw_gpio_in
toggle_start_stop: alias gpio_in[0]
gpio_out: external int[4] hw_gpio_out
tick_counter: external int clock

# Function to reset GPIOs at startup
function reset_all_gpios:
  gpio_in: const 0
  gpio_out: const 0
  is_running: const 0  # not running

# System startup detection
is_system_start: compare tick_counter == 0
.: call_if is_system_start reset_all_gpios

# Toggle running state based on input
.: call toggle toggle_start_stop is_running

function toggle $prm_trigger $prm_signal:
  toggle_triggered: compare $prm_trigger == 1
  $prm_signal: call_if toggle_triggered (not prm_signal)

# If running, set LED voltage
.: call_if is_running set_led_light_voltage

# Function to set LED voltage based on selector
function set_led_light_voltage:
  # Voltage selector cycles through 0, 1, 2 based on tick_counter
  voltage_select: mod tick_counter 3
  is_0v: compare voltage_select == 0 
  is_1v: compare voltage_select == 1
  is_2v: compare voltage_select == 2

  gpio_out[0]: call_if is_0v const 0
  gpio_out[0]: call_if is_1v const 1
  gpio_out[0]: call_if is_2v const 2

````

```
function toggle:
  input: alias $
  is_zero: compare input == 0
  is_one: compare input == 1

  input: call_if is_zero const 1
  input: call_if is_one const 0

````