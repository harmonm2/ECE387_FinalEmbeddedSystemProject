#include <Adafruit_GPS.h> // GPS Library
#include <SoftwareSerial.h> // Software Serial Library

SoftwareSerial mySerial(1, 0); // Setting up new serial port at pins 3 and 2 (Rx Tx of GPS)
Adafruit_GPS GPS(&mySerial); // Creating GPS object

String NMEA1; // Variable for first NMEA GPS sentence
String NMEA2; // variable for second NMEA GPS sentence
char c; // character to read incoming characters from GPS

void setup() {
  Serial.begin(115200);
  GPS.begin(9600);
  GPS.sendCommand("$PGCMD,33,0*6D"); // sending command into gps, antenna update
  GPS.sendCommand(PMTK_SET_NMEA_UPDATE_10HZ); // set update rate to 10 Hz
  GPS.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCGGA); // request rmc and gga sentences only
  delay(1000);

}

void loop() {

  readGPS();
  delay(250);

}

void readGPS() {

  clearGPS();
  // Read RMC setence
  while (!GPS.newNMEAreceived()) { // when you have a NMEA sentence
    c = GPS.read();
  }
  GPS.parse(GPS.lastNMEA()); // parse the last NMEA sentence
  NMEA1 = GPS.lastNMEA();

  // Read GGA sentence
  while (!GPS.newNMEAreceived()) { // when you have a NMEA sentence
    c = GPS.read();
  }
  GPS.parse(GPS.lastNMEA()); // parse the last NMEA sentence
  NMEA2 = GPS.lastNMEA();

  Serial.println(NMEA1);
  Serial.println(NMEA2);
  Serial.println("");
}

// Clear old and corrupt data from serial port
void clearGPS() {
  while (!GPS.newNMEAreceived()) { // when you have a NMEA sentence
    c = GPS.read();
  }
  GPS.parse(GPS.lastNMEA()); // parse the last NMEA sentence
  while (!GPS.newNMEAreceived()) { // when you have a NMEA sentence
    c = GPS.read();
  }
  GPS.parse(GPS.lastNMEA()); // parse the last NMEA sentence
  while (!GPS.newNMEAreceived()) { // when you have a NMEA sentence
    c = GPS.read();
  }
  GPS.parse(GPS.lastNMEA()); // parse the last NMEA sentence
}

// To get desired values
// GPS.latitude
// GPS.longitude 
