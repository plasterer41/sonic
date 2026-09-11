#include "watchman_sonic.h"
#include "esphome/core/log.h"
#include "esphome/components/cc1101/cc1101.h"
#include <vector>

namespace esphome {
namespace watchman_sonic {

static const char *TAG = "watchman_sonic";

void WatchmanSonicSensor::setup() {
  ESP_LOGI(TAG, "Watchman Sonic sensor initialized");

  auto *cc = cc1101::global_cc1101;

  cc->set_modulation(cc1101::MODULATION_ASK_OOK);
  cc->set_deviation(0);
  cc->set_data_rate(4800);
  cc->set_rx_bandwidth(58e3);
  cc->set_frequency(433.92e6);

  cc->apply_settings();
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
  auto *cc = cc1101::global_cc1101;

  if (!cc->packet_available())
    return false;

  std::vector<uint8_t> raw;
  cc->read_fifo(raw);

  if (raw.size() < 4)
    return false;

  packet = raw;
  return true;
}

void WatchmanSonicSensor::process_packet(const std::vector<uint8_t> &packet) {
  uint8_t ullage_raw = packet[5];  // Watchman Sonic protocol

  ESP_LOGI(TAG, "Ullage: %u cm", ullage_raw);
  this->publish_state(ullage_raw);
}

}  // namespace watchman_sonic
}  // namespace esphome
