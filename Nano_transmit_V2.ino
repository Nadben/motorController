#include <Wire.h>

byte dataStream[6]; //array de 6 bytes
int counter = 0 ;

void setup() {

  Wire.begin(); 

  //initialize the nunchuk without encryption
  Wire.beginTransmission(0x52);
  Wire.write((uint8_t)0xF0);
  Wire.write((uint8_t)0x55);
  Wire.endTransmission();

  Wire.beginTransmission(0x52);
  Wire.write((uint8_t)0xFB);
  Wire.write((uint8_t)0x00);
  Wire.endTransmission();

  Serial.begin(9600); //xbee's baudrate is 9600

  

}

void send_request(){

  Wire.beginTransmission(0x52);
  Wire.write((uint8_t)0x00);
  Wire.endTransmission();
  
}

void loop() {
  Wire.requestFrom(0x52,6);
  counter = 0;
  while(Wire.available()){
    dataStream[counter++] = Wire.read();
  }
  send_request(); //sans ca ca fuck up everything
  
  if(counter >= 5){
    //lit la valeur potvaly
    int potvalx = dataStream[0];
    int potvaly = dataStream[1];
    bool z_button = (dataStream[5] >> 0) & 1; 
    bool c_button = (dataStream[5] >> 1) & 1;
   

    //Serial.print("Joy y:");
    //Serial.print(potvaly, DEC);
    //Serial.println();
    //Serial.println(c_button);
    //Serial.println(z_button);
    //Serial.println();
    
    Serial.write(potvaly);//Send to xbee
    //Serial.write(z_button);

  }
  delay(20);
}






