# Erklärung des Entwicklungsprozesses

## Ausgangspunkt
Als Ausgangspunkt wurde das Tutorial "Ray Tracing in One Weekend" verwendet. Dieses stellte die grundlegenden Konzepte eines einfachen Raytracers bereit. Das Tutorial wurde bis einschließlich Kapitel 8 "Anti-Aliasing" befolgt. Das Tutorial stellte die folgende Funktionalität zur Verfügung:
- Erzeugen eines Bilds im ppm Format
- Für jeden Pixel das Schicken von Strahlen durch eine virtuelle Kamera in die Szene
- Grundlegende mathematische Operationen und 3d Vektoren
- Kugel mit dazugehörigem Strahl-Kugel-Schnittest
- Oberflächennormalen zur Färbung/ Visuallisierung der Oberfläche
- Konzept eines hittable Objekts und eine Liste mehrere hittable Objekte -> Szenen mit mehrere Objekten
- hit record zum Speichern von Treffern
- Antialiasing: statt eines Strahls pro Pixel: mehrere, leicht unerschiedliche Strahlen innerhalb eines Pixeln, Mitteln der Ergebnisse.

Insgesamt liefert das Tutorial eine grundlegende Raytracing Pipeline: eine Kamera erzeugt Strahlen, die gegen eine oder mehrere Kugeln getestet werden. Bei einem Treffer werden Informationen über den Schnittpunkt und die Oberflächennormale berechnet und daraus eine Farbe berechnet. Zusätzlich können mehrere Sample pro Pixel berechnet werden, Antialiasing zu ermöglichen.

## Entwicklungsprozess
- Festigstellung Tutotial bis Kapitel 8
- vec3.h beibehalten, neue vec4.h & matrizen.h erstellt -> ermöglicht homogene Notation und Transformationen
- simple_object definiert, Kamera und Kugel zu simple_object umgeschrieben, sodass sie Transformationsmatrizen unterstützen. 
- Kugel erweitert, sodass für Schnittberechnungen die Strahlen aus dem Kamera Space in den World- und dann den Object Space der Kugel transformiert werden. War mathematisch einfacher als anders rum. Kugel und Kamera können jetzt mithilfe von Transformationsmatrizen verschoben, skaliert, gedreht werden.
- triangle mit Schnitttest implementiert, erst eigener Schnittalgorithmus, dann Muller-Trumbore Algorithmus (ohne backface culling). 
- triangle_mesh implementiert, Muller-Trumbore Algorithmus erweitert für Schnitttest
- Genererll file Strukturen, includes und Ordner Struktur geändert & aufgeräumt
- .obj files eingelesen, daraus triangle_meshes erzeugt
- verschiedene .obj files getestet
- Belichtung: zuerst Lambert cosine law, dann Erweiterung zu Phong: diffuse, dann specular lighting, dann shadow rays. 
- eigene Testing Umgebung
- Lichtquelle, Material hinzugefügt, neue Definition für Farben
- Ordner Struktur geändert

## Wesentliche Unterschiede zu Tutorial Version
### Mathematische Struktur
Tutorial: 3d Vektoren vec3, Farben als vec3, Intervalle
Eigener Ray Tracer: 3d vektoren vec3, Intervalle, 4d Vektoren vec4, Matrizen, Homogene Notation, Transformationen
