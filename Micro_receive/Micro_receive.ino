/*Bibliothèque*/
#include <Servo.h>

/*VARIABLES GLOBALES*/

Servo esc ;

char beginTransmissionWord = '[';
char endTransmissionWord = ']';


byte inchar;
byte potvaly;
byte arr [4];
byte cnt = 0;

bool keepCurrent = true;
bool zButton;
bool cButton;

static unsigned long lastAccelTime = 0;

int neutral = 1300;
int consigneMax = 2000;
int increment = 20;
int accel = 200;
int throttle;
int spd;



void setup() {
  esc.attach(9); //pin 
  Serial.begin(9600); 
  Serial1.begin(9600); //Micro hardware Serial where the xbee is connected
}

void loop() {
  delay(100); //for some reason it reduces the random cuts that I have
  if(Serial1.available() == 0) { //If we lose connection, then we go immediately to neutral.
    throttle = neutral;
    esc.write(throttle);
    //Serial.println(throttle);
  }
  else {     
    while (Serial1.available()>0) {
      inchar = Serial1.read();
      
      if(inchar != endTransmissionWord) {
        arr[cnt] = inchar;
        cnt++;
      }
      
      else {        
        potvaly = arr [1];
        zButton = arr [2];
        cButton = arr [3];

        cnt = 0;

        if(!zButton && cButton) {
          if(keepCurrent == true) {
            throttle = map(potvaly, 0, 255, 700, 2000);
            esc.write(throttle);
            keepCurrent = false;
          }
        }
        
        else if(!cButton && zButton) {
          unsigned long currentTime = millis();
          if(currentTime - lastAccelTime > accel) {
            lastAccelTime = currentTime;
            if( spd < consigneMax) {
              spd += increment;
              esc.write(spd);
              //Serial.println(spd);
            }
          }
        }
        
        else {
          //Serial.println(potvaly);
          spd = neutral;
          throttle = map(potvaly, 27, 235, 700, 2000);
          esc.write(throttle);
          //Serial.println(throttle);
          keepCurrent = true;       
        }
      }
    }
    delay(20); // delay pour attendre que les donnes soient recu au cas d'un decrochage
  }
}
