double setRemote(int i) 
{
  int checkck = 0;
  int RemoteValue;
  int digits[] = {0, 0, 0};
  int SetValue;
  int cursorPos = 0;
  int buttonPushed = 0;
  
  while (checkck == 0) 
  {
      
      if (cursorPos >= 3) {
        cursorPos = 0; }
      
      SetValue = 100*digits[0]+10*digits[1]+digits[2];
      
      lcd.setCursor(0,1);
      if (buttonPushed == 0) {
        lcd.print("___"); }
      else if (buttonPushed == 1) {
        lcd.print(digits[0]);
        lcd.print("__"); }
      else if (buttonPushed == 2) {
        lcd.print(digits[0]);
        lcd.print(digits[1]);
        lcd.print("_"); }
      else {
        lcd.print(digits[0]);
        lcd.print(digits[1]);
        lcd.print(digits[2]); }
      delay(100);
        
      if (irrecv.decode(&results)) {
        RemoteValue = results.value;
        Serial.println(RemoteValue);
        irrecv.resume(); // Receive the next value
        buttonPushed = buttonPushed + 1;
    
        switch(RemoteValue)
        {
          case 4335: {                // 0 button push case
            digits[cursorPos] = 0;
            break; }
          case 12495: {               // 1 button push case
            digits[cursorPos] = 1;
            break; }
          case -20401: {              // 2 button push case
            digits[cursorPos] = 2;
            break; }
          case 28815: {               // 3 button push case
            digits[cursorPos] = 3;
            break; }
          case 2295: {                // 4 button push case
            digits[cursorPos] = 4;
            break; }
          case -30601: {              // 5 button push case
            digits[cursorPos] = 5;
            break; }
          case 18615: {               // 6 button push case
            digits[cursorPos] = 6;
            break; }
          case 10455: {               // 7 button push case
            digits[cursorPos] = 7;
            break; }
          case -22441: {              // 8 button push case
            digits[cursorPos] = 8;
            break; }
          case 26775: {               // 9 button push case
            digits[cursorPos] = 9;
            break; }
          case 255: {                 // play button push case "Select"
            if (SetValue>300 || SetValue<20)
          {lcd.clear();
           lcd.print("Invalid Input");}
            else
            {          
            t0 = millis()/1000;
            
            lcd.clear();
            if (i%2 == 0) {
              lcd.print("The Temperature ");       
              lcd.setCursor(0,1);
              lcd.print("is ");
              lcd.print(SetValue);
            }
            else {
              lcd.print("The Set Time ");       
              lcd.setCursor(0,1);
              lcd.print("is ");
              lcd.print(SetValue);
            }
            delay(1000);
            return SetValue;
            }
          }
      }
      cursorPos = cursorPos + 1;
      }
      else {
       lcd.setCursor(cursorPos,1);
       lcd.print(" "); 
       delay(100); }


  }
      

}
