const int segments[8] = {6, 7, 8, 9, 10, 11, 12, 13};
const int orderedSegments[8] = {7, 8, 9, 12, 11, 10, 6};
const int dotIndex = 7;
const int dot = 13;
int segmentsState[8] = {LOW};
int dotState = LOW;
const int numbers[16][8] = {
    {LOW,  HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, dotState}, // 0
    {LOW,  LOW,  LOW,  HIGH, LOW,  LOW,  HIGH, dotState}, // 1
    {HIGH, LOW,  HIGH, HIGH, HIGH, HIGH, LOW,  dotState}, // 2
    {HIGH, LOW,  HIGH, HIGH, LOW,  HIGH, HIGH, dotState}, // 3
    {HIGH, HIGH, LOW,  HIGH, LOW,  LOW,  HIGH, dotState}, // 4
    {HIGH, HIGH, HIGH, LOW,  LOW,  HIGH, HIGH, dotState}, // 5
    {HIGH, HIGH, HIGH, LOW,  HIGH, HIGH, HIGH, dotState}, // 6
    {LOW,  LOW,  HIGH, HIGH, LOW,  LOW,  HIGH, dotState}, // 7
    {HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, dotState}, // 8
    {HIGH, HIGH, HIGH, HIGH, LOW,  HIGH, HIGH, dotState}, // 9
    {HIGH, HIGH, HIGH, HIGH, HIGH,  LOW, HIGH, dotState}, // A
    {HIGH, HIGH, LOW,  LOW,  HIGH, HIGH, HIGH, dotState}, // B
    {LOW,  HIGH, HIGH, LOW,  HIGH, HIGH, LOW,  dotState}, // C
    {HIGH, LOW,  LOW,  HIGH, HIGH, HIGH, HIGH, dotState}, // D
    {HIGH, HIGH, HIGH, LOW, HIGH,  HIGH, LOW,  dotState}, // E
    {HIGH, HIGH, HIGH, LOW, HIGH,  LOW,  LOW,  dotState}  // F
 };
/*
  2
 1 3
  0
 4 6
  5  7
*/
const int button = 2;
const int base = 10;

int count = 0;
int lastState = 0;
int currentState = 0;

void setup() {
  //Serial.begin(9600);
  randomSeed(analogRead(0) * random(1, 123454312));
  pinMode(button, INPUT);
  for (int i = 0; i < 8; i++) {
    pinMode(segments[i], OUTPUT);
  }
  rotateClockwise(5);
  fillBlink(5, 125);
}

void loop() {
    currentState = digitalRead(button);
    if (currentState != lastState) {
      if (currentState == HIGH) {
        drawRandomNumber();
      }
    }
    lastState = currentState;
}

void displayNumber(int number) {
  for (int i = 0; i < 7; i++) {
    digitalWrite(segments[i], numbers[number][i]);
    segmentsState[i] = numbers[number][i];
  }
  digitalWrite(segments[7], dotState);
}

void clearDisplay(int clearDot, int clearState) {
  for (int i = 0; i < 7; i++) {
    digitalWrite(segments[i], LOW);
    if (clearState) {
      segmentsState[i] = LOW;
    }
  }
  if (clearDot) {
    digitalWrite(dotIndex, LOW);
    if (clearState) {
      dotState = LOW;
    }
  }
}

void fillDisplay(int fillDot) {
  for (int i = 0; i < 7; i++) {
    digitalWrite(segments[i], HIGH);
  }
  if (fillDot) {
    digitalWrite(dot, HIGH);
  }
}

void toggleDot() {
  if (dotState == LOW) {
    dotState = HIGH;
  } else {
    dotState = LOW;
  }
}

void rotateClockwise(int turns) {
  clearDisplay(0, 0);
  for (int i = 0; i < turns; i++) {
    for (int j = 0; j < 6; j++) {
      for (int k = 0; k < 6; k++) {
        if (k == j) {
          digitalWrite(orderedSegments[k], HIGH);
        } else {
          digitalWrite(orderedSegments[k], LOW);
        }
        delay(10);
      }
    }
  }
  clearDisplay(0, 0);
}

void fillBlink(int blinkTimes, int delayTime) {
  for (int i = 0; i < blinkTimes; i++) {
    fillDisplay(0);
    delay(delayTime);
    clearDisplay(0, 0);
    delay(delayTime);
  }
}

void fillWithState() {
  for (int i = 0; i < 8; i++) {
    digitalWrite(segments[i], segmentsState[i]);
  }
}

void blinkContent(int times, int interval) {
  for (int i = 0; i < times; i++) {
    clearDisplay(1, 0);
    delay(interval);
    fillWithState();
    delay(interval);
  }
}

void blinkRandom() {
  int number = random(0, base);
  int next = random(0, base);
  for (int i = 0; i < 15; i++) {
    displayNumber(number);
    delay(125);
    while (next == number) {
      next = random(0, base);
    }
    number = next;
  }
}

void drawRandomNumber() {
  int number = random(0, base);
  blinkRandom();
  displayNumber(number);
  blinkContent(3, 125);
}
