# 5wins_raspi

https://trello.com/b/tEX1zA8r

## Informationen

Die finale Version des Projektes liegt vorerst im Branch "QTGui"

Ziel des Projektes war es, eine simple Version des Spieles "5 gewinnt" in C++ inkl. GUI mithilfe des Qt-Frameworks zu implementieren, welche auch über das Netzwerk spielbar ist, sowie auch auf einem Raspberry Pi mit Touch-Display spielbar ist.

Verwendet wurde QtCreator 6.0.2

## Installation

Um das Programm zu starten ist es am einfachsten 
[Qt-Creator 6 zu installieren](https://www.qt.io/download), 
danach das Repo zu clonen
```git clone https://github.com/j-weissen/5wins_raspi -b QTGui```
und in der IDE zu öffnen.

## Probleme
Das größte Problem bei der Fertigstellung dieses Projekts war, dass alter Code aufgegrffen und erweitert werden musste. Dieser war nicht schön programmiert, wodurch viel refactored wurden musste und der Code größtenteils immer noch messy ist. 
