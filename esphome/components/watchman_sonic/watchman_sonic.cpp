#include "watchman_sonic.h"
#include "esphome/core/log.h"
#include <vector>

namespace esphome {
namespace watchman_sonic {

static const char *TAG = "watchman_sonic";

void WatchmanSonicSensor::setup() {
  ESP_LOGI(TAG, "Watchman Sonic sensor initialized");
}

void WatchmanSonicSensor::loop() {
  std::vector<uint8_t> packet;

  if (!this->read_packet(packet))
    return;

  if (packet.size() < 8) {
    ESP_LOGW(TAG, "Packet too short");
    return;
  }

  this->process_packet(packet);
}

bool WatchmanSonicSensor::read_packet(std::vector<uint8_t> &packet) {
  // Placeholder: CC1101 packet reader will be added next
  return false;
}

void WatchmanSonicSensor::process_packet(const std::vector<uint8_t> &packet) {
  uint8_t ullage_raw = packet[3];  // Watchman Sonic protocol: byte 3 = ullage cm

  ESP_LOGI(TAG, "Ullage: %u cm", ullage_raw);
  this->publish_state(ullage_raw);
}

}  // namespace watchman_sonic
}  // namespace esphome
