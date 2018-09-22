#include <M5Stack.h>

uint8_t Time = 60;
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
  }

  if(M5.BtnB.wasPressed()){  
    if(!ClockState){
      Start = millis(); 
      ClockState = true;
    }
  }

  if(M5.BtnC.wasPressed()){
    ClockState = !ClockState;
  }

  if(ClockState){
    if(now - Start > 1000){
      Time -= 1;
      Start = now;
    }
  }

  updateTimeDisplay();
  M5.update();
}