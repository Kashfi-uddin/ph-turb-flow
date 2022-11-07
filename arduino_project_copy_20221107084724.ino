#include <Arduino_FreeRTOS.h>
#include <ArduinoJson.h>
#include <SoftwareSerial.h>

#define ph_sensor A1
#define turbidity_sensor A0

SoftwareSerial nodemcu(15,14);
float ph_value,sensor_value;
int turbidity;



void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  nodemcu.begin(9600);

  xTaskCreate(ph,"ph",100,NULL,4,NULL);
  xTaskCreate(turb,"turb",100,NULL,3,NULL);
  xTaskCreate(json,"json",2043,NULL,2,NULL);
  vTaskStartScheduler();
  
}

void loop() {
  // put your main code here, to run repeatedly:

}





void ph(void*pvparameters)
{
  ph_value=analogRead(ph_sensor);
  sensor_value= ph_value;
  Serial.print("ph_value= ");
  Serial.println(sensor_value);
  vTaskDelay(1000/portTICK_PERIOD_MS);
}

void turb(void*pvparameters)
{
  turbidity=analogRead(turbidity_sensor);
  Serial.print("turbidity= ");
  Serial.println(turbidity);
  vTaskDelay(1000/portTICK_PERIOD_MS);
}



void json(void*pvparameters)
{
  StaticJsonBuffer<1000> jsonBuffer;
  JsonObject& doc = jsonBuffer.createObject();
  doc["ph"] = sensor_value;
  doc["turb"] = turbidity ;
  doc.printTo(nodemcu);
  jsonBuffer.clear();
  vTaskDelay(1000/portTICK_PERIOD_MS);
}


