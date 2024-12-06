#include <Servo.h> //import library
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <MHZ19.h>

Servo myservo; 

int led = 13;

Servo myservo1;   

int led1 = 12;
#define CO2_TX_PIN 3
#define CO2_RX_PIN 2
MHZ19 co2Sensor;

LiquidCrystal_I2C lcd(0x27, 16, 2);  // I2C address 0x27, 16 columns, 2 rows


void setup() 

{ 

pinMode(led, OUTPUT); 



   myservo.attach(9, 500, 2500);   



  pinMode(led1, OUTPUT);



  myservo1.attach(10, 500, 2500);
   Serial.begin(9600);
  
  // Start LCD
  lcd.begin();
  lcd.backlight();
  lcd.clear();
  // Initialize the CO2 sensor
  co2Sensor.begin(CO2_TX_PIN, CO2_RX_PIN);
  co2Sensor.setAutoCalibration(false);  // Disable auto-calibration (optional)
  
  // Display initial message on LCD
  lcd.setCursor(0, 0);
  lcd.print("CO2 Sensor Init...");
  delay(2000);
  lcd.clear();

} 

void loop() 

{ 
     int co2Concentration = co2Sensor.getCO2();
  
  // Check if sensor is available and valid
  if (co2Concentration >= 0) {
    // Print CO2 value to serial monitor
    Serial.print("CO2: ");
    Serial.print(co2Concentration);
    Serial.println(" ppm");

    // Display CO2 value on LCD
    lcd.setCursor(0, 0);  // Set cursor to the first line
    lcd.print("CO2: ");
    lcd.print(co2Concentration);
    lcd.print(" ppm");
  } else {
    // Handle error if the sensor does not return a valid value
    lcd.setCursor(0, 0);
    lcd.print("Error: Sensor");
    lcd.setCursor(0, 1);
    lcd.print("Unavailable");
  }

  // Wait 2 seconds before updating the display
  delay(2000);

    // Rotate Servo 3 by 180 degree

  myservo.write(90);

  myservo1.write(0);

  delay(10); 

 digitalWrite(led, HIGH);   

  delay(8000);              

  digitalWrite(led, LOW);  

  myservo.write(0);

  myservo1.write(0);

  delay(1000); 

  myservo.write(0);

  myservo1.write(90);

  delay(10); 

   digitalWrite(led1, HIGH);   

  delay(8000);               

  digitalWrite(led1, LOW);    

  myservo.write(0);

  myservo1.write(0);

  delay(1000); 

  //

}