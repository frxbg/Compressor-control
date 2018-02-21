/* ===================================================================== *
 *                                                                       *
   DISPLAY SYSTEM
 *                                                                       *
   =====================================================================
   every "disp menu function" needs three functions
   - void LCDML_DISP_setup(func_name)
   - void LCDML_DISP_loop(func_name)
   - void LCDML_DISP_loop_end(func_name)

   EXAMPLE CODE:
    void LCDML_DISP_setup(..menu_func_name..)
    {
      // setup
      // is called only if it is started

      // starts a trigger event for the loop function every 100 millisecounds
      LCDML_DISP_triggerMenu(100);
    }

    void LCDML_DISP_loop(..menu_func_name..)
    {
      // loop
      // is called when it is triggert
      // - with LCDML_DISP_triggerMenu( millisecounds )
      // - with every button status change

      // check if any button is presed (enter, up, down, left, right)
      if(LCDML_BUTTON_checkAny()) {
        LCDML_DISP_funcend();
      }
    }

    void LCDML_DISP_loop_end(..menu_func_name..)
    {
      // loop end
      // this functions is ever called when a DISP function is quit
      // you can here reset some global vars or do nothing
    }
   =====================================================================
*/

// *********************************************************************
void LCDML_DISP_setup(LCDML_FUNC_initscreen)
// *********************************************************************
{
  // setup function

}

void LCDML_DISP_loop(LCDML_FUNC_initscreen)
{

  lcd.setCursor(0, 0);
  lcd.print("Running: ");
  if (Comp1Stat == 1) {
    lcd.setCursor(9, 0);
    lcd.print("1");
  }
  if (Comp1Stat == 0) {
    lcd.setCursor(9, 0);
    lcd.print("_");
  }
  if (Comp2Stat == 1) {
    lcd.setCursor(10, 0);
    lcd.print("1");
  }
  if (Comp2Stat == 0) {
    lcd.setCursor(10, 0);
    lcd.print("_");
  }
  lcd.setCursor(12, 0);
  int OUT = Output;
  lcd.print(Output);
  lcd.setCursor(15, 0);
  lcd.print("%");
  lcd.setCursor(0, 1);
  lcd.print("IN:");
  lcd.setCursor(3, 1);
  lcd.print(Input);
  lcd.setCursor(7, 1);
  lcd.print(" ");
  lcd.setCursor(8, 1);
  lcd.print("SET:");
  lcd.setCursor(12, 1);
  lcd.print(Setpoint);
  lcd.setCursor(16, 1);
  lcd.print(" ");

  // loop function, can be run in a loop when LCDML_DISP_triggerMenu(xx) is set
  // the quit button works in every DISP function without any checks; it starts the loop_end function

  if (LCDML_BUTTON_checkAny()) { // check if any button is presed (enter, up, down, left, right)
    if (LCDML_BUTTON_checkEnter()) // check if button left is pressed
    {
      LCDML_BUTTON_resetEnter(); // reset the left button
      LCDML_DISP_funcend();
    }
  }
}

void LCDML_DISP_loop_end(LCDML_FUNC_initscreen)
{
  // this functions is ever called when a DISP function is quit
  // you can here reset some global vars or do nothing
}


//*********************************************************************
void LCDML_DISP_setup(LCDML_FUNC_MaxWorkT)
// *********************************************************************
{
  // setup function
  // print lcd content

  lcd.setCursor(0, 0);
  lcd.print(F("press up or down"));
  lcd.setCursor(0, 1);
  lcd.print(F("STime:          "));
  // Reset Button Value
  lcd.setCursor(8, 1); // set cursor
  lcd.print(MaxWorkT); // print change content
}

