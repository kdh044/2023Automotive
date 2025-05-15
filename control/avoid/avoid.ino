#include <Car_Library.h>

// 핀 번호 설정
int LeftmotorA1 = 2;    //모터 드라이버1  IN1
int LeftmotorA2 = 3;    //모터 드라이버1  IN2
int RightmotorA3 = 4;   //모터 드라이버2  IN1
int RightmotorA4 = 5;   //모터 드라이버2  IN2
int HandlemotorA5 = 6;  //모터 드라이버3  IN1
int HandlemotorA6 = 7;  //모터 드라이버3  IN2

int AnalogPin = A15;   //가변저항 Output Pin

int FRtrigPin = 42;
int FRechoPin = 43;
int BRtrigPin = 44;
int BRechoPin = 45;
int FLtrigPin = 46;
int FLechoPin = 47;
int BLtrigPin = 48;
int BLechoPin = 49;
int FFtrigPin = 50;
int FFechoPin = 51;

// 변수 설정
long FRduration, FRdistance;
long BRduration, BRdistance;
long FLduration, FLdistance;
long BLduration, BLdistance;
long FFduration, FFdistance;

int HandleDegree;     // 핸들 가변저항 값
int data;             // 파이썬에서 받아오는 데이터
int mode = 0;         // 기본 모드 : 자율 주행
int line = 1;         // 기본 차선 : 우측 차선

int Middle = 453;     // 조향 중심시 가변저항 값 : 차선이 직진으로 가지 않을 경우 측정해야하는 값 (변경 가능)
int xCoordSet = 132;  // 직진시 차선 좌표값 : 직진 코스시 중앙 좌표값 (변경 가능)
int xCoord = 132;     // 초기 좌표
int Speed = 150;      // 차량 속도
int time_set;
int time_stop_start;

float rate = 1;       // 반영 비율
int delta;            // 조향 차이
int HandleSet;        // 최종 목표 조향값

unsigned long time_previous = 0, time_current = 0, time_delta;
unsigned long time_previous_1 = 0, time_current_1 = 0, time_delta_1;

// 함수 선언
float FRUltraSonic();
float BRUltraSonic();
float FLUltraSonic();
float BLUltraSonic();
float FFUltraSonic();


void setup(){
    Serial.begin(9600);
    Serial.setTimeout(50);  // 시리얼 통신 초기화 주기
    pinMode(FRechoPin, INPUT);
    pinMode(FRtrigPin, OUTPUT);
    pinMode(BRechoPin, INPUT);
    pinMode(BRtrigPin, OUTPUT);
    pinMode(FLechoPin, INPUT);
    pinMode(FLtrigPin, OUTPUT);
    pinMode(BLechoPin, INPUT);
    pinMode(BLtrigPin, OUTPUT);
    pinMode(FFechoPin, INPUT);
    pinMode(FFtrigPin, OUTPUT);
    
    pinMode(LeftmotorA1, OUTPUT);
    pinMode(LeftmotorA2, OUTPUT);
    pinMode(RightmotorA3, OUTPUT);
    pinMode(RightmotorA4, OUTPUT);
    pinMode(HandlemotorA5, OUTPUT);
    pinMode(HandlemotorA6, OUTPUT);
}

