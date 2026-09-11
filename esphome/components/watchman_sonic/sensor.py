import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import sensor
from esphome.const import CONF_ID

watchman_ns = cg.esphome_ns.namespace("watchman_sonic")
WatchmanSonicSensor = watchman_ns.class_("WatchmanSonicSensor", sensor.Sensor, cg.Component)

CONFIG_SCHEMA = sensor.sensor_schema(WatchmanSonicSensor).extend({
    cv.Required(CONF_ID): cv.declare_id(WatchmanSonicSensor),
})

def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    yield sensor.register_sensor(var, config)
    yield cg.register_component(var, config)

