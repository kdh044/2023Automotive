#include <Car_Library.h>

// 핀 번호 설정 주차 1번
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

// 변수 설정
long FRduration, FRdistance;
long BRduration, BRdistance;

unsigned long time1 = 0, time2 = 0, time_delta;

int HandleDegree;     // 가변저항(조향값) 변수
//int Middle = 566;     // 가변저항 중앙값 (수시 확인)
int mode;             // 주차 모드 인식

float sonic1, sonic2;

// 함수 선언
float FRUltraSonic();
float BRUltraSonic();
float FLUltraSonic();
float BLUltraSonic();
float FFUltraSonic();
int HandleRead();

void setup() {
  Serial.begin(9600);
  pinMode(FRechoPin, INPUT);
  pinMode(FRtrigPin, OUTPUT);
  pinMode(BRechoPin, INPUT);
  pinMode(BRtrigPin, OUTPUT);

  pinMode(LeftmotorA1, OUTPUT);
  pinMode(LeftmotorA2, OUTPUT);
  pinMode(RightmotorA3, OUTPUT);
  pinMode(RightmotorA4, OUTPUT);
  pinMode(HandlemotorA5, OUTPUT);
  pinMode(HandlemotorA6, OUTPUT);
}

void loop() {    
  if(mode == 0){ // 단순 전진
      HandleDegree = HandleRead();
      sonic1 = FRUltraSonic();  // 앞부분 센서
      sonic2 = BRUltraSonic();  // 뒷부분 센서
      
      motor_forward(LeftmotorA1, LeftmotorA2,70);    // 전진시 속도 (변경 가능)
      motor_forward(RightmotorA3, RightmotorA4,70);
      motor_hold(HandlemotorA5, HandlemotorA6);
      
     /*if(HandleDegree >= Middle-5 && HandleDegree <= Middle+5){
        if(HandleDegree < Middle-2){
                motor_backward(HandlemotorA5,HandlemotorA6,35);  // 변경해야 할 부분 (핸들 조향 속도)
                }
            else if(HandleDegree > Middle+2){
                motor_forward(HandlemotorA5,HandlemotorA6,35);  // 변경해야 할 부분 (핸들 조향 속도)
                }
            else{
                motor_hold(HandlemotorA5,HandlemotorA6);
                }
            }
      else if(HandleDegree < Middle-5){
            motor_backward(HandlemotorA5,HandlemotorA6,70);  // 변경해야 할 부분 (핸들 조향 속도)
            }
      else if(HandleDegree > Middle+5){
            motor_forward(HandlemotorA5,HandlemotorA6,70);  // 변경해야 할 부분 (핸들 조향 속도)
            }
      else if(HandleDegree > Middle+15){
            motor_forward(HandlemotorA5,HandlemotorA6,100);
            }
      else if(HandleDegree < Middle-15){
            motor_backward(HandlemotorA5,HandlemotorA6,100);
            }*/
      
      if(sonic1 > 120 && sonic2 > 10 && sonic2 < 65 && time1 == 0){  // 장애물 거리값 (변경 가능)
          time1 = millis();
          Serial.print("First time:");
          Serial.println(time1);
          }
      if(sonic1 > 10 && sonic1 < 65 && sonic2 > 120 && time1 != 0 && time2 == 0){  // 장애물 거리값 (변경 가능)
          time2 = millis();
          Serial.print("Second time:");
          Serial.println(time2);
          time_delta = time2 - time1;
          Serial.println(time_delta);
          if(time_delta > 2500 && mode == 0){        // 약 2.5초 이상 공간 감지가 되면 주차 공간 인식 (인식 시간 변경 가능)
              //Serial.println("Parking Process");
              mode = 1;
              }
          else if (time_delta <= 2500 && mode == 0){ // 2.5초 이하 공간 감지가 되면 주차 공간 없고 넘어감 (인식 시간 변경 가능)
              mode = 0;
              time1 = 0;
              time2 = 0;
              }
          }
      }
 if(mode == 1){ // 주차 프로세스
      motor_hold(HandlemotorA5, HandlemotorA6);
      
      motor_backward(LeftmotorA1, LeftmotorA2,100);       // 감지되면 후진
      motor_backward(RightmotorA3, RightmotorA4,100);
      delay(700);

      motor_hold(LeftmotorA1, LeftmotorA2);               // 정지
      motor_hold(RightmotorA3, RightmotorA4);
      delay(1000);
   
      motor_backward(LeftmotorA1, LeftmotorA2,200);       // 반시계 방향으로 차체회전 1
      motor_forward(RightmotorA3, RightmotorA4,200);
      delay(2000);

      motor_hold(LeftmotorA1, LeftmotorA2);               // 정지
      motor_hold(RightmotorA3, RightmotorA4);
      delay(1000);

      motor_backward(LeftmotorA1, LeftmotorA2,200);       // 반시계 방향으로 차체회전 2
      motor_forward(RightmotorA3, RightmotorA4,200);
      delay(2000);
      
      motor_hold(LeftmotorA1, LeftmotorA2);               // 정지
      motor_hold(RightmotorA3, RightmotorA4);
      delay(1000);

      motor_backward(LeftmotorA1, LeftmotorA2,200);       // 반시계 방향으로 차체회전 3
      motor_forward(RightmotorA3, RightmotorA4,200);
      delay(1400);

      motor_hold(LeftmotorA1, LeftmotorA2);               // 정지
      motor_hold(RightmotorA3, RightmotorA4);
      delay(1000);

      motor_backward(LeftmotorA1, LeftmotorA2,100);       // 후진해서 주차완료
      motor_backward(RightmotorA3, RightmotorA4,100);
      delay(3000);

      motor_hold(LeftmotorA1, LeftmotorA2);               // 정차 (변경 가능)
      motor_hold(RightmotorA3, RightmotorA4);
      delay(4000);

      motor_forward(LeftmotorA1, LeftmotorA2,100);        // 전진시작
      motor_forward(RightmotorA3, RightmotorA4,100);
      delay(6000);

      motor_hold(LeftmotorA1, LeftmotorA2);               // 정지
      motor_hold(RightmotorA3, RightmotorA4);
      delay(1000);

      motor_backward(LeftmotorA1, LeftmotorA2,200);       // 반시계 방향으로 차체회전 4
      motor_forward(RightmotorA3, RightmotorA4,200);
      delay(1400);

      motor_hold(LeftmotorA1, LeftmotorA2);               // 정지
      motor_hold(RightmotorA3, RightmotorA4);
      delay(2000);

      motor_backward(LeftmotorA1, LeftmotorA2,200);       // 반시계 방향으로 차체회전 5
      motor_forward(RightmotorA3, RightmotorA4,200);
      delay(2000);

      motor_hold(LeftmotorA1, LeftmotorA2);               // 정지
      motor_hold(RightmotorA3, RightmotorA4);
      delay(2000);

      motor_backward(LeftmotorA1, LeftmotorA2,200);       // 반시계 방향으로 차체회전 6
      motor_forward(RightmotorA3, RightmotorA4,200);
      delay(1600);

      motor_hold(LeftmotorA1, LeftmotorA2);               // 정지
      motor_hold(RightmotorA3, RightmotorA4);
      delay(2000);

      motor_forward(LeftmotorA1, LeftmotorA2,100);        // 전진 (변경 가능)
      motor_forward(RightmotorA3, RightmotorA4,100);
      delay(14000);

      motor_hold(LeftmotorA1, LeftmotorA2);               // 정지
      motor_hold(RightmotorA3, RightmotorA4);
      delay(100000);
  }
}

float FRUltraSonic() {
  digitalWrite(FRtrigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(FRtrigPin, LOW);
  FRduration = pulseIn(FRechoPin, HIGH);
  FRdistance = ((float)(340 * FRduration) / 10000) / 2; 
  Serial.print("FRdistance:");
  Serial.print(FRdistance);
  Serial.println(" cm");
  return FRdistance;
  }
  
float BRUltraSonic() {
  digitalWrite(BRtrigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(BRtrigPin, LOW);
  BRduration = pulseIn(BRechoPin, HIGH);
  BRdistance = ((float)(340 * BRduration) / 10000) / 2; 
  Serial.print("BRdistance:");
  Serial.print(BRdistance);
  Serial.println(" cm");
  return BRdistance;
  }

int HandleRead() {
  HandleDegree = analogRead(AnalogPin);
  Serial.print("HandleDegree:");
  Serial.println(HandleDegree);
  return HandleDegree;
  }
