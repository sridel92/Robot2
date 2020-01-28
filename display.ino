
// *************************************
// *** SERIAL PRINT INFORMATION      ***
// *************************************
void SerialPrintInfo()  {                  // display data
 if((millis()-lastMilliPrint) >= 500)   {                     
   lastMilliPrint = millis();
   Serial.print(" SonarA :");        Serial.print(SonarA);
   Serial.print(" SonarCenter :");   Serial.print(SonarCenter);
   Serial.print(" SonarB :");        Serial.print(SonarB);
 Serial.print("Commande :");         Serial.println(command);  
 }
}
