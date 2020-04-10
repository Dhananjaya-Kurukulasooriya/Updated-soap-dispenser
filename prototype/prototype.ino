//libraries that need for this prototype
#include <NewPing.h>
#include <Servo.h>
#include <LiquidCrystal.h>


//ping define
//for lcd screen

#define rs 11 //register select
#define en 12 //enable pin
#define d4 2
#define d5 3
#define d6 4
#define d7 5


//for water level sensor
#define waterLevel A0

//for sonar
#define trig 6 //for the trigger pin
#define echo 7  //for the echo pin
#define maxDistance 10//this is the maximum distance that we need to meassure

// for IR sensor
#define irRead 8

//for the servo
#define servoPwm 9

//for the relay and motor control
#define relay 10


//instance creation
LiquidCrystal lcd(rs, en, d4, d5, d6, d7); //for the lcd display
Servo sg90;//for the servo motor
NewPing sonar(trig, echo, maxDistance); //for the distance sensor

//all the methods
int sonarRead();
int irReading();
int waterLevelIndicator();

//global variables
bool soap = false;
void setup() {

  //define the pin usages
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  pinMode(irRead, INPUT);
  pinMode(relay, OUTPUT);

  Serial.begin(9600);//just in case
  sg90.attach(servoPwm);//this is the pwm pin attached with the servo motor
  sg90.write(180);//default locaion for the servo motor
  lcd.begin(16, 2); //begin the lcd screen
  //greeting
  lcd.setCursor(3, 0);
  lcd.print("Have a Good ");
  lcd.setCursor(6, 1);
  lcd.print("Day!");

  delay(3000);

}

void loop() {


  int sonarReadValue = sonarRead();
  if (sonarReadValue < maxDistance)
  {


    lcd.clear();
    lcd.setCursor(6, 0);
    lcd.print("Soap!");
    Serial.println(sonarReadValue);
    sg90.write(90);
    delay(1000);
    sg90.write(180);
    delay(1000);

  }
  else
  {
    //greeting
    lcd.setCursor(3, 0);
    lcd.print("Have a Good ");
    lcd.setCursor(6, 1);
    lcd.print("Day!");




  }

  int waterLevelIndicatorValue = waterLevelIndicator();
  int irReadValue = irReading();
  if (waterLevelIndicatorValue == 0 && irReadValue == 0)
  {
    lcd.clear();
    lcd.setCursor(4, 0);
    lcd.print("No water!");
    delay(1000);
    //greeting
    lcd.setCursor(3, 0);
    lcd.print("Have a Good ");
    lcd.setCursor(6, 1);
    lcd.print("Day!");

  }
  else if (waterLevelIndicatorValue == 1  && irReadValue == 0 && soap == false)
  {
    lcd.clear();
    lcd.setCursor(0, 6);
    lcd.print("Water!");
    digitalWrite(relay, HIGH);
    delay(3000);
    digitalWrite(relay,LOW);
    lcd.clear();
    //greeting
    lcd.setCursor(3, 0);
    lcd.print("Have a Good ");
    lcd.setCursor(6, 1);
    lcd.print("Day!");

  }


}

//this functio for read and get the distance value for the soap dispenser
int sonarRead()
{
  int distance = sonar.ping_cm();
  delay(70);
  if (distance == 0)
  {
    return 200;
  }
  else
  {
    return distance;
  }
}

//this is the ir sensor read for the hand washer
int irReading()
{

  int handDetect1 = digitalRead(irRead);
  delay(50);
  int handDetect2 = digitalRead(irRead);
  delay(50);

  if (handDetect1 == 1 && handDetect2 == 1)
  {
    return 1;
  }
  else
  {
    return 0;
  }

}


//this is the water level indicator for the hand washer
int waterLevelIndicator()
{
  int waterLevel1 = analogRead(waterLevel);
  delay(100);
  int waterLevel2 = analogRead(waterLevel);

  if (waterLevel1 < 100 && waterLevel2 < 100)
  {
    return 0;
  }
  else
  {
    return 1;
  }
}
