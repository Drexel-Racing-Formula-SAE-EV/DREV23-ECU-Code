# DER 2023 ECU Firmware v0.1.0

Designed and writen by Cole Bardin (cab572)

Updated: 10/8/2023

## Platform

### Microcontroller

Nucleo-F767ZI development board which has an STM32F7 (an ARM Cortex-M7 based microcontroller). The development board is embedded on a custom PCB with other peripherals for the system.

### Environment

The project can be build and flashed using the STM32CubeIDE. It is an Eclipse based IDE with many added features to improve development on STM boards, such as their IOC file type. This IDE also offers good debugging tools.

[IDE Download Link](https://www.st.com/en/development-tools/stm32cubeide.html)

## Firmware

### Architecture

The entire program is embedded with the `app_data` structure found in `app.h`. This encapsulates all variables, structs, driver interfaces, etc for the program. An instance of the `app_data` struct named `app` lives inside the `app.c` file, and a pointer to the `app` struct can be passed to tasks and functions to handle data access.

The `app_data` struct contains highest priority data such as fault flags, throttle and brake percentage, etc. The structure also contains a `board` structure.

The `board` struct contains representations of physical devices on the ECU board such as the STM32F7, potentiometers, CANBus transceiver, etc. These devices are represented with driver structs.

The `stm32f767` struct helps contain the interfaces for the STM HAL. It holds all the handles, mutexes, and other data types used to interface with the MCU hardware.

Structs like the `poten` and `canbus_device` are wrappers around the physical devices on the board. Instances of these structs are stored in the `board` struct for conventient and reliable access.

Each RTOS task receives a pointer to the `app_data` struct instance so that they can parse out the required interfaces and data.

For example, the CANBus task would require access to the `canbus_device` struct instance that was initialized during setup. So it would make sense that the task function declares a local `struct canbus_device` pointer that references the struct instance stored within the shared `app_data` instance.

### File Organization

The base firmware is written in C and uses FreeRTOS middleware. The firmware is in the `DER-ECU-V1` directory. It is a rather standard STM32Cube project.

Within the `Core` subdirectory, the `Inc` and `Src` directories contain the header and source code files respectively. These two directories have identical internal structures.

Inside of both `Inc` and `Src`, lives `board`, `ext_drivers`, and `tasks` subdirectories. Along with `main.c/h`, and `app.c/h` files.

The `board` subdirectory includes the files for the `board` and `stm32f767` structs. 

The `ext_drivers` subdirectory holds the custom driver files for ICs and other devices on the board.

The `tasks` subdirectory contains a file for each task. A task file includes a function to create the task and a function for the task body. The task function should be locally scoped to the source file while the task creation function should be included in the header file.

### Program Entry

The program does not start in `main.c`. Instead the real entry is called from the *Daemon Task Startup Hook*. This hook function is called immediately after the scheduler is started. The hook function can be found in `Core/Src/freertos.c` and is called `vApplicationDaemonTaskStartupHook()`.

The hook function calls `app_create()` located in `app.c`. This function recursively initializes all the nested structures within the `app_data` structure instance and then creates the tasks to be run.

Once `app_create()` is finished, the `vApplicationDaemonTaskStartupHook()` function returns and the scheduler can now schedule the user defined tasks. Control has now been handed over to the OS and the program can execute as intended.

## FreeRTOS Tasks

### APPS Task (Accelerator Pedal Position Sensor)

As defined in the rules, the APPS sytem must read from two electrically isolated sensors to determine the accelerator position. The car uses two linear potentiometers to acoomplish this.

The APPS task reads both of the potentiometers and uses their calibration to calculate their percentages. Then the data is checked for implausibility to comply with secion T.4.2.5 of the rules. In the event of a sustained disagreement between the two sensors, the firmware enters a non-recoverable state. In this error state, the firmware will disable the RFE (Rotating Field Enable) signal to the motor controller, which will allow the motor to free spin, as well as repeatedly sending a 0% torque request to the motor controller. 

If there is no detected error with the APPS data, the task will then populate a CANBus packet with a torque command for the motor controller. The pedal position data is converted to the format specified in the motorcontroller's data sheet. 

Then, the task places the CANBus packet inside a message queue and sends a notification to the CANBus Task, letting it know there is a torque command to send. Lastly, the task delays itself for the appropriate amount of OS ticks such that it operates at the desired frequency.

### BPPC Task (Brake Pedal Plausibility Check)

The BPPC task reads the throttle and brake position data supplied by other tasks. Using thresholds specified by the rules, it determines if the throttle is engaged low (5%) or high (25%). It also determines if the brakes are engaged above a threshold that we consider them "engaged".

If the brakes are engaged and the throttle is above 25%, a BPPC fault has occured. The BPPC fault flag should be set so the ErrorHandle Task can respond appropriately. The BPPC fault is a soft fault, meaning it is recoverable. If there is an active BPPC fault, the throttle must released below 5% to unset the fault.

After handling whether or not to set or unset the BPPC fault flag, the task then delays so that it can run at a desired frequency.

### BSE Task (Brake System Encoder)

The BSE task is very similar to the APPS task. However, it reads the pressure transducers attached to the brake lines instead. The APPS task was given 2 out of 3 of the ADCs on the STM32F7 since accelerator data precision is much more important than the brakes. The BSE task is then left to use the remaining ADC for both sensors, requiring that the ADC channel is changed in between reads.

After acquiring the data, similar safety checks are performed and the average percentage is calculated. The brake light enabling or disabling is then handled for the current state of the brake pedal.

Lastly, the task delays such that it runs at the desired frequency.

### CANBus Task

The CANBus task handles sending and receiving CANBus messages. In this firmware version, it handles sending torque commands to the motor controller and receiving CANBus messages from other node on the network. Later versions of the firmware will have all incomming messages logged to the SD card, but logging has not been finished yet. For now, incomming messages are read but nothing is done with them.

This is an event driven task, meaning it does not delay itself for a predetermined amount of time. Instead, it waits for other tasks to send it a notification that there is something to do.

Upond receiving that notificaiton, it checks where the notificaion value. The task that notifies the CANBus task can set bits in the notificaiton value. For example, the APPS task sets bit 0 and the CANBus receive ISR sets bit 0. The task can check the notificaion value to determine if the CANBus packet in the message queue is a torque command to send to the motor controller or a received message to log.

CANBus packets are placed into a message queue for the CANBus task. Once notified, the task can retreive the packet and act on it accordingly. After processing the CANBus packet, the task awaits another notificaiton.

### Error Task

The Error task reads error flags set by other tasks and sets larger error states. This allows errors of different processes to be handled in specific ways. Currently there are two types of system faults: hard faults and soft faults.

Hard faults are non-recoverable and tasks can change their behavior to maximize safety. In this version of the firmware, the only hard faults are APPS and BSE. If the accelerator or brake pedals cannot be sensed properly, the car should not run. The motor's rotating field is disabled so it cannot be driven and the 0% torque command is sent to the motor controller. In the event of a hard fault, the car will be disabled so the error can be addressed.

Soft faults, on the other hand, are recoverable and do not require that the car be put into a full safety mode. The only soft fault currently defined is the BPPC fault. If both the throttle and brakes are both engaged, this is considered a soft fault and the firmware should stop all non-zero torque commands to the motor controller until the fault is resolved.

### RTD Task (Ready To Drive)

The RTD task checks the three safety criteria (defined in EV9.4.2) before allowing the car to be "started". These criteria include: Tractive System Active, Brakes engaged, and RTD button pressed by driver. If all three of these are met, the task will set the RTD flag, telling the other tasks to start operations, and then the task will delete itself.

### Dev Task

This is a temporary task used to develop and test features before they are fully implemented. It can be used to set values, trigger systems, etc. It will be removed in further versions of the firmware.