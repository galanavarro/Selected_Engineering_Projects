# PPG Sensor Acquisition — Arduino & MAX30102

Biomedical sensor-integration project involving red and infrared photoplethysmography (PPG) acquisition over I²C, serial recording and signal visualisation.

## Project overview
The project connects an Arduino UNO to a MAX30102 optical sensor to acquire red/infrared measurements. The accompanying team report documents the connections, recorded signals, visualisation using RealTerm and Excel, and factors affecting measurement quality.

## Firmware
`firmware/PPG_MAX30102/PPG_MAX30102.ino` configures red/infrared acquisition and prints the readings through the serial interface at **9600 baud**.

| Setting | Value |
|---|---|
| LED amplitude setting | `0x1F` |
| Sample averaging | 4 |
| LED mode | 2 — red and infrared |
| Configured sample rate | 400 samples/s |
| Pulse width | 411 µs |
| ADC range setting | 4096 |

The configured sensor sample rate should not be interpreted as a verified serial-output rate. The sketch outputs raw readings; it does not itself calculate heart rate or SpO₂.

## Files
- `firmware/PPG_MAX30102/PPG_MAX30102.ino` — Arduino sketch.
- `report/ppg_pulse_oximetry_report_es.pdf` — original project report in Spanish.
- `docs/compilation_check.md` — supplied Arduino UNO verification result and its scope.
- `LICENSE-SparkFun.txt` — MIT notice for the underlying SparkFun example.

## Setup
1. Install Arduino IDE and the **Arduino AVR Boards** package.
2. Install **SparkFun MAX3010x Pulse and Proximity Sensor Library** using Library Manager.
3. Open `firmware/PPG_MAX30102/PPG_MAX30102.ino` and select **Arduino Uno**.
4. Click **Verify** to compile. No board connection is needed for verification.
5. To acquire physical signals, connect the module using its documented power and logic-level requirements. On the UNO, SDA is A4 and SCL is A5; a common ground is required.
6. Select the connected board's port, upload the sketch and open the serial monitor at **9600 baud**.

The library uses the `MAX30105.h` class name for supported MAX3010x devices, including MAX30102. The original firmware header refers to a MAX30105 breakout; its power recommendations must not be treated as specifications for every MAX30102 module. The included configuration uses only red and infrared channels.

## Verification
The laboratory work included physical sensor acquisition, serial recording and signal visualisation, as documented in the project report.

The included Arduino sketch also compiled successfully for Arduino UNO: **5,784 bytes of program storage (17%)** and **555 bytes of global RAM (27%)**. See [compilation check](docs/compilation_check.md).

## Background and attribution
Team project completed for **Equipos de Monitorización, Diagnóstico y Terapia** at Universidad Politécnica de Cartagena.

The firmware adapts [SparkFun Example1_Basic_Readings](https://github.com/sparkfun/SparkFun_MAX3010x_Sensor_Library/tree/master/examples/Example1_Basic_Readings), by Nathan Seidle, to red/infrared acquisition. The SparkFun attribution and MIT notice are retained. The project demonstrates sensor integration and signal inspection rather than a clinically validated pulse oximeter.
