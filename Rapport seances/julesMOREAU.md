Rapport de Séance
==
Séance 1 01/09/2022
-
Choix du projet: modem LoRa/GSM

* Installation du git, création d'un repository, du fichier rapport de séance et du fichier markdown afin d'écrire l'avancé du projet au fil des séances.

* Prise en main de github et premier aperçu du projet via les différent fichiers/diapos à notre disposition.

* Recherche d'un modem 3G/4G/5G à faibe coût. 

Séance 2 02/09/2022
-
Choix entre 2 modem:
* https://www.digikey.fr/fr/products/detail/nimbelink,-llc/NL-SWN-LTE-NRF9160-B/13545238?utm_adgroup=RF%20Transceiver%20Modules&utm_source=google&utm_medium=cpc&utm_campaign=Shopping_Product_RF%2FIF%20and%20RFID&utm_term=&productid=13545238&gclid=CjwKCAjwsMGYBhAEEiwAGUXJaf7u7tiFCuqfYCbA0xugxWerXDCulKu48h5bCE_3MJ1FdUXBXE_tzxoCh5cQAvD_BwE
 
* https://www.digikey.fr/fr/products/detail/nimbelink,-llc/NL-SW-LTE-QBG95-B/13930379?utm_adgroup=RF%20Transceiver%20Modules&utm_source=google&utm_medium=cpc&utm_campaign=Shopping_Product_RF%2FIF%20and%20RFID&utm_term=&productid=13930379&gclid=CjwKCAjwsMGYBhAEEiwAGUXJaeWaWl2KfGZscGHEM1nGFe_TdwtNunfvPOaDJgOhnZRvBooB_zY8shoCOlwQAvD_BwE

Choix d'une antenne pour le modem:
https://www.digikey.fr/fr/products/detail/linx-technologies-inc/ANT-GNCP-C106L160/15294131

Création d'un tableau excel pour comparer les différents modem

Séance 3 09/09/2022
-
Finalisation du tableau et envoie de celui-ci au référent

Manuel d'utilisateur du SIM7000G https://usermanual.wiki/SIMCom-Wireless-Solutions/SIM7000G-4050964.pdf

Manuel de commande du SIM7000G https://cdn.geekfactory.mx/sim7000g/SIM7000%20Series_AT%20Command%20Manual_V1.06.pdf

Séance 4 15/09/2022
-
Prise en main de la LILYGO T-SIM7000G (schématique présente sur https://github.com/Xinyuan-LilyGO/LilyGO-T-SIM7000G/blob/master/schematic/SIM7000G_20200415.pdf et de l'environnement de travail) trouvé sur le site https://randomnerdtutorials.com/lilygo-t-sim7000g-esp32-lte-gprs-gps/

Séance 5 03/10/2022
-
Prise en main du modem

* téléchargement de l'IDE ARDUINO, installation des bibliothèques pour l'ESP32, édition d'un soft de test de communication entre l'ESP32 et le SIM7000G (scan wifi de la pièce)

* édition d'un soft pour tester l'envoie d'un SMS et la position GPS (réussi avec succès)

* test de mise en veille du modem

* essai de reception de sms et lecture sur le terminal (https://docs.arduino.cc/library-examples/gsm-library/GSMExamplesReceiveSMS)

Séance 6 13/10/2022
-

* ajout du code d'envoie SMS et position GPS sur le GIT ainsi que la librairie TinyGSM qu'on utilise

* ajout de la batterie et essai d'envoie SMS sans lien physique avec le PC

* essai de reception SMS et lecture de ce dernier sur le terminal

Séance 7 28/10/2022
-

* poursuivre la reception SMS (mise à jour: les codes précedent pour la réception de SMS étant trop difficile à mettre en place avec une gestion impossible de diverses librairies, nous cherchons dans le manuel de commandes Series_AT du SIM7000 pour effectuer la réception)

Séance 8 18/11/2022
-

* on a réussi a recevoir un SMS sur la carte et le lire
* on essai de gérer la mémoire de la carte SIM

Séance 9 25/11/2022
-

* on arrive a effacer tous les sms de la mémoire de la carte SIM après utilisation
* essais de récupérer la chaine de caractère du message envoyé par le téléphone pour faire une machine à états

Séance 10 01/12/2022
-

* travail sur la chaine de caractère et machine à états

Séance 11 09/12/2022
-

* on arrive à envoyer des commandes via la console arduino
* on continue sur la récupération des caractères

Séance 12 20/12/2022
-

* on commence à travailler sur les requêtes http

Séance 13 06/01/2023
-

* création du code pour se connecter au wifi et accèder à une page web avec contenu html (réussi)
* on commence à faire le code pour se connecter via la carte SIM et non par le wifi

Séance 14 19/01/2023
-

* code connection internet via carte sim

Séance 15 10/02/2023
-

* code connection internet via carte sim

Séance 16 17/02/2023
-

* code connection internet via carte sim

Séance 17 17/03/2023
-

* rédaction du code final avec uniquement des commandes AT + test du Hardware (nouvelle carte sur breadbord) avec implémentation d'un code fonctionnel (il manque l'adaptateur SIM pour pouvoir tester la carte SIM)

Séance 18 23/03/2023
-

* ajout GPS dans le code final + essai carte SIM sur nouvelle carte breadboard

Séance 19 28/03/2023
-

* ajout requête HTTP dans le code final + test fonctionnalités sur breadboard avec carte SIM 

Séance 20 06/04/2023
-

* connexion internet via gsm et non wifi + test fonctionnalités sur breadboard avec carte SIM

Séance 21 20/04/2023
-

* connexion 3G + test breadboard
