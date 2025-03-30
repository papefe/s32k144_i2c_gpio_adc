# S32K144 I2C-GPIO-ADC

This project implements a C application for the NXP S32K144 microcontroller. The application configures the device to act as an I²C peripheral by exposing 1-byte registers that allow:

- **Reading two simple ADC inputs:**  
  Two ADC channels (referenced to GND) are read. The input signals (5–20 V) are conditioned externally (using a voltage divider) to match the ADC’s input range.

- **Reading 8 GPIO pins:**  
  The logical state of 8 GPIO pins (configured as digital inputs) is provided.

- **SPI Configuration Output:**  
  A configuration register is provided to set the polarity and level of the 8 pins. When this register is modified via I²C, the new configuration is sent over SPI to the ISO1H816G, which adjusts the output levels (since the microcontroller itself cannot directly drive the higher voltage required).

Debug output is provided via semihosting.

---

## I²C Registers

The device exposes a set of 1-byte registers accessible over I²C:

- **Register 0 (REG_GPIO):**  
  Contains the current state of the 8 GPIO pins.

- **Register 1 (REG_ADC0):**  
  Contains the ADC conversion result (scaled to 8 bits) from ADC channel 0.

- **Register 2 (REG_ADC1):**  
  Contains the ADC conversion result (scaled to 8 bits) from ADC channel 1.

- **Register 3 (REG_SPICFG):**  
  A configuration register for SPI output. When a new value is written via I²C, the firmware transmits this byte over SPI to configure the ISO1H816G accordingly.

**Protocol:**  
- **Write:** The first byte sent by the master indicates the register index, followed by the data byte to store in that register.  
- **Read:** When the master reads from the slave, the device returns the value stored in the selected register.

---

## Compilation

This project is developed with S32 Design Studio (version 3.4 or compatible) and uses the S32K1xx SDK drivers for ADC, I²C, SPI, and GPIO.

### Requirements

- S32 Design Studio installed.
- S32K1xx SDK (including drivers for ADC, I²C, SPI, and GPIO).

### Compiler/Linker Options

- The project uses semihosting for debug output; ensure that semihosting is enabled in your debug configuration.
- To support floating point in `printf()`, the linker option `-u _printf_float` must be enabled. This can be added in the project properties under the linker settings (e.g., in “Other options”).

### Build Steps

1. Import the project into S32 Design Studio.
2. Verify the include paths and the linker options (especially `-u _printf_float`).
3. Build the project. It should compile without errors or warnings.

---

## Usage

1. **Programming and Debugging:**  
   - Connect your device and use OpenSDA or your appropriate debugger.
   - Run the project in debug mode and observe the semihosting console output.

2. **Device Behavior:**  
   - The microcontroller acts as an I²C peripheral. An I²C master can read registers to get the ADC and GPIO readings.
   - The I²C master can write to the REG_SPICFG register to change the output configuration. The firmware then sends this configuration via SPI to the ISO1H816G.

3. **Register Updates:**  
   - In the main loop, the firmware periodically updates the registers with the latest ADC and GPIO readings.
   - When a change is detected in REG_SPICFG (via an I²C write), the new configuration is transmitted via SPI.

---
