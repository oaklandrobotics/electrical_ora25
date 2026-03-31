// Remote Module
#define RX 17
#define TX 16
#define ESTOP 5

unsigned long sent_delay = 0;
unsigned long last_write = 0;
bool estopped = false;

void setup() {
  Serial2.begin(9600, SERIAL_8N1, RX, TX);
  pinMode(ESTOP, INPUT);
}

void loop() {
  sent_delay = millis() - last_write;
  if (sent_delay >= 1000) {
    last_write = millis();
    Serial2.write('h');
  }
  if (digitalRead(ESTOP) == HIGH && !estopped) {
    last_write = millis();
    Serial2.write('s');
    estopped = true;
  }
  if (digitalRead(ESTOP) == LOW && estopped) {
    last_write = millis();
    Serial2.write('g');
    estopped = false;
  }
}
