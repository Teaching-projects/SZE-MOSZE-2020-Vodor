# SZE-MOSZE-2020-Vodor
Ez a repository a Vödör csapat megoldását tartalmazza.
## Csapattagok: 
* Borbély Roland 
* Vitéz Marcell
* Voznek Péter
## Leírás
Az indításnál paraméterként egy JSON formátumú scenario fájlt kell megadni a helyes lefutáshoz. Példa: `./a.out scenarios/scenario5.json`

Egy játék elindítása után a játékos south, east, west, valamint north parancsokkal tud mozogni a pályán. Ha olyan mezőre lép a Hero, ahol Monster(ek) található(ak) csata veszi kezdetét. A csata addig tart, amíg a mezőn Monster(ek) található(ak). A játék addig tart, amíg a pályán van Monster, vagy a Hero meg nem hal.

A játék futása során négyféle kimenet keletkezik a jelenlegi beállítások alapján:
 - SVG fájlba menti az éppen aktuális pályát a program.
 - SVG fájlba menti a Hero által "belátott" területet a program.
 - Konzolra kiírja az aktuális pályát a program.
 - Konzolra kiírja a Hero által "belátott" területet a program.
 
Az SVG fájlokban mindig az utolsó lépés utáni kimenet látható.
### Használható parancsok a játék során

 - **north:** a karakter mozgatása északi irányba
 - **south:** a karakter mozgatása déli irányba
 - **east:** a karakter mozgatása keleti irányba
 - **west:** a karakter mozgatása nyugati irányba

### Documentation
https://teaching-projects.github.io/SZE-MOSZE-2020-Vodor/
