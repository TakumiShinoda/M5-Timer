#include <M5Stack.h>

uint8_t Time = 60;
uint16_t TempTime = 0;
long Start = 0;
bool ClockState = false;

void updateTimeDisplay(){
  m5.Lcd.setTextSize(7);
  m5.Lcd.setCursor(120, 80); 
  m5.Lcd.println(String(Time));
}

void setup(){
  m5.begin();
  updateTimeDisplay();
}

void loop(){
  long now = millis();

  if(M5.BtnA.wasPressed()){
    Time = 60;
    ClockState = false;
    Start = 0;
  }

  if(M5.BtnB.wasPressed()){  
    if(!ClockState){
      Start = millis(); 
      ClockState = true;
    }
  }

  if(M5.BtnC.wasPressed()){
    ClockState = !ClockState; 
    if(ClockState){
      if(Start != 0 && TempTime != 0){
        Start = now;
      }
    }else{
      TempTime = now - Start;
    }
  }

  if(ClockState){
    if((now - Start) + TempTime > 1000){
      Time -= 1;
      Start = now;
      TempTime = 0;
    }
  }

  updateTimeDisplay();
  M5.update();
}