/*!
 * @file Example1_GetPosition.ino
 * 
 * @mainpage SparkFun smôl ZOE-M8Q
 * 
 * @section intro_sec Examples
 * 
 * This example shows how to read the the position from the smôl ZOE-M8Q using
 * the SparkFun GNSS Library.
 * 
 * Want to support open source hardware? Buy a board from SparkFun!
 * SparkX smôl ZOE-M8Q (SPX-18358): https://www.sparkfun.com/products/18358
 * SparkX smôl ESP32 (SPX-18362): https://www.sparkfun.com/products/18362
 * 
 * @section author Author
 * 
 * This library was written by:
 * Paul Clark
 * July 28th 2021
 * 
 * @section license License
 * 
 * MIT: please see LICENSE.md for the full license information
 * 
 */

#include <Wire.h> //Needed for I2C to GNSS

#include <SparkFun_u-blox_GNSS_Arduino_Library.h> //http://librarymanager/All#SparkFun_u-blox_GNSS
SFE_UBLOX_GNSS myGNSS;

void setup()
{
  delay(1000);
  
  Serial.begin(115200);
  Serial.println("SparkFun u-blox example for the smôl ZOE-M8Q");

  // GNSS power is disabled by default on the smôl ZOE-M8.
  // We need to pull GPIO0 low to enable the power.
  // On the smôl ESP32, GPIO0 is connected to digital pin 27.
  // If you have an intermediate smôl board between the ESP32 and the ZOE-M8Q
  //  and that board also uses GPIO0, then the power enable will be connected
  //  to GPIO1 instead which is digital pin 26 on the smôl ESP32.
  pinMode(27, OUTPUT);
  digitalWrite(27, LOW); // Pull GPIO0 (digital pin 27) low to enable power for the ZOE-M8Q
  
  delay(1000); // Give the ZOE-M8Q some time to power up

  Wire.begin();

  //myGNSS.enableDebugging(); //Uncomment this line to enable helpful debug messages on Serial

  if (myGNSS.begin() == false) //Connect to the u-blox module using Wire port
  {
    Serial.println(F("u-blox GNSS not detected at default I2C address. Please check wiring. Freezing."));
    while (1);
  }

  myGNSS.setI2COutput(COM_TYPE_UBX); //Set the I2C port to output UBX only (turn off NMEA noise)
  myGNSS.saveConfigSelective(VAL_CFG_SUBSEC_IOPORT); //Save (only) the communications port settings to flash and BBR
}

void loop()
{
  //The module only responds when a new position is available
    
  Serial.print(myGNSS.getYear());
  Serial.print("/");
  Serial.print(myGNSS.getMonth());
  Serial.print("/");
  Serial.print(myGNSS.getDay());
  Serial.print(" ");
  Serial.print(myGNSS.getHour());
  Serial.print(":");
  Serial.print(myGNSS.getMinute());
  Serial.print(":");
  Serial.print(myGNSS.getSecond());

  Serial.print(F(" Lat: "));
  Serial.print(myGNSS.getLatitude());

  Serial.print(F(" Long: "));
  Serial.print(myGNSS.getLongitude());
  Serial.print(F(" (degrees * 10^-7)"));

  Serial.print(F(" Alt: "));
  Serial.print(myGNSS.getAltitudeMSL());
  Serial.print(F(" (mm)"));

  Serial.print(F(" SIV: "));
  Serial.print(myGNSS.getSIV());

  Serial.println();
}