void LCDML_DISP_loop(LCDML_FUNC_MaxWorkT)
{
  // loop function, can be run in a loop when LCDML_DISP_triggerMenu(xx) is set
  // the quit button works in every DISP function without any checks; it starts the loop_end function

  if (LCDML_BUTTON_checkAny()) // check if any button is pressed (enter, up, down, left, right)
  {
    if (LCDML_BUTTON_checkUp()) // check if button left is pressed
    {
      LCDML_BUTTON_resetUp(); // reset the left button
      MaxWorkT++;

      // update lcd content
      lcd.setCursor(8, 1); // set cursor
      lcd.print(MaxWorkT); // print change content
    }

    if (LCDML_BUTTON_checkDown()) // check if button left is pressed
    {
      LCDML_BUTTON_resetDown(); // reset the left button
      MaxWorkT--;

      // update lcd content
      lcd.setCursor(8, 2); // set cursor
      lcd.print(MaxWorkT); // print change content
    }
  }

  if (LCDML_BUTTON_checkEnter()) // check if button left is pressed
  {
    LCDML_BUTTON_resetEnter(); // reset the left button

    // update lcd content
    lcd.setCursor(0, 3); // set cursor
    lcd.print("EXIT"); // print change content
    delay(1000);
    LCDML_DISP_funcend();
  }
}


void LCDML_DISP_loop_end(LCDML_FUNC_MaxWorkT)
{
  // this functions is ever called when a DISP function is quit
  // you can here reset some global vars or do nothing
}


// *********************************************************************
double g_button_value1 = 0; // button value counter (global variable)
void LCDML_DISP_setup(LCDML_FUNC_Set)
// *********************************************************************
{
  // setup function
  // print lcd content
  lcd.setCursor(0, 0);
  lcd.print(F("press up or down"));
  lcd.setCursor(0, 1);
  lcd.print(F("Setpoint:       "));
  // Reset Button Value
  g_button_value1 = Setpoint;
  lcd.setCursor(10, 1); // set cursor
  lcd.print(g_button_value1); // print change content
}

void LCDML_DISP_loop(LCDML_FUNC_Set)
{
  // loop function, can be run in a loop when LCDML_DISP_triggerMenu(xx) is set
  // the quit button works in every DISP function without any checks; it starts the loop_end function

  if (LCDML_BUTTON_checkAny()) // check if any button is pressed (enter, up, down, left, right)
  {
    if (LCDML_BUTTON_checkUp()) // check if button left is pressed
    {
      LCDML_BUTTON_resetUp(); // reset the left button
      g_button_value1 = g_button_value1 + 0.1;

      // update lcd content
      lcd.setCursor(10, 1); // set cursor
      lcd.print(g_button_value1); // print change content
    }

    if (LCDML_BUTTON_checkDown()) // check if button left is pressed
    {
      LCDML_BUTTON_resetDown(); // reset the left button
      g_button_value1 = g_button_value1 - 0.1;

      // update lcd content
      lcd.setCursor(10, 1); // set cursor
      lcd.print(g_button_value1); // print change content
    }
    if (LCDML_BUTTON_checkEnter()) // check if button left is pressed
    {
      LCDML_BUTTON_resetDown(); // reset the left button
      Setpoint = g_button_value1;

      // update lcd content
      lcd.setCursor(10, 1); // set cursor
      lcd.print("Saved"); // print change content
      delay(1000);
      LCDML_DISP_funcend();
    }
  }
}

void LCDML_DISP_loop_end(LCDML_FUNC_Set)
{
  // this functions is ever called when a DISP function is quit
  // you can here reset some global vars or do nothing
}

// *********************************************************************
int g_button_value2 = 0; // button value counter (global variable)
void LCDML_DISP_setup(LCDML_FUNC_tuneP)
// *********************************************************************
{
  // setup function
  // print lcd content
  lcd.setCursor(0, 0);
  lcd.print(F("press up or down"));
  lcd.setCursor(0, 1);
  lcd.print(F("Tune P:         "));
  // Reset Button Value
  g_button_value2 = kp;
  lcd.setCursor(9, 1); // set cursor
  lcd.print(g_button_value2); // print change content
}

