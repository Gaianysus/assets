/**
 * The MySensors Arduino library handles the wireless radio link and protocol
 * between your home built sensors/actuators and HA controller of choice.
 * The sensors forms a self healing radio network with optional repeaters. Each
 * repeater and gateway builds a routing tables in EEPROM which keeps track of the
 * network topology allowing messages to be routed to nodes.
 *
 * Created by Henrik Ekblad <henrik.ekblad@mysensors.org>
 * Copyright (C) 2013-2015 Sensnology AB
 * Full contributor list: https://github.com/mysensors/Arduino/graphs/contributors
 *
 * Documentation: http://www.mysensors.org
 * Support Forum: http://forum.mysensors.org
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * version 2 as published by the Free Software Foundation.
 *
 *******************************
 *
 * REVISION HISTORY
 * Version 1.0 - Henrik Ekblad
 *
 * DESCRIPTION
 * Example sketch showing how to control physical relays.
 * This example will remember relay state after power failure.
 * http://www.mysensors.org/build/relay
 */
 #include "DHT.h"

DHT dht;

#define THROTTLE_LIMIT 30
// Enable debug prints to serial monitor
#define MY_DEBUG

#define TEMP_ID 21
#define HUM_ID 22

// Enable and select radio type attached
#define MY_RADIO_NRF24
//#define  

#define MY_NODE_ID 252

// Enable repeater functionality for this node
#define MY_REPEATER_FEATURE

#include <MySensors.h>

MyMessage tempmsg(TEMP_ID, V_TEMP);
MyMessage hummsg(HUM_ID, V_HUM);

int throttle = 0;

void before()
{

}

void setup()
{
  dht.setup(2); // data pin 2

}

void presentation()
{
  // Send the sketch version information to the gateway and Controller
  sendSketchInfo("Gaianysus DHTrepeat 7710", "1.1");

  present(TEMP_ID, S_TEMP);
  present(HUM_ID, S_HUM);
}


void loop()
{
  if( throttle > THROTTLE_LIMIT){
    throttle = 0;
    delay(dht.getMinimumSamplingPeriod());
    float humidity = dht.getHumidity();
    float temperature = dht.getTemperature();
    send(tempmsg.set(temperature, TEMP_ID));
    send(hummsg.set(humidity, HUM_ID));
  }
  sleep(1000);
  throttle++;
}

void receive(const MyMessage &message)
{

}

