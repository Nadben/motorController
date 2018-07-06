#include <Wire.h>

uint8_t dataStream[6]; //array de 6 bytes
int counter = 0 ;

//Dans le setup je dois lire la caibration actuel
//du joystick Y puis de sortir les valeurs suivantes
uint8_t joysticky_max = 0;//rentrer les bonnes valeurs
uint8_t joysticky_min = 0;//rentrer les bonnes valeurs
uint8_t joysticky_cent = 0;//rentrer les bonnes valeurs


void setup() {
  Serial.begin(9600);
  Wire.begin(); 
  //slave address or 0x54
  //initialize the nunchuk without encryption
  Wire.beginTransmission(0x52);
  Wire.write(0xF0);
  Wire.write(0x55);
  Wire.endTransmission();

  Wire.beginTransmission(0x52);
  Wire.write(0xFB);
  Wire.write(0x00);
  Wire.endTransmission();

  

}

void loop() {
  //boucle while avec counter qui enregistre les valeurs
  //lues et qui renvoient l'array
  Wire.requestFrom(0x52,6);
  counter = 0;
  while(Wire.available()){
    dataStream[counter++] = Wire.read();
   }

  if(counter >= 5){
    //lit la valeur potvaly
    uint8_t potvaly = dataStream[1];
    Serial.println(potvaly);
    Serial.write(potvaly);
    delay(20);
  }
}
