// master code with temperature setting, heater control, and safety

// Daria is amazing; remember that (Jessica)
// Chocholate Diablo is  but hot

#include <LiquidCrystal.h>
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

#include <PID_v1.h>
#include <IRremote.h>

float setTemp = 150; // temp threshold in Celsius    // unnecessary
int lcd_key = 0;
int adc_key_in = 0;
int check_key = 0;
int high = 300;                                      // unnecessary
int low = 20;                                        // unnecessary
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
double Setpoint[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

//Specify the links and initial tuning parameters
PID myPID(&Input, &Output, &UpdatedSetpoint,5,5,0.1, DIRECT);

int irReceiverPin = 3;
IRrecv irrecv(irReceiverPin);
decode_results results;

void setup()
{

  irrecv.enableIRIn();
  
  int startTemp = low; // start setting the Temp at 0.00            // unnecessary
  lcd.begin(16,2);
  pinMode(heaterPin,OUTPUT); // heaterPin is set as an output
  

  // Setpoint = setTemp;                                            // unnecessary
  
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
  
	Setpoint[0] = getTempCelsius();
        DisplayTime = Setpoint[7];
        Setpoint[8] = Setpoint[6];
        Setpoint[9] = Setpoint[7]+45;

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
        Serial.println(Setpoint[8]);
  	delay(5);
  	Serial.println(Setpoint[9]);
  	delay(5);
  
}


void loop()
{
  int seconds = millis()/1000;
  CurrentTime = seconds-t0;
  float TempCelsius = getTempCelsius();
  DisplayTime = Setpoint[9] - CurrentTime;

  Serial.println(getTempCelsius());
  
 
      if (irrecv.decode(&results)) {
        int RemoteValue = results.value;
        Serial.println(RemoteValue);
        irrecv.resume(); // Receive the next value
       }
  
  if (CurrentTime < Setpoint[3]) {
    UpdatedSetpoint = ramp(Setpoint, 3);
    UpdateLCD(Setpoint[2]);

    Error = UpdatedSetpoint - TempCelsius;
    Error = Error / UpdatedSetpoint;

    Serial.println(TempCelsius);
    //Serial.println("First If");
    //Serial.println("Current Time: ");    
    Serial.println(CurrentTime);
    //Serial.println("\n Updated Set Point: ");
    //Serial.print(UpdatedSetpoint);
    //Serial.println("\n Error: ");
    Serial.println(Error);
    //Serial.println("");
    delay(5); 
  }

  else if (CurrentTime < Setpoint[5]) {
    UpdatedSetpoint = ramp(Setpoint, 5);
    UpdateLCD(Setpoint[4]);

    Error = UpdatedSetpoint - TempCelsius;
    Error = Error / UpdatedSetpoint;

    Serial.println(TempCelsius);
    //Serial.println("Second If");
    //Serial.println("Current Time: ");
    Serial.println(CurrentTime);
    //Serial.println("\n Updated Set Point: ");
    //Serial.print(UpdatedSetpoint);
    //Serial.println("\n Error: ");
    Serial.println(Error);
    //Serial.println("");
    delay(5); 
  }
  
  else if (CurrentTime < Setpoint[7]) {
    UpdatedSetpoint = ramp(Setpoint, 7);
    UpdateLCD(Setpoint[6]);

    Error = UpdatedSetpoint - TempCelsius;
    Error = Error / UpdatedSetpoint;

    Serial.println(TempCelsius);
    //Serial.println("Last Case Structure");
    //Serial.println("Current Time: ");
    Serial.println(CurrentTime);
    //Serial.println("\n Updated Set Point: ");
    //Serial.print(UpdatedSetpoint);
    //Serial.println("\n Error: ");
    Serial.println(Error);
    //Serial.println("");
    delay(5);   
  }
  
  else if (CurrentTime < Setpoint[9]) {
    UpdatedSetpoint = ramp(Setpoint, 9);
    UpdateLCD(Setpoint[8]);

    Error = UpdatedSetpoint - TempCelsius;
    Error = Error / UpdatedSetpoint;
    
    Serial.println(TempCelsius);
    //Serial.println("Last Case Structure");
    //Serial.println("Current Time: ");
    Serial.println(CurrentTime);
    //Serial.println("\n Updated Set Point: ");
    //Serial.print(UpdatedSetpoint);
    //Serial.println("\n Error: ");
    Serial.println(Error);
    //Serial.println("");
    delay(5);   
  }

  else {
    lcd.clear();
    digitalWrite(heaterPin,LOW);
    lcd.print("You're through!");
    lcd.print("Temp: ");
    lcd.print(TempCelsius);
    Serial.println(TempCelsius);
    Serial.println(CurrentTime);
    Serial.println("NA");
    delay(1000);
  }
  Serial.println("Button Press Number:");
  Serial.println(results.value);
  
  if (irrecv.decode(&results)) {
        int RemoteValue = results.value;
        if (RemoteValue == 8415) {
        while (true) {                // 0 button push case
            lcd.clear();
            lcd.print("Arduino");
            lcd.setCursor(0,1);
            lcd.print("Interrupted");
            digitalWrite(heaterPin, LOW);
            delay(1000);
            }
        }
       }
  
  

  
  // if (analogRead(0)<1023){
  //  while(true)
  //  {
  //    Serial.println("ABORT!");
  //    digitalWrite(heaterPin, LOW);
  //  }
}

void UpdateLCD(double target)
  { 
  lcd.clear();
  heaterdisplay(target);
  delay(750);
  lcd.clear();
  heatersaftey();
  delay(750); 
    
}
