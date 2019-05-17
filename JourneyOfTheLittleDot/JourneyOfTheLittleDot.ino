#include <Adafruit_GPS.h> // GPS Library
#include <LiquidCrystal.h> // LCD library
#include <SoftwareSerial.h>

int contrast = 120;

// Defining pedometer
int x1, y1;

// Defining GPS
/*
  SoftwareSerial mySerial(1, 0);
  Adafruit_GPS GPS(&mySerial); // Creating GPS object

  String NMEA1; // Variable for first NMEA GPS sentence
  String NMEA2; // variable for second NMEA GPS sentence
  char c; // character to read incoming characters from GPS
*/


// Defining restrictions to play game at gym
// For testing purposes I added the coordinates for Benton as well
// can increment/decrement by 0.001  for both long and lat
// to be within enough distance of gym
const double gymLatitude = 39.502752;
const double gymLongitude = -84.737871;

// testing coordinates
const double bentonLatitude = 39.510872;
const double bentonLongitude = -84.732763;


// Defining buttons for game
const int startButton = 8;

// Defining up, down, left, right for joystick
const int upX = 56;
const int upY = 52;
const int downX = 48;
const int downY = 52;
const int leftX = 52;
const int leftY = 48;
const int rightX = 52;
const int rightY = 56;

// Intial player spot
// Used to reset cursor
int currentRow = 0;
int currentCol = 7;

// Coordinate variables
int xCoordinate = 0;
int yCoordinate = 0;
int xTreated = 0;
int yTreated = 0;

// Variables for changing button state
int startButtonState = 0; // current state of the start button

// Variables for Joystick
int joyPin1 = 4;                 // slider variable connecetd to analog pin 0
int joyPin2 = 5;                 // slider variable connecetd to analog pin 1
int x = 0;                  // variable to read the value from the analog pin 0
int y = 0;                  // variable to read the value from the analog pin 1

// LCD display
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

// Intial Step count given to player for game
int stepCount = 30;

