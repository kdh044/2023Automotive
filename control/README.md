# control 디렉토리 소개 (아두이노 기반 제어 로직)

이 디렉토리는 **2023 가천대학교 자율주행 SW 경진대회**에서 미션 수행을 위해 사용한 아두이노 코드를 포함하고 있습니다.  
차량의 주요 동작(고속주행, 장애물 회피, 주차 등)을 수행하는 소스가 포함되어 있습니다.

---

## 1. 장애물 회피 + 신호등 정지 미션 (`avoid.ino`)

- 전방 **초음파 센서**로 장애물을 감지하여 일정 거리 이내 진입 시 회피 주행 수행
- **신호등 정지**는 YOLO 인식 대신 **하드코딩된 타이머**로 구현됨

<p align="center">
  <img src="./avoid.gif" width="320">
</p>

---

## 2. 주차 미션 (`parking1.ino`, `parking2.ino`)

- 두 가지 방식의 **회전 주차 알고리즘** 구현
- **초음파 거리 센서**를 활용하여 주차 가능 공간을 인식하고 후진 주차 수행

<p align="center">
  <img src="./parking.gif" width="320">
</p>

---

## 3. 고속 주행 미션 (`speed.ino`)

- **YOLOv5**로 감지한 **차선 중심 좌표**를 아두이노로 전달
- 아두이노는 좌표와 **현재 핸들 위치(가변저항)** 차이를 계산해 조향
- delta값 크기에 따라 **조향 세기를 다르게 설정**, 오버슈팅을 줄임

<p align="center">
  <img src="./speed.gif" width="320">
</p>

---

## 주요 파일 요약

| 파일명           | 설명                                      |
|------------------|-------------------------------------------|
| `avoid.ino`      | 장애물 회피 + 신호등 정지 로직             |
| `parking1.ino`   | 주차 로직 1                                |
| `parking2.ino`   | 주차 로직 2                                |
| `speed.ino`      | 고속 주행 제어 로직                        |
| `handleset.ino`  | 핸들 중앙 캘리브레이션용 코드              |
| `avoid.gif`      | 장애물 회피 미션 시연 영상                  |
| `parking.gif`    | 주차 미션 시연 영상                        |
| `speed.gif`      | 고속 주행 미션 시연 영상                   |

---
