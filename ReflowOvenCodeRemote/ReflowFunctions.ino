int currentTemp = analogRead(tempPin);
float TempVolt = currentTemp*5/1023;
float TempCelsius = TempVolt/0.005; // test linear relationship

double getTempCelsius() {
  currentTemp = analogRead(tempPin);
  TempVolt = currentTemp*5/1023;
  return TempVolt/(0.005); // test linear relationship
  }

void heatersaftey(double thesettemperature) // saftey function
{
 TempCelsius = getTempCelsius();
  
  if (TempCelsius < thesettemperature) {
     digitalWrite(heaterPin,HIGH);
     lcd.setCursor(0,0);
     lcd.print("Heater ON!"); }
  else {
     digitalWrite(heaterPin,LOW);
     lcd.setCursor(0,0);
     lcd.print("Heater OFF"); }
   
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
  
  if (TempCelsius < setTemp) {
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
    // t0 is the variable tht we use when we press select
    
    delay(10); // checks the slope every .01 second
    float time = millis()-t0;
    float den = Setpoint[k]-Setpoint[k-2];
    float num=Setpoint[k-1]-Setpoint[k-3];
    UpdatedSetpoint=num*time/den+23;
    myPID.Compute();
    analogWrite(heaterPin,Output);
    return UpdatedSetpoint;
}

