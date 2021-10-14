
#include <LiquidCrystal_I2C.h>
#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN 9
#define SS_PIN 10
byte readCard[4];
byte a = 0;

LiquidCrystal_I2C lcd(0x27, 16, 2);
MFRC522 mfrc522(SS_PIN, RST_PIN);

void setup() {
Serial.begin(9600);
lcd.begin();
lcd.backlight();
while (!Serial);
SPI.begin();
mfrc522.PCD_Init();
delay(4);
mfrc522.PCD_DumpVersionToSerial();
lcd.setCursor(2, 0);
lcd.print("Kartinizi Koyun");
}

void loop() {
if ( ! mfrc522.PICC_IsNewCardPresent()) {
return;
}
if ( ! mfrc522.PICC_ReadCardSerial()) {
return;
}

lcd.clear();
lcd.setCursor(0, 0);
lcd.print("UID Tarandi");
a = 0;
Serial.println(F("PICC'nin UID'si Tarandı:"));
for ( uint8_t i = 0; i < 4; i++) { //
readCard[i] = mfrc522.uid.uidByte[i];
Serial.print(readCard[i], HEX);
Serial.print(" ");
lcd.setCursor(a, 1);
lcd.print(readCard[i], HEX);
lcd.print(" ");
delay(500);
a += 3;
}
Serial.println("");
mfrc522.PICC_HaltA();
return;
}
