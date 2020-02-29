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

namespace SHI {

class BME280 : public SHI::Sensor {
 public:
  explicit BME280(TwoWire &i2cPort) : Sensor("BME280"), i2cPort(&i2cPort) {}
  std::vector<SHI::MeasurementBundle> readSensor() override;
  bool setupSensor() override;
  bool stopSensor() override { return true; }

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
};

}  // namespace SHI
