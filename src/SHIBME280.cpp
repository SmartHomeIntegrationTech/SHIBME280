/*
 * Copyright (c) 2020 Karsten Becker All rights reserved.
 * Use of this source code is governed by a BSD-style
 * license that can be found in the LICENSE file.
 */
#include <Adafruit_BME280.h>
#include <Adafruit_Sensor.h>
#include <Arduino.h>
#include <SHIBME280.h>
#include <SHIHardware.h>
#include <SHISensor.h>
#include <Wire.h>

bool SHI::BME280::reconfigure(Configuration *newConfig) {
  config = castConfig<BME280Config>(newConfig);
  return reconfigure();
}

bool SHI::BME280::reconfigure() {
  switch (config.useBus) {
    case 0:
      i2cPort = &Wire;
      break;
    case 1:
      i2cPort = &Wire1;
      break;

    default:
      SHI_LOGERROR("Invaild bus");
      return false;
  }
  if (!bme.begin(config.primaryAddress ? 0x76 : 0x77, i2cPort)) return false;
  bme.setSampling(Adafruit_BME280::MODE_FORCED,
                  config.temperatureSampling,  // temperature
                  config.pressureSampling,     // pressure
                  config.humiditySampling,     // humidity
                  config.sensorFilter);
  return true;
}

bool SHI::BME280::setupSensor() {
  bool status = reconfigure();
  if (!status) {
    statusMessage = "Could not find a valid BME280 sensor, check wiring!";
    fatalError = true;
  }
  SHI::hw->feedWatchdog();
  addMetaData(temperature);
  addMetaData(humidity);
  addMetaData(pressure);
  return status;
}

std::vector<SHI::MeasurementBundle> SHI::BME280::readSensor() {
  SHI::hw->feedWatchdog();
  // wait for WiFi connection
  bme.takeForcedMeasurement();
  return {{{temperature->measuredFloat(bme.readTemperature()),
            humidity->measuredFloat(bme.readHumidity()),
            pressure->measuredFloat(bme.readPressure() / 100.0F)},
           this}};
}
