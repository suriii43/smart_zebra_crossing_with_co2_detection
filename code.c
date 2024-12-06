#include <Servo.h> // Import library for controlling servo motors
#include <NewPing.h> // Import library for ultrasonic sensor

Servo myservo;       // Create Servo object for servo motor 1
Servo myservo1;      // Create Servo object for servo motor 2

int led = 13;        // LED pin for servo 1 status
int led1 = 12;       // LED pin for servo 2 status

// Pin definitions for the ultrasonic sensor
const int triggerPin = 7; // Trigger pin for ultrasonic sensor
const int echoPin = 6;    // Echo pin for ultrasonic sensor

// Initialize the ultrasonic sensor
NewPing sonar(triggerPin, echoPin, 200); // Maximum distance 200 cm

// Pin for smoke sensor (MQ-2)
int smokeSensorPin = A0;  // Analog pin for smoke sensor

void setup() {
  pinMode(led, OUTPUT);    // Set LED pin as output
  pinMode(led1, OUTPUT);   // Set LED pin as output
  pinMode(smokeSensorPin, INPUT);  // Set smoke sensor pin as input

  myservo.attach(9, 500, 2500);   // Attach first servo to pin 9 with a 500-2500ms pulse width range
  myservo1.attach(10, 500, 2500); // Attach second servo to pin 10 with a 500-2500ms pulse width range
}

void loop() {
  // Read distance from ultrasonic sensor
  int distance = sonar.ping_cm(); // Distance in cm
  
  // Read smoke sensor value
  int smokeValue = analogRead(smokeSensorPin);

  // Check if smoke is detected (assuming a threshold value for smoke detection)
  bool smokeDetected = (smokeValue > 300);  // Adjust threshold as necessary
  
  // If smoke is detected and the barricade is close (distance < 10 cm), perform actions
  if (smokeDetected && distance < 10) {
    // Rotate servo motors to activate the system
    myservo.write(90);  // Move servo 1 to 90 degrees
    myservo1.write(0);  // Move servo 2 to 0 degrees
    
    digitalWrite(led, HIGH);    // Turn on LED 1
    delay(8000);                // Wait for 8 seconds
    digitalWrite(led, LOW);     // Turn off LED 1
    
    myservo.write(0);  // Return servo 1 to 0 degrees
    myservo1.write(0); // Return servo 2 to 0 degrees
    delay(1000);       // Wait for 1 second
    
    // Rotate servo motors again for a different position
    myservo.write(0);  // Keep servo 1 at 0 degrees
    myservo1.write(90); // Move servo 2 to 90 degrees
    
    digitalWrite(led1, HIGH);  // Turn on LED 2
    delay(8000);               // Wait for 8 seconds
    digitalWrite(led1, LOW);   // Turn off LED 2
    
    myservo.write(0);  // Return servo 1 to 0 degrees
    myservo1.write(0); // Return servo 2 to 0 degrees
    delay(1000);       // Wait for 1 second
  } else {
    // If no smoke is detected or the barricade is far away, stop servos and LEDs
    myservo.write(0);
    myservo1.write(0);
    digitalWrite(led, LOW);
    digitalWrite(led1, LOW);
  }
}
