# Tagok

| Név | Github azonosito  | Javasolt relatív érdemjegy | Becsült óra | Indoklás  | 
| --- | ---- | --- | ------------------ | --------- |
| Borbély Roland | @rolandborbely | +1 | 50-60 | Projekt managerként fogta össze a csapatot. A kiadott feladatokat a legrövidebb határidőn belül szépen megoldotta. Program kódjai szépek és átláthatóak. Tananyaghoz kapcsolódó feladatok megoldását átlátja, érti és alkalmazni is tudja. A Daemons csapat review-olásában jelentősen részt vett. |
| Vitéz Marcell | @vit3z-marcell | -2 | <10 | A rábízott feladatokat nehézkesen oldotta meg. |
| Voznek Péter | @petinexus | 0 | 40-50 | A feladatok megoldásakor az esetek döntő többségében jelen volt, segédkezett bennük, sokat ő végzett el. Amikor kellett jött és segített, a rá bízott feladatokat önállóan megoldotta. A dokumentáció legnagyobb részét ő készítette el, de a többi, tananyaghoz kapcsolódó feladat megoldását is közelről, érdeklődően figyelte, így alkalmazni is tudja őket. A Daemons csapat review-olásában is részt vett. |


# Videók

 - [Gameplay](/videos/mosze_vodor_gameplay.mp4)
 - [CodeBaseDefense](/videos/mosze_vodor_codebasedefense.mp4)

# Befejezett feladatok

| Feladat | Merge ideje a határidóhöz (nap) | Change request körök | Reviewer | 
| ------- | ------------------------------- | -------------------- | -------- |
| Feladat 1 | -3 | 2 | @hegyhati | 
| Feladat 2 | +3 | 0 | @wajzy |
| jsonparser | +2 | 1 | @wajzy |
| levelup | -1 | 2 | @oliverosz |
| attackspeed | -5 | 0 | @vizvezetek |
| documentation | -7 | 1 | @daemons / @Lazar-source, @mesmatyi |
| unittest | -4 | 0 | @daemons / @Lazar-source, @mesmatyi |
| makefile | -5 | 3 | @hegyhati |
| refactor | 0 | 1 | @hegyhati |
| docker | -6 | 1 | @hegyhati |
| jsonpimp | Merge: 11.12 | 0 | @petinexus |
| map | Merge: 11.20 | 0 | @daemons / @Lazar-source |
| game | Merge: 11.26 | 1 | @daemons / @Lazar-source, @mesmatyi |
| defense | Merge: 11.23 | 1 | @daemons / @Lazar-source |
| damage | Merge: 11.21 | 1 | @daemons / @Lazar-source  |
| markedmap | Merge: 12.01 | 0 | @daemons / @Lazar-source |
| preparedgame | Merge: 12.02 | 0 | @daemons / @mesmatyi |
| light radius | Merge: 12.02 | 0 | @daemons / @Lazar-source |
| rendering | Merge: 12.03 | 0 | @daemons / @Lazar-source, @mesmatyi |

# Unit tesztek

| Osztály | Publikus metódusok száma | Unit tesztelt metódusok száma | Unit tesztek száma |
| --- | --- | --- | --- |
| `Unit` | 8 | 6 | 7 |
| `Hero` | 9 | 6 | 8 | 
| `Monster` | 3 | 2 | 8 |
| `JSON` | 6 | 5 | 8 |
| `Game` | 12 | 5 | 2 |
| `PreparedGame` | 3 | 1 | 2 |
| `Map` | 6 | 2 | 1 |
| `MarkedMap` | 4 | 3 | 2 |
| `Render` | 1 | 0 | 0 |
| `SVGRenderer` | 2 | 0 | 0 |
| `CharacerSVGRenderer` | 2 | 0 | 0 |
| `ObserverSVGRenderer` | 2 | 0 | 0 |
| `TextRenderer` | 3 | 0 | 0 |
| `HeroTextRenderer` | 2 | 0 | 0 |
| `ObserverTextRenderer` | 2 | 0 | 0 |

# Kód dokumentáció

| Teljesen dokumentált osztályok | Részben dokumentált osztályok | Nem dokumentált osztályok |
| --- | --- | --- | 
| `Unit` | - | - |
| `Hero` | - | - |
| `Monster` | - | - |
| `JSON` | - | - |
| `Game` | - | - |
| `PreparedGame` | - | - |
| `Map` | - | - |
| `MarkedMap` | - | - |
| `Render` | - | - |
| `SVGRenderer` | - | - |
| `CharacerSVGRenderer` | - | - |
| `ObserverSVGRenderer` | - | - |
| `TextRenderer` | - | - |
| `HeroTextRenderer` | - | - |
| `ObserverTextRenderer` | - | - |


# Mindenféle számok

 - Összes cpp kódsor : 1230 (whitespace nélkül)
 - Egyéb kódsor (make,doxyfile,shellscript, ...) :
    - make: 52
    - doxy: 212
    - shell script: 6
    - docker: 16
    - yml: 49
 - cppcheck
   - warning : 0
   - style : 8
   - performance : 0
   - unusedFunction : 0
   - missingInclude : 1
 
# Implicit megtanult dolgok
Olyanok, amik nem a tárgy anyaga, de muszáj/hasznos volt elsajátítani:
 - alapvető shell scripting
 - `std::variant`
 - reguláris kifejezések használata
 - alapvető linux ismeretek

# Feedback

- Úgy érzem ez az egyik leghasznosabb tárgy az egész képzés során, még nem használtam a tanult eszközöket, de a jövőben biztos vagyok benne, hogy hasznát veszem ezeknek. Tetszik a gyakorlatias jellege a tárgynak, sokkal életszerűbbek körülmények így, mint bármi más tárgy esetében. A videós megoldás véleményem szerint jó volt, érthetőbb és könnyebben felfogható így az egész, mint teremben kivetített dolgokat nézegetni. (@rolandborbely)

- Nagyon tetszett, hogy a hetente kiadott feladatokat és a hozzá kapcsolódó anyagokat nem külön-külön kellett feldolgozni/megérteni, hanem egy projekt részeként. A videós formában tartót előadásokat, szerintem hasznosak voltak, mivel így elakadás esetén segített a hiba feltárásában. GUI-s megjelenítést vagy nyilakkal való irányítást hiányoltam a programból. (@petinexus)

# Üzenet a jövőbe

- A tervezett eszközök, technológiák kicsit részletesebben le lehetnének írva a félév elején, mint ami a tematikában van, mégha nem is jut idő mindenre végül. Ezen kívül szerintem akár maradhat is a videós oktatás. (@rolandborbely)

- GUI-s megjelenítést. (@petinexus)

Így, hogy túlvagytok rajta, mi az, aminek örültetek volna, ha első héten elmondom, avagy: jövőre mit lenne jó, ha elmondanék majd?
