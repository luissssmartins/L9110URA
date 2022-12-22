# URA
from mqtt.umqttsimple import MQTTClient
from sensors.hcsr04 import HCSR04

import ubinascii, machine, network, esp, gc, webrepl
import time, json

esp.osdebug(None)
gc.collect()

config_file = open('configuration/config.json')
config = json.load(config_file)
config_file.close()

client_id = ubinascii.hexlify(machine.unique_id())

ssid = config['ssid']
ssid_password = config['ssid_password']
mqtt_address = config['mqtt_address']
mqtt_port = config['mqtt_port']
mqtt_user = config['mqtt_user']
mqtt_password = config['mqtt_password']
webrepl_password = config['webrepl_password']

topic_sub = bytes(config['topic_sub'], 'utf-8')
topic_pub = bytes(config['topic_pub'], 'utf-8')

distSensor = HCSR04(trigger_pin=19, echo_pin=18)

last_message = 0
message_interval = 1

station = network.WLAN(network.STA_IF)

station.active(True)

if not station.isconnected():
    
    print('Connecting to WiFi')

    station.connect(ssid, ssid_password)

    while not station.isconnected():
        pass

    print(f'Connected to {ssid} with success. Config: {station.ifconfig()}')

webrepl.start(password= webrepl_password)

