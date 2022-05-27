#include <Wire.h>
#define I2C_ADDR 8

const byte LIJNVOLGER_PINS[] = {2, 3, 4, 5, 6, 7, 8, 9};

#define DEBUG

#ifdef DEBUG
#define DEBUG_PRINT(x) Serial.print(x)
#define DEBUG_PRINTBIN(x) Serial.println(x, BIN)
#else
#define DEBUG_PRINT(x)
#define DEBUG_PRINTDEC(x)
#endif

void setup()
{
    Serial.begin(115200);

    for (byte i = 0; i < 8; i++)
    {
        pinMode(LIJNVOLGER_PINS[i], INPUT);
    }
    Wire.begin(I2C_ADDR);
    Wire.onRequest(requestEvent);
}

void loop()
{
    delay(50);
}

void requestEvent()
{
    byte outp = 0x00;
    // Bit 3 tot 6 uitlezen van PIND en bit 1 tot 2 van PINB, dan bits samenstellen tot één byte.
    outp=((((1 << 2) - 1) & (PINB >> (1 - 1))) << 6) | (((1 << 6) - 1) & (PIND >> (3 - 1)));

    // Nulletjes in Serial monitor aanvullen voor duidelijkheid
    if (outp < 2) DEBUG_PRINT(B0);
    if (outp < 4) DEBUG_PRINT(B0);
    if (outp < 8) DEBUG_PRINT(B0);
    if (outp < 16) DEBUG_PRINT(B0);
    if (outp < 32) DEBUG_PRINT(B0);
    if (outp < 64) DEBUG_PRINT(B0);
    if (outp < 128) DEBUG_PRINT(B0);
    DEBUG_PRINTBIN(outp);
    Wire.write(outp);
}