// Environment Definitions
// Naming definitions are defined by row and col
// The beginning row starts at 1
// The beginning column starts at l
// The enviroment is drawn for a 16 x 2 LCD
byte row1col1[8] = {
  B11111,
  B10000,
  B10000,
  B10000,
  B00000,
  B00000,
  B00000,
  B00000
};
byte row1col2[8] = {
  B11111,
  B00000,
  B00000,
  B11100,
  B10000,
  B10000,
  B00000,
  B00000
};
byte row1col3[8] = {
  B11111,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000
};
byte row1col4[8] = {
  B11111,
  B00000,
  B00000,
  B01111,
  B00000,
  B00000,
  B00000,
  B00000
};
byte row1col5[8] = {
  B11111,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000
};
byte row1col6[8] = {
  B11111,
  B00000,
  B00000,
  B00000,
  B00000,
  B00010,
  B00010,
  B00010
};
byte row1col7[8] = {
  B11111,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000
};
byte row1col8[8] = {
  B00000,
  B00000,
  B00000,
  B11111,
  B00000,
  B00000,
  B00000,
  B00000
};
byte row1col9[8] = {
  B00000,
  B00000,
  B00000,
  B11111,
  B00000,
  B00000,
  B00000,
  B00000
};
byte row1col10[8] = {
  B11111,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000
};
byte row1col11[8] = {
  B11111,
  B00000,
  B00000,
  B00000,
  B00000,
  B01000,
  B01000,
  B01000
};
byte row1col12[8] = {
  B11111,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000
};
byte row1col13[8] = {
  B11111,
  B00000,
  B00000,
  B11110,
  B00000,
  B00000,
  B00000,
  B00000
};
byte row1col14[8] = {
  B11111,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000
};
byte row1col15[8] = {
  B11111,
  B00000,
  B00000,
  B00111,
  B00001,
  B00001,
  B00000,
  B00000
};
byte row1col16[8] = {
  B11111,
  B00001,
  B00001,
  B00001,
  B00000,
  B00000,
  B00000,
  B00000
};
byte row2col1[8] = {
  B00000,
  B00000,
  B00000,
  B00000,
  B10000,
  B10000,
  B10000,
  B11111
};
byte row2col2[8] = {
  B00000,
  B00000,
  B10000,
  B10000,
  B11110,
  B00000,
  B00000,
  B11111
};
byte row2col3[8] = {
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B11111
};
byte row2col4[8] = {
  B00000,
  B00000,
  B00000,
  B00000,
  B01111,
  B00000,
  B00000,
  B11111
};
byte row2col5[8] = {
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B11111
};
byte row2col6[8] = {
  B00010,
  B00010,
  B00010,
  B00000,
  B00000,
  B00000,
  B00000,
  B11111
};
byte row2col7[8] = {
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B11111
};
byte row2col8[8] = {
  B00000,
  B00000,
  B00000,
  B00000,
  B11111,
  B00000,
  B00000,
  B00000
};
byte row2col9[8] = {
  B00000,
  B00000,
  B00000,
  B00000,
  B11111,
  B00000,
  B00000,
  B00000
};
byte row2col10[8] = {
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B11111
};
byte row2col11[8] = {
  B01000,
  B01000,
  B01000,
  B00000,
  B00000,
  B00000,
  B00000,
  B11111
};
byte row2col12[8] = {
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B11111
};
byte row2col13[8] = {
  B00000,
  B00000,
  B00000,
  B00000,
  B11110,
  B00000,
  B00000,
  B11111
};
byte row2col14[8] = {
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B11111
};
byte row2col15[8] = {
  B00000,
  B00000,
  B00001,
  B00001,
  B01111,
  B00000,
  B00000,
  B11111
};
byte row2col16[8] = {
  B00000,
  B00000,
  B00000,
  B00000,
  B00001,
  B00001,
  B00001,
  B11111
};

byte beginningPlayerPosition[8] = {
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00001
};

byte anAwfulBlob[8] = {
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111
};

void setup() {
  // Serial
  Serial.begin(9600);
  /*
    GPS.begin(9600);
    GPS.sendCommand("$PGCMD,33,0*6D"); // sending command into gps, antenna update
    GPS.sendCommand(PMTK_SET_NMEA_UPDATE_10HZ); // set update rate to 10 Hz
    GPS.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCGGA); // request rmc and gga sentences only
    delay(1000);
  */

  // Sets the brightness of the LCD
  analogWrite(6, contrast);

  // intializes start button
  pinMode(startButton, INPUT);

  lcd.begin(16, 2);
  intializeEnviromentScences();
  drawMenu();
  //verifyCoordinates();
}

void loop() {
  // Pedometer readings
  x1 = analogRead(A0);
  y1 = analogRead(A1);

  // Updating step count
  if (((x1 < 325) || (x1 > 340)) && ((y1 < 325) || (y1 > 340))) {
    stepCount++;
    // Serial.println(count);
    delay(200);
  }

  // Reads input from GPS
  // readGPS();

  // reads the state of the start pin
  startButtonState = digitalRead(startButton);

  //getAnalogJoystickData();

  if (startButtonState == HIGH) {
    // Serial.println("Clicked");
    // drawEnvironment();
    lcd.clear();
    lcd.setCursor(7, 0);
    lcd.write(7);
  }
  if (stepCount > 0) {
    moveBlob();
  } else {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Please get more");
    lcd.setCursor(0, 1);
    lcd.print("steps to play");
  }

}

/*
  checkStartButtonClick();
*/



// Checks if start button has been clicked
// If the start has been clicked the intial environment is drawn
/*
  void checkStartButtonClick() {
  startButtonState = digitalRead(startButton);

  if (startButtonState != lastButtonState) {
    drawEnvironment();
  }
  }
*/

