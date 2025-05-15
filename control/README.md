# control 디렉토리 소개 (아두이노 기반 제어 로직)  
    이 디렉토리는 2023 가천대학교 자율주행 SW 경진대회에서 미션 수행을 위한 아두이노 코드를 담고 있습니다.
    각 코드는 자율주행 차량의 다양한 동작(고속주행, 장애물 회피, 주차 등)을 제어합니다.

## 1. 장애물 회피 + 신호등 정지 미션 (avoid.ino)

    전방 초음파 센서가 장애물을 감지하면 일정 시간 회피 주행을 수행하고, 이후 주행을 재개합니다.

    신호등은 YOLO 인식 대신 하드코딩된 정지 타이머로 구현되어 있습니다.
    <p align="center"><img src="./avoid.gif" width="320"></p>

## 2. 주차 미션 (parking1.ino, parking2.ino)

    주차 미션: 두 가지 방식으로 구현되어 있으며, 주차 구간에 진입하기 위한 조건을 초음파 거리로 판단하고,    
    회전 주차까지 수행하도록 구성되어 있습니다.
    <p align="center"><img src="./parking.gif" width="320"></p>

## 3. 고속 주행 미션 (speed.ino)

    YOLOv5로 감지된 차선 중심 좌표를 아두이노에 전달합니다.

    아두이노는 이 좌표값을 기준으로 현재 핸들 위치(가변저항)와의 delta를 계산하여 조향합니다.

    delta의 크기에 따라 조향 세기를 다르게 하여 오버슈팅을 줄입니다.
    <p align="center"><img src="./speed.gif" width="320"></p>

avoid.ino	장애물 회피 + 신호등 정지 미션
parking1.ino	주차 로직 1
parking2.ino	주차 로직 2
speed.ino	고속 주행 로직
handleset.ino	핸들 캘리브레이션 코드