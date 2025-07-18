#include <SoftwareSerial.h>
#include <LiquidCrystal.h>
#include <dht.h>

// Bluetooth module (HC-05) on pins 10 (TX) and 2 (RX)
SoftwareSerial EEBlue(10, 2);

// LCD on pins 8, 9, 4, 5, 6, 7
LiquidCrystal mlcd(8, 9, 4, 5, 6, 7);

// DHT11 setup
#define dht_apin A7
#define DHT_max_temp 30
dht DHT;  // Sensor pin S to pin 11

// Sensors and buzzer
int buzzer = 12;
int flame_sensor = 11;
int flame_detected;
float sensor = A8;  // Gas sensor
float gas_value;
int sensorThres = 200;

void setup() {
  Serial.begin(9600);
  pinMode(buzzer, OUTPUT);
  pinMode(flame_sensor, INPUT);
  pinMode(sensor, INPUT);

  mlcd.begin(16, 2);
  EEBlue.begin(9600); 
  
  Serial.println("The Bluetooth gates are open.\nConnect to HC-05 from any other "
                 "Bluetooth device with 1234 as pairing key!.");
}

void loop() {
  // Bluetooth passthrough
  if (EEBlue.available())
    Serial.write(EEBlue.read());
  if (Serial.available())
    EEBlue.write(Serial.read());

  // Flame sensor check
  flame_detected = digitalRead(flame_sensor);
  if (flame_detected == 1) {
    Serial.println("Flame detected...!");
    digitalWrite(buzzer, HIGH);
  } else {
    Serial.println("No flame detected.");
    digitalWrite(buzzer, LOW);
  }
  delay(1000);

  // Read DHT11 sensor data
  DHT.read11(dht_apin);
  mlcd.setCursor(0, 0);
  mlcd.print(" Humidity = ");
  mlcd.print(DHT.humidity);
  mlcd.setCursor(0, 1);
  mlcd.print(" Temp = ");
  mlcd.print(DHT.temperature);
  mlcd.println(" C ");
  delay(250);

  // Gas sensor reading
  gas_value = analogRead(sensor);
  Serial.println(gas_value);
  if (gas_value > sensorThres) {
    tone(buzzer, 1000, 200);
  } else {
    noTone(buzzer);
  }
  delay(100);

  // Over-temperature alarm
  if (DHT.temperature >= DHT_max_temp) {
    tone(buzzer, 1000, 200);
  } else {
    noTone(buzzer);
  }
  delay(100);
}