// Sets button to be ready for input
void intializeButtons() {
  pinMode(startButton, INPUT);
  digitalWrite(startButton, HIGH);
}

// Defines characters for each environment scence
void intializeEnviromentScences() {
  // Creating new characters using the defined arrays
  // Row 1
  lcd.createChar(0, row1col1);
  lcd.createChar(1, row1col3);
  lcd.createChar(2, row2col1);
  lcd.createChar(3, row2col3);
  lcd.createChar(4, row1col16);
  lcd.createChar(5, row2col16);
  lcd.createChar(6, beginningPlayerPosition);
  lcd.createChar(7, anAwfulBlob);
}

// Draws the intial menu
void drawMenu() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Journey of the");
  delay(1000);
  lcd.setCursor(0, 1);
  lcd.print("Little Dot");
  delay(3000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Click Start to");
  lcd.setCursor(0, 1);
  lcd.print("play");
}

// Draws the intial environment
void drawEnvironment() {
  lcd.clear();
  int row1 = 0;
  int row2  = 0;
  int charNumber = 1;
  // Row 1
  lcd.write(byte(0));
  lcd.setCursor(1, 0);
  lcd.write(1);
  lcd.setCursor(2, 0);
  lcd.write(1);
  lcd.setCursor(3, 0);
  lcd.write(1);
  lcd.setCursor(4, 0);
  lcd.write(1);
  lcd.setCursor(5, 0);
  lcd.write(1);
  lcd.setCursor(6, 0);
  lcd.write(1);
  lcd.setCursor(7, 0);
  lcd.write(6);
  lcd.setCursor(8, 0);
  //lcd.write(6);
  lcd.setCursor(9, 0);
  lcd.write(1);
  lcd.setCursor(10, 0);
  lcd.write(1);
  lcd.setCursor(11, 0);
  lcd.write(1);
  lcd.setCursor(12, 0);
  lcd.write(1);
  lcd.setCursor(13, 0);
  lcd.write(1);
  lcd.setCursor(14, 0);
  lcd.write(1);
  lcd.setCursor(15, 0);
  lcd.write(4);

  // Row 2
  lcd.setCursor(0, 1);
  lcd.write(2);
  lcd.setCursor(1, 1);
  lcd.write(3);
  lcd.setCursor(2, 1);
  lcd.write(3);
  lcd.setCursor(3, 1);
  lcd.write(3);
  lcd.setCursor(4, 1);
  lcd.write(3);
  lcd.setCursor(5, 1);
  lcd.write(3);
  lcd.setCursor(6, 1);
  lcd.write(3);
  lcd.setCursor(7, 1);
  // lcd.write(3);
  lcd.setCursor(8, 1);
  // lcd.write(3);
  lcd.setCursor(9, 1);
  lcd.write(3);
  lcd.setCursor(10, 1);
  lcd.write(3);
  lcd.setCursor(11, 1);
  lcd.write(3);
  lcd.setCursor(12, 1);
  lcd.write(3);
  lcd.setCursor(13, 1);
  lcd.write(3);
  lcd.setCursor(14, 1);
  lcd.write(3);
  lcd.setCursor(15, 1);
  lcd.write(5);


  /*
    // Loop goes through the first row columns setting the cursor
    // and displaying the defined environment
    for (int col = 0; col <= 16; col++) {
    lcd.setCursor(col, row1);
    lcd.write(charNumber);
    charNumber++;
    }
    // Loop goes through the second row columns setting the cursor
    // and displaying the defined environment
    for (int col = 0; col <= 16; col++) {
    lcd.setCursor(col, row1);
    lcd.write(charNumber);
    charNumber++;
    }
    }
  */
}

