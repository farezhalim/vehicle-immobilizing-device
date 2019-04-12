/*
* uartComm.cxx
* This program was developed for the vehilce immobilization devices
* for ECE 491 capstone project, group 7
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
#include <zmq.hpp>
#include <zhelpers.hpp>
#include <thread>

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

std::vector<char> getVehicleSpeed(int m_port){ //READ VEHICLE SPEED FROM SPARKFUN BOARD


	// std::cout << "get Speed: " << std::endl;
	speedCheckQuery(m_port); //Query OBDII Port

	usleep(1000000);

	std::vector<char> m_read; //Storage of packet recieved
	int twoCheck = 0;

	int numByte = serialDataAvail(m_port);

	while(numByte > 0){
		//std::cout << "I have bytes: "<< numByte << std::endl;
		for(int i = 0; i < numByte;i++){ //READ VEHICLE SPEED
			char ascii = (char)(serialGetchar(m_port));
			m_read.push_back(ascii);
			//std::cout << "I read from serial: "<< ascii << std::endl;

			if(ascii == '\r'){ //DETERMINE END OF PACKET
				//std::cout << "I am in two check" << std::endl;
				twoCheck++;
				if(twoCheck == 2){
					//std::cout << "Done reading 1." << std::endl;
					break;
				}
			}
		}
		if(twoCheck == 2){
			// std::cout << "Done reading 2." << std::endl;
			serialFlush(m_port);
			numByte = 0;
			break;
		}
	}
	return m_read;
}

bool readCorrectPacket(std::vector<char> goodVector, std::vector<char> vectorToCheck){ //ENSURE VECHICLE PACKET RETREIVED IS CORRECT
	bool match = false;

	// changed 6 to 11 and 7 to 12
	//std::cout << "goodvector size:" << goodVector.size() << std::endl;
	//std::cout << "compare vector size:" << vectorToCheck.size() << std::endl;
	if(goodVector.size() == vectorToCheck.size()){
		for(int i = 0; i < vectorToCheck.size(); i++){
			// if it is not the speed data and it matches

			//std::cout << "vector to check " << vectorToCheck.at(i) << std::endl;
			//std::cout << "good to check " << goodVector.at(i) << std::endl;
			if((i != (11 | 12)) && (goodVector.at(i) == vectorToCheck.at(i))){
				match = true;
			}
			// if it is the speed data, extract into speed array
			else if(match && (i == (11 | 12))){
				speed[0] = vectorToCheck.at(11);
				speed[1] = vectorToCheck.at(12);
			}
			else{
				match = false;
			}
		}
	}
	return match;

}

void immobilizeCar(int m_port){ //SEND BRAKING PACKET TO SPARKFUN BOARD
	bool vehicleSpeedReturn = false;

	while(!vehicleSpeedReturn){
		//Check for Vehicle Speed
		std::vector<char> m_currentVehicleSpeed = getVehicleSpeed(m_port);
		usleep(2000000);
		//std::cout << "I got speed!" << std::endl;

		std::vector<char> goodVector = {'0','1','0','d',' ','4','1',' ','0','D',' ','0','0',' ','E','0','\r','\r'}; // changed to \r

		//for (std::vector<char>::const_iterator j = m_currentVehicleSpeed.begin(); j != m_currentVehicleSpeed.end(); ++j) {
		//	std::cout << *j << ' ';
		//}

		vehicleSpeedReturn = readCorrectPacket(goodVector, m_currentVehicleSpeed);

		//std::cout << "I compared speed: "<< vehicleSpeedReturn << std::endl;


		if(vehicleSpeedReturn && (speed[0] == '0') && ((speed[1] - '0') < 5)){
			std::cout << "I am trying to immobilize: " << std::endl;

			immobilizeQuery(m_port); //Write Immobilized via ZMQ
		}

		//m_currentVehicleSpeed.clear();
		usleep(2000000);
	}

}

int main(int argc, char** argvv){
	//IPC COMMUNICATION
	zmq::context_t context(2);

	std::string m_socket_PUB_Detecting("tcp://127.0.0.1:5557");
	std::string m_socket_SUB_Immobilized("tcp://127.0.0.1:5556");
	std::string m_socket_SUB_Disabled("tcp://127.0.0.1:5558");

	zmq::socket_t publisher(context, ZMQ_PUB);
	publisher.bind(m_socket_PUB_Detecting);

	zmq::socket_t subscriber(context, ZMQ_SUB);
	subscriber.connect(m_socket_SUB_Immobilized);
	subscriber.connect(m_socket_SUB_Disabled);
	subscriber.setsockopt(ZMQ_SUBSCRIBE, "", 0);

	int serial_port;
	//START SERIAL COMMUNICATION AND VERIFY SETUP
	if(wiringPiSetup() < 0){
		std::cout << "wiringPi Setup failed"<< std::endl;
		return 1;
	}

	if((serial_port = serialOpen("/dev/ttyS0",9600)) < 0){
		std::cout << "serial device not open "<< std::endl;
		return 1;
	}


	while(true){ //STATUS MONITOR OF DEVICE
		std::string message = s_recv(subscriber);
		if(message.compare("Immobilized") == 0){
			immobilizeCar(serial_port);
			s_send(publisher, "EnableBT");
		}
		else if(message.compare("Disabled") == 0){
			disableQuery(serial_port);
			s_send(publisher, "Detecting");
		}
	}
	serialClose(serial_port);
	return 0;
}
