# Erklärung der grundlegenden Rendering Entscheidungen

## Primary rays
Die Kamera erzeugt für jeden Pixel einen primären Strahl. Dieser testet für alle Dreiecke/ Objekte in der Szene, ob er es trifft. Es wird nur der Treffer gezählt, der am weitesten an der Kamera dran ist (der Treffer mit dem kleinsten t).

## Anti-Aliasing
Optional können statt einem Strahl pro Pixel auch eine beliebige Anzahl an Rays geschickt werden. Die machen das Gleiche wie ein einzelner primärer Strahl, nur, dass deren Ergebnisse für den betreffenden Pixel gemittelt werden. Dadurch entstehen weiche Kanten und glattere Übergänge, ist aber deutlich teurer als das render mit einem Strahl pro Pixel. Kann in der main.cpp aus-/ oder einkommentiert werden. Die Zahl 100 wurde aud dem Tutorial übernommen, weil sie eine gute Balance zwischen Ergebnis und Rechenzeit bietet. 

## Phong
### Schattierung
Die Beleuchtung wurde mit dem Phong Modell erstellt. Für jeden primären Strahl wird, für jeden gefundenen Treffer und für jede Lichtquelle, erst ein weiterer Strahl von dem gefundenen Schnittpunkt zur Lichtquele geschickt. Wenn kein weiterer Treffer zwischen Schnittpunkt und Lichtquelle gefunden wird, trifft das Licht voll auf den Schnittpunkt. Wenn ein Treffer dazwischen gefunden wird, kommt das Licht dieser Lichtquelle nicht auf dem Schnittpunkt an. Dieser Teil ermöglicht Schattierung, da er destlegt, wie viel Licht der Lichtquelle tatsächlich beim Schnittpunkt ankommt. Das wird im Folgenden einkommendes Licht IL genannt.
### Diffuses Licht
Als nächstes wird das diffuse Licht berechnet. Der berechnet sich aus 
- Skalar kd (hier auf 1.0/pi gesetzt), repräsentiet die diffuse Reflektivität
- dem Winkel zwischen dem Normalenvektor des Schnittpunks N und dem Vektor, der in Richtung der Lichtquelle zeigt L. Da beide Vektoren normalisiert sind, ist das Skalrprodukt und der Winkel das Gleiche. Das repräsentiert die Intensität des diffus reflektierten Lichts.
- und dem einkommenden Licht IL, was oben bei Schattierung berechnet wird
- Insgesamt lautet die verwendete Formel: kd * dot(N,L) * IL. kd soll später eine Material Eigenschaft werden, ist momentan aber gehardcoded.
### Spekulares Licht
Das Spekulare Licht benutzt den Winkel zwischen de Sichtrichtung und der Reflektionsrichtung:
- der Sichtrichtung V, also dem Vektor von Schnittpunkt zu Kamera, normalisiert
- der Reflektionsrichtung R: 2 * dot(Normalenvektor Schnittpunkt, Richtungsvektor zur Lichtquelle) * Normalenvektor Schnittpunkt - Richtungsvektor zur Lichtquelle: 2 * (l * n) * n - l (alles normalisiert)
- Das ganze spekulare Licht wird dann berechnet aus: ks * dot(R, V)^ns * IL. ks und ns sind Konstanten, die im Code vorerst fest gesetzt werden, später aber wie kb bei diffusem Licht Materialeigenschaften werden sollen.
### Zusammensetzung
Insgesamt berechnet sich die Farbe für den Pixel, zu dem der Strahl gehört wie folgt: 
Füe alle Lichtquellen wird aufsummiert: diffuses Licht * Farbe diffuses Licht + spekulares Licht (später: * Farbe spekulares Licht)


