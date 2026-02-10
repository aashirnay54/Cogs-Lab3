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
const int encA = 3;
const int encB = 11;

// Photocell
const int photocellPin = A0;
int photocellValue = 0;
int threshold = 900;  // ADJUST THIS after calibration

// State: 0=waiting, 1=driving, 2=stopped
int state = 0;
bool autonomousMode = false;

// Telemetry
unsigned long lastPrintTime = 0;
const int PRINT_INTERVAL = 1000;
char currentCommand = 'e';
int motorASpeed = 0;
int motorBSpeed = 0;

// Encoder
volatile long encoderACount = 0;
volatile long encoderBCount = 0;
int lastEncAState = 0;
int lastEncBState = 0;

void setup() {
    pinMode(enA, OUTPUT);
    pinMode(in1, OUTPUT);
    pinMode(in2, OUTPUT);
    pinMode(enB, OUTPUT);
    pinMode(in3, OUTPUT);
    pinMode(in4, OUTPUT);
    pinMode(encA, INPUT_PULLUP);
    pinMode(encB, INPUT_PULLUP);
    
    lastEncAState = digitalRead(encA);
    lastEncBState = digitalRead(encB);
    
    Serial.begin(115200);
    Serial.println("time_ms,cmd,encA_count,encB_count,photocell,state");
}

void loop() {
    // Read encoders
    int encAState = digitalRead(encA);
    int encBState = digitalRead(encB);

    
    if (encAState != lastEncAState && encAState == HIGH) {
        encoderACount++;
    }
    if (encBState != lastEncBState && encBState == HIGH) {
        encoderBCount++;
    }
    lastEncAState = encAState;
    lastEncBState = encBState;
    
    // Read photocell
    photocellValue = analogRead(photocellPin);
    
    // Handle commands
    if (Serial.available()) {
        char c = Serial.read();
        currentCommand = c;
        
        if (c == 'm') {
            // Start autonomous mode
            autonomousMode = true;
            state = 0;
        }
        else if (c == 'e') {
            // Stop and return to manual
            autonomousMode = false;
            state = 0;
            stop();
        }
        else if (!autonomousMode) {
            // Manual controls
            switch (c) {
                case 'w': moveForward(); break;
                case 's': moveBackward(); break;
                case 'a': moveLeft(); break;
                case 'd': moveRight(); break;
                case 'q': turnRobotInPlace(); break;
                case 'r': encoderACount = 0; encoderBCount = 0; break;
            }
        }
    }
    
    // Autonomous behavior
    if (autonomousMode) {
        if (state == 0) {
            // Waiting on white tape
            if (photocellValue < threshold) {
                moveForward();
                state = 1;
            }
        }
        else if (state == 1) {
            // Driving on dark floor
            if (photocellValue > threshold) {
                stop();
                state = 2;
            }
        }
        // state 2: stay stopped
    }
    
    // Print telemetry
    unsigned long now = millis();
    if (now - lastPrintTime >= PRINT_INTERVAL) {
        Serial.print(now);
        Serial.print(',');
        Serial.print(currentCommand);
        Serial.print(',');
        Serial.print(encoderACount);
        Serial.print(',');
        Serial.print(encoderBCount);
        Serial.print(',');
        Serial.print(photocellValue);
        Serial.print(',');
        Serial.println(state);
        lastPrintTime = now;
    }
}   