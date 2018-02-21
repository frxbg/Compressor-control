// ============================================================
// Example:     LCDML: display liquid crystal
// ============================================================
// Autor:       Nils Feldkämper
// Last update: 08.01.2017
// License:     MIT
// ============================================================
// Descripton:
// This example shows you, how to use this lib with LiquidCrystal
// lib. The LCD object have to create in this tab. In "LCDML_DISO"
// you can edit the layout of the menu. (content, cursor, scrollbar)
//
// When you rewrite this function, you can use every other LCD
// or graphic LCD Lib with this menu.
// ============================================================

// include libs
#include <LiquidCrystal.h>
//#include <LiquidCrystal_I2C.h>
#include <LCDMenuLib.h>
#include <PID_v1.h>
#include <math.h>
#include <EEPROM.h>
#include "MegunoLink.h"
#include "Filter.h"


// Working varibles
uint8_t AntiShortCicle;
uint8_t MaxWorkT;
uint8_t CompNum;
uint8_t NextStep;
uint8_t FrostSet;
uint8_t PStartDelay;
uint8_t PStopDelay;

bool StepChange;
bool FirstStart;
bool Comp1Stat;
bool Comp2Stat;
bool SwitchExt;
bool PContCicle;

unsigned long StartDelay = 0;
unsigned long StepDelay;
unsigned long RotateTime;
unsigned long TimeStep;
unsigned long WorkDelay;
unsigned long PStopTime;
unsigned long PStartTime;

int CurentLoad;
int StepsCoeficient;
int Steps;
int LastComp;
double WaterTemp;


// EEPROM addresses for persisted data
const int SpAddress = 0;
const int KpAddress = 4;
const int KiAddress = 8;
const int KdAddress = 12;
const int ATime = 16;
const int CompNumAdr = 17;
const int MaxWorkTAdr = 18;
const int NextStepAdr = 19;
const int FrostSetAdr = 20;
const int PContCicleAdr = 21;
const int PStartDelayAdr = 22;
const int PStopDelayAdr = 23;
const int STAddress = 40;


//Define Variables we'll be connecting to
double Setpoint, Input, Output;
int SampleTime;

//Specify the links and initial tuning parameters
double kp = 20, ki = 0, kd = 0;
PID myPID(&Input, &Output, &Setpoint, kp, ki, kd, DIRECT);

// Create a new exponential filter with a weight of 10 and initial value of 0.
ExponentialFilter<long> ADCFilter(20, 0);

// lib config
#define _LCDML_DISP_cfg_button_press_time          200    // button press time in ms
#define _LCDML_DISP_cfg_scrollbar                  1      // enable a scrollbar
#define _LCDML_DISP_cfg_cursor                     0x7E   // cursor Symbol 

// *********************************************************************
// LCDML TYPE SELECT
// *********************************************************************
// settings for lcd
#define _LCDML_DISP_cols             16
#define _LCDML_DISP_rows             2

// lcd object
// liquid crystal needs (rs, e, dat4, dat5, dat6, dat7)
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);
//LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);  // Set the LCD I2C address

const uint8_t scroll_bar[5][8] = {
  {B10001, B10001, B10001, B10001, B10001, B10001, B10001, B10001}, // scrollbar top
  {B11111, B11111, B10001, B10001, B10001, B10001, B10001, B10001}, // scroll state 1
  {B10001, B10001, B11111, B11111, B10001, B10001, B10001, B10001}, // scroll state 2
  {B10001, B10001, B10001, B10001, B11111, B11111, B10001, B10001}, // scroll state 3
  {B10001, B10001, B10001, B10001, B10001, B10001, B11111, B11111}  // scrollbar bottom
};

// *********************************************************************
// LCDML MENU/DISP
// *********************************************************************
// create menu
// menu element count - last element id
// this value must be the same as the last menu element
#define _LCDML_DISP_cnt    16

// LCDML_root        => layer 0
// LCDML_root_X      => layer 1
// LCDML_root_X_X    => layer 2
// LCDML_root_X_X_X  => layer 3
// LCDML_root_...    => layer ...

