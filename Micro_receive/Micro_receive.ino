/*Bibliothèque*/
#include <Servo.h>

/*VARIABLES GLOBALES*/
byte dataStream [3]; //array de 5 bytes

char startTransmissionWord = '[';
char endTransmissionWord = ']';

bool zButton = true;
bool cButton = true;
bool rcvInProgress = true;
bool keepCurrent = true;
bool newData = false;

unsigned char inchar;
unsigned char potvaly;

int value ;
int throttle;
int cnt = 0;

/*Objets*/
Servo esc ;

void setup() {
  esc.attach(9);
  Serial.begin(9600);
  Serial1.begin(9600);
}

void loop() {

  if(Serial1.available() == 0){//serial1
    throttle = 1390;// Si nous ne recevons plus de donnee du Xbee on se met a neutre
    esc.write(throttle);
    Serial.println(throttle);
  }else { while (Serial1.available() > 0 and newData == false){//serial 1
      inchar = Serial.read();
      //start/end transmission
      if( rcvInProgress == true){
        if(inchar != endTransmissionWord){
          dataStream[cnt] = inchar;
          cnt++;
        }
        else{

          potvaly = dataStream[1];
          zButton = dataStream[2];
          cButton = dataStream[3];

          // cruise control
          if(!zButton){
            if(keepCurrent = true){
              throttle = map(potvaly, 0, 255, 700, 2000);
              esc.write(throttle);
              keepCurrent = false;
            }
            Serial.println(throttle);// pour debugger la valeur

          }else{
            throttle = map(potvaly, 0, 255, 700, 2000);
            esc.write(throttle);
            Serial.println(throttle);// pour debugger la valeur
            keepCurrent = true;
            rcvInProgress = false;
            newData = true;
            cnt = 0;
          }
        }
      }
      else if (inchar == startTransmissionWord){
        rcvInProgress = true;
      }
    }
    delay(20); // delay pour attendre que les donnes soient recu au cas d'un decrochage
  }
}
