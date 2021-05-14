// client code Arduino Uno 2

#include <SPI.h>
#include <RH_NRF24.h>

#include <stdio.h> 
#include <stdlib.h>

  
// Singleton instance of the radio driver
RH_NRF24 nrf24;
// RH_NRF24 nrf24(8, 7); // use this to be electrically compatible with Mirf
// RH_NRF24 nrf24(8, 10);// For Leonardo, need explicit SS pin
// RH_NRF24 nrf24(8, 7); // For RFM73 on Anarduino Mini

int VRx = A0;
int VRy = A1;
int SW = 2;

int xPosition = 0;
int yPosition = 0;
int SW_state = 0;
int mapX = 0;
int mapY = 0;
void setup() 
{
  Serial.begin(9600);
  while (!Serial) 
    ; // wait for serial port to connect. Needed for Leonardo only
  if (!nrf24.init())
    Serial.println("init failed");
  // Defaults after init are 2.402 GHz (channel 2), 2Mbps, 0dBm
  if (!nrf24.setChannel(1))
    Serial.println("setChannel failed");
  if (!nrf24.setRF(RH_NRF24::DataRate2Mbps, RH_NRF24::TransmitPower0dBm))
    Serial.println("setRF failed");

  //JoyStick
  pinMode(VRx, INPUT);
  pinMode(VRy, INPUT);
  pinMode(SW, INPUT_PULLUP); 
}


void loop()
{
  Serial.println("Sending to nrf24_server");
  // Send a message to nrf24_server
  /*int8_t data[] = "123456";
  nrf24.send(data, sizeof(data));
  */
  
  nrf24.waitPacketSent();
  // Now wait for a reply
  uint8_t buf[RH_NRF24_MAX_MESSAGE_LEN];
  uint8_t len = sizeof(buf);

  if (nrf24.waitAvailableTimeout(500))
  { 
    // Should be a reply message for us now   
    if (nrf24.recv(buf, &len))
    {
      Serial.print("got reply: ");
      Serial.println((char*)buf);
    }
    else
    {
      Serial.println("recv failed");  
    }
  }
  else
  {
    Serial.println("No reply, is nrf24_server running?");
  }
  //Joystick
  xPosition = analogRead(VRx);
  yPosition = analogRead(VRy);
  SW_state = digitalRead(SW);
  mapX = map(xPosition, 0, 1023, -512, 512);
  mapY = map(yPosition, 0, 1023, -512, 512);

  
  char str_x[21] = {0};
  char str_y[10] = {0};
  itoa(mapX, str_x, 10);
  itoa(mapY, str_y, 10);
  
  strcat(str_x," ");
  strcat(str_x,str_y);
  //strcat(str_x,"e");
  
  //nrf24.send(str_x, sizeof(str_x));
  //nrf24.send(str_y, sizeof(str_y));
  nrf24.send(str_x, sizeof(str_x));
  
  /*
  Serial.print("X: ");
  Serial.print(mapX);
  Serial.print(" | Y: ");
  Serial.print(mapY);
  Serial.print(" | Button: ");
  Serial.println(SW_state);
  */
  
  
  delay(10);
}
