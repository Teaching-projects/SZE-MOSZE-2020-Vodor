# SZE-MOSZE-2020-Vodor
Ez a repository a Vödör csapat megoldását tartalmazza.
## Csapattagok: 
* Borbély Roland 
* Vitéz Marcell
* Voznek Péter
## Leírás
Az indításnál 0 vagy 1 paramétert kell megadni a helyes lefutáshoz:
 - **0 paraméter:** Ebben az esetben a játék során a felhasználónak kell megadni a pályát, a Herot, valamint a Monstereket is. Ezek mindegyikéhez elérési útvonalat kell adni az adott elemet tartalmazó fájlhoz, illetve a Hero és a Monsterek esetében koordinátákat is.
 - **1 paraméter:** Ebben az esetben paraméterként egy JSON formátumú scenario fájlt kell átadni. A játék során azonban itt is meg kell adni a pályát, illetve az egyes Unitok koordinátáit a felhasználónak. Példa: `./a.out scenario1.json`

Egy játék elindítása után a játékos south, east, west, valamint north parancsokkal tud mozogni a pályán. Ha olyan mezőre lép a Hero, ahol Monster(ek) található(ak) csata veszi kezdetét. A csata addig tart, amíg a mezőn Monster(ek) található(ak). A játék addig tart, amíg a pályán van Monster, vagy a Hero meg nem hal.
 
### Használható parancsok a játék során
Menüben használható parancsok:
 - **setmap:** Játéktér beállítása.
 - **puthero:** Hero beállítása, ebből 1 lehetséges.
 - **putmonster:** Monster beállítása, ebből több is lehetséges.
 - **run:** A játék elindítása.
  - **exit:** Kilépés a programból.

Játék elindítása után használható parancsok:
 - **north:** a karakter mozgatása északi irányba
 - **south:** a karakter mozgatása déli irányba
 - **east:** a karakter mozgatása keleti irányba
 - **west:** a karakter mozgatása nyugati irányba

### Documentation
https://teaching-projects.github.io/SZE-MOSZE-2020-Vodor/
