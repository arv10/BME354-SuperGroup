// ------------------ Initializing variables to be called in subsequent functions -----------------------------

int currentTemp = analogRead(tempPin);                  // Reading binary values from 0 to 1023 as proxy for temperature
float TempVolt = currentTemp*5;                         // Converting binary values to analog voltages from 0 to 5 V
float TempVoltInt = TempVolt/1023;
float TempCelsius = TempVoltInt/0.005;                  // Converting analog voltage to temperature measurements        

// ------------------ Functions called in master code ---------------------------------------------------------

// Function to read temperature in degrees Celsius
double getTempCelsius() { 
  currentTemp = analogRead(tempPin);                    // Reading binary values from 0 to 1023 as proxy for temperature
  TempVolt = currentTemp*5;                             // Converting binary values to analog voltages from 0 to 5 V
  TempVolt = TempVolt/1023;
  return TempVolt/0.005;                                // Converting analog voltage to temperature measurements
  }

// Function to turn heater on and off, and display state of heater, error, and time remaining
void heatersaftey() // saftey function
{
 TempCelsius = getTempCelsius();                        // Receiving temperature in degrees Celsius
  
  if (TempCelsius < UpdatedSetpoint) {                  // When the current temperature of the heater is less than the updated set temperature:
     digitalWrite(heaterPin,HIGH);                      // Heater is turned on
     lcd.setCursor(0,0);
     lcd.print("Heater ON!");                           // LCD displays that the heater is turned on
     lcd.setCursor(0, 1);
     lcd.print("Err:");                                                   
     lcd.print(Error);                                  // LCD displays the error
     lcd.print(" T-");                                
     lcd.print(DisplayTime);}                           // LCD displays the time remaining
  else {                                                // When the current temperature is greater than or equal to the updated set temperature:
     digitalWrite(heaterPin,LOW);                       // Heater is turned off                                         
     lcd.setCursor(0,0);  
     lcd.print("Heater OFF");                           // LCD displays that the heater is turned off
     lcd.setCursor(0, 1);
     lcd.print("Err:");
     lcd.print(Error);                                  // LCD displays the error
     lcd.print(" T-");
     lcd.print(DisplayTime);}                           // LCD displays the time remaining
   
  while (TempCelsius >= 300) {                          // When the current temperature is greater than or equal to 300 degrees Celsius:
     lcd.setCursor(0,0);
     lcd.print("RUN AWAY!!");                           // LCD displays "RUN AWAY!!"
     lcd.setCursor(0,1);
     lcd.print("Critical Temp!");                       // LCD displays "Critical Temp!"
     TempCelsius = getTempCelsius();
     delay(1000);}
}

// Function to turn heater on and off, and display current temperature and input temperatures from user during each region of reflow curve
void heaterdisplay(double setTemps) // display function
{
  TempCelsius = getTempCelsius();                       // Receiving temperature in degrees Celsius
  
  if (TempCelsius < UpdatedSetpoint) {                  // When the current temperature is less than the updated set temperature:
     digitalWrite(heaterPin,HIGH); }                    // Heater is turned on
  else {                                                // When the current temperature is greater than or equal to the updated set temperature:
     digitalWrite(heaterPin,LOW); }                     // Heater is turned off
    
     lcd.setCursor(0,0);
     lcd.print("Current T:");                                             
     lcd.print(TempCelsius);                            // LCD displays current temperature
     lcd.print("C");
     lcd.setCursor(0,1);
     lcd.print("Set T:");
     lcd.print(setTemps);                               // LCD displays input temperature from user for each region of reflow curve (end temperature of each region)
     lcd.print("C");
}

// Function to control updated set temperature in each region
double ramp(double Setpoint[], int k)
{
    Input = getTempCelsius();                           // Receiving temperature in degrees Celsius
                                                        // t0 is the absolute time from when the code began running the Select button is pressed to begin heating
    float time;                                         // Declaring time
    delay(10);                                          // Checks the updated set temperature every .01 second
    time = millis()/1000-t0-Setpoint[k-2];              // Time is made into a relative 
      
    float den = Setpoint[k]-Setpoint[k-2];              // Denominator of slope of temperature change (input time at end of region minus input time at beginning of region)
    float num=Setpoint[k-1]-Setpoint[k-3];              // Numerator of slope of temperature change (input temperature at end of region minus input temperature at beginning of region)
    UpdatedSetpoint=num*time/den+Setpoint[k-3];         // Linear equation for updated set temperature
    myPID.Compute();                                    // Using PID to determine PWM
    analogWrite(heaterPin,Output);                      // Turning heater on or off based on output of PID
    return UpdatedSetpoint;                             // Returning updated set temperature for comparison with heater's current temperature
}
