/*
  Morgan Harmon
  ECE387 Midterm

  This program has a cat animation walking aross the LCD. This demostrates the uses of the LCD for
  similar projects.

*/

// include the library code:
#include  <LiquidCrystal.h>

int contrast = 120;

// initialization of the interface pins with library:
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

// animation speed:
int y = 250;

// defining each screen for animation
// --START CAT ANIMATION--
// --EMPTY START--
byte empty[8] = {
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000
};
// --EMPTY END--


// --FRAME 1--
byte catButtStanding[8] = {
  B01111,
  B01000,
  B01000,
  B01111,
  B01111,
  B01111,
  B01010,
  B01010
};

byte catFaceStanding[8] = {
  B01010,
  B01110,
  B00100,
  B11110,
  B11110,
  B11110,
  B01010,
  B01010
};
// --FRAME 1 END--

//--FRAME 2--
byte catButtRightLegBack[8] = {
  B01111,
  B01000,
  B01000,
  B01111,
  B01111,
  B01111,
  B01010,
  B01100
};

byte catFaceRightLegFront[8] = {
  B01010,
  B01110,
  B00100,
  B11110,
  B11110,
  B11110,
  B01010,
  B01001
};
//--FRAME 2 END--

//--FRAME 3--
byte catButtRightLegFront[8] = {
  B01110,
  B01010,
  B01000,
  B01111,
  B01111,
  B01111,
  B01010,
  B01001
};

byte catFaceRightLegBack[8] = {
  B01010,
  B01110,
  B00100,
  B11110,
  B11110,
  B11110,
  B01010,
  B01100
};
//--FRAME 3 END--

//--FRAME 4--
byte catButtLeftLegFront[8] = {
  B01111,
  B01000,
  B01000,
  B01111,
  B01111,
  B01111,
  B01010,
  B00110
};

byte catFaceLeftLegBack[8] = {
  B01010,
  B01110,
  B00100,
  B11110,
  B11110,
  B11110,
  B01010,
  B10010
};
//--FRAME 4 END--

//--FRAME 5--
byte catButtLeftLegBack[8] = {
  B01111,
  B01000,
  B01000,
  B01111,
  B01111,
  B01111,
  B01010,
  B10010
};
byte catFaceLeftLegFront[8] = {
  B01010,
  B01110,
  B01110,
  B11110,
  B11110,
  B11110,
  B01010,
  B00110
};
//--FRAME 5 END--
//--END--


void setup() {
  analogWrite(6, contrast);
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // clear the LCD screen:
  lcd.clear();
}


void loop() {
  welcome();
  catDrawSpace();
}

//set up the welcome part
void welcome() {
  lcd.clear();
  lcd.setCursor(1, 0);
  lcd.print("ECE387 MIDTERM");
  lcd.setCursor(6, 1);
  lcd.print("DEMO");
  delay(3000);
  lcd.clear();
  lcd.setCursor(4, 0);
  lcd.print("BY MORGAN");
  lcd.setCursor(5, 1);
  lcd.print("HARMON");
  delay(3000);
}

//set up the cat walking animation and make it move
void catDrawSpace() {
  for (int a = 0; a < 13; a += 2)
  {
    int b = a + 1;
    int c = a + 2;
    int d = a + 3;
    int e = a + 4;
    lcd.clear();
    lcd.setCursor(1, 1);
    lcd.print("KEEP ON WALKING");

    lcd.createChar(1, empty);

    //--FRAME 1--
    lcd.createChar(2, catButtStanding);
    lcd.createChar(3, catFaceStanding);

    //--FRAME 2--
    lcd.createChar(4, catButtRightLegBack);
    lcd.createChar(5, catFaceRightLegFront);

    //--FRAME 3--
    lcd.createChar(6, catButtRightLegFront);
    lcd.createChar(7, catFaceRightLegBack);

    //--FRAME 4--
    lcd.createChar(8, catButtLeftLegBack);
    lcd.createChar(9, catFaceLeftLegFront);

    //--FRAME 5--
    lcd.createChar(10, catButtLeftLegFront);
    lcd.createChar(11, catFaceLeftLegBack);

    // NOTE:
    // changed the leg movement per frame to make the cat walking more
    // organic
    //--FRAME 1--
    lcd.setCursor(a, 0);
    lcd.write(2);
    lcd.setCursor(b, 0);
    lcd.write(3);
    delay(y);

    //--FRAME 2--
    lcd.setCursor(a, 0);
    lcd.write(4);
    lcd.setCursor(b, 0);
    lcd.write(5);
    delay(y);

    //--FRAME 3--
    lcd.setCursor(a, 0);
    lcd.write(6);
    lcd.setCursor(b, 0);
    lcd.write(7);
    delay(y);

    //--FRAME 4--
    lcd.setCursor(a, 0);
    lcd.write(8);
    lcd.setCursor(b, 0);
    lcd.write(9);
    delay(y);

    //--FRAME 5--
    lcd.setCursor(a, 0);
    lcd.write(10);
    lcd.setCursor(b, 0);
    lcd.write(11);
    delay(y);
  }

  for (int a = 0; a < 13; a += 2)
  {
    int b = a + 1;
    int c = a + 2;
    int d = a + 3;
    int e = a + 4;
    lcd.clear();
    lcd.setCursor(1, 1);

    // NOTE:
    // changed the leg movement per frame to make the cat walking more
    // organic
    //--FRAME 1--
    lcd.setCursor(d, 1);
    lcd.write(2);
    lcd.setCursor(e, 1);
    lcd.write(3);
    delay(y);

    //--FRAME 2--
    lcd.setCursor(d, 1);
    lcd.write(4);
    lcd.setCursor(e, 1);
    lcd.write(5);
    delay(y);

    //--FRAME 3--
    lcd.setCursor(d, 1);
    lcd.write(6);
    lcd.setCursor(e, 1);
    lcd.write(7);
    delay(y);

    //--FRAME 4--
    lcd.setCursor(d, 1);
    lcd.write(8);
    lcd.setCursor(e, 1);
    lcd.write(9);
    delay(y);

    //--FRAME 5--
    lcd.setCursor(d, 1);
    lcd.write(10);
    lcd.setCursor(e, 1);
    lcd.write(11);
    delay(y);
  }
}
