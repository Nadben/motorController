/*Bibliothèque*/
#include <Servo.h>

/*VARIABLES GLOBALES*/
unsigned char inchar;
int value ;
int throttle;
Servo esc ;



`
void setup() {
  esc.attach(9);
  Serial.begin(9600);
}

void loop() {
  
  
  delay(100);
  if(Serial1.available() == 0){
    esc.write(throttle) == 1390;// Si nous ne recevons plus de donnee du Xbee on se met a neutre
    Serial.println(throttle);
  }else { while (Serial1.available()>0){
      throttle = map(inchar, 0, 255, 700, 2000);
      esc.write(throttle);
      Serial.println(throttle);// pour debugger la valeur
    }
    delay(20); // delay pour attendre que les donnes soient recu au cas d'un decrochage
  }
}
