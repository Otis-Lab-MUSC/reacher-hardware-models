# Head-Fixed Mice Hardware Designs

[![DOI](https://zenodo.org/badge/1114704891.svg)](https://doi.org/10.5281/zenodo.17903383)

*This repository hosts downloadable STL files for 3D-printable hardware components supporting the head-restrained drug self-administration protocol in mice, as described in Doncheck et al. (Nature Protocols, 2025). For the full protocol and software resources, visit the [main aggregation repo](https://github.com/otis-lab-musc/doncheck-et-al-nature-protocols-2025). Original designs editable in [Tinkercad](https://www.tinkercad.com/).*

## Overview

These STL files enable construction of custom equipment using affordable 3D printing, including levers for self-administration, surgical tools for vein elevation, neck braces for restraint, syringe pumps for infusions, and Arduino enclosures. Components are modular, built from common lab materials (e.g., M3/M6 screws, PLA filament), and optimized for head-fixed mouse setups.

- **Printing Recommendations**: Use PLA or ABS; 0.2mm layer height, 20% infill, supports where needed. Scale as required for your printer.
- **Total Files**: 20+ individual STLs, organized by category.
- **Reproducibility**: Files are versioned; download via GitHub Releases for snapshots.

For assembly instructions, wiring, and integration with the REACHER software stack, refer to the [paper](https://doi.org/10.1038/s41596-025-XXXXX) or main repo.

## Downloading Files

- **Latest Release (v1.0.0)**: [Download all STLs as ZIP](https://github.com/otis-lab-musc/reacher-hardware-models/releases/download/v0.0.0/models.zip) – Includes all files.
- **Individual Files**: Browse the Releases assets or clone the repo and access `/models/` folder (e.g., `models/lever/head.stl`).

After downloading, import STLs into slicer software (e.g., Cura, PrusaSlicer) for printing.

## Component List

STLs are grouped by category. Each includes print notes in the filename or accompanying README snippets.

### Self-Ad Lever

| Item    | File Path | Description |
|---------|------------------------------|-------------|
| Head   | `models/lever/lever_head.stl`     | The "C" and "NO" wires will come out through the holes on the bottom of the heads. The neck connector part of the design was also shortened. |
| Lid    | `models/lever/lever_lid.stl`      | Lid part to fix down the switches in the lever head. Screw with a M3 nut and 16mm (or longer) screw. The design will print 4 lids at a time, break to use individual parts. |
| Neck   | `models/lever/lever_neck.stl`     | Extended neck part to accommodate wider range for lever positioning. Screw to the lever head with a M6 screw and nuts. |
| Bridge | `models/lever/lever_bridge.stl`   | Height & length will accommodate wider range or lever positioning. |

### Vein Elevator

| Item         | File Path | Description |
|--------------|--------------------------------------------|-------------|
| Assembled   | `models/vein-elevator/vein_elevator_assembled.stl`      | Full assembly model for reference (print sub-components). |
| Needle Ball | `models/vein-elevator/vein_elevator_needle_ball.stl`    | We cut out the needle screw part of a 3 mL syringe and placed it in the hole of the ball using super glue (photo). Use a higher infill setting to make a weighted ball for a stabler support. |
| Needle Base | `models/vein-elevator/vein_elevator_needle_base.stl`    | Fill the inner space of the base with play-doh to hold the needle ball in the desired direction (photo). |
| Spatula Base| `models/vein-elevator/vein_elevator_spatula_base.stl`   | Adjust the negative space in the design to accommodate the spatula width, if needed. Fill the inner space of the base with play-doh to hold the spatula in the desired direction (photo). |

### Neck Brace

| Item     | File Path | Description |
|----------|------------------------------------|-------------|
| Small   | `models/neck-brace/neck_brace_small.stl`     | Sized for smaller mice/necks. |
| Medium  | `models/neck-brace/neck_brace_medium.stl`    | Standard size for adult mice. |
| Large   | `models/neck-brace/neck_brace_large.stl`     | For larger strains or adjustments. |
| X-Large | `models/neck-brace/neck_brace_x_large.stl`   | Extended for variable head-fixation setups. |

### Syringe Pump

| Item                  | File Path | Description |
|-----------------------|-------------------------------------------------------|-------------|
| Assembled            | `models/syringe-pump/syringe_pump_assembled.stl`                  | Full pump assembly for visualization (print sub-parts). |
| Motor End            | `models/syringe-pump/syringe_pump_motor_end.stl`                  | Mounts stepper motor; compatible with NEMA 17. |
| Carriage             | `models/syringe-pump/syringe_pump_carriage.stl`                   | Slides along rails for plunger push. |
| Clip                 | `models/syringe-pump/syringe_pump_clip.stl`                       | Adjust the negative space in the design to accommodate the syringe diameter. |
| Body Holder-semicircle | `models/syringe-pump/syringe_pump_syringe_holder.stl`   | Put an insulation tape on the curvature where the syringe sits to provide a better grip. Adjust the negative space in the design to accommodate the syringe diameter. |
| Idler End            | `models/syringe-pump/syringe_pump_idler_end.stl`                  | Non-motor end cap with bearings. |

### Arduino Box

| Item             | File Path | Description |
|------------------|--------------------------------------------------|-------------|
| Arduino Box-body| `models/syringe-pump/syringe_pump_arduino_box_body.stl`      | Remove the plastic holder on the bottom of the Arduino (Uno3) and screw in the box using M3 screws (photo). |
| Arduino Box-lid | `models/syringe-pump/syringe_pump_arduino_box_lid.stl`       | Snap-fit or screw-on cover for electronics protection. |

## Citation

Doncheck, E.M. et al. Drug self-administration in head-fixed mice. *Nat. Protoc.* (2025). https://doi.org/10.1038/s41596-025-XXXXX

For this repo: [Zenodo record](https://doi.org/10.5281/zenodo.17903383).

---

*Last updated: December 2025.*
