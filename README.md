# Sample to automation machine
## Project for automation of a machine to control relays, and motors showing the whole information in a display 7'
The project idea is to provide basic information on how to work with the GIT tool to create submodules and also handle C++ code in an Embedded environment.

#### We have three modules being:
```text
    1) electro-util: common component for all modules
    2) electro-board: component to handle the whole board, divided into:
      2.1) Hardware: motors, relay, sensors, and timers
      2.2) Interface: serial (i2c, spi, 1wire and UART)
      2.3) System: module to provide access to /dev/* providing low-level connection between the application and the OS Linux.
    3) electro-display: module to stabilize the communication with display touch GUI to control equipment management. This module is split into two parts:
        3.1) C part code: server service to connect to display touchscreen (GUI)
        3.2) python part code: client service to handle the communication protocol and also build the GUI structure (TKINTER framework).
```
#### Project workspace:
```bash
    .
    └── electro_horse
        ├── build.sh
        ├── CMakeLists.txt
        ├── eletro-app
        ├── eletro-board
        ├── eletro-display
        ├── eletro-util
        ├── script
        └── tags
```
