# fountain-controller
This controller control water valves and LEDs using multiple relays by received commands. 

ESP32 - 4 Relay
----------------------------------
D15 - R4 - H2O 1 - Centras
D14 - R3 - H2O 2 - Vidinis žiedas
D13 - R2 - H2O 3 - Išorinis žiedas
         - H2O 4 - 0V (žemė)

ESP32 - Bottom 8 SSR
----------------------------------
D2  - R1 - 12V for LEDs
    - R2 -
D4  - R3 - 2LED 1 - Red
D5  - R4 - 2LED 2 - Green
D18 - R5 - 2LED 3 - Blue
           2LED 4 - 12V

D19 - R6 - 1LED 1 - Red
D21 - R7 - 1LED 2 - Green
D22 - R8 - 1LED 3 - Blue
         - 1LED 4 - 12V

ESP32 - Top 8 SSR
-----------------------------------
D27 - R3 - 4LED 1 - Red
D26 - R4 - 4LED 2 - Green
D25 - R5 - 4LED 3 - Blue
         - 4LED 4 - 12V

D23 - R8 - 3LED 1 - Red
D32 - R7 - 3LED 2 - Green
D33 - R6 - 3LED 3 - Blue
         - 3LED 4 - 12V
