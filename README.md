# Vehicle Immobilizing Device
*ECE Capstone 2018-2019 Group 7*

The vehicle immobilization device monitors a vehicle's speed and acceleration through a combination of OBD-II queries and a digital accelerometer, and upon detection of a collision, the device immobilizes the vehicle by injecting CAN packets to ECUs in the vehicle. To disable the immobilization, an override is sent through Bluetooth using an Android app to the device to halt CAN message injection.

There are three main programs associated with the objectives as listed above:
1. detection.py - This is a python program that interfaces with the Digital Mems Accelerometer using I2C. Upon change in state, this program control's the status LED's as well as state transistions using Inter-Process Communication via a TCP/IP socket using the ZMQ library.
2. uartComm.cxx - A C++ program that interfaces with the UART to OBD-II circuitry (STN1110 Chip using ELM Command Set). Deals with immobilization, checking of speed, and disabling action. State transistions using ZMQ library. 
3. bluetooth_mgr.py - Python program that triggers linux services to interface with bluetooth and bluetooth file transfer on the Raspberry Pi. Further deals wih parsing of recieved file using /bluetooth/good.txt as the password file that is to be checked against. Also, triggers a bash script (bluetooth__ctl_mgr.sh) to interface with standard bluetooth stack of Linux to set power and discoverable. State transistions using ZMQ Library.

All three programs are run as one systemd service on the Raspberry Pi during boot:
- The service file is to be located in /etc/systemd/system/. The service name is mainController.service
- All systemd functions can be performed including checking the status, turning the service on/off, etc.
- The service file runs a bash script named mainController.sh located within /usr/bin. This bash script acts as a controller/manager of the aforementioned programs.

The following installations need to be done on the Raspberry Pi in the following order:
1. sudo apt-get install libtool pkg-config build-essential autoconf automake smbus adxl expect picap obexpushd bluez-tools python-dev
2. Libsodium for ZMQ purposes
        `wget https://github.com/jedisct1/libsodium/releases/download/1.0.3/libsodium-1.0.3.tar.gz`
`wget https://github.com/jedisct1/libsodium/releases/download/1.0.3/libsodium-1.0.3.tar.gz`
`wget https://github.com/jedisct1/libsodium/releases/download/1.0.3/libsodium-1.0.3.tar.gz`
`wget https://github.com/jedisct1/libsodium/releases/download/1.0.3/libsodium-1.0.3.tar.gz`
        tar -zxvf libsodium-1.0.3.tar.gz
        cd libsodium-1.0.3/
        ./configure
        make
        sudo make install`
3. ZMQ installation
        `wget http://download.zeromq.org/zeromq-4.1.3.tar.gz
        tar -zxvf zeromq-4.1.3.tar.gz
        cd zeromq-4.1.3/
        ./configure
        make
        sudo make install
        sudo ldconfig`
4. sudo pip install pyzmq
5. C++ headers for ZMQ installation:
        `cd /usr/include/
        sudo wget https://raw.githubusercontent.com/zeromq/cppzmq/master/zmq.hpp`