void LCDML_DISP_loop(LCDML_FUNC_tuneP)
{
  // loop function, can be run in a loop when LCDML_DISP_triggerMenu(xx) is set
  // the quit button works in every DISP function without any checks; it starts the loop_end function

  if (LCDML_BUTTON_checkAny()) // check if any button is pressed (enter, up, down, left, right)
  {
    if (LCDML_BUTTON_checkUp()) // check if button left is pressed
    {
      LCDML_BUTTON_resetUp(); // reset the left button
      g_button_value2++;

      // update lcd content
      lcd.setCursor(9, 1); // set cursor
      lcd.print(g_button_value2); // print change content
    }

    if (LCDML_BUTTON_checkDown()) // check if button left is pressed
    {
      LCDML_BUTTON_resetDown(); // reset the left button
      g_button_value2--;

      // update lcd content
      lcd.setCursor(9, 1); // set cursor
      lcd.print(g_button_value2); // print change content
    }
    if (LCDML_BUTTON_checkEnter()) // check if button left is pressed
    {
      LCDML_BUTTON_resetEnter(); // reset the left button
      kp = g_button_value2;

      // update lcd content
      lcd.setCursor(9, 1); // set cursor
      lcd.print("Saved"); // print change content
      delay(1000);
      LCDML_DISP_funcend();
    }
  }
}

void LCDML_DISP_loop_end(LCDML_FUNC_tuneP)
{
  // this functions is ever called when a DISP function is quit
  // you can here reset some global vars or do nothing
}
int g_button_value3 = 0; // button value counter (global variable)
void LCDML_DISP_setup(LCDML_FUNC_tuneI)
// *********************************************************************
{
  // setup function
  // print lcd content
  lcd.setCursor(0, 0);
  lcd.print(F("press up or down"));
  lcd.setCursor(0, 1);
  lcd.print(F("Tune I:         "));
  // Reset Button Value
  g_button_value3 = ki;
  lcd.setCursor(9, 1); // set cursor
  lcd.print(g_button_value3); // print change content
}

void LCDML_DISP_loop(LCDML_FUNC_tuneI)
{
  // loop function, can be run in a loop when LCDML_DISP_triggerMenu(xx) is set
  // the quit button works in every DISP function without any checks; it starts the loop_end function

  if (LCDML_BUTTON_checkAny()) // check if any button is pressed (enter, up, down, left, right)
  {
    if (LCDML_BUTTON_checkUp()) // check if button left is pressed
    {
      LCDML_BUTTON_resetUp(); // reset the left button
      g_button_value3++;

      // update lcd content
      lcd.setCursor(9, 1); // set cursor
      lcd.print(g_button_value3); // print change content
    }

    if (LCDML_BUTTON_checkDown()) // check if button left is pressed
    {
      LCDML_BUTTON_resetDown(); // reset the left button
      g_button_value3--;

      // update lcd content
      lcd.setCursor(9, 1); // set cursor
      lcd.print(g_button_value3); // print change content
    }
    if (LCDML_BUTTON_checkEnter()) // check if button left is pressed
    {
      LCDML_BUTTON_resetEnter(); // reset the left button
      ki = g_button_value3;

      // update lcd content
      lcd.setCursor(9, 1); // set cursor
      lcd.print("Saved"); // print change content
      delay(1000);
      LCDML_DISP_funcend();

    }
  }
}

void LCDML_DISP_loop_end(LCDML_FUNC_tuneI)
{
  // this functions is ever called when a DISP function is quit
  // you can here reset some global vars or do nothing
}

int g_button_value4 = 0; // button value counter (global variable)
void LCDML_DISP_setup(LCDML_FUNC_tuneD)
// *********************************************************************
{
  // setup function
  // print lcd content
  lcd.setCursor(0, 0);
  lcd.print(F("press up or down"));
  lcd.setCursor(0, 1);
  lcd.print(F("Tune D:         "));
  // Reset Button Value
  g_button_value4 = kd;
  lcd.setCursor(9, 1); // set cursor
  lcd.print(g_button_value4); // print change content
}

