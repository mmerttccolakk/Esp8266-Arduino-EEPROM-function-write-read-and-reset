#include <EEPROM.h>


void setup() {
  Serial.begin(9600);//serial begin
  EEPROM.begin(512);//eeprom
  eprom_write(100,"token_code");

  String reading =eprom_read(100);
  Serial.println("reading from eprom ");
  Serial.println(reading);

}

void loop() {


}

void eprom_write(unsigned int StartToWriteAddress,  const String &toWrite){
    unsigned int StringLength=toWrite.length();
    //begin address write how length
    EEPROM.write(StartToWriteAddress, StringLength);

    //debug
    Serial.println("");
    Serial.println("Writing information...");
    Serial.print("Begin addess ");
    Serial.print(StartToWriteAddress);
    Serial.print(" String lenght ");
    Serial.println(StringLength);

    //WriteString
    Serial.println("Writing ");
    for (int i = 0; i < StringLength; i++){
    EEPROM.write(StartToWriteAddress + 1 + i, toWrite[i]);
    Serial.print("address ");
    Serial.print(StartToWriteAddress + 1 + i);
    Serial.print(" data ");
    Serial.println(toWrite[i]);
    }
    Serial.println("finished");

    //saving
    if (EEPROM.commit()) {
        Serial.println("Data successfully committed");
      }else{
        Serial.println("ERROR! Data commit failed");
      }

  delay(500);
}
String eprom_read(unsigned int StartToReadAddress){
  //how lenght data reading from first address
  unsigned int StartToReadLength = EEPROM.read(StartToReadAddress);  
  char readingfromeprom[StartToReadLength + 1]; //new variable for reading data
  //debug
  Serial.println("");
  Serial.println("Reading information...");
  Serial.print("Begin addess ");
  Serial.print(StartToReadAddress);
  Serial.print(" String lenght ");
  Serial.println(StartToReadLength);

  //reading from eprom
  Serial.println(" Reading... ");
  for (int i = 0; i < StartToReadLength; i++){
    readingfromeprom[i] = EEPROM.read(StartToReadAddress + 1 + i);
    Serial.print("address ");
    Serial.print(StartToReadAddress + 1 + i);
    Serial.print(" data ");
    Serial.println(readingfromeprom[i]);
  }
  Serial.println("finished");

  //finishing variable
  readingfromeprom[StartToReadLength] = '\0';

  //return result
  return String(readingfromeprom);
}

void eprom_reset(){
   for (int i = 0; i < 512; i++) {
      EEPROM.write(i, 0);
    }
    EEPROM.commit();
    delay(500);
    if (EEPROM.commit()) {
        Serial.println("Data successfully deleted");
      } else {
        Serial.println("ERROR! Data not deleted");
      }
}
