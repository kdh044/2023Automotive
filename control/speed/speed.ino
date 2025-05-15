#include <Car_Library.h>

// 핀 번호 설정
int LeftmotorA1 = 2;    //모터 드라이버1  IN1
int LeftmotorA2 = 3;    //모터 드라이버1  IN2
int RightmotorA3 = 4;   //모터 드라이버2  IN1
int RightmotorA4 = 5;   //모터 드라이버2  IN2
int HandlemotorA5 = 6;  //모터 드라이버3  IN1
int HandlemotorA6 = 7;  //모터 드라이버3  IN2

int AnalogPin = A15;   //가변저항 Output Pin

int HandleDegree;     // 핸들 가변저항 값
int data;             // 파이썬에서 받아오는 데이터

int Middle = 358;     // 조향 중심시 가변저항 값 : 차선이 직진으로 가지 않을 경우 측정해야하는 값 (변경 가능)
int xCoordSet = 127;  // 직진시 차선 좌표값 : 직진 코스시 중앙 좌표값 (변경 가능)
int xCoord = 127;     // 초기 좌표
int Speed = 250;      // 차량 속도

float rate = 1;       // 반영 비율
int delta;            // 조향 차이
int HandleSet;        // 최종 목표 조향값

void setup(){
    Serial.begin(9600);
    Serial.setTimeout(50);  // 시리얼 통신 초기화 주기 
    pinMode(LeftmotorA1, OUTPUT);
    pinMode(LeftmotorA2, OUTPUT);
    pinMode(RightmotorA3, OUTPUT);
    pinMode(RightmotorA4, OUTPUT);
    pinMode(HandlemotorA5, OUTPUT);
    pinMode(HandlemotorA6, OUTPUT);
}

void loop() {
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
                motor_forward(HandlemotorA5,HandlemotorA6,35);  // 변경해야 할 부분 (핸들 조향 속도)
                }
            else{
                motor_hold(HandlemotorA5,HandlemotorA6);
                }
            }
        else if(HandleDegree < HandleSet-5){
            motor_backward(HandlemotorA5,HandlemotorA6,150);  // 변경해야 할 부분 (핸들 조향 속도)
            }
        else if(HandleDegree > HandleSet+5){
            motor_forward(HandlemotorA5,HandlemotorA6,150);  // 변경해야 할 부분 (핸들 조향 속도)
            }
        else if(HandleDegree > HandleSet+15){
            motor_forward(HandlemotorA5,HandlemotorA6,200);
            }
        else if(HandleDegree < HandleSet-15){
            motor_backward(HandlemotorA5,HandlemotorA6,200);
            }
    motor_forward(LeftmotorA1, LeftmotorA2,Speed);    // 전진 모터 속도 (변경 가능)
    motor_forward(RightmotorA3, RightmotorA4,Speed);
}

int HandleRead() {
  HandleDegree = analogRead(AnalogPin);
  return HandleDegree;
  }
