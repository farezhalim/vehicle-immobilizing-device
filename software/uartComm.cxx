/*
* uartComm.cxx
* 
* Copyright 2019  <pi@raspberrypi>
* 
* This program is free software; you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation; either version 2 of the License, or
* (at your option) any later version.
* 
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
* 
* You should have received a copy of the GNU General Public License
* along with this program; if not, write to the Free Software
* Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
* MA 02110-1301, USA.
* 
* 
*/

#include <iostream>
#include <vector>
#include <stdio.h>
#include <string>
#include <wiringPi.h>
#include <wiringSerial.h>
#include <unistd.h>
#include <fcntl.h>

char speed[2];

void speedCheckQuery(int m_port){
	//CAN Packet to Query OBDII port for Current Vehicle Speed
	serialPutchar(m_port, '0');
	serialPutchar(m_port, '1');
	serialPutchar(m_port, '0');
	serialPutchar(m_port, 'd');
	serialPutchar(m_port, '\r');
}

void immobilizeQuery(int m_port){	
	//CAN Packet to Send OBDII port for Immobilization(Brake, Transmission, etc)	
	serialPutchar(m_port, '0');
	serialPutchar(m_port, '1');
	serialPutchar(m_port, '4');
	serialPutchar(m_port, 'b');
	serialPutchar(m_port, '\r');
}

void disableQuery(int m_port){
	//CAN Packet to Send OBDII port for Disabling(Stop Immobilization)	
	serialPutchar(m_port, '0');
	serialPutchar(m_port, '1');
	serialPutchar(m_port, 'c');
	serialPutchar(m_port, 'c');
	serialPutchar(m_port, '\r');
}

std::vector<char> getVehicleSpeed(int m_port){
	std::cout << "get Speed: " << std::endl;
	speedCheckQuery(m_port); //Query OBDII Port

	int numByte = serialDataAvail(m_port);
	std::vector<char> m_read; //Storage of packet recieved
	int twoCheck = 0;

	while(numByte){
		std::cout << "I have bytes: "<< numByte << std::endl;
		for(int i = 0; i < numByte;i++){
			char ascii = (char)(serialGetchar(m_port));
			m_read.push_back(ascii);
			std::cout << "I read from serial: "<< ascii << std::endl;
			
			if(ascii == '/r'){
				twoCheck++;
				std::cout << "Done reading." << std::endl;
				return m_read;
			}			
		}
		serialFlush(m_port);	
	}	
	m_read.empty();
	return m_read;
}

bool readCorrectPacket(std::vector<char> goodVector, std::vector<char> vectorToCheck){
	bool match = false;

	if(goodVector.size() == vectorToCheck.size()){
		for(int i = 0; i < vectorToCheck.size(); i++){
			if((i != (6 | 7)) && (goodVector.at(i) == vectorToCheck.at(i))){
				match = true;
			}
			else if(match && (i == (6 | 7))){
				speed[0] = vectorToCheck.at(6);
				speed[1] = vectorToCheck.at(7);
			}
			else{
				match = false;
			}
		}
	}

}

int main(int argc, char** argvv){
	int serial_port;

	if(wiringPiSetup() < 0){
		std::cout << "wiringPi Setup failed"<< std::endl;
		return 1;
	}

	if((serial_port = serialOpen("/dev/ttyS0",9600)) < 0){
		std::cout << "serial device not open "<< std::endl;
		return 1;
	}
	
	while(true){
		//Check for Vehicle Speed
		std::vector<char> m_currentVehicleSpeed = getVehicleSpeed(serial_port);

		std::vector<char> goodVector = {'4','1',' ','0','D',' ','0','0',' ','E','0','/r','/r'};
		bool vehicleSpeedReturn = readCorrectPacket(goodVector, m_currentVehicleSpeed);
	
		m_currentVehicleSpeed.clear();

		if(vehicleSpeedReturn && (speed[0] == '0') && ((speed[1] - '0') < 5)){
			immobilizeQuery(serial_port); //Write Immobilized via ZMQ
		}
		
		usleep(500);
	}
	
	serialClose(serial_port);
	return 0;
}




