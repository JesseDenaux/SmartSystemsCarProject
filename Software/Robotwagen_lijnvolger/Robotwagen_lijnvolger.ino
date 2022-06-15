#include <Wire.h>
#include <SharpIR.h> 
#define I2C_ADDR 8

const byte LIJNVOLGER_PINS[] = {2, 3, 4, 5, 6, 7, 8, 9};
int trigPin = 11;         // TRIG pin
int echoPin = 10;         // ECHO pin
#define IRSensor = A0;   // IR sensor
#define model 1080

SharpIR mySensor = SharpIR(IRPin, model);

byte us_afstand_cm, tijd_us, ir_afstand_cm;

#define DEBUG
#define modus

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

    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);
    for (byte i = 0; i < 8; i++)
    {
        pinMode(LIJNVOLGER_PINS[i], INPUT);
    }
    Wire.begin(I2C_ADDR);
    
}

void loop()
{
    while (Wire.available()) {
      modus = Wire.read();
    }
    switch(modus){
      case 0:
        break;
      case 1:
        lineTracker();
        break;
      case 2:
        usSensor();
        break;
      case 3:
        irSensor();
        break;
      default:
        break;
    }
    delay(50);
}

void linetracker()
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

void usSensor(){
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  tijd_us = pulseIn(echoPin, HIGH);

  us_afstand_cm = byte(0.017 * tijd_us);

  Wire.write(us_afstand_cm);
}

void irSensor(){
  ir_afstand_cm = byte(mySensor.distance());
  Wire.write(ir_afstand_cm);
}