void loop() {
  FFUltraSonic();
  if (FFdistance < 90){ // 장애물 회피 모드 판단
    mode = 2;
    if(time_previous == 0){ // 모드 변경시 1번만 측정
      time_previous = millis();
      }
  }
  if (time_stop_start == 1){
    time_current_1 = millis ();
    time_delta_1 = time_current_1 - time_previous_1;
    if (time_delta_1 >= 15000){ // 모드 2 끝나고 전진 시간
      mode = 3;
      time_stop_start = 0; 
      }
  }
  if(mode == 0){ // 자율주행 모드
    HandleDegree = analogRead(AnalogPin);
    if(Serial.available() > 0){ // 시리얼 통신이 된 경우
      String data = Serial.readStringUntil('\n');
      data.trim();
      String xCoordStr = data.substring(0,3);
      xCoord = xCoordStr.toInt();
      delta = xCoordSet - xCoord;
      HandleSet = Middle + rate*(delta);
      }
    if(HandleDegree >= HandleSet-5 && HandleDegree <= HandleSet+5){
        if(HandleDegree < HandleSet-2){
                motor_backward(HandlemotorA5,HandlemotorA6,35);  // 변경해야 할 부분 (핸들 조향 속도)
                }
            else if(HandleDegree > HandleSet+2){
                motor_forward(HandlemotorA5,HandlemotorA6,35);   // 변경해야 할 부분 (핸들 조향 속도)
                }
            else{
                motor_hold(HandlemotorA5,HandlemotorA6);
                }
            }
        else if(HandleDegree < HandleSet-5){
            motor_backward(HandlemotorA5,HandlemotorA6,150);  // 변경해야 할 부분 (핸들 조향 속도)
            }
        else if(HandleDegree > HandleSet+5){
            motor_forward(HandlemotorA5,HandlemotorA6,150);   // 변경해야 할 부분 (핸들 조향 속도)
            }
        else if(HandleDegree > HandleSet+15){
            motor_forward(HandlemotorA5,HandlemotorA6,200);
            }
        else if(HandleDegree < HandleSet-15){
            motor_backward(HandlemotorA5,HandlemotorA6,200);
            }
    motor_forward(LeftmotorA1, LeftmotorA2,Speed);
    motor_forward(RightmotorA3, RightmotorA4,Speed);
    }
  /*else if(mode == 2){  // 모드 2 : 회피 모드  장애물 맨 앞에  정지까지 14초
      time_current = millis();
      time_delta = time_current - time_previous;
      if(time_delta < 3200){                                   // 좌회전
          motor_forward(LeftmotorA1, LeftmotorA2,70);
          motor_forward(RightmotorA3, RightmotorA4,130);
          motor_backward(HandlemotorA5,HandlemotorA6,250);
          }
      else if (time_delta >= 3200 && time_delta < 11500){      // 우회전
          motor_forward(LeftmotorA1, LeftmotorA2,130);
          motor_forward(RightmotorA3, RightmotorA4,70);
          motor_forward(HandlemotorA5,HandlemotorA6,250);
          }
      else if (time_delta >= 11500 && time_delta < 14000){     // 약간 좌회전
          motor_forward(LeftmotorA1, LeftmotorA2,70);
          motor_forward(RightmotorA3, RightmotorA4,150);
          motor_backward(HandlemotorA5,HandlemotorA6,250);
         }
      else if(time_delta >= 14000 && time_delta < 14100){      // 직진 맞추기
          motor_forward(LeftmotorA1, LeftmotorA2,130);
          motor_forward(RightmotorA3, RightmotorA4,130);
          HandleDegree = analogRead(AnalogPin);
          if(HandleDegree >= Middle-5 && HandleDegree <= Middle+5){
              if(HandleDegree < Middle-2){
                      motor_backward(HandlemotorA5,HandlemotorA6,35);  // 변경해야 할 부분 (핸들 조향 속도)
                      }
                  else if(HandleDegree > Middle+2){
                      motor_forward(HandlemotorA5,HandlemotorA6,35);   // 변경해야 할 부분 (핸들 조향 속도)
                      }
                  else{
                      motor_hold(HandlemotorA5,HandlemotorA6);
                      }
                  }
          else if(HandleDegree < Middle-5){
              motor_backward(HandlemotorA5,HandlemotorA6,150);  // 변경해야 할 부분 (핸들 조향 속도)
              }
          else if(HandleDegree > Middle+5){
              motor_forward(HandlemotorA5,HandlemotorA6,150);   // 변경해야 할 부분 (핸들 조향 속도)
              }
          else if(HandleDegree > Middle+15){
              motor_forward(HandlemotorA5,HandlemotorA6,200);
              }
          else if(HandleDegree < Middle-15){
              motor_backward(HandlemotorA5,HandlemotorA6,200);
              }
          mode = 0;
          time_stop_start = 1;
          time_previous_1 = millis();
          }  
  }*/
    else if(mode == 2){  // 모드 2 : 회피 모드  장애물 가운데  정지까지 15초
      time_current = millis();
      time_delta = time_current - time_previous;
      if(time_delta < 3200){                                   // 좌회전
          motor_forward(LeftmotorA1, LeftmotorA2,70);
          motor_forward(RightmotorA3, RightmotorA4,130);
          motor_backward(HandlemotorA5,HandlemotorA6,250);
          }
      else if (time_delta >= 3200 && time_delta < 11300){      // 우회전
          motor_forward(LeftmotorA1, LeftmotorA2,130);
          motor_forward(RightmotorA3, RightmotorA4,70);
          motor_forward(HandlemotorA5,HandlemotorA6,250);
          }
      else if (time_delta >= 11300 && time_delta < 13600){     // 약간 좌회전
          motor_forward(LeftmotorA1, LeftmotorA2,70);
          motor_forward(RightmotorA3, RightmotorA4,150);
          motor_backward(HandlemotorA5,HandlemotorA6,250);
         }
      else if(time_delta >= 13600 && time_delta < 13700){      // 직진 맞추기
          motor_forward(LeftmotorA1, LeftmotorA2,130);
          motor_forward(RightmotorA3, RightmotorA4,130);
          HandleDegree = analogRead(AnalogPin);
          if(HandleDegree >= Middle-5 && HandleDegree <= Middle+5){
              if(HandleDegree < Middle-2){
                      motor_backward(HandlemotorA5,HandlemotorA6,35);  // 변경해야 할 부분 (핸들 조향 속도)
                      }
                  else if(HandleDegree > Middle+2){
                      motor_forward(HandlemotorA5,HandlemotorA6,35);   // 변경해야 할 부분 (핸들 조향 속도)
                      }
                  else{
                      motor_hold(HandlemotorA5,HandlemotorA6);
                      }
                  }
          else if(HandleDegree < Middle-5){
              motor_backward(HandlemotorA5,HandlemotorA6,150);  // 변경해야 할 부분 (핸들 조향 속도)
              }
          else if(HandleDegree > Middle+5){
              motor_forward(HandlemotorA5,HandlemotorA6,150);   // 변경해야 할 부분 (핸들 조향 속도)
              }
          else if(HandleDegree > Middle+15){
              motor_forward(HandlemotorA5,HandlemotorA6,200);
              }
          else if(HandleDegree < Middle-15){
              motor_backward(HandlemotorA5,HandlemotorA6,200);
              }
          mode = 0;
          time_stop_start = 1;
          time_previous_1 = millis();
          }
  } 
  /*else if(mode == 2){  // 모드 2 : 회피 모드 장애물 맨 뒤에 정지까지 16초
      time_current = millis();
      time_delta = time_current - time_previous;
      if(time_delta < 3200){                                   // 좌회전
          motor_forward(LeftmotorA1, LeftmotorA2,70);
          motor_forward(RightmotorA3, RightmotorA4,130);
          motor_backward(HandlemotorA5,HandlemotorA6,250);
          }
      else if (time_delta >= 3200 && time_delta < 11100){      // 우회전
          motor_forward(LeftmotorA1, LeftmotorA2,130);
          motor_forward(RightmotorA3, RightmotorA4,70);
          motor_forward(HandlemotorA5,HandlemotorA6,250);
          }
      else if (time_delta >= 11100 && time_delta < 13800){     // 약간 좌회전
          motor_forward(LeftmotorA1, LeftmotorA2,70);
          motor_forward(RightmotorA3, RightmotorA4,150);
          motor_backward(HandlemotorA5,HandlemotorA6,250);
         }
      else if(time_delta >= 13800 && time_delta < 13900){      // 직진 맞추기
          motor_forward(LeftmotorA1, LeftmotorA2,130);
          motor_forward(RightmotorA3, RightmotorA4,130);
          HandleDegree = analogRead(AnalogPin);
          if(HandleDegree >= Middle-5 && HandleDegree <= Middle+5){
              if(HandleDegree < Middle-2){
                      motor_backward(HandlemotorA5,HandlemotorA6,35);  // 변경해야 할 부분 (핸들 조향 속도)
                      }
                  else if(HandleDegree > Middle+2){
                      motor_forward(HandlemotorA5,HandlemotorA6,35);   // 변경해야 할 부분 (핸들 조향 속도)
                      }
                  else{
                      motor_hold(HandlemotorA5,HandlemotorA6);
                      }
                  }
          else if(HandleDegree < Middle-5){
              motor_backward(HandlemotorA5,HandlemotorA6,150);  // 변경해야 할 부분 (핸들 조향 속도)
              }
          else if(HandleDegree > Middle+5){
              motor_forward(HandlemotorA5,HandlemotorA6,150);   // 변경해야 할 부분 (핸들 조향 속도)
              }
          else if(HandleDegree > Middle+15){
              motor_forward(HandlemotorA5,HandlemotorA6,200);
              }
          else if(HandleDegree < Middle-15){
              motor_backward(HandlemotorA5,HandlemotorA6,200);
              }
          mode = 0;
          time_stop_start = 1;
          time_previous_1 = millis();
          }
  }*/
  else if (mode == 3){
      motor_hold(LeftmotorA1, LeftmotorA2);
      motor_hold(RightmotorA3, RightmotorA4);
      motor_hold(HandlemotorA5,HandlemotorA6);
      delay(7000);                                      // 정차시간 (변경 가능)
      motor_forward(LeftmotorA1, LeftmotorA2,150);
      motor_forward(RightmotorA3, RightmotorA4,150);
      mode = 0;
      time_previous = 0;
      }
}
 
