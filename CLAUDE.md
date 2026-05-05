# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Repository purpose

Static asset repository for the REACHER head-restrained drug self-administration rig (Doncheck et al., Nature Protocols 2025). It hosts ~25 printable STL files, one PDF of machine-shop drawings, and one standalone Arduino sketch. There is no build system, no test suite, and no linter — edits are to design files and one .ino sketch.

This repo is downstream from `reacher-firmware` (which contains the in-experiment paradigm firmware) and is **not** loaded by the REACHER backend. The Arduino sketch here is a bench tool for calibrating syringe pumps, not a REACHER paradigm.

Releases are cut on GitHub as `v<semver>` and ship a single `models.zip` aggregating everything under `models/`.

## Layout

```
models/
├── Lever Components/               # Bridge, head, lid, neck STLs
├── Surgery tools/                  # Neck brace, vein elevator (ball + mount)
├── Pump componenets and Arduino file/   # NOTE: directory name has a typo ("componenets") — preserve it
│   ├── 01..06_*.stl                # Pump body parts
│   └── Pump_Calibration_030626/    # Standalone bench-calibration sketch
├── Ethernet Circuit Box/           # Body, lid, port clip
├── Ethernet Jack Plug Components/  # Body, lid, hinge, lid clip, port clip
└── Head Fixation station/          # PDF of SolidWorks machining specs (NOT 3D-printable)
```

File names follow `NN_MMDDYY_<part>.stl` — numeric prefix is intra-category assembly order, the 6-digit date is **MMDDYY** and is shared across all parts in a category release (e.g., every Lever part is dated `021226` = 2026-02-12). When revising one part in a category, the convention is to re-date the whole batch.

The README references a `Pump_HomeReturn_030626/` sketch in the pump folder, but only `Pump_Calibration_030626/` is currently present — treat the README list as aspirational for that one entry. There is also a stray `Pasted Text.txt` in the pump folder that is unrelated cruft from another conversation; ignore it.

## Pump calibration sketch

`models/Pump componenets and Arduino file/Pump_Calibration_030626/Pump_Calibration_030626.ino`

- Targets Arduino Uno + AccelStepper-driven NEMA 17 with a 2-pin step/dir driver (`stepPin=5`, `dirPin=6`).
- 3 button inputs (FF / STOP / FR on pins 2/3/4, INPUT_PULLUP) + 7 trigger pins (7–13) for parametric infusions. The user picks one of the 7 infusion configurations over Serial at 115200 baud at startup.
- The constant `steps_per_mm = 1 / 0.00051766304` was empirically determined (147,200 steps = 76.2 mm of carriage travel, verified 2022-10-05). Do not "simplify" this magic number — the comment block at the top of the file is the authoritative derivation. Per-syringe inner diameters (`syringe_id[]`) are also calibrated values; preserve them when refactoring.
- The `for (uint8_t i = 0; i <= 7; i++)` loop in `setup()` walks 8 indices into 7-element arrays — undefined behavior, almost certainly an off-by-one. Confirm intent with the user before "fixing" it: the rig has been calibrated against whatever this loop currently produces, and silently correcting it could change physical infusion volumes.

## Conventions

- **STL edits**: original designs live in Tinkercad (per README). Treat checked-in STLs as exported artifacts; do not attempt to programmatically rewrite mesh files.
- **Directory rename**: `Pump componenets and Arduino file` is referenced verbatim in the README and in URL paths within releases. Do not "fix" the typo without coordinating with the user.
- **README STL tables** are the canonical component list — when adding/removing files under `models/`, update the matching table row.
