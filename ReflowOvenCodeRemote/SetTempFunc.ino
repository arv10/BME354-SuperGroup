// ---------------------- Functions to record user inputs of temperature and time ------------------------------

// Initializing variables to be used
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
      
      if (cursorPos >= 3) {                                     // If the cursor position is moved "right" of the rightward most position, cursor wraps around to most leftward digit
        cursorPos = 0; }
      
      SetValue = 100*digits[0]+10*digits[1]+digits[2];          // Calculating numerical value based on digits
      
      
      // This block of code displays the number of available digits
      // and updates the position of each based on user input
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
            if (SetValue>300 || SetValue<20)            // If the input is greater than or equal to 300, or less than 20, the LCD displays "Invalid Input" and requires an allowable input.
          {lcd.clear();
           lcd.print("Invalid Input");}
            else
            {          
            t0 = millis()/1000;                         // Variable t0 is the time when the reflow curve begins from the program was run
            
            lcd.clear();                                
            if (i%2 == 0) {                             // LCD screen displays the set temperature after chosen by user
              lcd.print("The Temperature ");       
              lcd.setCursor(0,1);
              lcd.print("is ");
              lcd.print(SetValue);
            }
            else {                                      // LCD screen displays the set time after chosen by user
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
      cursorPos = cursorPos + 1;                        // shifts the cursor right after each loop
      }
      else {
       lcd.setCursor(cursorPos,1);
       lcd.print(" "); 
       delay(100); }


  }
      

}
