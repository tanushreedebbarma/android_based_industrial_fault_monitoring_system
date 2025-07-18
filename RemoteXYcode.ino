#define REMOTEXY_MODE__SOFTSERIAL
#include <SoftwareSerial.h>
#include <RemoteXY.h>

#define REMOTEXY_SERIAL_RX 11
#define REMOTEXY_SERIAL_TX 10
#define REMOTEXY_SERIAL_SPEED 9600

#pragma pack(push, 1)
// RemoteXY GUI configuration
uint8_t RemoteXY_CONF[] = {
  255,0,0,44,0,98,0,8,43,0,
  129,0,12,6,35,6,17,70,108,97,
  109,101,0,67,4,60,7,20,5,2,
  26,11,129,0,12,19,18,6,17,71,
  97,115,0,67,4,60,19,20,5,2,
  26,11,129,0,11,33,18,6,17,84,
  101,109,112,101,114,97,116,117,114,101,
  0,67,4,60,33,20,5,2,26,11,
  67,4,59,49,20,5,2,26,11,129,
  0,11,49,18,6,17,72,117,109,105,
  100,105,116,121,0
};

// RemoteXY variables structure
struct {
  char text_1[11];
  char text_2[11];
  char text_3[11];
  char text_4[11];
  uint8_t connect_flag;
} RemoteXY;

#pragma pack(pop)

#include <LiquidCrystal.h>
#include <dht.h>

LiquidCrystal mlcd(8, 9, 4, 5, 6, 7);

#define dht_apin 2
#define DHT_max_temp 35
dht DHT;

int chk;
float hum;
float temp;
int buzzer = 13;
int flame_sensor = 12;
int flame_detected;
float sensor = A8;
float gas_value;
int sensorThres = 200;

void setup() {
  RemoteXY_Init();
  Serial.begin(9600);
  mlcd.begin(16, 2);
  pinMode(buzzer, OUTPUT);
  pinMode(flame_sensor, INPUT);
  pinMode(sensor, INPUT);
}

void loop() {
  RemoteXY_Handler();
  delay(2000);

  // Read temperature and humidity
  DHT.read22(dht_apin);
  mlcd.setCursor(0, 0);
  mlcd.print(" Humidity = ");
  mlcd.print(DHT.humidity);
  mlcd.setCursor(0, 1);
  delay(100);

  // Update RemoteXY fields
  dtostrf(flame_detected, 0, 1, RemoteXY.text_1);
  dtostrf(gas_value, 0, 1, RemoteXY.text_2);

  // Flame sensor state for RemoteXY display
  if (digitalRead(12) == HIGH) {
    strcpy(RemoteXY.text_1, "High");
  } else {
    strcpy(RemoteXY.text_1, "Low");
  }
}
