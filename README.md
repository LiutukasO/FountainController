# Fountain Controller

Fontanas valdomas per **DMX512**: ESP32 (receiver) siunčia DMX komandas per RS485 į dekoderius, kurie valdo vandens vožtuvus ir RGB LED grupes.

Antras modulis — **Sender** (ESP32) — gali siųsti komandas per **ESP-NOW** (WiFi), bet pats fontanas reaguoja per DMX magistralę.

## Projekto struktūra

| Failas / modulis | Paskirtis |
|------------------|-----------|
| `src/receiver.h` + `main.cpp` | DMX receiver — valdo fontaną per dekoderius |
| `src/sender.h` | ESP-NOW siuntėjas (garso analizė, demo) |
| `src/dmx/ESPDMX.cpp` | DMX512 siuntimas (esp_dmx biblioteka) |
| `src/parameters.h` | Kanalų grupės, MAC adresai |

**PlatformIO aplinka:** `esp32doit-devkit-v1`

```bash
pio run -e esp32doit-devkit-v1
pio run -e esp32doit-devkit-v1 -t upload
```

---

## DMX kanalų žemėlapis

Programa siunčia reikšmes į **kanalus 1–16** (likę kanalai 17–512 = 0). Nustatymai faile `src/parameters.h`:

| DMX kanalas | Paskirtis | Reikšmė |
|-------------|-----------|---------|
| **1** | Vožtuvas — center | 0 = OFF, 255 = ON |
| **2** | Vožtuvas — ring1 | 0 / 255 |
| **3** | Vožtuvas — ring2 | 0 / 255 |
| **4** | Vožtuvas — ring3 | 0 / 255 |
| **5** | LED1 (center) — R | 0–255 |
| **6** | LED1 — G | 0–255 |
| **7** | LED1 — B | 0–255 |
| **8** | LED2 (middle) — R | 0–255 |
| **9** | LED2 — G | 0–255 |
| **10** | LED2 — B | 0–255 |
| **11** | LED3 (external) — R | 0–255 |
| **12** | LED3 — G | 0–255 |
| **13** | LED3 — B | 0–255 |
| **14** | LED4 (external) — R | 0–255 |
| **15** | LED4 — G | 0–255 |
| **16** | LED4 — B | 0–255 |

---

## ESP32 → RS485 → DMX jungtis

```
ESP32 GPIO4  ──►  RS485 DI
ESP32 3.3V   ──►  RS485 DE + RE (sujungti kartu, nuolatinis siuntimo režimas)
RS485 A, B   ──►  DMX dekoderiai (daisy-chain)
RS485 GND    ──►  Bendras GND su dekoderiais
```

| RS485 / XLR | Signalas |
|-------------|----------|
| GND (XLR 1) | Bendra masa |
| A (XLR 3 / Data+) | DMX+ |
| B (XLR 2 / Data−) | DMX− |

Debug: `src/dmx/ESPDMX.cpp` faile atkomentuokite `#define DMX_TRACE` — Serial Monitor rodys kanalus 1–16 kiekvieno siuntimo metu.

---

## DMX dekoderių adresų (DIP) konfigūracija

Dekoderio **1-as išėjimas** klauso DMX kanalo, kurį nurodo **adreso DIP jungikliai**.  
Kiti išėjimai eina iš eilės: 2-as išėjimas = startinis kanalas + 1, ir t.t.

Tipinis skaičiavimas (Decoder512, 30 kanalų ir panašūs):

```
Startinis DMX kanalas = 1 + (DIP1×1 + DIP2×2 + DIP3×4 + DIP4×8 + DIP5×16 + …)
```

### Du atskiri dekoderiai (rekomenduojama schema)

| Dekoderis | Kanalų sk. | Paskirtis | Startinis kanalas | DIP (1+2+4+8+16…) |
|-----------|------------|-----------|-------------------|-------------------|
| **#1** | 4 | Vožtuvai | **1** | Visos **OFF** |
| **#2** | 16 | LED RGB | **5** | Tik **3** svirtis ON (reikšmė 4 → 1+4=**5**) |

**Vožtuvų dekoderis (adresas 1):**

| Dekoderio išėjimas | DMX kanalas | Vožtuvas |
|--------------------|-------------|----------|
| OUT 1 | 1 | Center |
| OUT 2 | 2 | Ring1 |
| OUT 3 | 3 | Ring2 |
| OUT 4 | 4 | Ring3 |

**LED dekoderis (adresas 5):**

| Dekoderio išėjimas | DMX kanalas | LED |
|--------------------|-------------|-----|
| OUT 1 | 5 | LED1 R |
| OUT 2 | 6 | LED1 G |
| OUT 3 | 7 | LED1 B |
| OUT 4 | 8 | LED2 R |
| OUT 5 | 9 | LED2 G |
| OUT 6 | 10 | LED2 B |
| OUT 7 | 11 | LED3 R |
| OUT 8 | 12 | LED3 G |
| OUT 9 | 13 | LED3 B |
| OUT 10 | 14 | LED4 R |
| OUT 11 | 15 | LED4 G |
| OUT 12 | 16 | LED4 B |
| OUT 13–16 | 17–20 | nenaudojami (lieka 0) |

#### DIP lentelė startiniam kanalui 5

(Standartinė binary schema: DIP1=1, DIP2=2, DIP3=4, DIP4=8, DIP5=16)

| Startinis kanalas | DIP1 (1) | DIP2 (2) | DIP3 (4) | DIP4 (8) | DIP5 (16) |
|-------------------|----------|----------|----------|----------|-----------|
| **1** | OFF | OFF | OFF | OFF | OFF |
| **5** | OFF | OFF | **ON** | OFF | OFF |
| **17** | OFF | OFF | OFF | OFF | **ON** |

> **Pastaba:** skirtingų gamintojų plokštės gali turėti skirtingą jungiklių numeraciją ant korpus. Visada tikrinkite silkscreen užrašą **1, 2, 4, 8…** ant pačios plokštės.