// LCDMenuLib_add(id, group, prev_layer_element, new_element_num, lang_char_array, callback_function)
LCDML_DISP_init(_LCDML_DISP_cnt);
LCDML_DISP_add      (0  , _LCDML_G1  , LCDML_root        , 1  , "initscreen"         , LCDML_FUNC_initscreen);
LCDML_DISP_add      (1  , _LCDML_G1  , LCDML_root        , 2  , "Comp Settings"      , LCDML_FUNC);
LCDML_DISP_add      (2  , _LCDML_G1  , LCDML_root_2      , 1  , "MaxWorkTime"        , LCDML_FUNC_MaxWorkT);
LCDML_DISP_add      (3  , _LCDML_G1  , LCDML_root_2      , 2  , "Setpoint"           , LCDML_FUNC_Set);
LCDML_DISP_add      (4  , _LCDML_G1  , LCDML_root_2      , 3  , "Tune P"             , LCDML_FUNC_tuneP);
LCDML_DISP_add      (5  , _LCDML_G1  , LCDML_root_2      , 4  , "Tune I"             , LCDML_FUNC_tuneI);
LCDML_DISP_add      (6  , _LCDML_G1  , LCDML_root_2      , 5  , "Tune D"             , LCDML_FUNC_tuneD);
LCDML_DISP_add      (7  , _LCDML_G1  , LCDML_root_2      , 6  , "Time window"        , LCDML_FUNC_SampleTime);
LCDML_DISP_add      (8  , _LCDML_G1  , LCDML_root_2      , 7  , "Number of Steps"    , LCDML_FUNC_CompNum);
LCDML_DISP_add      (9  , _LCDML_G1  , LCDML_root_2      , 8  , "Anti short"         , LCDML_FUNC_AntiShortCicle);
LCDML_DISP_add      (10 , _LCDML_G1  , LCDML_root_2      , 9  , "Step Delay"         , LCDML_FUNC_StepDelay);
LCDML_DISP_add      (11 , _LCDML_G1  , LCDML_root_2      , 10 , "Frost protect"      , LCDML_FUNC_FrostSet);
LCDML_DISP_add      (12 , _LCDML_G1  , LCDML_root        , 3  , "Pump Setting"       , LCDML_FUNC);
LCDML_DISP_add      (13 , _LCDML_G1  , LCDML_root_3      , 1  , "Cont. cicle"        , LCDML_FUNC_PContCicle);
LCDML_DISP_add      (14 , _LCDML_G1  , LCDML_root_3      , 2  , "Start Delay"        , LCDML_FUNC_PStartDelay);
LCDML_DISP_add      (15 , _LCDML_G1  , LCDML_root_3      , 3  , "Stop Delay"         , LCDML_FUNC_PStopDelay);
LCDML_DISP_add      (16 , _LCDML_G1  , LCDML_root_2      , 11 , "Back"               , LCDML_FUNC_Back);

LCDML_DISP_createMenu(_LCDML_DISP_cnt);



// *********************************************************************
// LCDML BACKEND (core of the menu, do not change here anything yet)
// *********************************************************************
// define backend function
#define _LCDML_BACK_cnt    1  // last backend function id

LCDML_BACK_init(_LCDML_BACK_cnt);
LCDML_BACK_new_timebased_dynamic (0  , ( 20UL )         , _LCDML_start  , LCDML_BACKEND_control);
LCDML_BACK_new_timebased_dynamic (1  , ( 1000UL )       , _LCDML_stop   , LCDML_BACKEND_menu);
LCDML_BACK_create();

#define _LCDML_DISP_cfg_initscreen                 1
#define _LCDML_DISP_cfg_initscreen_time            10000

