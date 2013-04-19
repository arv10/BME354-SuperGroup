
#define btnRIGHT 0
#define btnUP 1
#define btnDOWN 2
#define btnLEFT 3
#define btnSELECT 4
#define btnNONE 5

#define V1 0+50
#define V2 99+50
#define V3 255+50
#define V4 409+50
#define V5 639+50
#define VNONE 1023

int read_LCD_buttons()
{
  adc_key_in = analogRead(0);    // read the value from the sensor
  if (adc_key_in > VNONE) return btnNONE;
  if (adc_key_in < V1) return btnRIGHT;
  if (adc_key_in < V2) return btnUP;
  if (adc_key_in < V3) return btnDOWN;
  if (adc_key_in < V4) return btnLEFT;
  if (adc_key_in < V5) return btnSELECT;
  return btnNONE;        // when all others fail, return this...
}

void heatersaftey(double thesettemperature) // saftey function
{
 int currentTemp = analogRead(tempPin);
  float TempVolt = currentTemp*(5/1023);
  float TempCelsius = TempVolt/(0.005); // test linear relationship
  
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
     currentTemp = analogRead(tempPin);
     TempVolt = currentTemp*(5/1023);
     TempCelsius = TempVolt/(0.005);
     delay(1000);}
}

void heaterdisplay(double setTemps) // display function
{
  int currentTemp = analogRead(tempPin);
  float TempVolt = currentTemp*(5/1023);
  float TempCelsius = TempVolt/(0.005); // test linear relationship
  
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
