#include <LiquidCrystal.h>
#include "I2Cdev.h"
#include "MPU6050.h"
#include "Wire.h"

// initialize the interface pins
LiquidCrystal lcd(12, 11, 5, 7, 8, 9);

MPU6050 accelgyro;

int16_t ax, ay, az;  //Setting up gyro axis integers
int16_t gx, gy, gz;
int16_t gxS, gyS, gzS;

#define OUTPUT_READABLE_ACCELGYRO

int mf=0;  //setting mf(minutes front), mb(minutes back) , secoundsf, secondsb and miliseconds to 0     
int mb=0;    
int sf=0;
int sb=0; 
int ms=0; 


const int reset_pin = 3; //the number of the reset button pin on nano
int brightness_pin = 6; //defines pin for setting brightness
int reset = 0;       // variable for reading the rest button status
int brightness=100; //you can change this number to change brightness 

// the 8 arrays that form each segment of the custom numbers
byte bar1[8] = 
{
        B11100,
        B11110,
        B11110,
        B11110,
        B11110,
        B11110,
        B11110,
        B11100
};
byte bar2[8] =
{
        B00111,
        B01111,
        B01111,
        B01111,
        B01111,
        B01111,
        B01111,
        B00111
};
byte bar3[8] =
{
        B11111,
        B11111,
        B00000,
        B00000,
        B00000,
        B00000,
        B11111,
        B11111
};
byte bar4[8] =
{
        B11110,
        B11100,
        B00000,
        B00000,
        B00000,
        B00000,
        B11000,
        B11100
};
byte bar5[8] =
{
        B01111,
        B00111,
        B00000,
        B00000,
        B00000,
        B00000,
        B00011,
        B00111
};
byte bar6[8] =
{
        B00000,
        B00000,
        B00000,
        B00000,
        B00000,
        B00000,
        B11111,
        B11111
};
byte bar7[8] =
{
        B00000,
        B00000,
        B00000,
        B00000,
        B00000,
        B00000,
        B00111,
        B01111
};
byte bar8[8] =
{
        B11111,
        B11111,
        B00000,
        B00000,
        B00000,
        B00000,
        B00000,
        B00000
};



void setup()
{
// join I2C bus (I2Cdev library doesn't do this automatically)
    #if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
        Wire.begin();
    #elif I2CDEV_IMPLEMENTATION == I2CDEV_BUILTIN_FASTWIRE
        Fastwire::setup(400, true);
    #endif

  // assignes each segment a write number
  lcd.createChar(1,bar1);
  lcd.createChar(2,bar2);
  lcd.createChar(3,bar3);
  lcd.createChar(4,bar4);
  lcd.createChar(5,bar5);
  lcd.createChar(6,bar6);
  lcd.createChar(7,bar7);
  lcd.createChar(8,bar8);
  
  // initialize Gyro device
  accelgyro.initialize();

  // initialize Serial Port for Diagnostics
  Serial.begin(9600);

  // sets the LCD's rows and colums:
  lcd.begin(16, 2);
  analogWrite(brightness_pin ,brightness); //this sets brightness on pin 6

  pinMode(reset_pin, INPUT); // initialize the pushbutton pin as an input
  pinMode(4, OUTPUT);
  digitalWrite(4, HIGH);
}

void custom0(int col)
{ // uses segments to build the number 0
  lcd.setCursor(col, 0); 
  lcd.write(2);  
  lcd.write(8); 
  lcd.write(1);
  lcd.setCursor(col, 1); 
  lcd.write(2);  
  lcd.write(6);  
  lcd.write(1);
}

void custom1(int col)
{
  lcd.setCursor(col,0);
  lcd.write(32);
  lcd.write(32);
  lcd.write(1);
  lcd.setCursor(col,1);
  lcd.write(32);
  lcd.write(32);
  lcd.write(1);
}

void custom2(int col)
{
  lcd.setCursor(col,0);
  lcd.write(5);
  lcd.write(3);
  lcd.write(1);
  lcd.setCursor(col, 1);
  lcd.write(2);
  lcd.write(6);
  lcd.write(6);
}

void custom3(int col)
{
  lcd.setCursor(col,0);
  lcd.write(5);
  lcd.write(3);
  lcd.write(1);
  lcd.setCursor(col, 1);
  lcd.write(7);
  lcd.write(6);
  lcd.write(1); 
}

void custom4(int col)
{
  lcd.setCursor(col,0);
  lcd.write(2);
  lcd.write(6);
  lcd.write(1);
  lcd.setCursor(col, 1);
  lcd.write(32);
  lcd.write(32);
  lcd.write(1);
}

