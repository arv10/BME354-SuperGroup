// master code with temperature setting, heater control, and safety

// Daria is amazing; remember that (Jessica)
// Chocholate Diablo is hot

// --------- Initialization of variables and importing libraries --------

#include <LiquidCrystal.h>			// include LCD library
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

#include <PID_v1.h>				// include PID library
#include <IRremote.h>				// include Remote library

int lcd_key = 0;
int adc_key_in = 0;
int check_key = 0;
int cursorPos = 2;
double CurrentTime = 0;
double t0;
int DisplayTime;

//Define Variables we'll be connecting to
int heaterPin = 2; 				// create heater pin value
int tempPin = 5;    				// create termocouple pin value

double UpdatedSetpoint = 0;
double Error;
double Input, Output;
double Setpoint[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

//Specify the links and initial tuning parameters
PID myPID(&Input, &Output, &UpdatedSetpoint,5,5,0.1, DIRECT);


// Initialize Remote variables needed for receiving signal from the Remote Control
int irReceiverPin = 3;
IRrecv irrecv(irReceiverPin);
decode_results results;

void setup()
{

  irrecv.enableIRIn();					// enable the IR sensor to receive signal
  
  lcd.begin(16,2);
  pinMode(heaterPin,OUTPUT); 				// heaterPin is set as an output
  
  
  //turn the PID on
  myPID.SetMode(AUTOMATIC);
  
  Serial.begin(9600);
  Serial.println("code started");
  delay(5);

  // for loop to get user input for T1,T2,T3,t1,t2,t2 temperature and time values  
  for (int i = 2; i < 7; i = i+2) {
        lcd.clear();
        lcd.print("Set Temp, T");
        lcd.print(i/2);
        lcd.print(", C");
	Setpoint[i]=setRemote(i);		// calls the function which takes button 
        lcd.clear();				// inputs and returns a 3 digit temperature
        lcd.print("Set Time, t");
        lcd.print(i/2);
        lcd.print(", s");
	Setpoint[i+1]=setRemote(i+1);		// calls the function which takes button inputs 
						//and returns a 3 digit time
    }
  
	Setpoint[0] = getTempCelsius();
        DisplayTime = Setpoint[7];
        Setpoint[8] = Setpoint[6];
        Setpoint[9] = Setpoint[7]+45;

	// We understand that including the serial monitor commands increases memory
	// We printed into the serial monitor for our own benefit
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
  //Variables to calculate the current time since heating started
  
  int seconds = millis()/1000;
  CurrentTime = seconds-t0;
  float TempCelsius = getTempCelsius();
  DisplayTime = Setpoint[9] - CurrentTime;

  Serial.println(getTempCelsius());
  
  // ------- If,Else If,Else structure that executes ramping code (to calculate the new set point)
  // and updates the display based on the values associated with each phase of the reflow oven -------

  if (CurrentTime < Setpoint[3]) {			// ramp to soak
    UpdatedSetpoint = ramp(Setpoint, 3);
    UpdateLCD(Setpoint[2]);

    Error = UpdatedSetpoint - TempCelsius;
    Error = Error / UpdatedSetpoint;

    Serial.println(TempCelsius);
    Serial.println(CurrentTime);
    Serial.println(Error);
    delay(5); 
  }

  else if (CurrentTime < Setpoint[5]) {			// pre-heat/soak
    UpdatedSetpoint = ramp(Setpoint, 5);
    UpdateLCD(Setpoint[4]);

    Error = UpdatedSetpoint - TempCelsius;
    Error = Error / UpdatedSetpoint;

    Serial.println(TempCelsius);
    Serial.println(CurrentTime);
    Serial.println(Error);
    delay(5); 
  }
  
  else if (CurrentTime < Setpoint[7]) {			// ramp to peak
    UpdatedSetpoint = ramp(Setpoint, 7);
    UpdateLCD(Setpoint[6]);

    Error = UpdatedSetpoint - TempCelsius;
    Error = Error / UpdatedSetpoint;

    Serial.println(TempCelsius);
    Serial.println(CurrentTime);
    Serial.println(Error);
    delay(5);   
  }
  
  else if (CurrentTime < Setpoint[9]) {			// reflow
    UpdatedSetpoint = ramp(Setpoint, 9);
    UpdateLCD(Setpoint[8]);

    Error = UpdatedSetpoint - TempCelsius;
    Error = Error / UpdatedSetpoint;
    
    Serial.println(TempCelsius);
    Serial.println(CurrentTime);
    Serial.println(Error);
    delay(5);   
  }

  else {						// finished!
    lcd.clear();
    digitalWrite(heaterPin,LOW);			// the heater was turned off
    lcd.print("You're through!");                       // turn on the fan for expedited heating
    lcd.setCursor(0,1);			
    lcd.print("Temp: ");
    lcd.print(TempCelsius);
    Serial.println(TempCelsius);
    Serial.println(CurrentTime);
    Serial.println("NA");
    delay(1000);
  }
  
  // --------- Code for Interupt (if EQ button is pushed) --------
  if (irrecv.decode(&results)) {		
        int RemoteValue = results.value;
        if (RemoteValue == 8415) {			// Checks if EQ button was pushed
        while (true) {                			// Condition indicates infinite loop
            lcd.clear();
            lcd.print("Arduino,");
            lcd.setCursor(0,1);
            lcd.print("Interrupted");
            digitalWrite(heaterPin, LOW);		// Oven is turned off indefinitely
            delay(1000);
            }
        }
       }
  

}

void UpdateLCD(double target)				// function that updates the LCD display
  { 
  lcd.clear();
  heaterdisplay(target);				// Displays current temp, and user input set temp
  delay(750);						// Also turns heater on when appropriate
  lcd.clear();
  heatersaftey();					// Displays heater status, relative error, and time remaining
  delay(750); 						// Also turns heater on when appropriate

							// Due to the two 750 delays, 
							// the void loop takes 1.5 seconds to run each iteration
    
}
