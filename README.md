# fountain-controller
This controller control water valves and LEDs using multiple relays by received commands. 

| ESP32 | 4 Relay | Connector |    Description       |
|-------|---------|-----------|----------------------|
|  D2   |    R1   |           | 12V - LEDs Flush     |
|       |         |   H2O 4   |  0V - Ground         |
|  D14  |    R2   |   H2O 3   | 12V - External valve |
|  D13  |    R3   |   H2O 2   | 12V - Inner valve    |
|  D15  |    R4   |   H2O 1   | 12V - Center valve   |

| ESP32 | Bottom 8 SSR | Connector |    Wired     | Description |
|-------|--------------|-----------|--------------|-------------|
|       |      R1      |           |              |             |
|       |      R2      |           |              |             |
|  D27  |      R3      |   2LED 1  |  0V - Red    |  External   |
|  D26  |      R4      |   2LED 2  |  0V - Green  |  External   |
|  D25  |      R5      |   2LED 3  |  0V - Blue   |  External   |
|       |              |   2LED 4  | 12V - Power  |  External   |
|-------|--------------|-----------|--------------|-------------|
|  D23  |      R6      |   1LED 1  |  0V - Red    |  External   |
|  D22  |      R7      |   1LED 2  |  0V - Green  |  External   |
|  D33  |      R8      |   1LED 3  |  0V - Blue   |  External   |
|       |              |   1LED 4  | 12V - Power  |  External   |

| ESP32 |  Top 8 SSR   | Connector |    Wired     | Description |
|----------------------|-----------|--------------|-------------|
|       |      R1      |           |              |             |
|       |      R2      |           |              |             |
|  D4   |      R3      |   4LED 1  |  0V - Red    |  Inner      |
|  D5   |      R4      |   4LED 2  |  0V - Green  |  Inner      |
|  D8   |      R5      |   4LED 3  |  0V - Blue   |  Inner      |
|       |              |   4LED 4  | 12V - Power  |  Inner      |
|-------|--------------|-----------|--------------|-------------|
|       |              |   3LED 4  | 12V - Power  |  Center     |
|  D19  |      R6      |   3LED 3  |  0V - Blue   |  Center     |
|  D21  |      R7      |   3LED 2  |  0V - Green  |  Center     |
|  D22  |      R8      |   3LED 1  |  0V - Red    |  Center     |
