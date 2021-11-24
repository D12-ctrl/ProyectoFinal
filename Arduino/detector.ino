#include <WiFiNINA.h>
#include <ArduinoJson.h>


/*Configuracion de la red Wifi*/

    /*Establecer los datos de la red*/
char ssid = "";
char password = "";

/*Estatus de la red*/
int status = WL_IDLE_STATUS;


char server[] = "";

String postData;
WiFiClient client;

/*Pines del buzzer y leds*/
int buzzer = 4;
int ledVerde = 6;
int ledAmarillo = 7;
int ledNaranja = 8;
int ledRojo = 9;

void setup()
{
    Serial.begin(9600);

    /*Ciclo mostrando el estatus de conexion*/
    while (status != WL_CONNECTED)
    {
        Serial.print("Attemptin to connect to Network: ")    
    }
    
}

void loop()
{
    DynamicJsonDocument data(1024);

    int sensor1 = analogRead(A0); /*MQ135 = calidad del aire*/
    int sensor2 = analogRead(A1); /*MQ7 = Monoxido de carbono*/
    int sensor3 = analogRead(A2); /*MQ9 = Combustible en el ambiente*/

    /*if calidad del aire > cierto valor
        se dispara el buzzer
        
        if concentraciones de monoxido and calidad del aire and combustible en el ambiente
            se enciende led verde o amarillo o rojo 
            dependiendo del valor
            */
    data["Calidad del aire:  "] = sensor1;
    data["Monoxido de carbono: "] = sensor2;
    data["Combustible en el ambiente: "] = sensor3;

    /*Calcular el valor del sensor 1 en ICA (indice de calidad del aire)*/
    /*Calcular sensor2  en ppm (partes por millon)*/
    /*Calcular sensor3 en ppb (partes por billon)*/

}