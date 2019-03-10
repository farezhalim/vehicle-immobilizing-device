/**************************
 *         Author         *
 *      omarCartera       *
 *                        *
 *        5/8/2017        *
 *                        *
 * c.omargamal@gmail.com  *
 **************************/

#include <SPI.h>          //SPI is used to talk to the CAN Controller
#include <mcp_can.h>

MCP_CAN CAN(10);          //set SPI Chip Select to pin 10

void setup()
{
  Serial.begin(115200);   //to communicate with Serial monitor

//tries to initialize, if failed --> it will loop here for ever
START_INIT:

    if(CAN_OK == CAN.begin(CAN_500KBPS))      //setting CAN baud rate to 500Kbps
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

//loading the data bytes of the message. Up to 8 bytes
//unsigned char data[8] = {};
unsigned char data[8] = {0xC0, 0x29, 0xEE, 0x00, 0x00, 0x00, 0x00, 0x00};

void loop()
{
    //CAN.sendMsgBuf(msg ID, extended?, #of data bytes, data array);
    CAN.sendMsgBuf(0xF1, 0, 8, data);
    delay(2000);                     
}
