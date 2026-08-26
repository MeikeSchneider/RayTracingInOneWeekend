# Überlick: Ein in C++ implementierter Ray Tracer

# Features:
## Aktuell unterstützt der Ray Tracer:
- Primäre rays
- Schatten rays
- Kugeln, Dreicke, Dreiecksnetze
- .obj Import
- Transformationen
- Phong Beleuchtung
- Simple Materialien
- PPM Ausgabe

## Kompilieren:
make compile

## Ausführen:
./main.exe > image.ppm

## Command Line Optionen:
noch keine

# Projektstruktur:
images/
math/
io/
notizen/
obj_files/
old_files/
rendering/
scene/
    hittable_objects/
tests/


# Geplante Erweiterungen:
- Command line parsing
- Statistiken erfassen
- reproduzierbare Szene
- Bounding box
- BVH