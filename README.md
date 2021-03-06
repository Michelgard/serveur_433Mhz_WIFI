# Serveur_433Mhz_WIFI
Serveur domotique en 433Mhz avec WIFI avec deux composants et trois fils

# Matériel utilisé
- Un arduino WIFI de ce modèle : D1 Mini NodeMCU Lua ESP8266 ESP-12 WeMos D1 Mini WIFI 4M Bytes Module commandé sur Ebay
- Un emetteur en 433Mhz : 433Mhz RF Module Émetteur Récepteur Télécommande Pour Projet Arduino ARM MCU
- 3 fils pour brancher l'émetteur à l'Arduino (masse, +5V et signal en pin D2) Attention il y a une erreur dans le schéma il faut connecter l'émetteur 433Mhz à la Pin D2 de ESP8266.
- Un cable USB et micro USB pour l'alimentation
 
# Utilisation
Il faut configurer le programme Arduino avec les deux librairies Rcswitch et ESP8266WiFi. Pour cette dernière procéder comme suis:
- Install Arduino 1.6.8 from the [Arduino website](http://www.arduino.cc/en/main/software).
- Start Arduino and open Preferences window.
- Enter ```http://arduino.esp8266.com/stable/package_esp8266com_index.json``` into *Additional Board Manager URLs* field. You can add multiple URLs, separating them with commas.
- Open Boards Manager from Tools > Board menu and install *esp8266* platform (and don't forget to select your ESP8266 board from Tools > Board menu after installation).

Voir tout cela ici : https://github.com/esp8266/Arduino#installing-with-boards-manager
  
Ensuite téléverser l'un des deux programmes ci-joint. Les deux sont identiques l'un plus simple que l'autre.
  
Une fois alimenté vous avez un serveur domotique en 433Mhz. Vous trouverez dans mon blog https://www.blog-de-michel.fr rubrique domotique les exemples pour le commander via page une web et/ou commande vocale.