void LCDML_DISP_loop(LCDML_FUNC_tuneD)
{
  // loop function, can be run in a loop when LCDML_DISP_triggerMenu(xx) is set
  // the quit button works in every DISP function without any checks; it starts the loop_end function

  if (LCDML_BUTTON_checkAny()) // check if any button is pressed (enter, up, down, left, right)
  {
    if (LCDML_BUTTON_checkUp()) // check if button left is pressed
    {
      LCDML_BUTTON_resetUp(); // reset the left button
      g_button_value4++;

      // update lcd content
      lcd.setCursor(9, 1); // set cursor
      lcd.print(g_button_value4); // print change content
    }

    if (LCDML_BUTTON_checkDown()) // check if button left is pressed
    {
      LCDML_BUTTON_resetDown(); // reset the left button
      g_button_value4--;

      // update lcd content
      lcd.setCursor(9, 1); // set cursor
      lcd.print(g_button_value4); // print change content
    }
    if (LCDML_BUTTON_checkEnter()) // check if button left is pressed
    {
      LCDML_BUTTON_resetEnter(); // reset the left button
      kd = g_button_value4;

      // update lcd content
      lcd.setCursor(9, 1); // set cursor
      lcd.print("Saved"); // print change content
      delay(1000);
      LCDML_DISP_funcend();
    }
  }

  // check if button count is three
  //  if (g_button_value4 >= 53) {
  // end function for callback
  //   LCDML_DISP_funcend();
  //  }
}

void LCDML_DISP_loop_end(LCDML_FUNC_tuneD)
{
  // this functions is ever called when a DISP function is quit
  // you can here reset some global vars or do nothing
}

// *********************************************************************
int g_button_value5 = 0; // button value counter (global variable)
void LCDML_DISP_setup(LCDML_FUNC_SampleTime)
// *********************************************************************
{
  // setup function
  // print lcd content
  lcd.setCursor(0, 0);
  lcd.print(F("press up or down"));
  lcd.setCursor(0, 1);
  lcd.print(F("STime:          "));
  // Reset Button Value
  g_button_value5 = SampleTime;
  lcd.setCursor(8, 1); // set cursor
  lcd.print(g_button_value5); // print change content

}

void LCDML_DISP_loop(LCDML_FUNC_SampleTime)
{
  // loop function, can be run in a loop when LCDML_DISP_triggerMenu(xx) is set
  // the quit button works in every DISP function without any checks; it starts the loop_end function

  if (LCDML_BUTTON_checkAny()) // check if any button is pressed (enter, up, down, left, right)
  {
    if (LCDML_BUTTON_checkUp()) // check if button left is pressed
    {
      LCDML_BUTTON_resetUp(); // reset the left button
      g_button_value5 = g_button_value5 + 1000;

      // update lcd content
      lcd.setCursor(8, 1); // set cursor
      lcd.print(g_button_value5); // print change content
    }

    if (LCDML_BUTTON_checkDown()) // check if button left is pressed
    {
      LCDML_BUTTON_resetDown(); // reset the left button
      g_button_value5 = g_button_value5 - 100;

      // update lcd content
      lcd.setCursor(8, 1); // set cursor
      lcd.print(g_button_value5); // print change content
    }
    if (LCDML_BUTTON_checkEnter()) // check if button left is pressed
    {
      LCDML_BUTTON_resetEnter(); // reset the left button
      SampleTime = g_button_value5;

      // update lcd content
      lcd.setCursor(8, 1); // set cursor
      lcd.print("Saved"); // print change content
      delay(1000);
      LCDML_DISP_funcend();
    }
  }

  // check if button count is three
  //  if (g_button_value1 >= 53) {
  // end function for callback
  //    LCDML_DISP_funcend();
  //  }
}

void LCDML_DISP_loop_end(LCDML_FUNC_SampleTime)
{
  // this functions is ever called when a DISP function is quit
  // you can here reset some global vars or do nothing
}


