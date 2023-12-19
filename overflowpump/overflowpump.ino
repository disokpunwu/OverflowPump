int sensorPin = 2;
int relay_1 = 4;
int relay_2 = 7;
int relay_3 = 8;
int relay_4 = 12;
volatile long pulse;
bool ledState = false;
long lastPulse;

void setup() {
  Serial.begin(9600);
  pinMode(sensorPin, INPUT_PULLUP);
  pinMode(relay_1, OUTPUT);
  pinMode(relay_2, OUTPUT);
  pinMode(relay_3, OUTPUT);
  pinMode(relay_4, OUTPUT);
  pinMode(13, OUTPUT);
  pulse = 0;
  lastPulse = 0;
  attachInterrupt(digitalPinToInterrupt (sensorPin), increase, RISING);
}

void increase() {
  pulse++;
}

void loop() {
  delay(500);
  
  Serial.println(pulse*0.006/0.5);

  if (pulse > 0 && lastPulse == 0) {
    digitalWrite(relay_1, HIGH);
    digitalWrite(relay_2, HIGH);
    Serial.println("Overflow Pumps On");
  } else if (lastPulse != 0 && pulse == 0) {
  digitalWrite(relay_1, LOW);
  digitalWrite(relay_2, LOW);
  Serial.println("Overflow Pumps Off");
  }
  lastPulse = pulse;
  pulse = 0;

  digitalWrite(13, ledState);
  ledState = !ledState;
}
