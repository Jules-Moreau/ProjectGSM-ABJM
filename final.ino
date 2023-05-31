//define the module for tinygsm
#define TINY_GSM_MODEM_SIM7000
#define TINY_GSM_RX_BUFFER 1024 // Set RX buffer to 1Kb
#define SerialAT Serial1
#include <SoftwareSerial.h>

// See all AT commands, if wanted
#define DUMP_AT_COMMANDS

// Initialisation du port série logiciel pour communiquer avec le module SIM7000G
SoftwareSerial simSerial(26, 27); // RX, TX

//define the pinout of the module
#define UART_BAUD   115200
#define PIN_TX      27
#define PIN_RX      26
#define PWR_PIN     4
#define LED_PIN     12

// set GSM PIN, if any
#define GSM_PIN "0000"

// Your GPRS credentials, if any
const char apn[]  = "sl2sfr";     //SET TO YOUR APN
const char gprsUser[] = "sfr";
const char gprsPass[] = "sfr";

const unsigned int MAX_MESSAGE_LENGTH = 25;

const char* ssid = "HUAWEI_Jules";
const char* password = "123412345";

// Set phone number, if you want to test SMS
#define SMS_TARGET  "+33695452128" //numéro de Jules

#include <TinyGsmClient.h>
#include <SPI.h>
#include <Adafruit_FONA.h>
#include <stdlib.h>
#include <WiFi.h>

//tinygsm instance
#ifdef DUMP_AT_COMMANDS  // if enabled it requires the streamDebugger lib
  #include <StreamDebugger.h>
  StreamDebugger debugger(SerialAT, Serial);
  TinyGsm modem(debugger);
#else
  TinyGsm modem(SerialAT);
#endif

void setup() {
  // put your setup code here, to run once:

  // Set console baud rate
  Serial.begin(115200);
  delay(10);

  //power the modem ON
  pinMode(PWR_PIN, OUTPUT);
  digitalWrite(PWR_PIN, HIGH);
  delay(300);
  digitalWrite(PWR_PIN, LOW);

  //start serial communication
  SerialAT.begin(UART_BAUD, SERIAL_8N1, PIN_RX, PIN_TX);

  // Restart the modem (takes quite some time)
  // To skip it, call init() instead of restart()
  Serial.println("Initializing modem...");
  if (!modem.restart()) {
    Serial.println("Failed to restart modem, attempting to continue without restarting");
  }

  //Wifi connection (with ssid and password of the wifi device)
  /*Serial.print("connection au wifi...\r\n");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(1000);
    Serial.print(". \r\n");
  }
  Serial.print("Wifi connecté \r\n");
  */

// Initialisation de la communication série avec le port série logiciel
  Serial.begin(00);
  simSerial.begin(115200);

  // Initialisation de la connexion HTTP
  simSerial.println("AT+HTTPINIT");

  // Configuration de l'URL de la requête PHP
  simSerial.println("AT+HTTPPARA=\"URL\",\"http://example.com/api.php\"");

  // Envoi de la requête
  simSerial.println("AT+HTTPACTION=0");

  // Lecture des données de la réponse
  simSerial.println("AT+HTTPREAD");
  
  
}

char fonaNotificationBuffer[64]; //for notifications from the FONA
char smsBuffer[250]; //buffer to read sms

