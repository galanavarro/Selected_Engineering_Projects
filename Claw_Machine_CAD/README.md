# Claw Machine — Mechanical CAD Design

We modelled a plush-toy claw machine in **SolidWorks**, bringing together the supporting structure, gripping mechanism and lifting assembly in a mechanical CAD project.

## What we designed
- **Supporting structure and housing components:** we modelled the base, panels, pillars and structural supports.
- **Claw assembly:** we assembled the gripping fingers, supports, shafts and connecting parts.
- **Lifting mechanism:** we worked on the parts and assemblies connecting the claw to its vertical movement system.
- **Assembly integration:** we brought the subsystems together in a top-level assembly.

## Editable CAD files
We include native SolidWorks parts (`.SLDPRT`) and assemblies (`.SLDASM`). We have preserved the original filenames and directory structure within each recovered project folder so that their references can be resolved in SolidWorks.

| Folder | Contents |
|---|---|
| `cad/main_project/` | Main project, including `Ensamblaje en proceso.SLDASM` and the organised part/subassembly folders |
| `cad/mechanism_assembly/` | Recovered `ENSAMBLAJE AB.SLDASM` and its mechanism components |
| `cad/alternative_assembly/` | Alternative recovered assembly set from the original `ENSAMBLAJE VIDEO` folder |
| `docs/file_inventory.csv` | List of included CAD files |

## Suggested inspection order
1. Download the full repository and keep its directory structure.
2. In SolidWorks, open `cad/main_project/Ensamblaje en proceso.SLDASM` to inspect the integrated assembly.
3. Explore `Gancho.SLDASM`, `Gancho + sist arriba-abajo.SLDASM` and `Enganche.SLDASM` within the main project's subfolders.
4. Inspect `cad/mechanism_assembly/ENSAMBLAJE AB.SLDASM` for the recovered mechanism assembly.

If SolidWorks requests a referenced part, locate the corresponding file within the recovered folders. Some filenames recur in different subassemblies, so we have not flattened the folder structure or merged identically named files.

## Project background
We completed this work collaboratively as a Computer-Aided Design project at Universidad Politécnica de Cartagena. We present our design in the first-person plural as a team project.

## Tools and skills
SolidWorks, mechanical part modelling, assembly modelling, mechanical interfaces, gripping mechanisms and electromechanical-system geometry.

## Project status
We developed the machine as a CAD project; we did not manufacture a physical machine. The recovered source files have been copied unchanged. Their references, rebuild status and required SolidWorks version have not been verified by reopening them during portfolio preparation. The top-level file retains its original name, `Ensamblaje en proceso.SLDASM`; no claim is made that it is a production-ready design. We retain the alternative assembly set separately rather than presenting it as another completed machine.

The current repository contains editable CAD files rather than exported renders or a video. The source folder name `ENSAMBLAJE VIDEO` refers to an assembly file set; no video file was present in that archive.
