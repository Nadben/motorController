/*Bibliothèque*/
#include <Servo.h>

/*VARIABLES GLOBALES*/
byte inchar;
int throttle;
Servo esc ;

byte potvaly;
byte arr [4];
byte cnt = 0;

bool zButton;
bool cButton;
bool keepCurrent = true;

static unsigned long lastAccelTime = 0;

int spd = 1300;
int consigneMax = 2000;
int increment = 20;
int accel = 75;

void setup() {
  esc.attach(9);
  Serial.begin(9600);
  Serial1.begin(9600);
}

void loop() {
  if(Serial1.available() == 0){
    throttle = 1390;
    esc.write(throttle);// Si nous ne recevons plus de donnee du Xbee on se met a neutre
    Serial.println(throttle);
  }else { while (Serial1.available()>0){
      inchar = Serial1.read();
      if(inchar != 93){
        arr[cnt] = inchar;
        cnt++;
      }else{
        
        potvaly = arr [1];
        zButton = arr [2];
        cButton = arr [3];

        //Serial.println(zButton);
        cnt = 0;

        if(!zButton && cButton){
          if(keepCurrent == true){
            throttle = map(potvaly, 0, 255, 700, 2000);
            esc.write(throttle);
            keepCurrent = false;
          }
        }else if(!cButton && zButton){
          //static unsigned long lastAccelTime = 0;
          unsigned long currentTime = millis();
          if(currentTime - lastAccelTime > accel){
            lastAccelTime = currentTime;
            if( spd < consigneMax){
              spd += increment;
              esc.write(spd);
              Serial.println(spd);
            }
          }
        }
        
        else{
          //Serial.println(potvaly);
          spd = 1300;
          throttle = map(potvaly, 27, 235, 700, 2000);
          esc.write(throttle);
          Serial.println(throttle);// pour debugger la valeur 
          keepCurrent = true;       
        }
      }
    }
    delay(20); // delay pour attendre que les donnes soient recu au cas d'un decrochage
  }
}
