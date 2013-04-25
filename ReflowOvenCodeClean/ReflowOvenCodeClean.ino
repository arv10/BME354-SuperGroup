// master code with temperature setting, heater control, and safety

// Daria is amazing; remember that (Jessica)
// Chocholate Diablo is  but hot

#include <LiquidCrystal.h>
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

#include <PID_v1.h>

float setTemp = 150; // temp threshold in Celsius
int lcd_key = 0;
int adc_key_in = 0;
int check_key = 0;
int shouldwesetthetemperature=0;
int high = 300;
int low = 20;
int cursorPos = 2;

int heaterPin = 2; // check this value
int tempPin = 5;    // check this value

//Define Variables we'll   be connecting to
double Setpoint, Input, Output;

//Specify the links and initial tuning parameters
PID myPID(&Input, &Output, &Setpoint,2,0.1,5, DIRECT);


void setup()
{

  int startTemp = low; // start setting the Temp at 0.00
  lcd.begin(16,2);
  pinMode(heaterPin,OUTPUT); // heaterPin is set as an output
  lcd.setCursor(0,0);
  lcd.print("Set Temperature");
  lcd.setCursor(1,1); 
  lcd.print(startTemp);

  Setpoint = setTemp;
  
  //turn the PID on
  myPID.SetMode(AUTOMATIC);
  
}


void loop()
{
  while (shouldwesetthetemperature == 0)
  {
	Setpoint=setthetemperature();
  }
  
  Input = analogRead(tempPin);
  myPID.Compute();
  analogWrite(heaterPin,Output);
  lcd.setCursor(7,1);
  lcd.print(Output);
  lcd.clear();
  heaterdisplay(Setpoint);
  delay(750);
  lcd.clear();
  heatersaftey(Setpoint);
  delay(750);
}
