void SensorEC(){
currentTime = millis();

  // Read Sensors
  // Check for start read time
  if ( currentTime - readStartTime >= READ_INTERVAL ){          // Initialize EC Meter read sequence
    readStartTime = currentTime;                                // Set start time
  }  
  else if ( currentTime - READ_DURATION <= readStartTime )      // Power Up / Read
  {
    startPower( POWER_PIN );                                    // Start charging solution
    delay(250);                                                 // Delay until fully charged
    readSensors();                                              // Take sensor readings
    delay(250);
  } else {                                                      // Power Down
    stopPower( POWER_PIN );                                     // Stop charging and let solution depolarize
  }
  
  writeToSerial();
}

/*
  -------------------------------------------------------------------------------------------------------
    SENSOR/ARDUINO PROCESSING
  -------------------------------------------------------------------------------------------------------
*/

void startPower( byte pin ){
  digitalWrite( pin , HIGH );
}

void stopPower ( byte pin ){
  digitalWrite( pin , LOW );
}

void readSensors() {
  ecMeterReading = analogRead( EC_PIN );            // read the voltage from the EC Meter
  ecMeterVoltage = ecMeterReading * 5.0;
  ecMeterVoltage = ecMeterVoltage / 1024;
  PPM = ((1065*ecMeterVoltage)+0.349);

}

/*
  -------------------------------------------------------------------------------------------------------
    OUTGOING SERIAL DATA TO EXCEL PROCESSING CODE
  -------------------------------------------------------------------------------------------------------
*/

void writeToSerial()
{
  // Ignore if not within output interval
  if ( currentTime - lastOutputTime < SERIAL_OUTPUT_INTERVAL ) {
    return;
  }
  Serial.print(ecMeterVoltage, 4);
  Serial.print( SERIAL_OUTPUT_DELIMITER ); Serial.print("Partes por millon = "); Serial.print(PPM);
  
  Serial.println();

  lastOutputTime = currentTime;
}
