/*
 * Copyright (c) 2020 Karsten Becker All rights reserved.
 * Use of this source code is governed by a BSD-style
 * license that can be found in the LICENSE file.
 */
#pragma once
#include <Adafruit_BME280.h>
#include <Adafruit_Sensor.h>
#include <SHISensor.h>

#include <memory>
#include <vector>

namespace SHI {

class BME280Config : public Configuration {
 public:
  BME280Config() {}
  explicit BME280Config(const JsonObject &obj);
  int getExpectedCapacity() const override;
  void fillData(JsonObject &doc) const override;
  int useBus = 0;
  bool primaryAddress = true;
  Adafruit_BME280::sensor_filter sensorFilter = Adafruit_BME280::FILTER_OFF;
  Adafruit_BME280::sensor_sampling temperatureSampling =
      Adafruit_BME280::SAMPLING_X1;
  Adafruit_BME280::sensor_sampling humiditySampling =
      Adafruit_BME280::SAMPLING_X1;
  Adafruit_BME280::sensor_sampling pressureSampling =
      Adafruit_BME280::SAMPLING_X1;
};

class BME280 : public SHI::Sensor {
 public:
  explicit BME280(const BME280Config &config)
      : Sensor("BME280"), config(config) {}
  std::vector<SHI::MeasurementBundle> readSensor() override;
  bool setupSensor() override;
  bool stopSensor() override { return true; }
  const Configuration *getConfig() const override { return &config; }
  bool reconfigure(Configuration *newConfig) override;
  bool reconfigure();

 private:
  std::shared_ptr<SHI::MeasurementMetaData> temperature =
      std::make_shared<SHI::MeasurementMetaData>("Temperature", "°C",
                                                 SHI::SensorDataType::FLOAT);
  std::shared_ptr<SHI::MeasurementMetaData> humidity =
      std::make_shared<SHI::MeasurementMetaData>("Humidity", "%",
                                                 SHI::SensorDataType::FLOAT);
  std::shared_ptr<SHI::MeasurementMetaData> pressure =
      std::make_shared<SHI::MeasurementMetaData>("Pressure", "hPa",
                                                 SHI::SensorDataType::FLOAT);
  TwoWire *i2cPort;
  Adafruit_BME280 bme;
  BME280Config config;
};

}  // namespace SHI
