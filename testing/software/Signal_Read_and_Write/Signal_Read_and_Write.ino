//References:
//https://www.instructables.com/id/Yes-We-CAN-BUS-With-Arduino-in-30-Seconds/
//https://www.instructables.com/id/Arduino-OBD2-Simulator/


#include <mcp_can.h>
#include <SPI.h>

MCP_CAN CAN(10);                                      // Set CS to pin 10
//LED pin assignment
#define LEDG 4
#define LEDR 5

unsigned int canId = 0x000;

unsigned char len = 0;
unsigned char buf[8];
char str[20];

String BuildMessage="";
int MSGIdentifier=0;


void setup() {
  Serial.begin(115200);
  //LED pin initialization
  pinMode(LEDR, OUTPUT);
  pinMode(LEDG, OUTPUT);
  //Default State of the Car is NOT immobilized - Green means the car is moving
  digitalWrite(LEDG, HIGH);
//tries to initialize, if failed --> it will loop here for ever
START_INIT:

    if(CAN_OK == CAN.begin(CAN_500KBPS))                   // init can bus : baudrate = 500k
    {
        Serial.println("CAN BUS Shield init ok!");
    }
    else
    {
        Serial.println("CAN BUS Shield init fail");
        Serial.println("Init CAN BUS Shield again");
        delay(100);
        goto START_INIT;
    }
}

void loop()
{
    //randomized Data Frames
    unsigned char rndCoolantTemp=random(1,200);
    unsigned char rndRPM=random(1,55);
    unsigned char rndSpeed=random(0,5);
    unsigned char rndIAT=random(0,255);
    unsigned char rndMAF=random(0,255);
    unsigned char rndAmbientAirTemp=random(0,200);
    unsigned char rndCAT1Temp=random(1,55);
    
    //GENERAL ROUTINE
    unsigned char SupportedPID[8] =       {1,2,3,4,5,6,7,8};
    unsigned char MilCleared[7] =         {4, 65, 63, 34, 224, 185, 147}; 
    
    //SENSORS
    unsigned char CoolantTemp[7] =        {4, 65, 5, rndCoolantTemp, 0, 185, 147};  
    unsigned char rpm[7] =                {4, 65, 12, rndRPM, 224, 185, 147};
    unsigned char vspeed[7] =             {4, 65, 13, rndSpeed, 224, 185, 147};
    unsigned char IATSensor[7] =          {4, 65, 15, rndIAT, 0, 185, 147};
    unsigned char MAFSensor[7] =          {4, 65, 16, rndMAF, 0, 185, 147};
    unsigned char AmbientAirTemp[7] =     {4, 65, 70, rndAmbientAirTemp, 0, 185, 147};
    unsigned char CAT1Temp[7] =           {4, 65, 60, rndCAT1Temp, 224, 185, 147};
    unsigned char CAT2Temp[7] =           {4, 65, 61, rndCAT1Temp, 224, 185, 147};
    unsigned char CAT3Temp[7] =           {4, 65, 62, rndCAT1Temp, 224, 185, 147};
    unsigned char CAT4Temp[7] =           {4, 65, 63, rndCAT1Temp, 224, 185, 147};
    
    //Read Packet
    if(CAN_MSGAVAIL == CAN.checkReceive())  
    {
      
      CAN.readMsgBuf(&len, buf); 
        canId = CAN.getCanId();
        Serial.print("<");Serial.print(canId);Serial.print(",");

        for(int i = 0; i<len; i++)
        {  
          BuildMessage = BuildMessage + buf[i] + ",";
        }
        Serial.println(BuildMessage);
        
        //Check wich message was received.
        if(BuildMessage=="2,1,0,0,0,0,0,0,") {CAN.sendMsgBuf(0x7E8, 0, 8, SupportedPID);}
        if(BuildMessage=="2,1,1,0,0,0,0,0,") {CAN.sendMsgBuf(0x7E8, 0, 7, MilCleared);}
        
        //SEND SENSOR STATUSES
        if(BuildMessage=="2,1,5,0,0,0,0,0,") {CAN.sendMsgBuf(0x7E8, 0, 7, CoolantTemp);}
        if(BuildMessage=="2,1,12,0,0,0,0,0,"){CAN.sendMsgBuf(0x7E8, 0, 7, rpm);}
        if(BuildMessage=="2,1,13,0,0,0,0,0,"){CAN.sendMsgBuf(0x7E8, 0, 7, vspeed);}
        if(BuildMessage=="2,1,15,0,0,0,0,0,"){CAN.sendMsgBuf(0x7E8, 0, 7, IATSensor);}
        if(BuildMessage=="2,1,16,0,0,0,0,0,"){CAN.sendMsgBuf(0x7E8, 0, 7, MAFSensor);}
        if(BuildMessage=="2,1,70,0,0,0,0,0,"){CAN.sendMsgBuf(0x7E8, 0, 7, AmbientAirTemp);}
        if(BuildMessage=="2,1,60,0,0,0,0,0,"){CAN.sendMsgBuf(0x7E8, 0, 7, CAT1Temp);}
        if(BuildMessage=="2,1,61,0,0,0,0,0,"){CAN.sendMsgBuf(0x7E8, 0, 7, CAT2Temp);}
        if(BuildMessage=="2,1,62,0,0,0,0,0,"){CAN.sendMsgBuf(0x7E8, 0, 7, CAT3Temp);}
        if(BuildMessage=="2,1,63,0,0,0,0,0,"){CAN.sendMsgBuf(0x7E8, 0, 7, CAT4Temp);}


        
        if (BuildMessage=="2,1,75,0,0,0,0,0,")          //Lookout for 75 (0x4B) as the immobilization packet
        {
          //LED Block Code
          //============================================//
          //vehicle immobilized, RED light ON
          digitalWrite(LEDR, HIGH);
          digitalWrite(LEDG, LOW);
        }
        else
        {
          //vehicle NOT immobilized, GREEN light ON
          digitalWrite(LEDG, HIGH);
          digitalWrite(LEDR, LOW);
          //============================================//   
        }

        if (BuildMessage=="2,1,204,0,0,0,0,0,")          //Lookout for 204 (0xCC) as the de-immobilization packet
        {
          //LED Block Code
          //============================================//
          //vehicle NOT immobilized, GREEN light ON
          digitalWrite(LEDR, LOW);
          digitalWrite(LEDG, HIGH);
        }
        else
        {
          //vehicle immobilized, RED light ON
          digitalWrite(LEDG, LOW);
          digitalWrite(LEDR, HIGH);
          //============================================//   
        }
        BuildMessage="";      //Resets the packet to nothing
    }
}