// 센서 함수
float FRUltraSonic() {
  digitalWrite(FRtrigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(FRtrigPin, LOW);
  FRduration = pulseIn(FRechoPin, HIGH);
  FRdistance = ((float)(340 * FRduration) / 10000) / 2; 
  //Serial.print("FRdistance:");
  //Serial.print(FRdistance);
  //Serial.println(" cm");
  return FRdistance;
  }
  
float BRUltraSonic() {
  digitalWrite(BRtrigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(BRtrigPin, LOW);
  BRduration = pulseIn(BRechoPin, HIGH);
  BRdistance = ((float)(340 * BRduration) / 10000) / 2; 
  //Serial.print("BRdistance:");
  //Serial.print(BRdistance);
  //Serial.println(" cm");
  return BRdistance;
  }
  
float FLUltraSonic() {
  digitalWrite(FLtrigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(FLtrigPin, LOW);
  FLduration = pulseIn(FLechoPin, HIGH);
  FLdistance = ((float)(340 * FLduration) / 10000) / 2; 
  //Serial.print("FLdistance:");
  //Serial.print(FLdistance);
  //Serial.println(" cm");
  return FLdistance;
  }
  
float BLUltraSonic() {
  digitalWrite(BLtrigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(BLtrigPin, LOW);
  BLduration = pulseIn(BLechoPin, HIGH);
  BLdistance = ((float)(340 * BLduration) / 10000) / 2; 
  //Serial.print("BLdistance:");
  //Serial.print(BLdistance);
  //Serial.println(" cm");
  return BLdistance;
  }
  
float FFUltraSonic() {
  digitalWrite(FFtrigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(FFtrigPin, LOW);
  
  FFduration = pulseIn(FFechoPin, HIGH);
  
  FFdistance = ((float)(340 * FFduration) / 10000) / 2; 
  //Serial.print("FFdistance:");
  //Serial.print(FFdistance);
  //Serial.println(" cm");
  return FFdistance;
  }

int HandleRead() {
  HandleDegree = analogRead(AnalogPin);
  return HandleDegree;
  }
