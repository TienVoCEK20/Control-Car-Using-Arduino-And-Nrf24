// client code Arduino Uno 2

#include <SPI.h>
#include <RH_NRF24.h>
// Include the Servo library  
// Singleton instance of the radio driver
RH_NRF24 nrf24;
// RH_NRF24 nrf24(8, 7); // use this to be electrically compatible with Mirf
// RH_NRF24 nrf24(8, 10);// For Leonardo, need explicit SS pin
// RH_NRF24 nrf24(8, 7); // For RFM73 on Anarduino Mini
int motor1pin1 = 4;
int motor1pin2 = 5;

int motor2pin1 = 7;
int motor2pin2 = 6;

int En1 = 3;
int En2 = 9; 
void setup() 
{
    pinMode(En1, OUTPUT);   // where the motor is connected to
    pinMode(En2, OUTPUT);   // where the motor is connected to
    pinMode(motor1pin1, OUTPUT);
    pinMode(motor1pin2, OUTPUT);
    pinMode(motor2pin1, OUTPUT);
    pinMode(motor2pin2, OUTPUT);  
  Serial.begin(9600);
  // We need to attach the servo to the used pin number  
  while (!Serial) 
    ; // wait for serial port to connect. Needed for Leonardo only
  if (!nrf24.init())
    Serial.println("init failed");
  // Defaults after init are 2.402 GHz (channel 2), 2Mbps, 0dBm
  if (!nrf24.setChannel(1))
    Serial.println("setChannel failed");
  if (!nrf24.setRF(RH_NRF24::DataRate2Mbps, RH_NRF24::TransmitPower0dBm))
    Serial.println("setRF failed");    
}


void loop()
{
  Serial.println("Sending to nrf24_server");
  // Send a message to nrf24_server
  uint8_t data[] = "Hello World!";
  nrf24.send(data, sizeof(data));
  
  nrf24.waitPacketSent();
  // Now wait for a reply
  uint8_t buf[RH_NRF24_MAX_MESSAGE_LEN];
    uint8_t len = sizeof(buf);
  char *x;
  char *y;
  char s[2] = " ";
  x = strtok(buf,s);
  y = strtok(NULL,s);
  int posx,posy;
  posx = atoi(x);
  posy = atoi(y);
   
  if (nrf24.waitAvailableTimeout(500))
  { 
    // Should be a reply message for us now   
    if (nrf24.recv(buf, &len))
    {
      //go forward
      if(posx > -20 && posx < 20 && posy > -20 && posy < 20)
      {
        Serial.println("S");
        digitalWrite(motor1pin1,LOW);
        digitalWrite(motor1pin2,LOW);
        digitalWrite(motor2pin1,LOW);
        digitalWrite(motor2pin2,LOW);
      }
      else if(posx > -20 && posx <20 && posy >=20)
      {
        Serial.println("F");
        analogWrite(En1,200);
        analogWrite(En2,200);
        digitalWrite(motor1pin1,HIGH);
        digitalWrite(motor1pin2,LOW);
        digitalWrite(motor2pin1,HIGH);
        digitalWrite(motor2pin2,LOW);        
      }
      else if(posx > -20 && posx < 20 && posy <= -20)
      {
        Serial.println("B");
        analogWrite(En1,200);
        analogWrite(En2,200);       
        digitalWrite(motor1pin1,LOW);
        digitalWrite(motor1pin2,HIGH);
        digitalWrite(motor2pin1,LOW);
        digitalWrite(motor2pin2,HIGH);
      }
      else if(posy < 20 && posy >-20 && posx >= 20) 
      { 
        Serial.println("R");
        analogWrite(En1,200);
        analogWrite(En2,0);
        digitalWrite(motor1pin1,HIGH);
        digitalWrite(motor1pin2,LOW);
        digitalWrite(motor2pin1,HIGH);
        digitalWrite(motor2pin2,LOW);
      }
      else if(posy < 20 && posy >-20 && posx <= -20)
      {
        Serial.println("L");
        analogWrite(En1,0);
        analogWrite(En2,200);
        digitalWrite(motor1pin1,HIGH);
        digitalWrite(motor1pin2,LOW);
        digitalWrite(motor2pin1,HIGH);
        digitalWrite(motor2pin2,LOW);       
      }
      Serial.print("got reply: ");
      Serial.println((char*)buf);
      Serial.println(posx);
      Serial.println(posy);
      delay(50);
      
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
  delay(10);
}