// *********************************************************************
// SETUP
// *********************************************************************
void setup()
{

  pinMode(A5, INPUT_PULLUP);
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);

  // serial init; only be needed if serial control is used
  while (!Serial);                   // wait until serial ready
  Serial.begin(9600);                // start serial
  Serial.println(F(_LCDML_VERSION)); // only for examples

  // LCD Begin
  lcd.begin(_LCDML_DISP_cols, _LCDML_DISP_rows);
  // set special chars for scrollbar
  lcd.createChar(0, (uint8_t*)scroll_bar[0]);
  lcd.createChar(1, (uint8_t*)scroll_bar[1]);
  lcd.createChar(2, (uint8_t*)scroll_bar[2]);
  lcd.createChar(3, (uint8_t*)scroll_bar[3]);
  lcd.createChar(4, (uint8_t*)scroll_bar[4]);

  // Enable all items with _LCDML_G1
  LCDML_DISP_groupEnable(_LCDML_G1); // enable group 1

  // LCDMenu Setup
  LCDML_setup(_LCDML_BACK_cnt);
  LoadParameters();

  // put your setup code here, to run once:
  // serial init; only be needed if serial control is used
  while (!Serial);                   // wait until serial ready
  Serial.begin(115000);                // start serial

  StartDelay = millis() + (AntiShortCicle * 60000);
  LastComp = 1;
  myPID.SetOutputLimits(0, 100);
  StepsCoeficient = 100 / CompNum;
  StepDelay = millis() + 60000;

}

// *********************************************************************
// LOOP
// *********************************************************************
void loop()
{

#if (_LCDML_DISP_cfg_initscreen == 1)
  if ((millis() - g_lcdml_initscreen) >= _LCDML_DISP_cfg_initscreen_time) {
    g_lcdml_initscreen = millis(); // reset init screen time
    LCDML_DISP_jumpToFunc(LCDML_FUNC_initscreen); // jump to initscreen
  }
#endif

  // this function must called here, do not delete it
#
  LCDML_run(_LCDML_priority);

  if (Serial.available() > 0) {
    // read the incoming byte:
    Setpoint = Serial.parseInt();
    Serial.print("Setpoint: ");
    Serial.println(Setpoint);
  }

  SwitchExt = digitalRead(A5);

  myPID.SetSampleTime(SampleTime);

  GetTemp();

  GetWaterTemp();

  myPID.Compute();

  // Serial.println(Output);
  if (SwitchExt == 0 && millis() > StartDelay && Output > 10) {
    myPID.SetMode(AUTOMATIC);
    CompControl();
  }
  PumpControl();

  if (SwitchExt == 1 || Output <= 2) {
    CompStop();
  }
  if (FrostSet > WaterTemp) {
    CompStop();
  }
  if (millis() > PStartTime) {
    if (Comp1Stat == 1) {
      digitalWrite(2, HIGH);
    }
    if (Comp2Stat == 1) {
      digitalWrite(3, HIGH);
    }
    if (Comp1Stat == 0) {
      digitalWrite(2, LOW);
    }
    if (Comp2Stat == 0) {
      digitalWrite(3, LOW);
    }
  }
  SaveParameters();
}

// *********************************************************************
// CompStop
// *********************************************************************
void CompStop()
{
  myPID.SetMode(MANUAL);
  Output = 0;
  StartDelay = millis() + (AntiShortCicle * 60000);
  Comp2Stat = 0;
  Comp1Stat = 0;
  CurentLoad = 0;
  Steps = 0;
  StepDelay = millis() + 300000;
  FirstStart = 0;

}

// *********************************************************************
// PumpControl
// *********************************************************************
void PumpControl()
{
  if (PContCicle == 1) {
    digitalWrite(4, HIGH);
  }
  if (Output > 2 && PContCicle == 0 && SwitchExt == 0) {
    digitalWrite(4, HIGH);
    PStopTime = millis() + (PStopDelay * 60000);
  }
  if (SwitchExt == 1 || Output < 2 && PContCicle == 0) {
    if (millis() > PStopTime) {
      digitalWrite(4, LOW);
      PStartTime = millis() + (PStartDelay * 60000);
    }
  }
}

