// ------------------ Initializing variables to be called in subsequent functions -----------------------------

int currentTemp = analogRead(tempPin);                                    // Reading binary values from 0 to 1023 as proxy for temperature
float TempVolt = currentTemp*5;                                           // Converting binary values to analog voltages from 0 to 5 V
float TempVoltInt = TempVolt/1023;
float TempCelsius = TempVoltInt/0.005;                                    // Converting analog voltage to temperature measurements        

// ------------------ Functions called in master code ---------------------------------------------------------

// Function to read temperature in degrees Celsius
double getTempCelsius() { 
  currentTemp = analogRead(tempPin);                                      // Reading binary values from 0 to 1023 as proxy for temperature
  TempVolt = currentTemp*5;                                               // Converting binary values to analog voltages from 0 to 5 V
  TempVolt = TempVolt/1023;
  return TempVolt/0.005;                                                  // Converting analog voltage to temperature measurements
  }

void heatersaftey() // saftey function
{
 TempCelsius = getTempCelsius();
  
  if (TempCelsius < UpdatedSetpoint) {
     digitalWrite(heaterPin,HIGH);
     lcd.setCursor(0,0);
     lcd.print("Heater ON!");
     lcd.setCursor(0, 1);
     lcd.print("Err:");
     lcd.print(Error);
     lcd.print(" T-");
     lcd.print(DisplayTime);}
  else {
     digitalWrite(heaterPin,LOW);
     lcd.setCursor(0,0);
     lcd.print("Heater OFF");
     lcd.setCursor(0, 1);
     lcd.print("Err:");
     lcd.print(Error);    
     lcd.print(" T-");
     lcd.print(DisplayTime);}
   
  while (TempCelsius >= 300) {
     lcd.setCursor(0,0);
     lcd.print("RUN AWAY!!");
     lcd.setCursor(0,1);
     lcd.print("Critical Temp!"); 
     TempCelsius = getTempCelsius();
     delay(1000);}
}

void heaterdisplay(double setTemps) // display function
{
  TempCelsius = getTempCelsius();
  
  if (TempCelsius < UpdatedSetpoint) {
     digitalWrite(heaterPin,HIGH); }
  else {
     digitalWrite(heaterPin,LOW); }
    
     lcd.setCursor(0,0);
     lcd.print("Current T:");
     lcd.print(TempCelsius);
     lcd.print("C");
     lcd.setCursor(0,1);
     lcd.print("Set T:");
     lcd.print(setTemps);
     lcd.print("C");
}
  
double ramp(double Setpoint[], int k)
{
    Input = getTempCelsius();
    // t0 is the variable that we use when we press select
    float time;
    delay(10); // checks the slope every .01 second
    time = millis()/1000-t0-Setpoint[k-2];
      
    float den = Setpoint[k]-Setpoint[k-2];
    float num=Setpoint[k-1]-Setpoint[k-3];
    UpdatedSetpoint=num*time/den+Setpoint[k-3];
    myPID.Compute();
    analogWrite(heaterPin,Output);
    return UpdatedSetpoint;
}
