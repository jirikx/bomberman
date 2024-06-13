## Možnosti hry

Moje implementace hry Bomberman umožňuje uživateli vybrat hru na mapě načtené z config souboru.
V tomto souboru si i nastaví, zda chce režim hry proti člověku na stejné klávesnici, nebo proti počítači, nebo kombinace obojího.
Hráč může ovládat pohyby svého panáčka, pokládat bomby, a nebo ukončit hru. Hráči si před hrou zapíšou do config souboru přezdívky,
pod kterými bude v žebříčku s výsledky uloženo jejich skóre (pokud vyhrají).
Hráči řízení počítačem nemůžou pokládat bombu, místo toho se jen snaží během svého tahu dotknout nepřítele a tím ho zabít. Stejnou
taktiku může použít i živý hráč - dotek je smrtelný pro kohokoliv.

Na herní mapě jsou umístěny zdi, po jejichž zničení může dojít k odemčení bonusu, který hráči zůstává do konce hry (pokud nemá dán limit).
Bonusy jsou následující:
- Hráč může přeskočit zeď (max. 1 blok), přičemž má omezený počet přeskoků
- Hráč získá extra životy
- Hráč získá extra bomby
- Plamen bomby má delší dosah
- Hráč je imunní vůči svým vlastním bombám (až do konce hry)
  Bonusy mají šanci na vygenerování nastavenou z config souboru.

Rozhraní hry je terminálové pomocí ncurses knihovny.


## Nastavení hry
- Viz příklady konfiguračních souborů ve složce examples/levels
- V konfiguračním souboru musí být vždycky aspoň 1 player
- Ovládání se nesmí překrývat
- Nemusí být definovány všechny bonusy najednou (nějaká kombinace klíč-hodnota může chybět)
- Číselné hodnoty u bonusů musí být celá čísla v intervalu <0, 100>

## Výchozí ovládání
- WASD - pohyb
- X - položení bomby
- Q - vypnutí hry

## Možnosti spuštění programu
- Kompilace a spuštění hry s výchozí konfigurací: `make run`
- Spuštení jiné než defaultní konfigurace: `./konviji1 <cesta_k_configu>`
- Zobrazení žebříčku nejlepších hráčů: `./konviji1 --leaderboard`

![Ukázka běžící hry](/readme/gameplay.png "Gameplay")