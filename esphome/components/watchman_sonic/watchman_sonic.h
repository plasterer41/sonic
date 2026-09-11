#pragma once
#include "esphome/core/component.h"
#include "esphome/components/sensor/sensor.h"

namespace esphome {
namespace watchman_sonic {

class WatchmanSonicSensor : public sensor::Sensor, public Component {
 public:
  void setup() override;
  void loop() override;

 protected:
  void process_packet(const std::vector<uint8_t> &packet);
  bool read_packet(std::vector<uint8_t> &packet);
};

}  // namespace watchman_sonic
}  // namespace esphome
