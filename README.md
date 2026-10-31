# Squashimoto

A self-driving, self-balancing surveyor robot built from salvaged hoverboard hub motors in Belize City. It roams town on its own, maps and films its route, delivers 3D prints from the shop, and can stand up and balance on either wheel pair for a ~1 m camera vantage.

Built with support from Hack Club Fabricate, and as a Hack Club Fallen build (demo at Maker Faire Shenzhen, Dec 2026).

## Layout

| Path | What lives there |
|---|---|
| `bom/` | Bill of materials (`squashimoto-bom.csv`) |
| `hardware/pcb/controller/` | Main controller board — KiCad (ESP32-WROOM-32E, ICM-42688-P IMU, TPS54360B buck from 36 V) |
| `hardware/pcb/encoder/` | AS5600 steering encoder board — KiCad |
| `cad/` | SolidWorks parts and assemblies, plus Bambu Studio `.3mf` print projects; `cad/exports/` for STEP / STL |
| `firmware/controller/` | Balance loop and high-level control for the controller board |
| `firmware/hoverboard/` | Notes and config for the reflashed hoverboard boards |
| `docs/journal/` | Build journal |

## Drive electronics

- **Rear pair:** GD32F103 hoverboard mainboard running [EFeru hoverboard-firmware-hack-FOC](https://github.com/EFeru/hoverboard-firmware-hack-FOC) (USART control).
- **Front pair:** GD32E230 split boards running [RoboDurden Hoverboard-Firmware-Hack-Gen2.x-GD32](https://github.com/RoboDurden/Hoverboard-Firmware-Hack-Gen2.x-GD32).

## Status

V1 in progress. Controller PCB order deadline: Nov 10, 2026.

## License

All rights reserved for now (private). License to be chosen before going public.
