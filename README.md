# SZE-MOSZE-2020-Vodor
Ez a repository a Vödör csapat megoldását tartalmazza.
## Csapattagok: 
* Borbély Roland 
* Vitéz Marcell
* Voznek Péter
## Leírás
Az indításnál 6 paramétert kell megadni a helyes lefutáshoz. Egy példa a bemenetre: *Maple 150 10 Sally 45 30*. Ezután lefut a játék, amelynek során folyamatosan kiírja a köröket. A játék addig tart, amíg az egyik karakter életereje el nem fogy, ekkor győztest hírdet a játék.

A program lefutását két osztály biztosítja: 
* Unit 
* Game
### Unit 
Az osztály 3 adattaggal rendelkezik, amelyek a karakterek nevét, életerejét és sebzését határozzák meg. 

Két függvényt - adattagokhoz tartozó getter függvényeken kívül - tartalmaz az osztály, az egyik a **takeDmg()**, ami sebzést oszt ki az adott karakterre egy előre megadaott érték alapján, a másik a(z) **isDead()**, ami azt vizsgálja, hogy az adott karakter meghalt-e.
### Game
Ez az osztály a program lefutását vezényeli le. 5 adattagot tartalmaz:
* **round**: a körök számát tartalmazza
* **winner**: logikai változó, ami azt jelzi van-e győztes
* **units**: egy vector, ami Unit osztályra mutató objektumokat tárol
* **att**, **def**: éppen aktuálisan támadó és védekező karaktert emeli ki
Ezenfelül 4 darab függvény van az osztályban.
* **initVector()**: feltölti a korrában említett vectort, az inditási paraméterként megadott adatokkal
* **setAttacker()**: kiválasztja a támadó és védekező felet
* **showStats()**: kiírja a karakterek információit 
* **runGame()**: levezényli a játékot