// *********************************************************************
// CompControl
// *********************************************************************
void CompControl()
{
  unsigned long DelayStep2;
  SwitchExt = digitalRead(A5);
  Serial.println("CompControl");

  if (millis() < StepDelay && Output > 10 && FirstStart == 0) {
    if (FirstStart == 0) {
      Steps = 1;
      StepUp();
      FirstStart = 1;
      Serial.println("FirstStart");
    }
  }

  if (millis() > StepDelay && Output > 10) {
    if (Output > CurentLoad && Output > 10 && Output < StepsCoeficient) {
      Steps = 1;
      Serial.println(Steps);
      StepUp();
      WorkDelay = millis() + (MaxWorkT * 500);
      DelayStep2 = millis() + (NextStep * 1000);
    }
    else if (Output > CurentLoad && Output > StepsCoeficient) {
      if (millis() >= DelayStep2) {
        Steps = 2;
        Serial.println(Steps);
        StepUp();
      }
    }
    if (Output <= StepsCoeficient && Output > 10) {
      DelayStep2 = millis() + (NextStep * 1000);
      Steps = 1;
      Serial.println(Steps);
      StepDown();
    }
  }

  if (SwitchExt == 1 || Output <= 10) {
    CompStop();
  }

  if (Steps == 1 && millis() > WorkDelay) {
    Steps = 2;
    StepUp();
  }
}

// *********************************************************************
// StepUp
// *********************************************************************
void StepUp() {

  Serial.println("StepUp");

  if (Steps == 1) {
    if (LastComp == 2) {
      Comp1Stat = 1;
      LastComp = 1;
    }
    else {
      Comp2Stat = 1;
      LastComp = 2;
    }
    CurentLoad = StepsCoeficient * Steps;
  }

  if (Steps == 2) {
    if (Comp1Stat == 0) {
      Comp1Stat = 1;
      LastComp = 1;
    }
    else if (Comp2Stat == 0) {
      Comp2Stat = 1;
      LastComp = 2;
    }
    CurentLoad = StepsCoeficient * Steps;
  }

  Serial.println(Comp1Stat);

  Serial.println(Comp2Stat);
}

// *********************************************************************
// StepDown
// *********************************************************************
void StepDown() {

  Serial.println("StepDown");

  if (CurentLoad > StepsCoeficient * Steps) {
    if (LastComp == 2) {
      Comp1Stat = 0;
      LastComp = 2;
    }
    else {
      Comp2Stat = 0;
      LastComp = 1;
    }
    CurentLoad = StepsCoeficient * Steps;
    WorkDelay = millis() + (MaxWorkT * 90);
  }
  Serial.println(Comp1Stat);
  Serial.println(Comp2Stat);
}

// *********************************************************************
// GetTemp
// *********************************************************************
void GetTemp()
{
  int RawADC;
  float FiltTemp;
  RawADC = analogRead(A3);
  double Temp;
  Temp = log(10000.0 * ((1024.0 / RawADC - 1)));
  Temp = 1 / (0.001129148 + (0.000234125 + (0.0000000876741 * Temp * Temp )) * Temp );
  FiltTemp = Temp - 273.15;
  ADCFilter.Filter(FiltTemp);
  Input = FiltTemp;
}

// *********************************************************************
// GetWaterTemp
// *********************************************************************
void GetWaterTemp()
{
  int RawADC;
  float FiltWaterTemp;
  RawADC = analogRead(A4);
  double Temp;
  Temp = log(10000.0 * ((1024.0 / RawADC - 1)));
  Temp = 1 / (0.001129148 + (0.000234125 + (0.0000000876741 * Temp * Temp )) * Temp );
  FiltWaterTemp = Temp - 273.15;
  ADCFilter.Filter(FiltWaterTemp);
  WaterTemp = FiltWaterTemp;
}

