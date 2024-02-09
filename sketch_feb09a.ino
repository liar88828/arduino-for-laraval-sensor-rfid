#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN D1
#define SDA_PIN D2

MFRC522 mfrc522(SDA_PIN, RST_PIN);

void setup() {
  Serial.begin(9600);
  SPI.begin();
  mfrc522.PCD_Init();
  Serial.println("Put your card to the reader...");
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
  String content = "";
  byte letter;

  for (byte i = 0; i < mfrc522.uid.size; i++) {
    Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
    Serial.print(mfrc522.uid.uidByte[i], HEX);
    content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
    content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }

  Serial.println();
  Serial.print("Pesan : ");
  content.toUpperCase();



  if (content.substring(1) == "50 2D 8C 15") {
    Serial.println("Kartu cocok");
    Serial.println();
    digitalWrite(LED_BUILTIN, LOW);  // turn the LED on (HIGH is the voltage level)
    delay(1000);
  }

  else if (content.substring(1) == "79 D0 24 A3") {
    Serial.println("Kartu cocok");
    Serial.println();
    digitalWrite(LED_BUILTIN, LOW);  // turn the LED on (HIGH is the voltage level)
    delay(1000);
  } else {
    Serial.println("Kartu Tidak cocok");
    delay(1000);
  }


 
  digitalWrite(LED_BUILTIN, HIGH);
}
