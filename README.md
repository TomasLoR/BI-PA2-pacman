# Tahový Pacman

## Popis aplikace

Tahový Pacman je zjednodušená, tahová verze známé hry Pacman, která se hraje v konzoli. Hráč ovládá postavu Pacmana, jehož cílem je sesbírat všechny mince na mapě a vyhýbat se duchům. Hra je plně konfigurovatelná ze souborů, včetně map, obtížnosti a chování duchů.

## Pravidla hry

- Cílem hry je sesbírat všechny mince na mapě.
- Pokud duch chytí Pacmana, Pacman ztratí jeden život a všechny postavy se vrátí na své startovní pozice.
- Hra končí, když Pacman ztratí všechny životy nebo když sesbírá všechny mince.
- Po dohrání se vaše skóre uloží do tabulky nejlepších hráčů.

## Ovládání

Pohyb Pacmana se ovládá pomocí následujících kláves:
- `w` - nahoru
- `a` - doleva
- `s` - dolů
- `d` - doprava

## Herní mechaniky a objekty

| Znak | Objekt | Popis | Skóre |
| :--- | :--- | :--- | :--- |
| `P` | **Pacman** | Hlavní postava ovládaná hráčem. | |
| `.` | **Mince** | Základní předmět ke sbírání. | +1 |
| `@` | **Třešeň** | Umožní Pacmanovi dočasně jíst duchy. | +5 |
| `T` | **Teleport** | Okamžitě přemístí Pacmana na jiný teleport na mapě. | |
| `#` | **Zeď** | Nepřekonatelná překážka. | |
| `p` | **Start Pacmana** | Místo, kde Pacman začíná a vrací se po ztrátě života. | |
| `g` | **Start duchů** | Místo, kde duchové začínají a vrací se po snědení. | +50 |

### Duchové

| Znak | Duch | Chování | Skóre (při snědení) |
| :--- | :--- | :--- | :--- |
| `D` | **Dumb Ghost** | Pohybuje se náhodně. | +100 |
| `S` | **Smart Ghost** | Aktivně pronásleduje Pacmana pomocí BFS algoritmu. | +100 |
| `R` | **Pattern Ghost** | Pohybuje se podle předem definovaného vzoru. | +100 |
| `f` | **Vyděšený duch** | Poté, co Pacman sní třešeň, duchové přejdou do tohoto stavu, kdy utíkají před Pacmanem a mohou být snědeni. | |

## Spuštění programu

1.  **Kompilace a spuštění**: Použijte přiložený `Makefile` pro zkompilování a spuštění programu. Spusťte příkaz:
    ```bash
    make
    ```

2.  **Hlavní menu**: Po spuštění aplikace se zobrazí hlavní menu, kde si můžete vybrat:
    - Hrát hru
    - Zobrazit tabulku nejlepších hráčů
    - Nastavit obtížnost
    - Ukončit aplikaci

3.  **Výběr mapy**: Před začátkem hry si vyberete mapu ze souboru.

## Implementační poznámky

Pro implementaci polymorfismu byly využity virtuální metody:

-   **`CTile`**:
    -   `doEffect()`: Vyvolá různý efekt podle typu políčka (např. sebrání mince, teleportace).
    -   `print()`: Vykreslí různé typy políček.
-   **`CGhost`**:
    -   `move()`: Definuje pohyb ducha podle jeho typu (náhodný, chytrý, podle vzoru).
