# Embedded Systems Using Motion Sensor

Welcome to the Embedded Systems Using Motion Sensor repository. This project is an intelligent automated security and lighting system powered by the ESP8266 development framework. It integrates motion tracking and ambient light monitoring to build an energy-efficient, responsive smart environment controller.

By combining presence detection with light sensitivity levels, the system operates as an automated corridor nightlight, a home security alarm, or an automated energy-saving system that triggers components only when human activity is sensed under low-light conditions.

### Core Features
- Human Presence Detection: Uses a Passive Infrared (PIR) motion sensor to catch infrared heat signatures radiating from moving objects or people.
- Ambient Light Sensitivity: Integrates a Light Dependent Resistor (LDR) to evaluate surrounding brightness levels, ensuring visual outputs only activate when it is dark.
- Dynamic Security Warning: Features a localized Piezo Buzzer to broadcast an immediate audio alert whenever unexpected movement trips the sensor thresholds.
- Smart Power Saving: Automatically controls a high-efficiency LED indicator, acting as a smart ambient light source that only activates when someone passes by in the dark.
- Standalone Prototyping Base: Built completely within the local ESP8266 processing framework to handle rapid inputs and trigger instant local hardware output routines.