void loop() {
  // put your main code here, to run repeatedly:
 
  String res;  //Global Value to send sms
  //String ans;  //Global Value to read sms
  //char* readSMS; //value to read sms
  
  //-----MODEM NAME & INFO-----
  Serial.println("\n-----MODEM NAME & INFO-----\n");
  String name = modem.getModemName();
  delay(500);
  Serial.println("Modem Name: " + name);

  String modemInfo = modem.getModemInfo();
  delay(500);
  Serial.println("Modem Info: " + modemInfo);

  //-----GPRS-----
  Serial.println("\n-----GPRS-----\n");
  Serial.println("Connecting to: " + String(apn));
  if (!modem.gprsConnect(apn, gprsUser, gprsPass)) {
  delay(10000);
  return;
  }
  Serial.print("GPRS status: ");
  if (modem.isGprsConnected()) {
    Serial.println("GPRS CONNECTED\n");
  } else {
    Serial.println("GPRS NOT CONNECTED\n");
  }

  //-----SMS-----
  Serial.println("\n-----SEND SMS-----\n");
  //res = modem.sendSMS(SMS_TARGET, String("Vole de ruche en cours "));
  //DBG("SMS:", res ? "OK sending sms" : "fail");

  /*modem.sendAT("+CMGS=?"); //send SMS
  modem.waitResponse();
  modem.sendAT("+CMGS=\"SMS_TARGET\"<CR>\"Sending test !\"<Ctrl+z>\"");
  modem.waitResponse();*/
  Serial.println("\n-----READ SMS-----\n");
  String mem;
  modem.sendAT("+CMGF=1"); //select text mode
  modem.waitResponse();
  modem.sendAT("+CMGD=?");
  modem.waitResponse();
  modem.sendAT("+CPMS=?"); //ask message storage area
  modem.waitResponse();
  modem.sendAT("+CPMS=\"SM\""); //select message storage area (18,30)
  modem.waitResponse();
  /*if(modem.waitResponse(5000, mem) == 1){
    Serial.println(mem);
  } //essais de recupérer les 18 messages sur 30
  modem.sendAT("+CMGR=? ");
  modem.waitResponse();*/
  //N'ENVOYEZ QU'UN SMS A LA FOIS!!!
  modem.sendAT("+CMGR=0");
  //modem.sendAT("+CMGR=",i);
  modem.waitResponse();
  delay(10000);
  modem.sendAT("+CMGD=1,4");
  modem.waitResponse();
  //Serial.println(ans);

  //-----GPS-----
  Serial.println("\n-----GPS POSITION-----\n");
  /*// Only in version 20200415 is there a function to control GPS power
  modem.sendAT("+SGPIO=0,4,1,1");// Set SIM7000G GPIO4 HIGH ,turn on GPS power
  if (modem.waitResponse(10000L) != 1) {
    DBG(" SGPIO=0,4,1,1 false ");
  }
  modem.enableGPS();
  float lat,  lon;
  int tempsGPS;
  while (tempsGPS<20) {
    if (modem.getGPS(&lat, &lon)) {
      Serial.printf("lat:%f lon:%f\n", lat, lon);
      break;
    } else {
      Serial.print("getGPS ");
      Serial.println(millis());
    }
    delay(2000);
    tempsGPS++;
  }
  modem.disableGPS();
  
  // Only in version 20200415 is there a function to control GPS power
  modem.sendAT("+SGPIO=0,4,1,0");// Set SIM7000G GPIO4 LOW ,turn off GPS power
  if (modem.waitResponse(10000L) != 1) {
    DBG(" SGPIO=0,4,1,0 false ");
  }
*/
  //-----HTTP-----
  Serial.println("\n-----HTTP QUERY-----\n");
 
  WiFiClient client;
  const int httpPort = 80;
  if (!client.connect("rucher.polytech.unice.fr", httpPort)) {
    Serial.println("Connection failed");
    return;
  }

//***********http://rucher.polytech.unice.fr/~cpeter/exemple.html***************//

  // Make a HTTP GET request:
  client.print(String("GET /~cpeter/exemple.html HTTP/1.1\r\n") +
               "Host: rucher.polytech.unice.fr\r\n" + 
               "Connection: close\r\n\r\n");
  unsigned long timeout = millis();
  while (client.available() == 0) {
    if (millis() - timeout > 5000) {
      Serial.println(">>> Client Timeout !");
      client.stop();
      return;
    }
  }

  // Read the response and print it to the serial console:
  while(client.available()){
    String line = client.readStringUntil('\r');
    Serial.print(line);
  }

  Serial.println();
  Serial.println("closing connection");

  //-----HTTP GSM-----
  Serial.println("\n-----HTTP QUERY GSM 3G/4G-----\n");
  // Attente de la réponse de la commande AT+HTTPREAD
  while (!simSerial.available()) {
    delay(10);
  }

  // Récupération de la réponse de la commande AT+HTTPREAD
  String response = simSerial.readString();

  // Affichage de la réponse
  Serial.println(response);
}
