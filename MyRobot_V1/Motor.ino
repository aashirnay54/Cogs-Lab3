/**
 * @file Motor.ino
 * @brief Simple H-bridge motor control helpers.
 *
 * Provides a minimal interface for driving a DC motor using
 * digital GPIO pins (e.g. Arduino-style platforms).
 *
 * The motor direction is controlled via two input pins,
 * while a separate enable pin turns the motor on or off.
 *
 * @author Paul Bucci
 * @date 2026
 */


/**
 * @brief Drives a DC motor in a fixed direction using an H-bridge.
 *
 * @param in1 GPIO pin connected to motor driver input 1 (direction control)
 * @param in2 GPIO pin connected to motor driver input 2 (direction control)
 * @param enA GPIO pin connected to motor driver enable pin (motor on/off)
 */




void drive(int in1, int in2, int enA) {
    digitalWrite(in1, LOW);   // Direction control: IN1
    digitalWrite(in2, HIGH);  // Direction control: IN2 (sets rotation direction)
    digitalWrite(enA, HIGH);  // Enable motor driver
}

void stop(int in1, int in2, int enA) {
    digitalWrite(in1, LOW);   // Direction control: IN1
    digitalWrite(in2, HIGH);  // Direction control: IN2 (sets rotation direction)
    digitalWrite(enA, LOW);   // Disable motor driver
}

// TODO: add your own driving functions here


void moveForward(int in1, int in2, int enA, int in3, int in4, int enB) {
    digitalWrite(int1, LOW);
    digitalWrite(int2, HIGH);
    digitalWrite(enA, HIGH);  


    digitalWrite(int3, LOW);
    digitalWrite(int4, HIGH);
    digitalWrite(enB, HIGH);  
}



void moveBackward(int in1, int in2, int enA, int in3, int in4, int enB) {

    digitalWrite(int1, HIGH);
    digitalWrite(int2, LOW);
    digitalWrite(enA, HIGH);  


    digitalWrite(int3, HIGH);
    digitalWrite(int4, LOW);
    digitalWrite(enB, HIGH); 

}


void moveRight(int in1, int in2, int enA, int in3, int in4, int enB) {

    digitalWrite(int1, LOW);
    digitalWrite(int2, HIGH);
    digitalWrite(enA, HIGH);  


    digitalWrite(int3, LOW);
    digitalWrite(int4, HIGH);
    digitalWrite(enB, LOW); 

}

void moveLeft(int in1, int in2, int enA, int in3, int in4, int enB) {

    digitalWrite(int1, LOW);
    digitalWrite(int2, HIGH);
    digitalWrite(enA, LOW);  


    digitalWrite(int3, LOW);
    digitalWrite(int4, HIGH);
    digitalWrite(enB, HIGH); 

}








