#include <DallasTemperature.h>
#include <OneWire.h>

/*
 * TODO:
 * 1) микроядро:
 *  - спящий режим
 *  - таймеры
 *  - маска событий
 * 2) контрольная сумма для пакетов телеметрии (CRC | ROT13 | ?)
 * 3) DS1820 с паразитным питанием
 * 4) GitHub
 */
 #define PIN_DS18B20 8
 #define buttonPin  3
 #define ledPin  LED_BUILTIN
 
 int buttonState = 0;
 int buttonState0 = 0;

 OneWire oneWire(PIN_DS18B20);
 DallasTemperature ds(&oneWire);
 //DeviceAddress sensorAddress;  // Специальный объект для хранения адреса устройства
 DeviceAddress dsAddr[4];
 int nDevs;

// Вспомогательная функция для отображения адреса датчика ds18b20
void printTemperature(DeviceAddress deviceAddress){
  float tempC = ds.getTempC(deviceAddress);
  Serial.print("Temp C: ");
  Serial.println(tempC);
}

void setup() {
  //pinMode(LED_BUILTIN, OUTPUT);
  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT);
  Serial.begin(9600);
  Serial.println("Hello StratoSAT");
  
  ds.begin();
  nDevs = ds.getDeviceCount();
  Serial.print("Found ");
  Serial.print(nDevs, DEC);
  Serial.println(" devices");
  int i; for(i=0; i<nDevs; i++) ds.getAddress(dsAddr[i],i);
}

void loop() {
  ds.requestTemperatures(); // Просим ds18b20 собрать данные
  buttonState = digitalRead(buttonPin);
  if (buttonState == HIGH) {
    digitalWrite(ledPin, HIGH);
    if(buttonState!=buttonState0) Serial.println('+');
  } else {
    digitalWrite(ledPin, LOW);
    if(buttonState!=buttonState0) Serial.println('-');
  }
  buttonState0 = buttonState;
  printTemperature(dsAddr[0]);
}
