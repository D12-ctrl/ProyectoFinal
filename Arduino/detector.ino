#include <ArduinoHttpClient.h>
#include <ArduinoJson.h>
#include <WiFiNINA.h>

 /*Red Wifi*/
char ssid[] = "SoteloNetwork";
char password[] = "1turr1aga";

int status = WL_IDLE_STATUS;

char server[] = "ccaf-187-162-69-235.ngrok.io";    /*Servidor de ngrok*/

/*Declarar pines de leds*/
int ledVerde = 8;
int ledAmarillo = 7;
int ledRojo = 6;

WiFiClient client;

void setup(){
  Serial.begin(9600);

  while (status != WL_CONNECTED) {
    Serial.println("Attempting to connect to Network: ");
    Serial.println(ssid);
    status = WiFi.begin(ssid,password);
    delay (1000);
  }

  Serial.print("Connected to SSID: ");
  Serial.println(WiFi.SSID());
  IPAddress ip = WiFi.localIP();
  IPAddress gateway = WiFi.gatewayIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

}

void loop()
{
  /*Iniciar el JSON*/

  DynamicJsonDocument datos1(1024);
  DynamicJsonDocument datos2(1024);
  DynamicJsonDocument datos3(1024);

  /*Declaracion y lectura de sensores*/
  float sensor1 = analogRead(A0); /*MQ5*/
  float sensor2 = analogRead(A1); /*MQ7*/
  float sensor3 = analogRead(A2); /*MQ9*/
  
  /*Estado leds*/

 /* if(sensor1 < 150 && sensor2 < 80 && sensor3 < 80)
  {
    digitalWrite(ledVerde, HIGH);
    }
    else if(sensor1 > 150 && sensor2 > 80 && sensor3 > 80)
    {
      digitalWrite(ledAmarillo, HIGH);
      delay(1000);
      digitalWrite(ledAmarillo, LOW);
      
      }else if(sensor1 > 300 && sensor2 > 150 && sensor3 > 150)
      {
        
        digitalWrite(ledRojo, HIGH);
        
        }*/

     float voltaje1 = sensor1 * (5.0/1023.0);
     float Rs1 = 1000 * ((5.0 - voltaje1)/ voltaje1);
     float data1 = 78.378 * pow(Rs1/428, -2.533);

     float voltaje2 = sensor2 * (5.0/1023.0);
     float Rs2 = 1000 * ((5.0 - voltaje2)/ voltaje2);
     float data2 = 107.03 * pow(Rs2/408 -1.468);

     float voltaje3 = sensor3 * (5.0/1230);
     float Rs3 = 1000 * ((5.0 - voltaje3)/ voltaje3);
     float data3 = 4623.7 * pow(Rs3/428, - -2.659);
     
    datos1["valor"] = data1;
    datos1["idParametro"] = 1;
    datos1["idDispositivo"] = 1;
    
    datos2["valor"] = data2;
    datos2["idParametro"] = 2;
    datos2["idDispositivo"] = 2;
    
    datos3["valor"] = data3;
    datos3["idParametro"] = 3;
    datos3["idDispositivo"] = 3;
    

  String postdata1;
  String postdata2;
  String postdata3;

  serializeJson(datos1, postdata1);
  serializeJson(datos2, postdata2);
  serializeJson(datos3, postdata3);

  /*Añadir los datos al servidor*/

  if(client.connect(server, 80))
  {
    client.println("POST mediciones/agregar HTTP/1.1");
    client.println("Host: http://ccaf-187-162-69-235.ngrok.io");
    client.println("Content-Type: application/json");
    //client.println("Content-Length: ");
    //client.println(postdata1.length());
    client.println();
    client.print(postdata1);
    
    }

   if(client.connect(server, 80))
   {
    client.println("POST mediciones/agregar HTTP/1.1");
    client.println("Host: http://ccaf-187-162-69-235.ngrok.io");
    client.println("Content-Type: application/json");
    //client.print("Content-Length: ");
    //client.println(postdata2, length());
    client.println();
    client.print(postdata2);
    }

    if(client.connect(server, 80))
   {
    client.println("POST mediciones/agregar HTTP/1.1");
    client.println("Host: http://ccaf-187-162-69-235.ngrok.io");
    client.println("Content-Type: application/json");
    //client.print("Content-Length: ");
    //client.println(postdata3, length());
    client.println();
    client.print(postdata3);
    }
 
 if(client.connected())
 {
  client.stop();
  }
 
 Serial.println(postData1);
}