// *********************************************************************
uint8_t g_button_value6 = 0; // button value counter (global variable)
void LCDML_DISP_setup(LCDML_FUNC_CompNum)
// *********************************************************************
{
  // setup function
  // print lcd content
  lcd.setCursor(0, 0);
  lcd.print(F("press up or down"));
  lcd.setCursor(0, 1);
  lcd.print(F("Comp:          "));
  // Reset Button Value
  g_button_value6 = CompNum;
  lcd.setCursor(8, 1); // set cursor
  lcd.print(g_button_value6); // print change content

}

void LCDML_DISP_loop(LCDML_FUNC_CompNum)
{
  // loop function, can be run in a loop when LCDML_DISP_triggerMenu(xx) is set
  // the quit button works in every DISP function without any checks; it starts the loop_end function

  if (LCDML_BUTTON_checkAny()) // check if any button is pressed (enter, up, down, left, right)
  {
    if (LCDML_BUTTON_checkUp()) // check if button left is pressed
    {
      LCDML_BUTTON_resetUp(); // reset the left button
      g_button_value6++;

      if (g_button_value6 >= 3) {
        g_button_value6 = 2;
      }

      // update lcd content
      lcd.setCursor(8, 1); // set cursor
      lcd.print(g_button_value6); // print change content
    }

    if (LCDML_BUTTON_checkDown()) // check if button left is pressed
    {
      LCDML_BUTTON_resetDown(); // reset the left button
      g_button_value6--;

      if (g_button_value6 <= 0) {
        g_button_value6 = 1;
      }

      // update lcd content
      lcd.setCursor(8, 1); // set cursor
      lcd.print(g_button_value6); // print change content
    }
    if (LCDML_BUTTON_checkEnter()) // check if button left is pressed
    {
      LCDML_BUTTON_resetEnter(); // reset the left button
      CompNum = g_button_value6;

      // update lcd content
      lcd.setCursor(8, 1); // set cursor
      lcd.print("Saved"); // print change content
      StepsCoeficient = 100 / CompNum;
      delay(1000);
      LCDML_DISP_funcend();
    }
  }

  // check if button count is three
  //  if (g_button_value1 >= 53) {
  // end function for callback
  //    LCDML_DISP_funcend();
  //  }
}

void LCDML_DISP_loop_end(LCDML_FUNC_CompNum)
{
  // this functions is ever called when a DISP function is quit
  // you can here reset some global vars or do nothing
}

// *********************************************************************
uint8_t g_button_value7 = 0; // button value counter (global variable)
void LCDML_DISP_setup(LCDML_FUNC_AntiShortCicle)
// *********************************************************************
{
  // setup function
  // print lcd content
  lcd.setCursor(0, 0);
  lcd.print(F("press up or down"));
  lcd.setCursor(0, 1);
  lcd.print(F("Min.:          "));
  // Reset Button Value
  g_button_value7 = AntiShortCicle;
  lcd.setCursor(8, 1); // set cursor
  lcd.print(g_button_value7); // print change content

}

void LCDML_DISP_loop(LCDML_FUNC_AntiShortCicle)
{
  // loop function, can be run in a loop when LCDML_DISP_triggerMenu(xx) is set
  // the quit button works in every DISP function without any checks; it starts the loop_end function

  if (LCDML_BUTTON_checkAny()) // check if any button is pressed (enter, up, down, left, right)
  {
    if (LCDML_BUTTON_checkUp()) // check if button left is pressed
    {
      LCDML_BUTTON_resetUp(); // reset the left button
      g_button_value7++;

      // update lcd content
      lcd.setCursor(8, 1); // set cursor
      lcd.print(g_button_value7); // print change content
    }

    if (LCDML_BUTTON_checkDown()) // check if button left is pressed
    {
      LCDML_BUTTON_resetDown(); // reset the left button
      g_button_value7--;

      // update lcd content
      lcd.setCursor(8, 1); // set cursor
      lcd.print(g_button_value7); // print change content
    }
    if (LCDML_BUTTON_checkEnter()) // check if button left is pressed
    {
      LCDML_BUTTON_resetEnter(); // reset the left button
      AntiShortCicle = g_button_value7;

      // update lcd content
      lcd.setCursor(8, 1); // set cursor
      lcd.print("Saved"); // print change content
      delay(1000);
      LCDML_DISP_funcend();
    }
  }

  // check if button count is three
  //  if (g_button_value1 >= 53) {
  // end function for callback
  //    LCDML_DISP_funcend();
  //  }
}

