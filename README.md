# ANDROID BASED INDUSTRIAL FAULT MONITORING SYSTEM
This project uses an Arduino ATmega2560 with multiple sensors to monitor LPG gas levels, flames, temperature, and humidity.  
It alerts the user through a buzzer, LCD display, and the RemoteXY mobile app (via Bluetooth).

# Hardware
- Arduino ATmega2560 board  
- HC-05 Bluetooth module  
- 16x2 LCD display  
- DHT22 Temperature & Humidity Sensor  
- LPG Gas Sensor (MQ-series)  
- Flame Sensor  
- Buzzer & jumper wires

# Software
- Arduino IDE (for coding and uploading)  
- [RemoteXY](https://remotexy.com/en/) (for creating the mobile app interface)  

# Repository Structure
- `Arduino/` - All Arduino sketches (sensor monitoring and RemoteXY app)
- `docs/` - Circuit diagram
- `README.md` - Overview of the project

# RemoteXY App
The system integrates with the RemoteXY mobile app over Bluetooth, displaying:
- Gas level
- Flame detection status
- Temperature and humidity
