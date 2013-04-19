double setthetemperature()
{
  double settemperature; // the threshold value
  int checkck = 0; 
  
  lcd_key = read_LCD_buttons();
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
        int max = 9;
        if (cursorPos == 4)
        {
          if (digit[cursorPos-1] < max)
          {
            digit[cursorPos-1] = digit[cursorPos-1] + 1;
            lcd.print(digit[cursorPos-1]);
          }
          else
          {
            digit[cursorPos-1] = 0;
            lcd.print(digit[cursorPos-1]);
          }
        }
        else
        {
          if (digit[cursorPos] < 9)
          {
            digit[cursorPos] = digit[cursorPos] + 1;
            lcd.print(digit[cursorPos]);
          }
          else
          {
            digit[cursorPos] = 0;
            lcd.print(digit[cursorPos]);
          }
        }
        break;
      }
    case btnDOWN:
      {
        lcd.setCursor(cursorPos,1);
        int max = 9;
        
        if (cursorPos == 4)
        { 
          if (digit[cursorPos-1] == 0)
          {
            digit[cursorPos-1] = max;
            lcd.print(digit[cursorPos-1]);
          }
          else if (digit[cursorPos-1] <= max)
          {
            digit[cursorPos-1] = digit[cursorPos-1] - 1;
            lcd.print(digit[cursorPos-1]);
          }
        }
        else
        {
          if (digit[cursorPos] == 0)
          {
            digit[cursorPos] = 9;
            lcd.print(digit[cursorPos]);
          }
          else if (digit[cursorPos] <= 9)
          {
            digit[cursorPos] = digit[cursorPos] - 1;
            lcd.print(digit[cursorPos]);
          }
        }
        break;
      }
      case btnSELECT:
      {
        int checker=0;

        settemperature = 100*digit[0]+10*digit[1]+digit[2]+.1*digit[3];
        lcd.setCursor(0,0);
        lcd.println("The Temperature ");
        if (settemperature > high)
        {
          lcd.setCursor(0,1);
          lcd.println("is Too HIGH    ");
        }
        else if (settemperature < low)
        {
          lcd.setCursor(0,1);
          lcd.println("is Too LOW     ");
        }
        else
        {
    	checker = 1;
  	checkck = 1;
          lcd.setCursor(0,1);
          lcd.print("is ");
          lcd.print(settemperature);
  	lcd.print("      ");
        }
        int pause = 1;
        while (pause == 1) 
        {
                        delay(100);
                        check_key = 0;
                        check_key = read_LCD_buttons();
                        
                        if (check_key == 4) 
                          {
  				pause=pause+1;
  			if (checker == 0)
  			{
                          lcd.setCursor(0,0);
    			lcd.print("Set Temperature     ");
    			lcd.setCursor(0,1); 
    			lcd.print(digit[0]);
    			lcd.print(digit[1]);
    			lcd.print(digit[2]);
  			lcd.print('.'); 
    			lcd.print(digit[3]);
    			lcd.print("                      ");
  			}
                           }
    	}
        
      }
      case btnNONE:
      {
      // Instructions for what to do if no button is pressed.
       lcd.setCursor(cursorPos,1);
       lcd.print(" ");
       delay(100);
      
      lcd.setCursor(cursorPos,1);
      if (cursorPos > 2)
      {
        lcd.print(digit[cursorPos-1]);
      }
      else
      {
        lcd.print(digit[cursorPos]);
      }  
      }
  }
  }
}
