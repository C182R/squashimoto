// squashimoto controller
#include <Arduino.h>

constexpr int PIN_REAR_TX = 17;
constexpr int PIN_REAR_RX = 16;
constexpr int PIN_ESTOP   = 15;

constexpr uint32_t HOVER_BAUD          = 115200;
constexpr uint16_t START_FRAME         = 0xABCD;
constexpr uint32_t LOOP_PERIOD_MS      = 10;    // 100 Hz
constexpr uint32_t FEEDBACK_TIMEOUT_MS = 200;
constexpr int16_t  TORQUE_LIMIT        = 300;   
constexpr int16_t  TORQUE_SLEW         = 20;    

struct __attribute__((packed)) HoverCmd {
  uint16_t start;
  int16_t  steer;
  int16_t  speed;      
  uint16_t checksum;
};

struct __attribute__((packed)) HoverFeedback {
  uint16_t start;
  int16_t  cmd1, cmd2;
  int16_t  speedR_meas, speedL_meas;  // rpm
  int16_t  batVoltage;                // V x 100
  int16_t  boardTemp;                 // °C x 10
  uint16_t cmdLed;
  uint16_t checksum;
};

HardwareSerial& Rear = Serial2;
HoverFeedback fb{};
uint32_t lastFeedbackMs = 0;
bool     stopLatched    = true;   // boot stopped; must be re-armed
int16_t  applied        = 0;

DualSense and balance-loop modules
bool    controllerAlive();
int16_t requestedTorque();

void sendRear(int16_t steer, int16_t speed) {
  HoverCmd c{START_FRAME, steer, speed, 0};
  c.checksum = c.start ^ (uint16_t)c.steer ^ (uint16_t)c.speed;
  Rear.write(reinterpret_cast<const uint8_t*>(&c), sizeof(c));
}

void pollRear() {
  static uint8_t buf[sizeof(HoverFeedback)];
  static size_t  idx  = 0;
  static uint8_t prev = 0;

  while (Rear.available()) {
    uint8_t b = Rear.read();
    if (idx == 0) {
      if (prev == 0xCD && b == 0xAB) { buf[0] = 0xCD; buf[1] = 0xAB; idx = 2; }
      prev = b;
      continue;
    }
    buf[idx++] = b;
    if (idx == sizeof(buf)) {
      HoverFeedback f;
      memcpy(&f, buf, sizeof(f));
      uint16_t chk = f.start ^ f.cmd1 ^ f.cmd2 ^ f.speedR_meas ^ f.speedL_meas
                   ^ f.batVoltage ^ f.boardTemp ^ f.cmdLed;
      if (chk == f.checksum) { fb = f; lastFeedbackMs = millis(); }
      idx = 0; prev = 0;
    }
  }
}

void setup() {
  Serial.begin(115200);                      
  pinMode(PIN_ESTOP, INPUT_PULLUP);          
  Rear.begin(HOVER_BAUD, SERIAL_8N1, PIN_REAR_RX, PIN_REAR_TX);
}

void loop() {
  static uint32_t next = millis();
  pollRear();
  if ((int32_t)(millis() - next) < 0) return;
  next += LOOP_PERIOD_MS;

  bool estop  = digitalRead(PIN_ESTOP) == HIGH;
  bool linkOk = (millis() - lastFeedbackMs) < FEEDBACK_TIMEOUT_MS;
  int16_t want = constrain(requestedTorque(), -TORQUE_LIMIT, TORQUE_LIMIT);

  if (estop || !linkOk || !controllerAlive()) {
    stopLatched = true;
  } else if (stopLatched && abs(want) < 20) {
    stopLatched = false;   
  }

  if (stopLatched) {
    applied = 0;           
  } else {
    applied += constrain(want - applied, -TORQUE_SLEW, TORQUE_SLEW);
  }
  sendRear(0, applied);    

  static uint8_t n = 0;
  if (++n >= 10) {         
    n = 0;
    Serial.printf("trq %4d  %s  bat %.2f V  temp %.1f C  rpm %d/%d\n",
                  applied, stopLatched ? "STOP" : "RUN ",
                  fb.batVoltage / 100.0f, fb.boardTemp / 10.0f,
                  fb.speedL_meas, fb.speedR_meas);
  }
}


// bool    controllerAlive() { return false; }   // keeps it latched in STOP
// int16_t requestedTorque() { return 0; }
// for compilation