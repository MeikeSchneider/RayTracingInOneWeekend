# Erklärung der grundlegenden Architektur Entscheidungen

## Ordner Struktur
- **docs:** Dokumentation der Orderstruktur und generellen Code- und Designentscheidungen
- **images:** enthält einige hübsche, gerenderte Bilder
- **io:** Dateien, die mit input/ output zu tun haben.
Der obj_loader ließt .obj Dateien ein und setzt alle nötigen Variablen, sodass dann ein Dreiecksnetz aus den Daten erstellt werden kann. image_writer enthält Funktionen, um Farben in ein gewünschtes Datei Format wie ppm zu schreiben.
- **math:** enthält alles, was an reiner Mathematik nötig ist. vec3.h aus dem Tutorial "ray tracing in one weekend" wurde fast unverändert gelassen. Daraus abgeleitet wurde vec4.h, um homogene Koordinaten und Vektor-Matrix-Operationen zu ermöglichen. matrix.h enthält Matrix Mathematik wie Invertierung, aber auch die Erstellung der Transformationsmatrizen mit verschiedenen Eingaben wie zB translation. interval.h ist wiederum fast unverändert aus dem Tutorial übernommen. Wird hauptsächlich benutzt, um Intervalle zu definieren, in denen Treffer der Schnitttest Funktionen gültig sein sollen. 
- **notizen:** enthält eigene Aufschriebe. notizen.txt beschreibt ausführen und testen des Codes, notizenC++.txt enthält Aufschriebe und Gelerntes über C++, notizenObj.txt beschäftigt sich mit dem .obj file Format, notizenTutorial.txt enthält Aufschriebe über das Tutorial.
- **obj_files:** enthält einige .obj files, die zu Testzwecken, als Beispiele oder weil die Modelle schön waren, verwendet wurden. 
- **old_files:** enthalten alte Dateien aus "Ray Tracing in One Weekend", die komplett durch eigene Versionen ersetzt wurden und damit überflüssig geworden sind. Die dateien sind zu Dokumentationszwecken aufgehoben.
- **rendering:** enthält alles, was zum rendern einer Szene nötig ist. Dazu gehören Farben, das Speichern von Treffern beim Schnitttest, Matterialien und die Strahlen.
- **scene:** enthält simple_object.h und alles, was davon erbt. Das sind also alles Objekte, die transformiert werden können. Die Untergruppierung hittable_objects sind alle Objecte, die zusätzlich von Strahlen getroffen werden können.
- **tests:** enthält alle Test Dateien
- **gitignore:** ist dafür da, dass zB .exe Dateien nicht mir auf git hochgeladen werden
- **image.ppm:** das aktuelle ppm Bild. 
- **main.cpp:** Main Funktion
- **Makefile:** ermöglicht make compile und make test
- **rtweekend.h:** häufig benutzte Mathe Dinge und Header, die überall zur Verfügung gestellt werden sollen, um unnötig viele includes zu vermeiden.