// ************************************************
// Save any parameter changes to EEPROM
// ************************************************
void SaveParameters()
{
  if (Setpoint != EEPROM_readDouble(SpAddress))
  {
    EEPROM_writeDouble(SpAddress, Setpoint);
  }
  if (kp != EEPROM_readDouble(KpAddress))
  {
    EEPROM_writeDouble(KpAddress, kp);
  }
  if (ki != EEPROM_readDouble(KiAddress))
  {
    EEPROM_writeDouble(KiAddress, ki);
  }
  if (kd != EEPROM_readDouble(KdAddress))
  {
    EEPROM_writeDouble(KdAddress, kd);
  }
  if (SampleTime != EEPROM_readDouble(STAddress))
  {
    EEPROM_writeDouble(STAddress, SampleTime);
  }
  if (AntiShortCicle != EEPROM.read(ATime)) {
    EEPROM.write(ATime, AntiShortCicle);
  }
  if (CompNum != EEPROM.read(CompNumAdr)) {
    EEPROM.write(CompNumAdr, CompNum);
  }
  if (MaxWorkT != EEPROM.read(MaxWorkTAdr)) {
    EEPROM.write(MaxWorkTAdr, MaxWorkT);
  }
  if (NextStep != EEPROM.read(NextStepAdr)) {
    EEPROM.write(NextStepAdr, NextStep);
  }
  if (FrostSet != EEPROM.read(FrostSetAdr)) {
    EEPROM.write(FrostSetAdr, FrostSet);
  }
  if (PStartDelay != EEPROM.read(PStartDelayAdr)) {
    EEPROM.write(PStartDelayAdr, PStartDelay);
  }
  if (PStopDelay != EEPROM.read(PStopDelayAdr)) {
    EEPROM.write(PStopDelayAdr, PStopDelay);
  }
}

// ************************************************
// Load parameters from EEPROM
// ************************************************
void LoadParameters()
{
  // Load from EEPROM
  Setpoint = EEPROM_readDouble(SpAddress);
  kp = EEPROM_readDouble(KpAddress);
  ki = EEPROM_readDouble(KiAddress);
  kd = EEPROM_readDouble(KdAddress);
  SampleTime = EEPROM_readDouble(STAddress);
  AntiShortCicle = EEPROM.read(ATime);
  CompNum = EEPROM.read(CompNumAdr);
  MaxWorkT = EEPROM.read(MaxWorkTAdr);
  MaxWorkT = EEPROM.read(NextStepAdr);
  FrostSet = EEPROM.read(FrostSetAdr);
  PStartDelay = EEPROM.read(PStartDelayAdr);
  PStopDelay = EEPROM.read(PStopDelayAdr);

  // Use defaults if EEPROM values are invalid
  if (isnan(Setpoint))
  {
    Setpoint = 40;
  }
  if (isnan(kp))
  {
    kp = 85;
  }
  if (isnan(ki))
  {
    ki = 0.5;
  }
  if (isnan(kd))
  {
    kd = 0;
  }
  if (isnan(SampleTime))
  {
    SampleTime = 15000;
  }
  if (isnan(AntiShortCicle))
  {
    AntiShortCicle = 1;
  }
  if (isnan(MaxWorkT))
  {
    MaxWorkT = 60;
  }
  if (isnan(NextStep))
  {
    NextStep = 60;
  }
  if (isnan(FrostSet))
  {
    FrostSet = 4;
  }
  if (isnan(PStartDelay))
  {
    PStartDelay = 2;
  }
  if (isnan(PStopDelay))
  {
    PStopDelay = 2;
  }
}


// ************************************************
// Write floating point values to EEPROM
// ************************************************
void EEPROM_writeDouble(int address, double value)
{
  byte* p = (byte*)(void*)&value;
  for (int i = 0; i < sizeof(value); i++)
  {
    EEPROM.write(address++, *p++);
  }
}

// ************************************************
// Read floating point values from EEPROM
// ************************************************
double EEPROM_readDouble(int address)
{
  double value = 0.0;
  byte* p = (byte*)(void*)&value;
  for (int i = 0; i < sizeof(value); i++)
  {
    *p++ = EEPROM.read(address++);
  }
  return value;
}

// *********************************************************************
// check some errors - do not change here anything
// *********************************************************************
# if(_LCDML_DISP_rows > _LCDML_DISP_cfg_max_rows)
# error change value of _LCDML_DISP_cfg_max_rows in LCDMenuLib.h
# endif
# if(_LCDML_DISP_cols > _LCDML_DISP_cfg_max_string_length)
# error change value of _LCDML_DISP_cfg_max_string_length in LCDMenuLib.h
# endif
