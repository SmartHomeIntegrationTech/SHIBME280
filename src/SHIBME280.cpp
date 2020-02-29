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

bool SHI::BME280::setupSensor() {
  bool status = bme.begin(0x76, i2cPort);
  bme.setSampling(Adafruit_BME280::MODE_FORCED,
                  Adafruit_BME280::SAMPLING_X1,  // temperature
                  Adafruit_BME280::SAMPLING_X1,  // pressure
                  Adafruit_BME280::SAMPLING_X1,  // humidity
                  Adafruit_BME280::FILTER_OFF);
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
