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
  
    // Match the request
    if(req.indexOf("/LED1/ON") != -1) {
        rf_send(1381719);
    }
    else if(req.indexOf("/LED1/OFF") != -1) {
        rf_send(1381716);
    } 
    else if(req.indexOf("/LED2/ON") != -1)  {
        rf_send(1394007);
    } 
    else if(req.indexOf("/LED2/OFF") != -1)  {
        rf_send(1394004);
    }
    else if(req.indexOf("/LED3/ON") != -1)  {
       rf_send(1397079);
    } 
    else if(req.indexOf("/LED3/OFF") != -1) {
       rf_send(1397076);
    }
    else if(req.indexOf("/LED4/ON") != -1)  {
       rf_send(5510485);
    } 
    else if(req.indexOf("/LED4/OFF") != -1)   {
       rf_send(5510484);
    }
    else if(req.indexOf("/LED5/ON") != -1)   {
       rf_send(5522773);
    }  
    else  if(req.indexOf("/LED5/OFF") != -1)  {
       rf_send(5522774);
    }
    else if(req.indexOf("/LED6/ON") != -1)  {
       rf_send(5525845);
    } 
    else if(req.indexOf("/LED6/OFF") != -1)   {
       rf_send(5525844);
    }
    else if(req.indexOf("/LEDA/ON") != -1)  {
       rf_send(4028056);
    }
    else if(req.indexOf("/LEDA/OFF") != -1) {
       rf_send(4028056);
    }
    else if(req.indexOf("/LEDB/ON") != -1)  {
       rf_send(4028052);
    } 
    else if(req.indexOf("/LEDB/OFF") != -1)  {
       rf_send(4028052);
    }
    else if(req.indexOf("/LEDC/ON") != -1) {
       rf_send(4028049);
    } 
    else if(req.indexOf("/LEDC/OFF") != -1)  {
       rf_send(4028049);
    }
    else if(req.indexOf("/LEDD/ON") != -1) {
       rf_send(4028050);
    } 
    else if(req.indexOf("/LEDD/OFF") != -1){
       rf_send(4028050);
    }  
    else if(req.indexOf("/VOLETLU/MON") != -1) {
       rf_send(4232320);
    }
    else if(req.indexOf("/VOLETLU/STO") != -1) {
       rf_send(4232322);
    }
    else if(req.indexOf("/VOLETLU/DES") != -1) {
       rf_send(4232324);
    }
    else{
        String s = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n<!DOCTYPE HTML>\r\n<html>\r\n<head><title>Arduino 192.168.0.22</title></head><body><h3>Arduino erreur</h3></body>";
        s += "</html>\n";
        // Send the response to the client
        client.print(s);
        client.stop();
        return;
    }
  
    client.flush();

    // Prepare the response
    String s = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n<!DOCTYPE HTML>\r\n<html>\r\n<head><title>Arduino 192.168.0.22</title></head><body><h3>Arduino OK</h3></body>";
    s += "</html>\n";
    // Send the response to the client
    client.print(s);
    client.stop();
    delay(1);
}

