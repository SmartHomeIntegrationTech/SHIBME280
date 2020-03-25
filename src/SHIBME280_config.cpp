/*
 * Copyright (c) 2020 Karsten Becker All rights reserved.
 * Use of this source code is governed by a BSD-style
 * license that can be found in the LICENSE file.
 */

// WARNING, this is an automatically generated file!
// Don't change anything in here.
// Last update 2020-03-25

# include <iostream>
# include <string>


# include "SHIBME280.h"
// Configuration implementation for class SHI::BME280Config

namespace {
    
}  // namespace

SHI::BME280Config::BME280Config(const JsonObject &obj):
      useBus(obj["useBus"] | 0),
      primaryAddress(obj["primaryAddress"] | true),
      sensorFilter(static_cast<Adafruit_BME280::sensor_filter>(obj["sensorFilter"].as<int>() | Adafruit_BME280::FILTER_OFF)),
      temperatureSampling(static_cast<Adafruit_BME280::sensor_sampling>(obj["temperatureSampling"].as<int>() | Adafruit_BME280::SAMPLING_X1)),
      humiditySampling(static_cast<Adafruit_BME280::sensor_sampling>(obj["humiditySampling"].as<int>() | Adafruit_BME280::SAMPLING_X1)),
      pressureSampling(static_cast<Adafruit_BME280::sensor_sampling>(obj["pressureSampling"].as<int>() | Adafruit_BME280::SAMPLING_X1))
  {}

void SHI::BME280Config::fillData(JsonObject &doc) const {
    doc["useBus"] = useBus;
  doc["primaryAddress"] = primaryAddress;
  doc["sensorFilter"] = sensorFilter;
  doc["temperatureSampling"] = temperatureSampling;
  doc["humiditySampling"] = humiditySampling;
  doc["pressureSampling"] = pressureSampling;
}

int SHI::BME280Config::getExpectedCapacity() const {
  return JSON_OBJECT_SIZE(6);
}