void LCDML_DISP_loop_end(LCDML_FUNC_AntiShortCicle)
{
  // this functions is ever called when a DISP function is quit
  // you can here reset some global vars or do nothing
}

// *********************************************************************
uint8_t g_button_value8 = 0; // button value counter (global variable)
void LCDML_DISP_setup(LCDML_FUNC_StepDelay)
// *********************************************************************
{
  // setup function
  // print lcd content
  lcd.setCursor(0, 0);
  lcd.print(F("press up or down"));
  lcd.setCursor(0, 1);
  lcd.print(F("Sec.:          "));
  // Reset Button Value
  g_button_value8 = NextStep;
  lcd.setCursor(8, 1); // set cursor
  lcd.print(g_button_value8); // print change content

}

void LCDML_DISP_loop(LCDML_FUNC_StepDelay)
{
  // loop function, can be run in a loop when LCDML_DISP_triggerMenu(xx) is set
  // the quit button works in every DISP function without any checks; it starts the loop_end function

  if (LCDML_BUTTON_checkAny()) // check if any button is pressed (enter, up, down, left, right)
  {
    if (LCDML_BUTTON_checkUp()) // check if button left is pressed
    {
      LCDML_BUTTON_resetUp(); // reset the left button
      g_button_value8++;

      // update lcd content
      lcd.setCursor(8, 1); // set cursor
      lcd.print(g_button_value8); // print change content
    }

    if (LCDML_BUTTON_checkDown()) // check if button left is pressed
    {
      LCDML_BUTTON_resetDown(); // reset the left button
      g_button_value8--;

      // update lcd content
      lcd.setCursor(8, 1); // set cursor
      lcd.print(g_button_value8); // print change content
    }
    if (LCDML_BUTTON_checkEnter()) // check if button left is pressed
    {
      LCDML_BUTTON_resetEnter(); // reset the left button
      NextStep = g_button_value8;

      // update lcd content
      lcd.setCursor(8, 1); // set cursor
      lcd.print("Saved"); // print change content
      delay(1000);
      LCDML_DISP_funcend();
    }
  }

  // check if button count is three
  //  if (g_button_value1 >= 53) {
  // end function for callback
  //    LCDML_DISP_funcend();
  //  }
}

void LCDML_DISP_loop_end(LCDML_FUNC_StepDelay)
{
  // this functions is ever called when a DISP function is quit
  // you can here reset some global vars or do nothing
}

// *********************************************************************
uint8_t g_button_value9 = 0; // button value counter (global variable)
void LCDML_DISP_setup(LCDML_FUNC_FrostSet)
// *********************************************************************
{
  // setup function
  // print lcd content
  lcd.setCursor(0, 0);
  lcd.print(F("press up or down"));
  lcd.setCursor(0, 1);
  lcd.print(F("Set.:          "));
  // Reset Button Value
  g_button_value9 = FrostSet;
  lcd.setCursor(8, 1); // set cursor
  lcd.print(g_button_value9); // print change content

}

