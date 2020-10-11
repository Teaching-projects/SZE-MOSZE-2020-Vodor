# SZE-MOSZE-2020-Vodor
Ez a repository a Vödör csapat megoldását tartalmazza.
## Csapattagok: 
* Borbély Roland 
* Vitéz Marcell
* Voznek Péter
## Leírás
Az indításnál 2 paramétert kell megadni a helyes lefutáshoz, ez két fájlnevet/elérési utat jelent. Egy példa a bemeneti paraméterekre: *unit1.json unit2.json*. Ezután lefut a játék, amely leszimulálja a két karakter közötti harcot. A játék addig tart, amíg az egyik karakter életereje el nem fogy, ekkor győztest hírdet a játék.

A program lefutását két osztály biztosítja: 
* Unit 
* Game
### Unit 
Az osztály 3 adattaggal rendelkezik, amelyek a karakterek nevét, életerejét és sebzését határozzák meg. 

Három függvényt - adattagokhoz tartozó getter függvényeken kívül - tartalmaz az osztály, az egyik a **takeDmg()**, ami sebzést oszt ki az adott karakterre egy előre megadaott érték alapján, a másik a(z) **isDead()**, ami azt vizsgálja, hogy az adott karakter meghalt-e. Ezeken felül a **parseUnit()**, amely az inputként megadott fájlok feldolgozásáért felelős.

### Game
Ez az osztály a program lefutását vezényeli le. 2 adattagot tartalmaz:
* **u1**, **u2**: a játékban részt vevő két karakter

Ezenfelül 1 darab függvény van az osztályban. 
* **runGame()**: levezényli a játékot

### Documentation
https://teaching-projects.github.io/SZE-MOSZE-2020-Vodor/
