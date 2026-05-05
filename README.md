# REACHER Hardware Models — 3D-Printable Rig Components

**Downloadable STL files and Arduino sketches for building a complete head-fixed behavioral rig**

[![Version](https://img.shields.io/badge/version-1.0.0-blue)](https://github.com/Otis-Lab-MUSC/reacher-hardware-models)
[![Platform](https://img.shields.io/badge/platform-STL%20%2F%20Arduino-blue)]()
[![License](https://img.shields.io/badge/license-MIT-green)](LICENSE)
[![REACHER Suite](https://img.shields.io/badge/REACHER_Suite-member-orange)](https://github.com/Otis-Lab-MUSC)

*Written by*: Joshua Boquiren

[![](https://img.shields.io/badge/@thejoshbq-grey?style=flat&logo=github)](https://github.com/thejoshbq)

---

## Table of Contents

- [Overview](#overview)
- [Downloading Files](#downloading-files)
- [Component List](#component-list)
  - [Lever Components](#lever-components)
  - [Surgery Tools](#surgery-tools)
  - [Syringe Pump & Arduino](#syringe-pump--arduino)
  - [Ethernet Circuit Box](#ethernet-circuit-box)
  - [Ethernet Jack Plug Components](#ethernet-jack-plug-components)
  - [Head Fixation Station](#head-fixation-station)
- [License](#license)
- [Contact](#contact)

## Overview

This repository hosts downloadable STL files for 3D-printable hardware components supporting the head-restrained drug self-administration protocol in mice, as described in Doncheck et al. (Nature Protocols, 2025). For the full protocol and software resources, visit the [main aggregation repo](https://github.com/otis-lab-musc/doncheck-et-al-nature-protocols-2025). Original designs editable in [Tinkercad](https://www.tinkercad.com/).

These STL files enable construction of custom equipment using affordable 3D printing, including levers for self-administration, surgical tools for vein elevation and neck restraint, syringe pumps for infusions, Arduino enclosures, Ethernet circuit and jack plug housings, and head fixation station specs. Components are modular, built from common lab materials (e.g., M3/M6 screws, PLA filament), and optimized for head-fixed mouse setups.

- **Printing Recommendations**: Use PLA or ABS; 0.2mm layer height, 20% infill, supports where needed. Scale as required for your printer.
- **Total Files**: ~25 STLs, 1 Arduino sketch, and 1 PDF engineering spec, organized by category.
- **Reproducibility**: Files are versioned; download via GitHub Releases for snapshots.

For assembly instructions, wiring, and integration with the REACHER software stack, refer to the [paper](https://doi.org/10.1038/s41596-025-XXXXX) or main repo.

## Downloading Files

- **Latest Release (v1.0.0)**: [Download all STLs as ZIP](https://github.com/otis-lab-musc/reacher-hardware-models/releases/download/v1.0.0/models.zip) – Includes all files.
- **Individual Files**: Browse the Releases assets or clone the repo and access the `/models/` subfolders (e.g., `models/Lever Components/`, `models/Surgery tools/`).

After downloading, import STLs into slicer software (e.g., Cura, PrusaSlicer) for printing.

## Component List

STLs are grouped by category. Each includes print notes in the filename or accompanying README snippets.

### Lever Components

| Item   | File Path | Description |
|--------|-----------|-------------|
| Bridge | [`models/Lever Components/01_021226_Lever bridge.stl`](models/Lever%20Components/01_021226_Lever%20bridge.stl) | Height & length will accommodate wider range of lever positioning. |
| Head   | [`models/Lever Components/02_021226_Lever head.stl`](models/Lever%20Components/02_021226_Lever%20head.stl)   | The "C" and "NO" wires will come out through the holes on the bottom of the heads. The neck connector part of the design was also shortened. |
| Lid    | [`models/Lever Components/03_021226_Lever lid.stl`](models/Lever%20Components/03_021226_Lever%20lid.stl)    | Lid part to fix down the switches in the lever head. Screw with a M3 nut and 16mm (or longer) screw. The design will print 4 lids at a time, break to use individual parts. |
| Neck   | [`models/Lever Components/04_021226_Lever neck.stl`](models/Lever%20Components/04_021226_Lever%20neck.stl)   | Extended neck part to accommodate wider range for lever positioning. Screw to the lever head with a M6 screw and nuts. |

### Surgery Tools

| Item            | File Path | Description |
|-----------------|-----------|-------------|
| Neck Brace      | [`models/Surgery tools/01_030626_Neck Brace.stl`](models/Surgery%20tools/01_030626_Neck%20Brace.stl)          | Single-size neck brace for mouse restraint during surgery. |
| Vein Elevator Ball  | [`models/Surgery tools/02_030626_Vein Elevator_Ball.stl`](models/Surgery%20tools/02_030626_Vein%20Elevator_Ball.stl)   | We cut out the needle screw part of a 3 mL syringe and placed it in the hole of the ball using super glue. Use a higher infill setting to make a weighted ball for a stabler support. |
| Vein Elevator Mount | [`models/Surgery tools/03_030626_Vein Elevator_Mount.stl`](models/Surgery%20tools/03_030626_Vein%20Elevator_Mount.stl)  | Fill the inner space of the mount with play-doh to hold the needle ball in the desired direction. |

### Syringe Pump & Arduino

| Item                   | File Path | Description |
|------------------------|-----------|-------------|
| Arduino Box            | [`models/Pump componenets and Arduino file/01_030626_Syringe PumpArduino_Box.stl`](models/Pump%20componenets%20and%20Arduino%20file/01_030626_Syringe%20PumpArduino_Box.stl)    | Remove the plastic holder on the bottom of the Arduino (Uno3) and screw in the box using M3 screws. |
| Arduino Box Lid        | [`models/Pump componenets and Arduino file/02_030626_Syringe PumpArduinoBox_Lid.stl`](models/Pump%20componenets%20and%20Arduino%20file/02_030626_Syringe%20PumpArduinoBox_Lid.stl) | Snap-fit or screw-on cover for electronics protection. |
| Carriage               | [`models/Pump componenets and Arduino file/03_030626_Syringe Pump_Carriage.stl`](models/Pump%20componenets%20and%20Arduino%20file/03_030626_Syringe%20Pump_Carriage.stl)      | Slides along rails for plunger push. |
| Idler End              | [`models/Pump componenets and Arduino file/04_030626_Syringe Pump_Idler End.stl`](models/Pump%20componenets%20and%20Arduino%20file/04_030626_Syringe%20Pump_Idler%20End.stl)     | Non-motor end cap with bearings. |
| Motor End              | [`models/Pump componenets and Arduino file/05_030626_Syringe Pump-Motor End.stl`](models/Pump%20componenets%20and%20Arduino%20file/05_030626_Syringe%20Pump-Motor%20End.stl)     | Mounts stepper motor; compatible with NEMA 17. |
| Syringe Holder         | [`models/Pump componenets and Arduino file/06_Syringe Pump-Syringe holder.stl`](models/Pump%20componenets%20and%20Arduino%20file/06_Syringe%20Pump-Syringe%20holder.stl)       | Put insulation tape on the curvature where the syringe sits for a better grip. Adjust the negative space to accommodate the syringe diameter. |
| Arduino Sketch         | [`models/Pump componenets and Arduino file/Pump_Calibration_030626/`](models/Pump%20componenets%20and%20Arduino%20file/Pump_Calibration_030626/)                  | AccelStepper-based bench-calibration sketch for the NEMA 17 syringe pump. Supports serial commands, button input, and trigger pin control. |

### Ethernet Circuit Box

| Item      | File Path | Description |
|-----------|-----------|-------------|
| Body      | [`models/Ethernet Circuit Box/01_022526_ECB_Body.stl`](models/Ethernet%20Circuit%20Box/01_022526_ECB_Body.stl)      | Main enclosure body for the Ethernet circuit board. |
| Lid       | [`models/Ethernet Circuit Box/02_022526_ECB_Lid.stl`](models/Ethernet%20Circuit%20Box/02_022526_ECB_Lid.stl)       | Snap-fit lid for the Ethernet circuit box. |
| Port Clip | [`models/Ethernet Circuit Box/05_022526_EJPB_Portclip.stl`](models/Ethernet%20Circuit%20Box/05_022526_EJPB_Portclip.stl) | Shared port clip component (also used with Ethernet Jack Plug). |

### Ethernet Jack Plug Components

| Item      | File Path | Description |
|-----------|-----------|-------------|
| Body      | [`models/Ethernet Jack Plug Components/01_022526_EJPB_Body.stl`](models/Ethernet%20Jack%20Plug%20Components/01_022526_EJPB_Body.stl)    | Main body for the Ethernet jack plug enclosure. |
| Lid       | [`models/Ethernet Jack Plug Components/02_022526_EJPB_Lid.stl`](models/Ethernet%20Jack%20Plug%20Components/02_022526_EJPB_Lid.stl)     | Lid for the Ethernet jack plug enclosure. |
| Hinge     | [`models/Ethernet Jack Plug Components/03_022526_EJPB_Hinge.stl`](models/Ethernet%20Jack%20Plug%20Components/03_022526_EJPB_Hinge.stl)   | Hinge component for lid attachment. |
| Lid Clip  | [`models/Ethernet Jack Plug Components/04_022526_EJPB_Lidclip.stl`](models/Ethernet%20Jack%20Plug%20Components/04_022526_EJPB_Lidclip.stl) | Clip to secure the lid in place. |
| Port Clip | [`models/Ethernet Jack Plug Components/05_022526_EJPB_Portclip.stl`](models/Ethernet%20Jack%20Plug%20Components/05_022526_EJPB_Portclip.stl)| Shared port clip component (also used with Ethernet Circuit Box). |

### Head Fixation Station

> **Note:** These are **machining specifications**, not 3D-printed STL files. The PDF contains SolidWorks engineering drawings for stainless steel head rings (holder top, holder bottom, stereotax base, and hole5mm component) intended for fabrication by a machine shop.

| Item               | File Path | Description |
|--------------------|-----------|-------------|
| Head Rings Specs   | [`models/Head Fixation station/head_fixationstation_headrings_specs.pdf`](models/Head%20Fixation%20station/head_fixationstation_headrings_specs.pdf) | Engineering drawings for stainless steel head fixation ring components. |

---

*Last updated: March 2026.*

---

## License

This project is licensed under the MIT License. See [LICENSE](LICENSE) for details.

## Contact

Joshua Boquiren — [thejoshbq@proton.me](mailto:thejoshbq@proton.me)

[GitHub: Otis-Lab-MUSC/reacher-hardware-models](https://github.com/Otis-Lab-MUSC/reacher-hardware-models)
