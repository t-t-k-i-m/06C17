const int ledPin = 7;
int period_us = 1000;       // 1ms 
int duty_percent = 0;       // 현재 duty
int on_time = 0;            // 켜진 시간
int steps = 100;            // 밝기 단계 (0~100 = 101단계)
int step_delay_us = 5000;   // 각 단계 유지 시간 (0.5초 / 101단계 ≈ 5ms)

void setup() {
  pinMode(ledPin, OUTPUT);
}

// duty에 따라 on_time 계산
void set_duty(int duty) {
  duty_percent = constrain(duty, 0, 100);
  on_time = (period_us * duty_percent) / 100;
}

// 소프트 PWM: 각 단계에서 반복
void softPWM(int repeat) {
  // 0% → LED 완전 OFF
  if(duty_percent == 0) {
    digitalWrite(ledPin, 0);
    delayMicroseconds(repeat * period_us);
    return;
  }

  // 100% → LED 완전 ON
  if(duty_percent == 100) {
    digitalWrite(ledPin, 1);
    delayMicroseconds(repeat * period_us);
    return;
  }

  int off_time = period_us - on_time;
  for(int i = 0; i < repeat; i++) {
    digitalWrite(ledPin, 1);
    delayMicroseconds(on_time);
    digitalWrite(ledPin, 0);
    delayMicroseconds(off_time);
  }
}

void loop() {
  for(int duty = 0; duty <= steps; duty++) {
    set_duty(duty);
    int repeat = max(1, step_delay_us / period_us); // 최소 1회 반복
    softPWM(repeat);
  }

  for(int duty = steps; duty >= 0; duty--) {
    set_duty(duty);
    int repeat = max(1, step_delay_us / period_us);
    softPWM(repeat);
  }
}
