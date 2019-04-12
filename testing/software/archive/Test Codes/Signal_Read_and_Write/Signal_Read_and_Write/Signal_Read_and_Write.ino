#include <SPI.h>          //SPI is used to talk to the CAN Controller
#include <mcp_can.h>
#include <mcp_can_dfs.h>  //Include the definitions

MCP_CAN CAN(10);          //set SPI Chip Select to pin 10

#define LEDG 4
#define LEDR 5

//=======================================//
unsigned char len = 0;
unsigned char buf[8] = {0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
unsigned int canID;

unsigned char car_speed;
unsigned int engine_rpm;
unsigned char temp;
//=======================================//

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);   //to communicate with Serial monitor
  pinMode(LEDR, OUTPUT);
  pinMode(LEDG, OUTPUT); 
//tries to initialize, if failed --> it will loop here for ever
START_INIT:

//CAN_125KBPS
    //if(CAN_OK == CAN.begin(CAN_500KBPS))      //setting CAN baud rate to 500Kbps
    if(CAN_OK == CAN.begin(CAN_125KBPS))      //setting CAN baud rate to 500Kbps
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

//Initialize speed to 3 kmph
unsigned char speed = 3;
unsigned char stmp[8] = {speed, 0x01, 0xFF, 0xEE, 0xAA, 0x00, 0x00, 0x03};
                        //{speed in kph, state, 6 bytes unused}

void loop() {
    //Signal_Write
    //CAN.sendMsgBuf(msg ID, extended?, #of data bytes, data array);
    //loading the data bytes of the message. Up to 8 bytes
    //This ECU will be sending speed information through the CAN Bus. From Signal_Write
    
    //Speed function block

    stmp[0] = speed;

    CAN.sendMsgBuf(0x2F1, 0, 8, stmp);
    delay(500);
    Serial.println(speed);
    if (speed > 0) {
          --speed;
    }

    //Signal_Read
    if(CAN_MSGAVAIL == CAN.checkReceive())        //check if data coming
    {
        CAN.readMsgBuf(&len, buf);    //read data,  len: data length, buf: data buffer
        canID = CAN.getCanId();       //getting the ID of the incoming message

        if (canID == 0xF1)            //reading only our beloved 0xF1 message
        {
          Serial.print("ID is: ");
          Serial.print(canID, HEX);     //printing the ID in its standard form, HEX

          Serial.print("    Length is: ");
          Serial.println(len);

          Serial.println("\n\n");

          //LED state block//
//============================================//
          Serial.println(buf[1]);
          if (buf[1]==1) {
            //vehicle immobilized
              digitalWrite(LEDR, HIGH);
              digitalWrite(LEDG, LOW);
              
              Serial.print("buf[1] is: ");
              Serial.print(buf[1]);
              Serial.print("\n");
            }
            else{
              //vehicle NOT immobilized
              digitalWrite(LEDG, HIGH);
              digitalWrite(LEDR, LOW);
              
              Serial.print("buf[1] is: ");
              Serial.print(buf[1]);
              Serial.print("\n");
            }
//============================================//          

          Serial.println("\n\n\t*************");
        }
      }
}
