# Network Packet Simulation  

## Overview  
This project is a **network packet simulation program** written in C++. It models basic networking devices such as **PCs, Switches, and Routers** and simulates packet transmission between them.  

The program reads network device configurations from a file (`devices.txt`), allows the user to specify a **source and destination device**, and then traces the **path** the packet takes through the network.  

## Features  
- Object-oriented design using **inheritance and polymorphism**.  
- Supports **PCs, Switches, and Routers** as network devices.  
- Reads **device details from a file** (`devices.txt`).  
- Uses **dynamic memory allocation** for managing devices.  
- **Simulates packet transfer** between network nodes.  
- Displays the **path** of the packet as it moves through the network.  

## How It Works  
1. The program reads device data from a file (`devices.txt`).  
2. The user is prompted to enter a **source device** and a **destination device**.  
3. The program searches for the specified devices in the network.  
4. If both devices exist, it simulates packet transfer from **source to destination**, printing each step of the journey.  
5. The dynamically allocated memory is freed before exiting.  

## File Format (`devices.txt`)  
The file should list devices in the following format:  

```
PC PC1 192.168.1.2 AA:BB:CC:DD:EE:01  
PC PC2 192.168.1.3 AA:BB:CC:DD:EE:02  
Switch SW1 AA:BB:CC:DD:EE:03  
Router R1 AA:BB:CC:DD:EE:04 192.168.1.1 192.168.2.1  
```

- **PC:** `PC <Name> <IP Address> <MAC Address>`  
- **Switch:** `Switch <Name> <MAC Address>`  
- **Router:** `Router <Name> <MAC Address> <Interface IP1> <Interface IP2>`  

## Example Run  

### Input  
```
Source (e.g., PC1): PC1  
Destination (e.g., PC2): PC2  
```

### Output  
```
PC1 - IP: 192.168.1.2, MAC: AA:BB:CC:DD:EE:01  
Leaving PC1 > Arrived at Switch SW1 > Leaving Switch SW1 > Arrived at PC2 >  
```

## Dependencies  
- C++ compiler (`g++`, `clang++`, etc.)  

## Compilation & Execution  
### Compile:  
```sh
g++ -o network_simulator network_simulator.cpp
```  

### Run:  
```sh
./network_simulator
```  

## Future Improvements  
- Implement **dynamic MAC address learning** in switches.  
- Extend support for **multiple network paths** and routing algorithms.  
- Add a **GUI or visualization** for better understanding.  

## License  
This project is open-source and available under the **MIT License**.
