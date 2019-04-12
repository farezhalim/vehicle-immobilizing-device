# Vehicle Immobilizing Device

## ECE Capstone 2018-2019 Group 7

The vehicle immobilization device monitors a vehicle's speed and acceleration through a combination of OBD-II queries and a digital accelerometer, and upon detection of a collision, the device immobilizes the vehicle by injecting CAN packets to ECUs in the vehicle. To disable the immobilization, an override is sent through Bluetooth using an Android app to the device to halt CAN message injection