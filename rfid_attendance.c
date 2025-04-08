#include <LiquidCrystalRus.h>

LiquidCrystalRus lcd(8,14,9,10,11,12,13);

#include <SPI.h>
#include <MFRC522.h>
MFRC522 mfrc522(10,9);
 byte cardx[4]= {0x3F,0x01,0x23,0x44};
 String cardreaded(byte *buffer,byte bufferSize)
 {
 String card="";
 for (byte i=0; i<bufferSize; i++)
 {
 card+=String(buffer[i]<0x10 ? " 0" : " ");
 card+=String(buffer[i],HEX);
 }
 return card;
  }


void setup() {
  Serial.begin(115200);
  lcd.begin(16,2);

  SPI.begin();

  mfrc522.PCD_Init();


}

void loop() {
     if (mfrc522.PICC_ReadCardSerial() == 1 | mfrc522.PICC_IsNewCardPresent() == 1) {
      rfid_val = cardreaded(mfrc522.uid.uidByte, mfrc522.uid.size);
      }
       if (rfid_val == "23it111") {
      Serial.println("Attendance Noted");
      lcd.setCursor(0, 0);
       lcd.print("Attendance Noted");
       pinMode(25, OUTPUT);
       digitalWrite(25, 1);
      pinMode(26, OUTPUT);
       digitalWrite(26, 0);
    } else {
      Serial.println("Invalid ID");
      lcd.setCursor(0, 0);
       lcd.print("Invalid ID");
       pinMode(26, OUTPUT);
       digitalWrite(26, 1);
      pinMode(25, OUTPUT);
       digitalWrite(25, 0);
    }

}
