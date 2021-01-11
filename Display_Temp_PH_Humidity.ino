
#include <LiquidCrystal.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <dht.h>

// Data wire is plugged into pin 6 on the Arduino
#define ONE_WIRE_BUS 6

// Setup a oneWire instance to communicate with any OneWire devices 
// (not just Maxim/Dallas temperature ICs)
OneWire oneWire(ONE_WIRE_BUS);
 
// Pass our oneWire reference to Dallas Temperature.
DallasTemperature sensors(&oneWire);

//Humidity Sensor
dht DHT;
#define DHT11_PIN 7


/*  The circuit:
 * LCD RS pin to digital pin 12
 * LCD Enable pin to digital pin 11
 * LCD D4 pin to digital pin 5
 * LCD D5 pin to digital pin 4
 * LCD D6 pin to digital pin 3
 * LCD D7 pin to digital pin 2
 * LCD R/W pin to ground
 * LCD VSS pin to ground
 * LCD VCC pin to 5V
 * ends to +5V and ground
 * wiper to LCD VO pin (pin 3) 
*/

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

//PH SENSOR
const int PhSensor = A0;
int sensorValue = 0; 
unsigned long int avgValue; 
float b;
int buf[10],temp;

//Water Level Sensor
int resval = 0;
int respin = A5;


void setup() {
  lcd.begin(16, 2);
  
  Serial.begin(115200);
  Serial.println();

  Serial.println("Dallas Temperature IC Control Library Demo");

  // Start up the library
  sensors.begin();
}

void loop() {
  
 // WATER TEMP SENSOR 
   // call sensors.requestTemperatures() to issue a global temperature
  // request to all devices on the bus
  Serial.print(" Requesting temperatures...");
  sensors.requestTemperatures(); // Send the command to get temperatures
  Serial.println("DONE");

  Serial.print("Temperature is: ");
  Serial.print(sensors.getTempCByIndex(0)); // Why "byIndex"? 
    // You can have more than one IC on the same bus. 
    // 0 refers to the first IC on the wire
    delay(10);

 //WATER TEMP DISPLAY
  lcd.setCursor(0,0);
  lcd.print("Water Temp:");
  lcd.println(sensors.getTempCByIndex(0));
  //  delay(2000);
  // Turn on the display:
  lcd.display();
  //delay(2000); 


  //PH SENSOR
  
  for(int i=0;i<10;i++) 
 { 
  buf[i]=analogRead(PhSensor);
  delay(10);
 }
 for(int i=0;i<9;i++)
 {
  for(int j=i+1;j<10;j++)
  {
   if(buf[i]>buf[j])
   {
    temp=buf[i];
    buf[i]=buf[j];
    buf[j]=temp;
   }
  }
 }
 avgValue=0;
 for(int i=2;i<8;i++)
 avgValue+=buf[i];
 float pHVol=(float)avgValue*5.0/1024/6;
 float phValue = -4.70 * pHVol + 21.34;
 Serial.print(" Ph Level = ");
 Serial.println(phValue);
 
  //PH Display
   lcd.setCursor(0,1);
  lcd.print("Ph Level:   ");
  lcd.println(phValue);
    delay(1000);
  // Turn on the display:
  lcd.display();
  delay(1000);
  
  //HUMIDITY SENSOR/AMBIENT TEMP SENSOR
  int chk = DHT.read11(DHT11_PIN);
  Serial.print("Temperature = ");
  Serial.println(DHT.temperature);
  Serial.print("Humidity = ");
  Serial.println(DHT.humidity);
  delay(10);

  lcd.setCursor(0,0);
  lcd.print("Amb Temp:  ");
  lcd.println(DHT.temperature);
  delay(1000);
  lcd.setCursor(0,1);
  lcd.print("Humidity:  ");
  lcd.println(DHT.humidity);
  delay(2000);

  delay(000);

//WATER LEVEL SENSOR

  resval = analogRead(respin);
  if (resval<=100){Serial.println("Water Level:Empty");} 
    else if (resval>100 && resval<=300){Serial.println("Water Level: Low");} 
    else if(resval<=330){Serial.println("Water Level: Medium");} 
    else if (resval>330){Serial.println("Water Level: High");
    }
    delay(1000);
  
 }

  
  
