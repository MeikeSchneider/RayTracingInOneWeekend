# Erklärung der grundlegenden obj loader Entscheidungen

## Struktur von .obj files
Der obj_loader ließt aktuell: 
- v
- vt
- vn
- f

### Vertices v
Eine Zeile besteht aus v und den x, y, z Koordinaten eines vertex. Werden im obj loader benutzt, um die Liste von vertices zu setzen.

### Vertex texture vt
Eine Zeile besteht aus vt und zwei Werten zwischen 0 und ist. Beschreibt Position auf Textur, normalerweise 2 Werte zwischen 0 & 1, optional ein dritter (default = 0). Texture Koordinaten. Da keine Texturen verwendet werden, wird das zwar eingelesen, aber nicht verwendet. 

### Normalenvektoren vn
Eine Zeile besteht aus vn und den x, y, z Koordinaten eines Normalenvektors. Diese werden benutzt, um glattere Oberflächen zu erzeugen. Werden hier nicht benutzt, aber eingelesen.

### Face Vertices f
Eine Zeile hat mehrere Optionen, wie sie aussehen kann: 
- f 1 2 3: Bedeutet: erzeuge ein Dreieck aus vertices 1, 2 und 3. Die Zahlen sind dabei Indizes für die vertices.
- f 1/1/1 2/2/2 3/3/3: Bedeutet: Position/ Textur Koordinate / Normalenvektor. 1/1/1 bedeutet vertex 1, Textur Koordinate 1, Normalenvektor 1 usw. 
- f 1//7 2//8 3//9 Bedeutet: Vertex / keine Texture Coordinate / Normal
- f 1/4 2/5 3/6 Bedeutet: Vertex / Textur / keine Normal
Wird benutzt, um die Liste an indices zu erzeugen, mit deren Hilfe dann das Mesh erzeugt wird.
#### Handhabung im Code
Im Code werden die vier Fälle so gehandhabt, als ob immer alle neuen Werte da sind. Sollten aber welche fehlen, werden diese mit -1 gesetzt. Da alle drei Werte Indices sind, können diese nicht negativ werden. Ein negativer indice bedeutet also, dass die Information nicht vorhanden ist. So können die vier Fälle relativ einfach abgebildet werden. Später kann dann geprüft werden, ob die Werte -1, also nicht gesetzt wurden. v 1 2 3 wird also gelesen als 1/-1/-1  2/-1/-1  3/-1/-1. 

### Sonstiges
In .obj files kann es zusätzliche Dinge geben wie mtllib [external .mtl file name]. Da solche Sachen meistens mit Materialbeschreibungen in externen .mtl files zu tun, wird das hier nicht verwendet und beim Einlesen ignoriert.

## Ablauf
Zuerst wird ein obj_loader Objekt in der main.cpp erstellt. Mit der Funktion load wird dann die Datei eingelesen, die aus der Datei Zeile für Zeile die gewünschten Informationen in die Klassenvariablen schreibt. Dabei werden auch die vier möglichen Fälle, wie eine f Zeile aussehen kann, berücksichtigt. Die Daten aus v, vt, vn und f werden in vier Listen gespeichert. Alles andere in der Datei, wie Kommentare, wird ignoriert.
Aus diesen Listen wird dann im nächsten Schritt mit der make_triangle_mesh Funktion ein Dreiecksnetz erstellt. Dieses kann dann der Welt hinzugefügt und gerendert werden. 
