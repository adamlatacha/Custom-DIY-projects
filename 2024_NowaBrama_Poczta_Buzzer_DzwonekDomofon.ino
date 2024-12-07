/*
  Copyright (C) AC SOFTWARE SP. Z O.O.
  
  This program is free software; you can redistribute it and/or
  modify it under the terms of the GNU General Public License
  as published by the Free Software Foundation; either version 2
  of the License, or (at your option) any later version.
  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.
  You should have received a copy of the GNU General Public License
  along with this program; if not, write to the Free Software
  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
*/

#include <SuplaDevice.h>
#include <supla/control/relay.h>
#include <supla/control/sequence_button.h>
#include <supla/control/virtual_relay.h>
#include <supla/control/button.h>
#include <supla/control/action_trigger.h>
#include <supla/sensor/binary.h>
#include <supla/sensor/virtual_binary.h>

// Choose proper network interface for your card:
#ifdef ARDUINO_ARCH_AVR
  // Arduino Mega with EthernetShield W5100:
  #include <supla/network/ethernet_shield.h>
  // Ethernet MAC address
  uint8_t mac[6] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05};
  Supla::EthernetShield ethernet(mac);

  // Arduino Mega with ENC28J60:
  // #include <supla/network/ENC28J60.h>
  // Supla::ENC28J60 ethernet(mac);
#elif defined(ARDUINO_ARCH_ESP8266) || defined(ARDUINO_ARCH_ESP32)
  // ESP8266 and ESP32 based board:
  #include <supla/network/esp_wifi.h>
  Supla::ESPWifi wifi("network", "88888888");
#endif

Supla::Control::Relay *buzzer = nullptr;


void setup() {

  Serial.begin(115200);

  pinMode (0 ,OUTPUT) ;            // set buzzer on pin 5 (D1)

  // Replace the falowing GUID with value that you can retrieve from https://www.supla.org/arduino/get-guid
  char GUID[SUPLA_GUID_SIZE] = {0x77,0x67,0xD4,0x75,0xB1,0x9F,0xFE,0xBC,0x57,0x74,0xCE,0x88,0x75,0x7C,0x90,0xC6};

  // Replace the following AUTHKEY with value that you can retrieve from: https://www.supla.org/arduino/get-authkey
  char AUTHKEY[SUPLA_AUTHKEY_SIZE] = {0x9F,0x73,0x75,0x9C,0x7F,0xC4,0x0F,0xFE,0x6C,0x37,0x9F,0x83,0xAF,0xC0,0x3B,0x9B};

  SuplaDevice.setName("ESP8266_brama_gar_furtka_poczta");


  auto gateRelay = new Supla::Control::Relay(5, false); // Low level trigger relay on pin D1
  auto partialGateSensor = new Supla::Sensor::Binary(12, false, false); // pin D6, pullUp, invert logic
  auto fullGateSensor = new Supla::Sensor::Binary(14, false, false); //D5

  auto buzzer = new Supla::Control::Relay(0, false); //D3
  auto mailboxSensor = new Supla::Sensor::Binary(4, false, false); // D2
  auto gateSensor = new Supla::Sensor::Binary(13, false, false); // D7
  auto ringSensor = new Supla::Sensor::Binary(15, false, false); // D8


 

 
  /*
   * SuplaDevice Initialization.
   * Server address is available at https://cloud.supla.org 
   * If you do not have an account, you can create it at https://cloud.supla.org/account/create
   * SUPLA and SUPLA CLOUD are free of charge
   * 
   */
 
  SuplaDevice.begin(GUID,              // Global Unique Identifier 
                    "svr5.supla.org",  // SUPLA server address
                    "adam.latacha@gmail.com",   // Email address used to login to Supla Cloud
                    AUTHKEY);          // Authorization key
    
}

void loop() {
  SuplaDevice.iterate();

   bool buzzer_state = buzzer->isOn();

   if(buzzer_state == 1){
      tone(0, 2500, 500);
   }

}