void LCDML_DISP_loop(LCDML_FUNC_FrostSet)
{
  // loop function, can be run in a loop when LCDML_DISP_triggerMenu(xx) is set
  // the quit button works in every DISP function without any checks; it starts the loop_end function

  if (LCDML_BUTTON_checkAny()) // check if any button is pressed (enter, up, down, left, right)
  {
    if (LCDML_BUTTON_checkUp()) // check if button left is pressed
    {
      LCDML_BUTTON_resetUp(); // reset the left button
      g_button_value9++;

      // update lcd content
      lcd.setCursor(8, 1); // set cursor
      lcd.print(g_button_value9); // print change content
    }

    if (LCDML_BUTTON_checkDown()) // check if button left is pressed
    {
      LCDML_BUTTON_resetDown(); // reset the left button
      g_button_value9--;

      // update lcd content
      lcd.setCursor(8, 1); // set cursor
      lcd.print(g_button_value9); // print change content
    }
    if (LCDML_BUTTON_checkEnter()) // check if button left is pressed
    {
      LCDML_BUTTON_resetEnter(); // reset the left button
      FrostSet = g_button_value9;

      // update lcd content
      lcd.setCursor(8, 1); // set cursor
      lcd.print("Saved"); // print change content
      delay(1000);
      LCDML_DISP_funcend();
    }
  }

  // check if button count is three
  //  if (g_button_value1 >= 53) {
  // end function for callback
  //    LCDML_DISP_funcend();
  //  }
}

void LCDML_DISP_loop_end(LCDML_FUNC_FrostSet)
{
  // this functions is ever called when a DISP function is quit
  // you can here reset some global vars or do nothing
}

// *********************************************************************
bool g_button_value10; // button value counter (global variable)
void LCDML_DISP_setup(LCDML_FUNC_PContCicle)
// *********************************************************************
{
  // setup function
  // print lcd content
  lcd.setCursor(0, 0);
  lcd.print(F("press up or down"));
  lcd.setCursor(0, 1);
  lcd.print(F("Set.:          "));
  // Reset Button Value
  g_button_value10 = PContCicle;
  lcd.setCursor(8, 1); // set cursor
  lcd.print(g_button_value10); // print change content

}

void LCDML_DISP_loop(LCDML_FUNC_PContCicle)
{
  // loop function, can be run in a loop when LCDML_DISP_triggerMenu(xx) is set
  // the quit button works in every DISP function without any checks; it starts the loop_end function

  if (LCDML_BUTTON_checkAny()) // check if any button is pressed (enter, up, down, left, right)
  {
    if (LCDML_BUTTON_checkUp()) // check if button left is pressed
    {
      LCDML_BUTTON_resetUp(); // reset the left button
      g_button_value10 = g_button_value10 + 1;

      // update lcd content
      lcd.setCursor(8, 1); // set cursor
      lcd.print(g_button_value10); // print change content
    }

    if (LCDML_BUTTON_checkDown()) // check if button left is pressed
    {
      LCDML_BUTTON_resetDown(); // reset the left button
      g_button_value10 = g_button_value10 - 1;

      // update lcd content
      lcd.setCursor(8, 1); // set cursor
      lcd.print(g_button_value10); // print change content
    }
    if (LCDML_BUTTON_checkEnter()) // check if button left is pressed
    {
      LCDML_BUTTON_resetEnter(); // reset the left button
      PContCicle = g_button_value10;

      // update lcd content
      lcd.setCursor(8, 1); // set cursor
      lcd.print("Saved"); // print change content
      delay(1000);
      LCDML_DISP_funcend();
    }
  }
}

void LCDML_DISP_loop_end(LCDML_FUNC_PContCicle)
{
  // this functions is ever called when a DISP function is quit
  // you can here reset some global vars or do nothing
}

// *********************************************************************
uint8_t g_button_value11; // button value counter (global variable)
void LCDML_DISP_setup(LCDML_FUNC_PStartDelay)
// *********************************************************************
{
  // setup function
  // print lcd content
  lcd.setCursor(0, 0);
  lcd.print(F("press up or down"));
  lcd.setCursor(0, 1);
  lcd.print(F("Set.:          "));
  // Reset Button Value
  g_button_value11 = PStartDelay;
  lcd.setCursor(8, 1); // set cursor
  lcd.print(g_button_value11); // print change content

}

