# Projekt_Breakout

Pádlo se ovládá pomocí šipek doprava a doleva nebo pomocí kláves 'A' a 'D'.
Míč lze vypustit pomocí levého tlačítka myši nebo pomocí mezerníku.

Hráč má 3 míče na zničení 2 obrazovek kostek.
Po zničení celé obrazovky 2x, hráč vyhrává. Pokud se mu toto nepodaří tím, že vyčerpá všechny míče, hráč prohrává.

Je možné vytvořit svou vlastní mapu v textovém souboru.
Soubor může obsahovat maximálně 20 řádků a 14 sloupců (14 čísel oddělených mezerou).
Jednotlivé bloky jsou značený pomocí čísla 0 - 4.
0 - Volný prostor
1 - Žlutá
2 - Zelená
3 - Oranžová
4 - Červená
Mapu lze využít pomocí zadání cesty k souboru jako argument při spuštění programu.

Příklad mapy je přiložen jako soubor "map.txt" ve složce "build".
Ve složce "build" se také nachází spustitelný soubor "Breakout" a font "arial.ttf", který je nutný pro zobrazení textu ve hře.

Pro vytvoření souborů pro překlad (CMake) (nad kořenovou složkou): cmake -S ./ -B ./build
Pro přeložení programu (nad složkou "build"): make

!!! Font "arial.ttf" je nutný mít při spouštění uložený ve stejné složce jako je spustitelný soubor !!!
