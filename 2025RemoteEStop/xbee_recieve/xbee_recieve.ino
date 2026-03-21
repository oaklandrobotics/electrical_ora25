// Onboard Module
#define RX 17
#define TX 16
#define ESTOP 5

unsigned long watchdog = 0; // Current time since last ping
unsigned long last_ping = 0; // Time of last ping
bool estopped = false;

void setup() {
  Serial2.begin(9600, SERIAL_8N1, RX, TX);
  pinMode(ESTOP, OUTPUT);
  digitalWrite(ESTOP, LOW);
}

void loop() {
  // Update Watchdog Time
  watchdog = millis() - last_ping;
  // Query XBEE
  if (Serial2.available()) {
    char data = Serial2.read();
    switch (data) {
      case 'h': // "Hey there"
        last_ping = millis();
        break;
      case 's': // "Stop"
        last_ping = millis();
        digitalWrite(ESTOP, HIGH);
        estopped = true;
        break;
      case 'g': // "Go"
        last_ping = millis();
        digitalWrite(ESTOP, LOW);
        estopped = false;
        break;
    }
  }
  // Determine if we need to stop based on Watchdog Time
  // TODO: Determine best timeout time based on latency
  if (watchdog >= 5000 && !estopped) { 
    digitalWrite(ESTOP, HIGH);
    estopped = true;
  }
}
