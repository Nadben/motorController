/*Bibliothèque*/
#include <Servo.h>

/*VARIABLES GLOBALES*/
byte inchar;
int throttle;
Servo esc ;




void setup() {
  esc.attach(9);
  Serial.begin(9600);
  Serial1.begin(9600);
}

void loop() {
  
  
  delay(100);
  if(Serial1.available() == 0){
    throttle = 1390;
    esc.write(throttle);// Si nous ne recevons plus de donnee du Xbee on se met a neutre
    Serial.println(throttle);
  }else { while (Serial1.available()>0){
      inchar = Serial1.read();
      //Serial.println(inchar);
      throttle = map(inchar, 35, 235, 700, 2000);
      esc.write(throttle);
      Serial.println(throttle);// pour debugger la valeur
    }
    delay(20); // delay pour attendre que les donnes soient recu au cas d'un decrochage
  }
}
