double setthetemperature()
{
  int settemperature = low; // the threshold value
  int checkck = 0; 

  while (checkck == 0) {
      lcd_key = read_LCD_buttons();

  
  switch (lcd_key)   
  {
  // depending on which button was pushed, we perform an act:
    case btnRIGHT:      // Instructions for what to do on RIGHT button press
      {
        if (cursorPos < 2) {
             cursorPos = cursorPos + 1; }
        else if (cursorPos == 2) {
          cursorPos = 0;}
          
        lcd.setCursor(cursorPos,1);
        break;
      }
    case btnLEFT:       // Instructions for what to do on LEFT button press
      {
      if (cursorPos > 0) {
             cursorPos = cursorPos - 1; }
      else if (cursorPos == 0) {
        cursorPos = 2; }

        lcd.setCursor(cursorPos,1);
        break; 
      }
    case btnUP:
      {
        lcd.setCursor(cursorPos,1);
        if (cursorPos == 0 && settemperature < 201) {
          settemperature = settemperature + 100; }
        else if (cursorPos == 1 && settemperature < 291) {
          settemperature = settemperature + 10; }
        else if (cursorPos == 2 && settemperature < 300) {
          settemperature = settemperature + 1; }
        
        break;
      }
    case btnDOWN:
      {
        lcd.setCursor(cursorPos,1);
        if (cursorPos == 0 && settemperature > 119) {
          settemperature = settemperature - 100; }
        else if (cursorPos == 1 && settemperature > 29) {
          settemperature = settemperature - 10; }
        else if (cursorPos == 2 && settemperature > 20) {
          settemperature = settemperature - 1; }
        break;
      }
      case btnSELECT:
      {
        int checker=0;

        lcd.setCursor(0,0);
        lcd.println("The Temperature ");       
        lcd.setCursor(0,1);
        lcd.print("is ");
        lcd.print(settemperature);
        setTemp = settemperature;
        shouldwesetthetemperature=1;
        delay(1000);
        return setTemp=settemperature;
      }
      case btnNONE:
      {
      // Instructions for what to do if no button is pressed.
       lcd.setCursor(cursorPos,1);
       lcd.print("_");
       delay(100);
      
       lcd.setCursor(0,1);
       lcd.print("                     ");
       if (settemperature < 100) {
       lcd.setCursor(1,1);
       lcd.print(settemperature); }
       else {
       lcd.setCursor(0,1);
       lcd.print(settemperature);
       }
       delay(50);
       break;
      }
  }
  delay(100);
  }
}