// Determines the state of the buttons
// If a button is pressed, either the x or y coordinate
// of the player will change
/*void readButtonState() {
  // Read the left button input
  leftButtonState = digitalRead(leftButton);

  // Compare state to previous state
  if (leftButtonState != lastButtonState) {
    xCoordinate--;
  }
  if (leftButtonState == HIGH) {
    buttonPushCounter++;
  }
  lastButtonState = leftButtonState;

  // Read the right button input
  rightButtonState = digitalRead(rightButton);

  // Compare state to previous state
  if (rightButtonState != lastButtonState) {
    xCoordinate++;
  }
  if (rightButtonState == HIGH) {
    buttonPushCounter++;
  }
  lastButtonState = rightButtonState;

  // Read the up button input
  upButtonState = digitalRead(upButton);

  // Compare state to previous state
  if (upButtonState != lastButtonState) {
    yCoordinate++;
  }
  if (upButtonState == HIGH) {
    buttonPushCounter++;
  }
  lastButtonState = upButtonState;

  // Read the down button input
  downButtonState = digitalRead(downButton);

  // Compare state to previous state
  if (downButtonState != lastButtonState) {
    yCoordinate--;
  }
  if (downButtonState == HIGH) {
    buttonPushCounter++;
  }
  lastButtonState = downButtonState;
  }
*/

void moveBlob() {
  getAnalogJoystickData();
  // Move left
  if ((xTreated == leftX) && (yTreated == leftY)) {
    // Serial.println("Im here");
    stepCount--;
    Serial.println(stepCount);
    lcd.clear();
    if (currentCol >= 0) {
      currentCol = currentCol - 1;
    }
    lcd.setCursor(currentCol, currentRow);
    lcd.write(7);
  }
  // Move right
  if ((xTreated == rightX) && (yTreated == rightY)) {
    // Serial.println("Im here");
    stepCount--;
    Serial.println(stepCount);
    lcd.clear();
    if (currentCol <= 14) {
      currentCol = currentCol + 1;
    }
    lcd.setCursor(currentCol, currentRow);
    lcd.write(7);
  }
  // Move up
  if ((xTreated == upX) && (yTreated == upY)) {
    // Serial.println("Im here");
    stepCount--;
    Serial.println(stepCount);
    lcd.clear();
    if (currentRow == 1) {
      currentRow = currentRow - 1;
    }
    lcd.setCursor(currentCol, currentRow);
    lcd.write(7);
  }
  // Move down
  if ((xTreated == downX) && (yTreated == downY)) {
    // Serial.println("Im here");
    stepCount--;
    Serial.println(stepCount);
    lcd.clear();
    if (currentRow == 0) {
      currentRow = currentRow + 1;
    }
    lcd.setCursor(currentCol, currentRow);
    lcd.write(7);
  }
}

// Redraws the enviroment based on the player
void redrawEnvironment() {
  /*getAnalogJoystickData();

    if ((xTreated == leftX) && (yTreated == leftY)) {
    if ((xTreated == leftX) && (yTreated == leftY)) {
    }
    }*/
  /*
    for (int i = 0; i < initialLength; i++)
    {
    lcd.drawCircle(Ax, Ay, 1, BLACK);
    }
    lcd.display();
  */

}

void getAnalogJoystickData() {
  // reads the value of the variable resistor
  x = analogRead(joyPin1);
  // this small pause is needed between reading
  // analog pins, otherwise we get the same value twice
  delay(100);
  // reads the value of the variable resistor
  y = analogRead(joyPin2);

  xTreated = treatValue(x);
  yTreated = treatValue(y);

  // Serial.println(xTreated);
  // Serial.println(yTreated);
  // Serial.println("");

}

int treatValue(int data) {
  return (data * 9 / 1024) + 48;
}

/*
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
*/

/*
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
*/
/*
  void verifyCoordinates() {
  if (((GPS.latitude > 39.501752) || (GPS.latitude < 39.503752)) && ((GPS.latitude > -84.738871) || (GPS.latitude < -84.736871))) {
    Serial.println("You are within gym range");
  } else {
    Serial.println("You must be in the gym to play :)");
  }
*/
