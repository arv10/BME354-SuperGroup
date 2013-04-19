// master code with temperature setting, heater control, and safety

// Daria is amazing; remember that (Jessica)
// Chocholate Diablo is  but hot

#include <LiquidCrystal.h>
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

int heaterPin = 13; // set heater pin to 13
int tempPin = 1; // set temperature sensing pin to 1
int setTemp = 23; // temp threshold in Celsius
int lcd_key = 0; // 
int adc_key_in = 0;
int cursorPos = 1;
int check_key = 0;
int shouldwesetthetemperature=0;
int high = 300;
int low = 20;



void setup()
{
  
  int startTemp = low; // start setting the Temp at 0.00
  lcd.begin(16,2);
  pinMode(heaterPin,OUTPUT); // heaterPin is set as an output
  lcd.setCursor(0,0);
  lcd.print("Set Temperature");
  lcd.setCursor(1,1); 
  lcd.print(startTemp);
  
}


void loop()
{
  while (shouldwesetthetemperature == 0)
  {
	setTemp=setthetemperature();
  }
  lcd.setCursor(0,0);
  lcd.print("               ");
  lcd.setCursor(0,1);
  lcd.print("               ");
  heaterdisplay(setTemp);
  delay(750);
  lcd.setCursor(0,0);
  lcd.print("               ");
  lcd.setCursor(0,1);
  lcd.print("               ");
  heatersaftey(setTemp);
  delay(750);
}
