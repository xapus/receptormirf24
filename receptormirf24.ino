/**
 * NRF24l01 - Codigo Cliente, ejemplo 3.
 * Recibe una estructura de datos.
 */

#include <SPI.h>
#include <Mirf.h>
#include <nRF24L01.h>
#include <MirfHardwareSpiDriver.h>

#include <Wire.h>

struct DATOS {
  float         temp;
  unsigned long time;
}
datos;


void setup()
{
  Serial.begin(9600);

  Mirf.spi    = &MirfHardwareSpi;
  Mirf.cePin  = 7;
  Mirf.csnPin = 8;

  Mirf.init();
  Mirf.setRADDR((byte *)"client");
  Mirf.payload = sizeof(datos);
  Mirf.channel = 50;
  Mirf.config();
  // Read and print RF_SETUP
  byte rf_setup = 0;
  Mirf.readRegister( RF_SETUP, &rf_setup, sizeof(rf_setup) );
  Serial.print( "rf_setup = " );
  Serial.println( rf_setup, BIN );

  Serial.println( "Wireless initialized!" );
}


void loop()
{
  if ( !Mirf.isSending()  &&  Mirf.dataReady() )
  {
    Mirf.getData((byte *) &datos);

    Serial.print(datos.temp);
    Serial.print(" c");
    Serial.print(datos.time);
    Serial.println(" s");
  }
}
