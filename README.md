# Abschlussarbeit Semniar Angewandte Informatik

Dieses Repository stellt den Beispielcode fuer eine Seminararbeit bereit. Diese Seminararbeit wurde an der htw saar 
fuer das Wahlpflichtmodul Seminar Angewandte Informatik (Studiengang Praktische Informatik) von Lukas Reichmann 
erstellt.

## Uebersetzen
Zum Uebersetzen des Programmes ist CMake (https://cmake.org/) und ein C Compiler benötigt.

Die folgenden Befehle uebersetzen den Quellcode in ein ausfuerbahres Programm. Es wird davon ausgegangen, dass sich 
das CWD im Wurzelverzeichnis des Projektes befindet (das Verzeichnis, in dem diese Datei liegt).

```
mkdir build
cd build
cmake ..
cmake --build .
```

Nachdem diese Befehle erfolgreich ausgefuehrt wurden, befindet sich eine ausfuehrbare Datei mit dem Namen 
"opengl-example".
