#include <Servo.h>

#define PIN_LED   9
#define PIN_SERVO 10
#define PIN_TRIG  12
#define PIN_ECHO  13

#define SND_VEL 346.0
#define INTERVAL 25
#define PULSE_DURATION 10
#define _DIST_MIN 180
#define _DIST_MAX 360

#define TIMEOUT ((INTERVAL / 2) * 1000.0)
#define SCALE (0.001 * 0.5 * SND_VEL)

#define _EMA_ALPHA 0.5

unsigned long last_sampling_time;
float dist_prev = _DIST_MAX;
float dist_ema;

Servo myservo;

void setup() {
  pinMode(PIN_LED, OUTPUT);
  pinMode(PIN_TRIG, OUTPUT);
  pinMode(PIN_ECHO, INPUT);
  digitalWrite(PIN_TRIG, LOW);

  myservo.attach(PIN_SERVO); 
  myservo.write(0);

  Serial.begin(57600);

  dist_ema = _DIST_MIN;
}

void loop() {
  float dist_raw, dist_filtered;
  
  if (millis() < last_sampling_time + INTERVAL)
    return;

  dist_raw = USS_measure(PIN_TRIG, PIN_ECHO);

  if ((dist_raw < _DIST_MIN) || (dist_raw > _DIST_MAX)) {
    dist_filtered = dist_prev;
    digitalWrite(PIN_LED, LOW);
  } else {
    dist_filtered = dist_raw;
    dist_prev = dist_raw;
    digitalWrite(PIN_LED, HIGH);
  }

  dist_ema = _EMA_ALPHA * dist_filtered + (1.0 - _EMA_ALPHA) * dist_ema;

  int servo_angle = map((int)dist_ema, _DIST_MIN, _DIST_MAX, 0, 180);
  
  if (servo_angle < 0) servo_angle = 0;
  if (servo_angle > 180) servo_angle = 180;

  myservo.write(servo_angle);

  Serial.print("Min:");    Serial.print(_DIST_MIN);
  Serial.print(",dist:");  Serial.print(dist_raw);
  Serial.print(",ema:");   Serial.print(dist_ema);
  Serial.print(",Servo:"); Serial.print(myservo.read());
  Serial.print(",Max:");   Serial.print(_DIST_MAX);
  Serial.println("");

  last_sampling_time += INTERVAL;
}

float USS_measure(int TRIG, int ECHO)
{
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(PULSE_DURATION);
  digitalWrite(TRIG, LOW);
  
  float duration = pulseIn(ECHO, HIGH, TIMEOUT);
  
  if(duration == 0) return _DIST_MAX + 10.0; 
  
  return duration * SCALE;
}
