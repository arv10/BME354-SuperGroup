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
double t0 = 0;
double CurrentTime = 0;

int heaterPin = 2; // check this value
int tempPin = 5;    // check this value
double UpdatedSetpoint = 0;

//Define Variables we'll   be connecting to
double Input, Output;
double Setpoint[] = {23, 0, 0, 0, 0, 0, 0, 0};

//Specify the links and initial tuning parameters
PID myPID(&Input, &Output, &UpdatedSetpoint,2,0.1,5, DIRECT);


void setup()
{

  int startTemp = low; // start setting the Temp at 0.00
  lcd.begin(16,2);
  pinMode(heaterPin,OUTPUT); // heaterPin is set as an output
  

  // Setpoint = setTemp;
  
  //turn the PID on
  myPID.SetMode(AUTOMATIC);
  
  for (int i = 0; i < 3; i++) {
        lcd.setCursor(0,0);
        lcd.print("Set Temperature:");
        lcd.setCursor(1,1); 
        lcd.print(startTemp);
	Setpoint[i]=setthetemperature(i);

        lcd.setCursor(0,0);
        lcd.print("Set Time:");
        lcd.setCursor(1,1); 
        lcd.print(startTemp);
        Setpoint[i+1]=setthetemperature(i+1);
    }
    
  Serial.begin(9600);
  Serial.println("Void Setup Line"); 
  delay(5); 
}


void loop()
{
  int seconds = millis()/1000;
  CurrentTime = seconds-t0;
  
  Serial.println("In the Void Loop");
  delay(5);  
  
  if (CurrentTime < Setpoint[3]) {
    UpdatedSetpoint = ramp(Setpoint, 3);
    UpdateLCD(Setpoint[2]);
    
  }
 
  else if (CurrentTime < Setpoint[5]) {
    UpdatedSetpoint = ramp(Setpoint, 5);
    UpdateLCD(Setpoint[4]);
  
  }
  
  else if (CurrentTime < Setpoint[5]) {
    UpdatedSetpoint = ramp(Setpoint, 7);
    UpdateLCD(Setpoint[6]);
  }
}

void UpdateLCD(double target)
  { 
  Serial.println("In the function"); 
  delay(5); 
  lcd.clear();
  heaterdisplay(target);
  delay(750);
  lcd.clear();
  heatersaftey(target);
  delay(750); 
    
}

