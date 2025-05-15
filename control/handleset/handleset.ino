#include <Car_Library.h>

// 핀 번호 설정
int LeftmotorA1 = 2;    //모터 드라이버1  IN1
int LeftmotorA2 = 3;    //모터 드라이버1  IN2
int RightmotorA3 = 4;   //모터 드라이버2  IN1
int RightmotorA4 = 5;   //모터 드라이버2  IN2
int HandlemotorA5 = 6;  //모터 드라이버3  IN1
int HandlemotorA6 = 7;  //모터 드라이버3  IN2

int AnalogPin = A15;   //가변저항 Output Pin

int FRtrigPin = 42;    //오른쪽 전방 초음파 센서
int FRechoPin = 43;
int BRtrigPin = 44;
int BRechoPin = 45;
int FLtrigPin = 46;
int FLechoPin = 47;
int BLtrigPin = 48;
int BLechoPin = 49;
int FFtrigPin = 50;
int FFechoPin = 51;

float Sonic1, Sonic2;
int Handle1, Handle2;

// 변수 설정
long FRduration, FRdistance;      //오른쪽 초음파 센서와의 거리
long BRduration, BRdistance;
long FLduration, FLdistance;
long BLduration, BLdistance;
long FFduration, FFdistance;

unsigned long time_previous, time_current, time_delta;

int HandleDegree;
int data;

// 함수 선언
float FRUltraSonic();
float BRUltraSonic();
float FLUltraSonic();
float BLUltraSonic();
float FFUltraSonic();


void setup() {
  Serial.begin(9600);
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

  time_previous = millis();
}

void loop() {
  HandleDegree=analogRead(AnalogPin);
   
   Serial.println(HandleDegree);
}


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
