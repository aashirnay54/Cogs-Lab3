// MyRobot-V1.ino

// Motor A pins
const int enA = 9;
const int in1 = 8;
const int in2 = 7;

// Motor B pins
const int enB = 5;
const int in3 = 4;
const int in4 = 2;

// Encoder pins
const int encA = 3;  // Use interrupt-capable pins if possible
const int encB = 11;

// Telemetry variables
unsigned long lastPrintTime = 0;
const int PRINT_INTERVAL = 50;  // Print every 50ms (20 Hz)
char currentCommand = 'e';      // Track current movement command
int motorASpeed = 0;
int motorBSpeed = 0;

// Encoder tick counters (volatile for interrupt use later)
volatile long encoderACount = 0;
volatile long encoderBCount = 0;
int lastEncAState = 0;
int lastEncBState = 0;

void setup() {
    // Motor pins
    pinMode(enA, OUTPUT);
    pinMode(in1, OUTPUT);
    pinMode(in2, OUTPUT);
    pinMode(enB, OUTPUT);
    pinMode(in3, OUTPUT);
    pinMode(in4, OUTPUT);
    
    // Encoder pins
    pinMode(encA, INPUT_PULLUP);
    pinMode(encB, INPUT_PULLUP);
    
    // Initialize encoder states
    lastEncAState = digitalRead(encA);
    lastEncBState = digitalRead(encB);
    
    Serial.begin(115200);
    
    // Print CSV header for easy parsing
    Serial.println("time_ms,cmd,encA_raw,encB_raw,encA_count,encB_count,motorA_spd,motorB_spd");
}

void loop() {
    // Read encoder states
    int encAState = digitalRead(encA);
    int encBState = digitalRead(encB);
    
    // Simple edge counting (rising edge)
    if (encAState != lastEncAState && encAState == HIGH) {
        encoderACount++;
    }
    if (encBState != lastEncBState && encBState == HIGH) {
        encoderBCount++;
    }
    lastEncAState = encAState;
    lastEncBState = encBState;
    
    // Handle serial commands
    if (Serial.available()) {
        char c = Serial.read();
        currentCommand = c;
        
        switch (c) {
            case 'w':
                moveForward(in1, in2, enA, in3, in4, enB);
                break;
            case 's':
                moveBackward(in1, in2, enA, in3, in4, enB);
                break;
            case 'a':
                moveLeft(in1, in2, enA, in3, in4, enB);
                break;
            case 'd':
                moveRight(in1, in2, enA, in3, in4, enB);
                break;
            case 'q':
                turnRobotInPlace(in1, in2, enA, in3, in4, enB);
                break;
            case 'e':
                stop(in1, in2, enA, in3, in4, enB);
                break;
            case 'r':  // Reset encoder counts
                encoderACount = 0;
                encoderBCount = 0;
                break;
        }
    }
    
    // Print telemetry at fixed interval
    unsigned long now = millis();
    if (now - lastPrintTime >= PRINT_INTERVAL) {
        printTelemetry(now, encAState, encBState);
        lastPrintTime = now;
    }
}

void printTelemetry(unsigned long timestamp, int encARaw, int encBRaw) {
    // Format: time_ms,cmd,encA_raw,encB_raw,encA_count,encB_count,motorA_spd,motorB_spd
    Serial.print(timestamp);
    Serial.print(',');
    Serial.print(currentCommand);
    Serial.print(',');
    Serial.print(encARaw);
    Serial.print(',');
    Serial.print(encBRaw);
    Serial.print(',');
    Serial.print(encoderACount);
    Serial.print(',');
    Serial.print(encoderBCount);
    Serial.print(',');
    Serial.print(motorASpeed);
    Serial.print(',');
    Serial.println(motorBSpeed);
}