void custom5(int col)
{
  lcd.setCursor(col,0);
  lcd.write(2);
  lcd.write(3);
  lcd.write(4);
  lcd.setCursor(col, 1);
  lcd.write(7);
  lcd.write(6);
  lcd.write(1);
}

void custom6(int col)
{
  lcd.setCursor(col,0);
  lcd.write(2);
  lcd.write(3);
  lcd.write(4);
  lcd.setCursor(col, 1);
  lcd.write(2);
  lcd.write(6);
  lcd.write(1);
}

void custom7(int col)
{
  lcd.setCursor(col,0);
  lcd.write(2);
  lcd.write(8);
  lcd.write(1);
  lcd.setCursor(col, 1);
  lcd.write(32);
  lcd.write(32);
  lcd.write(1);
}

void custom8(int col)
{
  lcd.setCursor(col, 0); 
  lcd.write(2);  
  lcd.write(3); 
  lcd.write(1);
  lcd.setCursor(col, 1); 
  lcd.write(2);  
  lcd.write(6);  
  lcd.write(1);
}

void custom9(int col)
{
  lcd.setCursor(col, 0); 
  lcd.write(2);  
  lcd.write(3); 
  lcd.write(1);
  lcd.setCursor(col, 1); 
  lcd.write(7);  
  lcd.write(6);  
  lcd.write(1);
}

void printNumber(int value, int col) {
  if (value == 0) {
    custom0(col);
  } if (value == 1) {
    custom1(col);
  } if (value == 2) {
    custom2(col);
  } if (value == 3) {
    custom3(col);
  } if (value == 4) {
    custom4(col);
  } if (value == 5) {
    custom5(col);
  } if (value == 6) {
    custom6(col);
  } if (value == 7) {
    custom7(col);
  } if (value == 8) {
    custom8(col);
  } if (value == 9) {
    custom9(col);
  }      
}  

void loop() 
{ 
  lcd.setCursor(0,0); 
  lcd.print("KNUCKLES GLASS");  
  lcd.setCursor(0,1);  
  lcd.print("KILN TIMER 1.3");  
  delay(2000);
  lcd.clear();
  stopwatch(); //goes to sub program stopwatch

 
} 



//--------------------SUB PROGRAMS-------------------------



void stopwatch()
{ 
  digitalWrite(4, HIGH);
  lcd.setCursor(0,0);        //setting start point on lcd      
  printNumber(mf,0);         //writing minutes front number
  printNumber(mb,3);         //writing minutes back number
  printNumber(sf,7);         //writing seconds front number
  printNumber(sb,10);        //writeing second back number
  ms=ms+10;           
  delay(9); 
   
 if(ms==520)           
  {
   lcd.clear();  //clears LCD
  }
  
 if(ms==520)     //if state for counting up seconds
  { 
  ms=0; 
  sb=sb+1; 
  }
  
  if(sb==10)     //if state for counting up minutes
  { 
  sb=0; 
  sf=sf+1; 
  }

  if(sf==6)     //if state for counting up minutes
  { 
  sb=0; 
  sf=0;
  mb=mb+1; 
  }

  if(mb==10)     //if state for counting up minutes
  { 
  mb=0; 
  mf=mf+1; 
  }

  if(mf==10)     //if state for counting up minutes
  { 
  mb=0; 
  mf=0; 
  }
 
 reset = digitalRead(reset_pin); // read the state of the pushbutton value:

 accelgyro.getRotation(&gx, &gy, &gz);
    int sum = (gx + gy + gz);
    int potValue = analogRead(A0);
    int Sensitivity = (potValue * 30); 
    if (Sensitivity <= 2000)
    {
      Sensitivity = 2000; //Set lower threshHold for Sensitivity
    }

    OUTPUT_READABLE_ACCELGYRO
        if(sum > Sensitivity)       
        {
          stopwatch_reset();
        }
        if(sum < -Sensitivity)
        {
          stopwatch_reset();
        }

    Serial.println(sum); //Print Tilt and Sensitivity Values in Serial Window
    Serial.println(Sensitivity);

 if(reset == HIGH)
 {
   stopwatch_reset();   
 }
 else
 {
   stopwatch();
 }
}

void stopwatch_reset()
{
 digitalWrite(4, LOW);
 lcd.clear();
 mf=0;        // zero everything out
 mb=0;    
 sf=0;
 sb=0; 
 ms=0;
 delay(500);
 stopwatch(); 
}