void LCDML_DISP_loop(LCDML_FUNC_PStartDelay)
{
  // loop function, can be run in a loop when LCDML_DISP_triggerMenu(xx) is set
  // the quit button works in every DISP function without any checks; it starts the loop_end function

  if (LCDML_BUTTON_checkAny()) // check if any button is pressed (enter, up, down, left, right)
  {
    if (LCDML_BUTTON_checkUp()) // check if button left is pressed
    {
      LCDML_BUTTON_resetUp(); // reset the left button
      g_button_value11++;

      // update lcd content
      lcd.setCursor(8, 1); // set cursor
      lcd.print(g_button_value11); // print change content
    }

    if (LCDML_BUTTON_checkDown()) // check if button left is pressed
    {
      LCDML_BUTTON_resetDown(); // reset the left button
      g_button_value11--;

      // update lcd content
      lcd.setCursor(8, 1); // set cursor
      lcd.print(g_button_value11); // print change content
    }
    if (LCDML_BUTTON_checkEnter()) // check if button left is pressed
    {
      LCDML_BUTTON_resetEnter(); // reset the left button
      PStartDelay = g_button_value11;

      // update lcd content
      lcd.setCursor(8, 1); // set cursor
      lcd.print("Saved"); // print change content
      delay(1000);
      LCDML_DISP_funcend();
    }
  }
}

void LCDML_DISP_loop_end(LCDML_FUNC_PStartDelay)
{
  // this functions is ever called when a DISP function is quit
  // you can here reset some global vars or do nothing
}

// *********************************************************************
uint8_t g_button_value12 = 0; // button value counter (global variable)
void LCDML_DISP_setup(LCDML_FUNC_PStopDelay)
// *********************************************************************
{
  // setup function
  // print lcd content
  lcd.setCursor(0, 0);
  lcd.print(F("press up or down"));
  lcd.setCursor(0, 1);
  lcd.print(F("Set.:          "));
  // Reset Button Value
  g_button_value12 = PStopDelay;
  lcd.setCursor(8, 1); // set cursor
  lcd.print(g_button_value12); // print change content

}

void LCDML_DISP_loop(LCDML_FUNC_PStopDelay)
{
  // loop function, can be run in a loop when LCDML_DISP_triggerMenu(xx) is set
  // the quit button works in every DISP function without any checks; it starts the loop_end function

  if (LCDML_BUTTON_checkAny()) // check if any button is pressed (enter, up, down, left, right)
  {
    if (LCDML_BUTTON_checkUp()) // check if button left is pressed
    {
      LCDML_BUTTON_resetUp(); // reset the left button
      g_button_value12++;

      // update lcd content
      lcd.setCursor(8, 1); // set cursor
      lcd.print(g_button_value12); // print change content
    }

    if (LCDML_BUTTON_checkDown()) // check if button left is pressed
    {
      LCDML_BUTTON_resetDown(); // reset the left button
      g_button_value12--;

      // update lcd content
      lcd.setCursor(8, 1); // set cursor
      lcd.print(g_button_value12); // print change content
    }
    if (LCDML_BUTTON_checkEnter()) // check if button left is pressed
    {
      LCDML_BUTTON_resetEnter(); // reset the left button
      PStopDelay = g_button_value12;

      // update lcd content
      lcd.setCursor(8, 1); // set cursor
      lcd.print("Saved"); // print change content
      delay(1000);
      LCDML_DISP_funcend();
    }
  }
}

void LCDML_DISP_loop_end(LCDML_FUNC_PStopDelay)
{
  // this functions is ever called when a DISP function is quit
  // you can here reset some global vars or do nothing
}

// *********************************************************************
void LCDML_DISP_setup(LCDML_FUNC_Back)
// *********************************************************************
{
  LCDML_DISP_jumpToFunc(LCDML_FUNC_initscreen);
}

void LCDML_DISP_loop(LCDML_FUNC_Back)
{

}
void LCDML_DISP_loop_end(LCDML_FUNC_Back)
{
  // this functions is ever called when a DISP function is quit
  // you can here reset some global vars or do nothing
}

