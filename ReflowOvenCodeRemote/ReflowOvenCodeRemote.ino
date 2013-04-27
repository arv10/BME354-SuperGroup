// master code with temperature setting, heater control, and safety

// Daria is amazing; remember that (Jessica)
// Chocholate Diablo is  but hot

#include <LiquidCrystal.h>
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

#include <PID_v1.h>
#include <IRremote.h>

float setTemp = 150; // temp threshold in Celsius
int lcd_key = 0;
int adc_key_in = 0;
int check_key = 0;
int high = 300;
int low = 20;
int cursorPos = 0;
double t0 = 0;
double CurrentTime = 0;

int heaterPin = 2; // check this value
int tempPin = 5;    // check this value
double UpdatedSetpoint = 0;

//Define Variables we'll be connecting to
double Input, Output;
double Setpoint[] = {23, 0, 0, 0, 0, 0, 0, 0};

//Specify the links and initial tuning parameters
PID myPID(&Input, &Output, &UpdatedSetpoint,2,0.1,5, DIRECT);

int irReceiverPin = 3;
IRrecv irrecv(irReceiverPin);
decode_results results;

void setup()
{

  irrecv.enableIRIn();
  
  int startTemp = low; // start setting the Temp at 0.00
  lcd.begin(16,2);
  pinMode(heaterPin,OUTPUT); // heaterPin is set as an output
  

  // Setpoint = setTemp;
  
  //turn the PID on
  myPID.SetMode(AUTOMATIC);
  
  Serial.begin(9600);
  Serial.println("code started");
  delay(5);

  
  for (int i = 2; i < 7; i = i+2) {
        lcd.clear();
        lcd.print("Set Temp, T");
        lcd.print(i/2);
        lcd.print(", C");
	Setpoint[i]=setRemote(i);

        lcd.clear();
        lcd.print("Set Time, t");
        lcd.print(i/2);
        lcd.print(", s");
	Setpoint[i+1]=setRemote(i+1);
    }
  
}


void loop()
{
  int seconds = millis()/1000;
  CurrentTime = seconds-t0;

      if (irrecv.decode(&results)) {
        int RemoteValue = results.value;
        Serial.println(RemoteValue);
        irrecv.resume(); // Receive the next value
       }
  
  if (CurrentTime < Setpoint[3]) {
    UpdatedSetpoint = ramp(Setpoint, 3);
    UpdateLCD(Setpoint[2]);
    Serial.println("First If");
    delay(5); 
  }
  else if (CurrentTime < Setpoint[5]) {
    UpdatedSetpoint = ramp(Setpoint, 5);
    UpdateLCD(Setpoint[4]);
    Serial.println("Second If");
    delay(5); 
  }
  
  else if (CurrentTime < Setpoint[7]) {
    UpdatedSetpoint = ramp(Setpoint, 7);
    UpdateLCD(Setpoint[6]);
    Serial.println("Last Case Structure");
    delay(5); 
  }
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

