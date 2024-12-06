#define BLYNK_TEMPLATE_ID "TMPL3MF6JSr1M"
#define BLYNK_TEMPLATE_NAME "IOT"
#define BLYNK_AUTH_TOKEN "Missing"

//BLYNK Library Initalization.
#define BLYNK_PRINT Serial
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

BlynkTimer timer;

//BLYNK Variables
char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "ONEPLUS8";
char pass[] = "kg@12345";

// UltraSonic Sensor Pins and Variable Declarations
int echoPin = 19;
int trigPin = 18;
double t;
int distance;

int Moist_Sen =2;
int Moist_Sen_V;

int Cond_Sen = 23;
int Cond_Sen_V;

#include <DHT.h>
#define DHTPIN 5   
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);
float temp;
float humid;

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,2);//SCL 22   //SDA 21

#include <OneWire.h>
#include <DallasTemperature.h>
#define ONE_WIRE_BUS 4
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);


void setup() 
{
  Serial.begin(9600);
  dht.begin();
  sensors.begin();
  Blynk.begin(auth, ssid, pass); 
  
  pinMode(trigPin,OUTPUT);
  pinMode(echoPin,INPUT);

  pinMode(Cond_Sen,INPUT);
  pinMode(Moist_Sen,INPUT);
  
  timer.setInterval(2000,Sensor_loop);
  
  lcd.init(); // Initialize the LCD
  lcd.backlight(); // Turn on the backlight
  lcd.clear();
}


void loop ()
{
  
  Blynk.run();
  timer.run();
  
}


void Sensor_loop()
{
    //Getting the Ultrasonic Sensor Value.
    digitalWrite(trigPin,LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin,HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin,LOW);
    t=pulseIn(echoPin,HIGH);
    distance=(t*0.034/2);

    Moist_Sen_V = digitalRead(Moist_Sen);

    Cond_Sen_V = digitalRead(Cond_Sen);
    
    temp = dht.readTemperature();
    humid = dht.readHumidity();

    lcd.clear();
    
    Blynk.virtualWrite(V0,"Water level: "+String(distance));
    Serial.println("WATER LEVEL : "+String(distance));
    lcd.setCursor(0,0);
    lcd.print("WL:"+String(distance));
    
    Blynk.virtualWrite(V1,"Soil Moisture: "+String(Moist_Sen_V));
    Serial.println("Soil Moisture: "+String(Moist_Sen_V));
    
    Blynk.virtualWrite(V2,"Soil Cond: "+String(Cond_Sen_V));
    Serial.println("Soil Cond: "+String(Cond_Sen_V));
    
    Blynk.virtualWrite(V3,"Temperature: "+String(temp));
    Serial.println("Temperature: "+String(temp));
    lcd.setCursor(8,0);
    lcd.print("T:"+String(temp));

    Blynk.virtualWrite(V4,"Humidity: "+String(humid));
    Serial.println("Humidity: "+String(humid));
    lcd.setCursor(0,1);
    lcd.print("H:"+String(humid));
    
    sensors.requestTemperatures();
    float temperatureC = sensors.getTempCByIndex(0);
    Serial.print("Temperature: ");
    Serial.print(temperatureC);
    Serial.println("C");
    Blynk.virtualWrite(V5,"Water Turbidity: "+String(temperatureC));
    Serial.println("Water Turbidity: "+String(temperatureC));
    lcd.setCursor(8,1);
    lcd.print("WT:"+String(temperatureC));

    delay(3000);

}
