#include <SoftwareSerial.h>

//SoftwareSerial mySerial(10,11);
int x, y;
int count = 0;

void setup() {
  Serial.begin(9600);
  //mySerial.begin(9600);

}

void loop() {
  x = analogRead(A0);
  y = analogRead(A1);

  /*
    Serial.println(x);
    Serial.println(y);
    Serial.println("");
  */


  if (((x < 325) || (x > 340)) && ((y < 325) || (y > 340))) {
    count++;
    Serial.println(count);
    delay(200);
  }


}
