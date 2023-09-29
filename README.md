# DER 2023 ECU Firmware Version 1.0

Designed and writen by Cole Bardin (cab572)

Updated: 9/23/2023

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
