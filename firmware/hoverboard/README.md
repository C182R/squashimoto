# Hoverboard board firmware

Upstream firmware is not vendored here — this folder holds our config changes and flashing notes.

| Board | Role | Firmware |
|---|---|---|
| GD32F103 mainboard + 2 sideboards (hoverboard A) | Rear wheel pair | [EFeru/hoverboard-firmware-hack-FOC](https://github.com/EFeru/hoverboard-firmware-hack-FOC) — `VARIANT_USART` on USART3, `TRQ_MODE` |
| GD32E230 split boards (hoverboard B) | Front swerve bogie | [RoboDurden/Hoverboard-Firmware-Hack-Gen2.x-GD32](https://github.com/RoboDurden/Hoverboard-Firmware-Hack-Gen2.x-GD32) — target 3 (gd32e230) |

To pin exact upstream versions later, add them as submodules:

```
git submodule add https://github.com/EFeru/hoverboard-firmware-hack-FOC firmware/hoverboard/efru-foc
git submodule add https://github.com/RoboDurden/Hoverboard-Firmware-Hack-Gen2.x-GD32 firmware/hoverboard/gen2x
```
