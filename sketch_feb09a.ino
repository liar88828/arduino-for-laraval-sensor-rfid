// #include <SPI.h>
// #include <MFRC522.h>

// #define RST_PIN D1
// #define SDA_PIN D2

// MFRC522 mfrc522(SDA_PIN, RST_PIN);

// void setup() {
//   Serial.begin(9600);
//   SPI.begin();
//   mfrc522.PCD_Init();
//   Serial.println("Put your card to the reader...");
//   pinMode(LED_BUILTIN, OUTPUT);
// }

// void loop() {



//   if (!mfrc522.PICC_IsNewCardPresent()) {
//     return;
//   }

//   if (!mfrc522.PICC_ReadCardSerial()) {
//     return;
//   }

//   Serial.print("UID tag :");
//   String content = "";
//   byte letter;

//   for (byte i = 0; i < mfrc522.uid.size; i++) {
//     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
//     Serial.print(mfrc522.uid.uidByte[i], HEX);
//     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
//     content.concat(String(mfrc522.uid.uidByte[i], HEX));
//   }

//   Serial.println();
//   Serial.print("Pesan : ");
//   content.toUpperCase();



//   if (content.substring(1) == "50 2D 8C 15") {
//     Serial.println("Kartu cocok");
//     Serial.println();
//     digitalWrite(LED_BUILTIN, LOW);  // turn the LED on (HIGH is the voltage level)
//     delay(1000);
//   }

//   else if (content.substring(1) == "79 D0 24 A3") {
//     Serial.println("Kartu cocok");
//     Serial.println();
//     digitalWrite(LED_BUILTIN, LOW);  // turn the LED on (HIGH is the voltage level)
//     delay(1000);
//   } else {
//     Serial.println("Kartu Tidak cocok");
//     delay(1000);
//   }



//   digitalWrite(LED_BUILTIN, HIGH);
// }



// #include <ESP8266WiFi.h>
// #include <ESP8266HTTPClient.h>
// #include <WiFiClient.h>

// const char* ssid = "Slamet";
// const char* password = "jalakjetis";

// String serverName = "http://192.168.1.8:8000";

// unsigned long lastTime = 0;
// unsigned long timerDelay = 5000;
// -----------------------
// void setup() {
//   Serial.begin(9600);

//   WiFi.begin(ssid, password);
//   Serial.println("Connecting");
//   while(WiFi.status() != WL_CONNECTED) {
//     delay(1000);
//     Serial.print(".");
//   }
//   Serial.println("");
//   Serial.print("Connected to WiFi network with IP Address: ");
//   Serial.println(WiFi.localIP());

//   Serial.println("Timer set to 5 seconds (timerDelay variable), it will take 5 seconds before publishing the first reading.");
// }
// -----------------------

// void loop() {
//   // Send an HTTP POST request depending on timerDelay
//   if ((millis() - lastTime) > timerDelay) {
//     //Check WiFi connection status
//     if(WiFi.status()== WL_CONNECTED){
//       WiFiClient client;
//       HTTPClient http;

//       String serverPath = serverName + "/test?id=10";

//       // Your Domain name with URL path or IP address with path
//       http.begin(client, serverPath.c_str());

//       // If you need Node-RED/server authentication, insert user and password below
//       //http.setAuthorization("REPLACE_WITH_SERVER_USERNAME", "REPLACE_WITH_SERVER_PASSWORD");

//       // Send HTTP GET request
//       int httpResponseCode = http.GET();

//       if (httpResponseCode>0) {
//         Serial.print("HTTP Response code: ");
//         Serial.println(httpResponseCode);
//         String payload = http.getString();
//         Serial.println(payload);
//       }
//       else {
//         Serial.print("Error code send data : ");
//         Serial.println(httpResponseCode);
//       }
//       // Free resources
//       http.end();
//     }
//     else {
//       Serial.println("WiFi Disconnected");
//     }
//     lastTime = millis();
//   }
// }



//---------- Wifi and webserver
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
const char* ssid = "SOEDER";// nama wifi
const char* password = "987654321";// password wifi

// webserver laravel

String Link;
const char* host = "192.168.1.25";// target api
const int httpPort = 8000;
String serverName = "http://" + String(host) + ":" + httpPort;


// ----------------

// ------------RFID
#include <SPI.h>
#include <MFRC522.h>
#define RST_PIN D1
#define SDA_PIN D2

MFRC522 mfrc522(SDA_PIN, RST_PIN);
// ----------
void setup() {
  Serial.begin(9600);

  // ------ Wifi Setup
  // seting wifi
  WiFi.hostname("NodeMcu");

  WiFi.begin(ssid, password);
  Serial.println("Connecting");
  // Process Connect Wifi AccesPoint
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());
  // ----------------------

  // ------- RFID Setup
  SPI.begin();
  mfrc522.PCD_Init();
  Serial.println("Dekatkan Kartu RFID...");
  // ----------------

  // pin lampu LED arduino
  pinMode(LED_BUILTIN, OUTPUT);
}



void loop() {

  if (!mfrc522.PICC_IsNewCardPresent()) {
    return;
  }


  if (!mfrc522.PICC_ReadCardSerial()) {
    return;
  }

  Serial.print("UID tag :");
  String content = "";  // RFID card
  // byte letter;

  for (byte i = 0; i < mfrc522.uid.size; i++) {
    content += mfrc522.uid.uidByte[i];
    // Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
    // Serial.print(mfrc522.uid.uidByte[i], HEX);
    // content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
    // content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }

  Serial.print(content);
  Serial.println();
  // Serial.print("Pesan : ");
  // content.toUpperCase();
  // if (content.substring(1) == "50 2D 8C 15") {
  //   Serial.println("Kartu cocok");
  //   Serial.println();
  //   digitalWrite(LED_BUILTIN, LOW);  // turn the LED on (HIGH is the voltage level)
  //   delay(1000);
  // }

  // Kirim nomor RFID ke Webservices Laravel
  WiFiClient client;
  HTTPClient http;

  if (!client.connect(host, httpPort)) {
    Serial.println("Connect Fail");
  }
  digitalWrite(LED_BUILTIN, HIGH);
  String serverPath = serverName + "/api/sensor/" + content;
  http.begin(client, serverPath.c_str());  // link kirim webserver
  int httpResponseCode = http.GET();       // method yang di gunakan

  // String payload = http.getString();// response dari webserver
  // Serial.println(payload);// print isi data

  if (httpResponseCode > 0) {  // apa bila response code

    Serial.print("HTTP Response code: ");
    Serial.println(httpResponseCode);
    String payload = http.getString();  // response dari webserver
    Serial.println(payload);            // print isi data

  } else {
    Serial.print("Error code send data : ");
    Serial.println(httpResponseCode);
  }
  // Free resources
  digitalWrite(LED_BUILTIN, LOW);
  http.end();
  delay(2000);
}
