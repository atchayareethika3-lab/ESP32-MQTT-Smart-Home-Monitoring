# ESP32 MQTT-Based Smart Home Monitoring and Alert System

## Overview
A simulated IoT system consisting of two independent ESP32 nodes that communicate over Wi-Fi using MQTT. Room A monitors temperature and publishes status messages, while Room B receives the messages and controls an LED as a remote indicator.

## System Architecture
1. Room A reads temperature data from a DHT22 sensor.
2. The ESP32 evaluates the temperature against a 30°C threshold.
3. Room A publishes `HIGH_TEMP` or `NORMAL_TEMP` to `smart-home/demo123/roomA/status`.
4. Room B subscribes to the same MQTT topic.
5. Room B turns its LED on or off according to the received message.

## Technologies Used
- ESP32
- DHT22 temperature and humidity sensor
- Wi-Fi (`Wokwi-GUEST`)
- MQTT publish/subscribe messaging
- TCP/IP networking
- Arduino C++
- PubSubClient and DHTesp libraries
- Wokwi simulator

## MQTT Configuration
- Broker: `test.mosquitto.org`
- Port: `1883`
- Topic: `smart-home/demo123/roomA/status`
- Publisher: Room A
- Subscriber: Room B

## Repository Structure
- `Room-A-Temperature-Monitor/`: sensor reading and MQTT publishing
- `Room-B-Alert-Node/`: MQTT subscription and LED control
- `images/`: circuit and testing screenshots

## Simulation and Testing
Both ESP32 nodes were simulated as separate Wokwi projects. The system was tested by changing the temperature input and observing the published status and corresponding LED response.

## Applications
- Distributed room temperature monitoring
- Remote status indication
- Basic smart home automation prototypes
- Foundation for multi-room environmental monitoring

## Limitations and Future Improvements
This project uses a public MQTT broker and a simulated environment. Future improvements include secure MQTT communication, a private broker, additional sensor nodes, and a dashboard for live monitoring.

## Author
Atchaya Reethika
