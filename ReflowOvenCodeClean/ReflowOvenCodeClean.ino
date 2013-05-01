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
int high = 300;
int low = 20;
int cursorPos = 2;
double CurrentTime = 0;
double t0;
int DisplayTime;

int heaterPin = 2; // check this value
int tempPin = 5;    // check this value
double UpdatedSetpoint = 0;
double Error;

//Define Variables we'll be connecting to
double Input, Output;
double Setpoint[] = {0, 0, 0, 0, 0, 0, 0, 0};

//Specify the links and initial tuning parameters
PID myPID(&Input, &Output, &UpdatedSetpoint,5,5,0.1, DIRECT);

void setup()
{

  int startTemp = low; // start setting the Temp at 0.00
  lcd.begin(16,2);
  pinMode(heaterPin,OUTPUT); // heaterPin is set as an output
  

  // Setpoint = setTemp;
  
  //turn the PID on
  myPID.SetMode(AUTOMATIC);
  
  Serial.begin(9600);
  
  for (int i = 2; i < 7; i = i+2) {
        lcd.clear();
        lcd.print("Set Temp, T");
        lcd.print(i/2);
        lcd.print(", C");
        lcd.setCursor(1,1); 
        lcd.print(startTemp);
	Setpoint[i]=setthetemperature(i);

        lcd.clear();
        lcd.print("Set Time, t");
        lcd.print(i/2);
        lcd.print(", s");
        lcd.setCursor(1,1); 
        lcd.print(startTemp);
        Setpoint[i+1]=setthetemperature(i+1);
    }

  Setpoint[0] = getTempCelsius();
  DisplayTime = Setpoint[7];
  
  Serial.println(Setpoint[0]);
  delay(5);
  Serial.println(Setpoint[1]);
  delay(5);
  Serial.println(Setpoint[2]);
  delay(5);
  Serial.println(Setpoint[3]);
  delay(5);
  Serial.println(Setpoint[4]);
  delay(5);
  Serial.println(Setpoint[5]);
  delay(5);
  Serial.println(Setpoint[6]);
  delay(5);
  Serial.println(Setpoint[7]);
  delay(5);
  
}


void loop()
{
  int seconds = millis()/1000;
  CurrentTime = seconds-t0;
  float TempCelsius = getTempCelsius(); // test linear relationship
  DisplayTime = Setpoint[7] - CurrentTime;
  
  Serial.println("In the Void Loop");
  delay(5);  
  
  if (CurrentTime < Setpoint[3]) {
    UpdatedSetpoint = ramp(Setpoint, 3);
    UpdateLCD(Setpoint[2]);
    
    Error = UpdatedSetpoint - TempCelsius;
    Error = Error / UpdatedSetpoint;
    
    Serial.println("First If");
    Serial.println("Current Time: ");    
    Serial.print(CurrentTime);
    Serial.println("\n Updated Set Point: ");
    Serial.print(UpdatedSetpoint);
    Serial.println("\n Error: ");
    Serial.print(Error);
    Serial.println("");
    delay(5); 
  }
  else if (CurrentTime < Setpoint[5]) {
    UpdatedSetpoint = ramp(Setpoint, 5);
    UpdateLCD(Setpoint[4]);
    
    Error = UpdatedSetpoint - TempCelsius;
    Error = Error / UpdatedSetpoint;
    
    Serial.println("Second If");
    Serial.println("Current Time: ");
    Serial.print(CurrentTime);
    Serial.println("\n Updated Set Point: ");
    Serial.print(UpdatedSetpoint);
    Serial.println("\n Error: ");
    Serial.print(Error);
    Serial.println("");
    delay(5); 
  }
  
  else if (CurrentTime < Setpoint[7]) {
    UpdatedSetpoint = ramp(Setpoint, 7);
    UpdateLCD(Setpoint[6]);
    
    Error = UpdatedSetpoint - TempCelsius;
    Error = Error / UpdatedSetpoint;
    
    Serial.println("Last Case Structure");
    Serial.println("Current Time: ");
    Serial.print(CurrentTime);
    Serial.println("\n Updated Set Point: ");
    Serial.print(UpdatedSetpoint);
    Serial.println("\n Error: ");
    Serial.print(Error);
    Serial.println("");
    delay(5); 
  }
  
  
  else {
   UpdateLCD(Setpoint[6]);
   Serial.println("You're Through!");
   delay(5);
  }
  
  if (analogRead(0)<1023){
    while(true)
    {
      Serial.println("ABORT!");
      digitalWrite(heaterPin, LOW);
    }
  }
  delay(1000);
}

void UpdateLCD(double target)
  { 
  lcd.clear();
  heaterdisplay(target);
  delay(750);
  lcd.clear();
  heatersaftey(target);
  delay(750); 
    
}
