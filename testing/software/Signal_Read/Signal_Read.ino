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

unsigned char len = 0;
unsigned char buf[8];
unsigned int canID;

unsigned char car_speed;
unsigned int engine_rpm;
unsigned char temp;

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


void loop()
{
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

          //for the first signal: car speed
          car_speed = buf[0];
          
          Serial.print("Car speed = ");
          Serial.println(car_speed);


          //for the third signal: check engine light
          if((buf[2] & 0x40) >> 6 == 1)
          {
            Serial.println("Turn ON check engine light");
          }

          else if((buf[2] & 0x40) >> 6 == 0)
          {
            Serial.println("Turn OFF check engine light");
          }


          //for the fourth signal: oil indicator
          if((buf[2] & 0x80) >> 7 == 1)
          {
            Serial.println("Turn ON Oil indicator");
          }

          else if((buf[2] & 0x80) >> 7 == 0)
          {
            Serial.println("Turn OFF Oil indicator");
          }



          //for the second signal: engine RPM
          engine_rpm = buf[1];
          engine_rpm = engine_rpm << 8;
          temp = buf[2] & 0x3F;
          engine_rpm = engine_rpm + temp;

          Serial.print("Engine RPM = ");
          Serial.println(engine_rpm);

          
          Serial.println("\n\n\t*************");
        }
      }
}
