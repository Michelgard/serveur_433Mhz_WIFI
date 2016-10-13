#include <ESP8266WiFi.h>
#include <RCSwitch.h>

const char* ssid = ""; //le nom de votre reseau WIFI
const char* password = ""; // Votre mot de passe

// Création du serveur
// avec le port découte des requètes HTML
WiFiServer server(90);

RCSwitch rf_cmd = RCSwitch(); // initialisation de la partie 433Mhz
const char rf_mode = 24; // mode 24 bits
const char rf_pin = 4; // l'emetteur est connecte au pin 4 de l'arduino

//tableau des arguments de la requète HTTP
char *led[] = {"/LED1/ON", "/LED1/OFF", "/LED2/ON", "/LED2/OFF", "/LED3/ON", "/LED3/OFF", 
"/LED4/ON", "/LED4/OFF", "/LED5/ON", "/LED5/OFF", "/LED6/ON", "/LED6/OFF", 
"/LEDA/ON", "/LEDA/OFF", "/LEDB/ON", "/LEDB/OFF", "/LEDC/ON", "/LEDC/OFF", "/LEDD/ON", "/LEDD/OFF",
"/VOLETLU/MON", "/VOLETLU/STO", "/VOLETLU/DES"};

//Tableau des commandes envoyées
int freq[] = {1381719, 1381716, 1394007, 1394004, 1397079, 1397076, 
5510485, 5510484, 5522773, 5522774, 5525845, 5525844,
4028056, 4028056, 4028052, 4028052, 4028049, 4028049, 4028050, 4028050};

void setup() {
  
    WiFi.begin(ssid, password);
  
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
    }
  
    // Démarrage du serveur
    server.begin();

    rf_cmd.enableTransmit(rf_pin); // emetteur sur la broche 4
    rf_cmd.setProtocol(1); // par defaut le protocole utilisé est le 1
    rf_cmd.setRepeatTransmit(15); // on repete la transmission 15 fois pour etre sur qu'elle arrive bien
    // Optional set pulse length.
    rf_cmd.setPulseLength(320);
}

//Fonction d'emission des codes
void rf_send(unsigned long rf_code) {
    rf_cmd.send(rf_code, rf_mode);
}

void loop() {
    // test si client connecté
    WiFiClient client = server.available();
    if (!client) {
        return;
    }
  
    // attendre les données
    while(!client.available()){
        delay(1);
    }
  
    // lecture 1ère ligne
    String req = client.readStringUntil('\r');
    client.flush();
    
    for (int i = 0; i < (sizeof(freq) - 1); i++){ //Boucle quiparcours le tableau des commandes
        if(req.indexOf(led[i]) != -1) {
            rf_send(freq[i]);
            String s = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n<!DOCTYPE HTML>\r\n<html>\r\n<head><title>Arduino 192.168.0.22</title></head><body><h3>Arduino OK</h3></body>";
            s += "</html>\n";
            // Send the response to the client
            client.print(s);
            client.stop();
            return;
        }
    }

    // Prepare the response
    String s = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n<!DOCTYPE HTML>\r\n<html>\r\n<head><title>Arduino 192.168.0.22</title></head><body><h3>Arduino erreur</h3></body>";
    s += "</html>\n";
    // Send the response to the client
    client.print(s);
    client.stop();
    delay(1);
}

