#include <M5Stack.h>

#define BEEPHZ 1319
#define BEEPDURATION 100
#define VOLUME 1
#define LIMIT 60

uint8_t Time = LIMIT;
uint16_t TempTime = 0;
long Start = 0;
bool ClockState = false;
bool ClockOver = false;

void beep(int hz, int ms){
  int start = millis();
  double freq = 1000.0 / hz;
  boolean sw = false;

  while(true){
    if(sw){
      dacWrite(25, VOLUME);
    }else{
      dacWrite(25, 0);
    }
    if(millis() - start > ms) break;
    sw = !sw;
    delayMicroseconds(freq * 1000);
  }
}

void updateTimeDisplay(){
  m5.Lcd.setTextSize(7);
  m5.Lcd.setCursor(120, 80); 
  m5.Lcd.fillRect(120, 80, 80, 50, 0); 
  if(Time < 10){
    m5.Lcd.println('0' + String(Time));
  }else{
    m5.Lcd.println(String(Time));
  }
}

void checkResetButton(){
  if(M5.BtnA.wasPressed()){
    Time = LIMIT;
    ClockState = false;
    ClockOver = false;
    Start = 0;
    TempTime = 0;
    updateTimeDisplay();
  }
}

void setup(){
  m5.begin();
  updateTimeDisplay();
}

void loop(){
  long now = millis();

  checkResetButton();

  if(M5.BtnB.wasPressed() && !ClockOver){  
    if(!ClockState && TempTime == 0){
      Start = millis(); 
      ClockState = true;
    }
  }

  if(M5.BtnC.wasPressed() && ! ClockOver){
    if(!ClockState && Start != 0 && TempTime != 0){ 
      Start = now;
      ClockState = !ClockState; 
    }else if(ClockState){
      TempTime = now - Start;
      ClockState = !ClockState; 
    }
  }

  if(ClockState){
    if((now - Start) + TempTime > 1000){
      Start = now;
      TempTime = 0;
      if(!ClockOver){
        Time -= 1;
        updateTimeDisplay();
        beep(BEEPHZ, BEEPDURATION);
      }else{ 
        uint8_t cnt = 0;

        Time = 0;
        updateTimeDisplay(); 
        while(cnt < 3){
          beep(BEEPHZ, BEEPDURATION);
          cnt += 1;
          delay(100);
        }
      }
    }
    if(Time == 1) ClockOver = true;
  }
  M5.update();
}