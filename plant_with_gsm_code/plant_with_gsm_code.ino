
#include <WiFi.h>
#include <HTTPClient.h>
#include <Wire.h>


#include "DHT.h"
#define DHTPIN 23
#define DHTTYPE DHT11

HardwareSerial GsmModule(2);
static const uint32_t GPSBaud = 9600;
int h;
int t;


DHT dht(DHTPIN, DHTTYPE);
String url;
const char* ssid     = "C4-Projexels";
const char* password = "321ytrewq";
String host = "http://192.168.18.62/";   // system ip address


String PhoneNumber = "+9233312345678";
String Message = "";

int soil_sensor_pin1 = 32;
int soil_sensor_pin2 = 33;
int soilmoisture1;
int soilmoisture2;
int buzz = 19;

void setup() {
  Serial.begin(9600);
  Wire.begin();
  GsmModule.begin(GPSBaud , SERIAL_8N1, 16, 17);                                // to send data from arduino nano to nod mcu esp9266 serially
  dht.begin();
  pinMode(soil_sensor_pin1, INPUT);
  pinMode(soil_sensor_pin2, INPUT);
  pinMode(buzz, OUTPUT);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.print("Connecting...");


  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");

    delay(300);
  }
  Serial.println();
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
  delay(2000);




}

void loop() {
  // This sketch displays information every time a new sentence is correctly encoded.
  h = dht.readHumidity();
  t = dht.readTemperature();
  soilmoisture1 = analogRead(soil_sensor_pin1);
  soilmoisture1 = map(soilmoisture1, 0, 4095 , 100, 0);
  soilmoisture2 = analogRead(soil_sensor_pin2);
  soilmoisture2 = map(soilmoisture2, 0, 4095 , 100, 0);


  // printing on a serial monitor
  Serial.print(F("Humidity: "));  Serial.print(h);
  Serial.print(F("%  Temperature: "));
  Serial.print(t);
  Serial.print(F("°C "));
  Serial.println(" ");
  Serial.print("Moisture Level1: ");
  Serial.print(soilmoisture1);
  Serial.println("%");
  Serial.print("Moisture Level2: ");
  Serial.print(soilmoisture2);
  Serial.println("%");


  if (soilmoisture1 <  20 || soilmoisture2 < 20 )
  {
    Message = "Plant moisture level Alert";
    Send_Message(Message);
    digitalWrite(buzz, HIGH );   //ON
    delay(500);
    digitalWrite(buzz, LOW );   //ON
    delay(10000);
  }

delay(10000);

datasend();
delay(2000);
}



void Send_Message(String x)
{
  lcd.clear();
  Serial.println(x);
  GsmModule.begin(9600);
  GsmModule.println("AT");
  delay(500);
  GsmModule.println("AT+CMGF=1");
  delay(500);
  GsmModule.println("AT+CMGS=\"" + PhoneNumber + "\"\r");
  delay(500);
  //-----message body
  GsmModule.print(x + " Temperature:" + t + "*C ," + " Humidity:" + h + " % ," +  "Moisture1=" +  soilmoisture1 +"% ," + " Moisture2=" +  soilmoisture2+ "%" );
  delay(200);
  GsmModule.println((char)26);
  delay(200);
  Serial.println("SMS Send");
  lcd.setCursor(0, 1);
  lcd.print("    SMS-SEND    ");
  delay(1000);
  lcd.clear();
}




void datasend()
{
  HTTPClient http;
  url = host + "plantcare/hit.php?t=" + t + "&h=" + h +  "&m1=" +  soilmoisture1 + "&m2=" +  soilmoisture2;
  Serial.println(url);
  http.begin(url);
  int statusCode = http.GET();
  http.end();
  delay(1000);
}
