# Licenses

This repository uses two licenses: one for software and one for hardware.

## Software: MIT

Applies to everything in `firmware/`.

Full text: [`LICENSES/MIT.txt`](LICENSES/MIT.txt)

SPDX-License-Identifier: MIT

## Hardware: CERN-OHL-S v2

CERN Open Hardware Licence Version 2 - Strongly Reciprocal. Applies to the hardware design files and their documentation:

- `hardware/` (KiCad schematics, PCB layouts, symbol and footprint library, fabrication outputs)
- `cad/` (SolidWorks parts and assemblies, STEP exports)
- `bom/` (bill of materials)
- `docs/` (schematic exports, renders and images)

Full text: [`LICENSES/CERN-OHL-S-2.0.txt`](LICENSES/CERN-OHL-S-2.0.txt)

SPDX-License-Identifier: CERN-OHL-S-2.0

Copyright C182R 2026.

This source describes Open Hardware and is licensed under the CERN-OHL-S v2.

You may redistribute and modify this source and make products using it under the terms of the CERN-OHL-S v2 (https://ohwr.org/cern_ohl_s_v2.txt).

This source is distributed WITHOUT ANY EXPRESS OR IMPLIED WARRANTY, INCLUDING OF MERCHANTABILITY, SATISFACTORY QUALITY AND FITNESS FOR A PARTICULAR PURPOSE. Please see the CERN-OHL-S v2 for applicable conditions.

Source location: https://github.com/C182R/squashimoto

As per CERN-OHL-S v2 section 4, should you produce hardware based on this source, you must where practicable maintain the Source Location visible on the external case of the hardware or other products you make using this source.

## Third-party files

Files made by others keep their own licenses and are not covered by the licenses above. These include:

- KiCad stock footprints in `hardware/pcb/lib/squashimoto.pretty/` (see `SOURCES.txt` there), under the KiCad library license (CC-BY-SA 4.0 with the KiCad design exception)
- Vendor and library 3D models in `cad/` and `cad/exports/` (bearings, fasteners, servos, lidar, camera and similar bought parts)
- Datasheets in `docs/datasheets/`
