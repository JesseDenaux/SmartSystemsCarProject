#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <WiFi.h>              // Standard ESP32 Library
#include <PubSubClient.h>      // https://github.com/knolleary/pubsubclient (intall with library Manager)

//LIJN == 1
#define ADRES_SENSOR 8
#define LINETRACKER 1
#define USSENSOR 2
#define IRSENSOR 3

//Afstand van 10cm gekozen om wagen achteruit te laten rijden voor 1 seconde
#define afstand_threshold 10

float afstand_obstakel_us = 0;
float afstand_obstakel_ir = 0;

float us_afstand_cm = 0;
float ir_afstand_cm = 0;

// WIFI Credentials
// Connect to Hotspot on mobile phone
const char* WIFI_SSID = "jessephone"; // Fill wifi SSID between quotes
const char* WIFI_PASS = "passwoord"; // Fill wifi pass between quotes

//MQTT Information
const char* MQTT_SERVER = "mqtt.luytsm.be";
const char* TOPIC = "motorstand";

// WIFI and MQTT class instances 
WiFiClient espClient;
PubSubClient client(espClient);

// Buffer voor MQTT messages 
char msg[32];

// PWM Settings
const int PWM_FREQUENCY = 500;
const int PWM_RESOLUTION = 8;
const int PWM_MAX_DC = 255;

// Motor PWM Pin declaratie
const int PWM_CHANNEL_COUNT = 4;
const int MOTOR_COUNT = 2;

int MOTOR_PINS[PWM_CHANNEL_COUNT] = {18, 5, 2, 15};
int MOTOR_CHANNELS[PWM_CHANNEL_COUNT] = {0, 1, 2, 3};

//I2C LCD Initialisatie
//int LCD_COLUMNS = 16;
//int LCD_ROWS = 2;
//LiquidCrystal_I2C lcd(0x27, LCD_COLUMNS, LCD_ROWS);

// Phototransitor Pin Declaratie
const int PL_PIN = 25;
const int TRIG_PIN = 19;
const int ECHO_PIN = 23;

enum COMMANDS {
  LEFT_TURN_FORWARD,      // 0
  FORWARD,                // 1
  RIGHT_TURN_FORWARD,     // 2
  RIGHT,                  //3
  RIGHT_TURN_BACKWARDS,   //4
  BACKWARDS,              //5
  LEFT_TURN_BACKWARDS,    //6
  LEFT,                   //7
  STOP,                   //8
  LIJN_VOLGEN,            //9
  VOORBESTEMD_PROGRAMMA   //10
};


// Enum declaration for driving direction
// This is done to ensure that the right value is assigned  to the correct
// variable and easy usage in switch statement
enum MOTOR_DIRECTION {
  MOTOR_BACKWARDS = -1,
  MOTOR_STOP = 0,
  MOTOR_FORWARD = 1
};

//variables to store commands and information
int command, lastCommand;

int drivingSpeed = 128;

byte linetracker;
#define LINKS true
#define RECHTS false
bool vorige_afslag = LINKS;

// Function to setup wifi
void setup_wifi() {
  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(WIFI_SSID);

  WiFi.begin(WIFI_SSID, WIFI_PASS);
  //Display that we still are trying to connect
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  // Normaly the wifi will connect very fast. If it hangs reset the controller with EN button
  // This needs to be done after the controller is programmed

  // Print connection information
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

// Function to (re)connect to the MQTT server
void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect("ESP8266Client")) {
      Serial.println("connected WD");
      // Subscribe
      client.subscribe(TOPIC);
      client.publish(TOPIC, "connected WD");
    }
    else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Wire.begin();

  for (int i = 0; i < PWM_CHANNEL_COUNT; i++) {
    ledcSetup(MOTOR_CHANNELS[i], PWM_FREQUENCY, PWM_RESOLUTION);
    ledcAttachPin(MOTOR_PINS[i], MOTOR_CHANNELS[i]);
  }

  // wifi init
  setup_wifi();

  //mqtt init
  client.setServer(MQTT_SERVER, 1883);
  client.setCallback(callback);

//  lcd.init();
//  lcd.backlight();
}

//This function is called when MQTT receives a message
void callback(char* topic, byte* message, unsigned int length) {
  memset(msg, '\0', sizeof(msg));       // clear the execisting data in the buffer
  memcpy(msg, (char*)message, length);  // copy the byte array to char array
  Serial.print("msg: ");                // print msg (1/2)
  Serial.println(msg);                  // print msg (2/2)
}

void loop() {
  // put your main code here, to run repeatedly:
  if (!client.connected()) {
    reconnect();
  }

  // every loop we will run the MQTT loop and trigger the callback function if neccesary
  client.loop();

  //convert the msg Array TO Integert
  command = atoi(msg);

  if (command != lastCommand) {
        Serial.print("Command: ");
        Serial.println(command);

        //Checken afstand en indien kleiner dan threshold rijden achteruit voor 1 seconde
//        afstand_obstakel_us = usSensor();
//        afstand_obstakel_ir = irSensor();
//        if (afstand_obstakel_us < afstand_threshold || afstand_obstakel_us < afstand_threshold){
//          driveMotors(MOTOR_BACKWARDS, drivingSpeed, MOTOR_BACKWARDS, drivingSpeed);
//          delay(1000);
//        }
        
        switch (command) {
        case LEFT_TURN_FORWARD:  // Curved turn forward to the left
            driveMotors(MOTOR_FORWARD, drivingSpeed, MOTOR_FORWARD, drivingSpeed / 2);
            break;
        case FORWARD: // Drive forward
            driveMotors(MOTOR_FORWARD, drivingSpeed, MOTOR_FORWARD, drivingSpeed);
            break;
        case RIGHT_TURN_FORWARD: // Curved turn forward to the right
            driveMotors(MOTOR_FORWARD, drivingSpeed / 2, MOTOR_FORWARD, drivingSpeed);
            break;
        case RIGHT: // Turn right around center point chassis
            driveMotors(MOTOR_BACKWARDS, drivingSpeed, MOTOR_FORWARD, drivingSpeed);
            break;
        case RIGHT_TURN_BACKWARDS: // Curved turn backwards to the right
            driveMotors(MOTOR_BACKWARDS, drivingSpeed / 2, MOTOR_BACKWARDS, drivingSpeed);
            break;
        case BACKWARDS: // Drive backwards
            driveMotors(MOTOR_BACKWARDS, drivingSpeed, MOTOR_BACKWARDS, drivingSpeed);
            break;
        case LEFT_TURN_BACKWARDS: // Curved turn backwards to the right 
            driveMotors(MOTOR_BACKWARDS, drivingSpeed, MOTOR_BACKWARDS, drivingSpeed / 2);
            break;
        case LEFT: // Turn left around center point chassis
            driveMotors(MOTOR_FORWARD, drivingSpeed, MOTOR_BACKWARDS, drivingSpeed);
            break;
        case STOP: // Stop driving
            driveMotors(MOTOR_STOP, 0, MOTOR_STOP, 0);
            break;
        case LIJN_VOLGEN:
            lijnVolgen();
            break;
        case VOORBESTEMD_PROGRAMMA:
            voorbestemdProgramma();
            break;
        default: //Set the driving speed 
            drivingSpeed = command;
            break;
        }
        lastCommand = command; //Another question on the assignment, why is this statement necessary 
    }
}
 
void lijnVolgen(){
  Wire.beginTransmission(ADRES_SENSOR);
  Wire.write(LINETRACKER);
  Wire.endTransmission();
  Wire.requestFrom(ADRES_SENSOR, 1);
  while (Wire.available()) {
    linetracker = Wire.read();
    Serial.println(linetracker, BIN);
  }
  
  if (linetracker == 0b11111111 || linetracker == 0b11111110 ||  linetracker == 0b01111111) {
    driveMotors(MOTOR_STOP, 0, MOTOR_STOP, 0);
    delay(250);
    richtingKiezen(500);
  }
  else if ((linetracker == 0b11111100 || linetracker == 0b11111000) &&  vorige_afslag == LINKS) {
    richtingKiezen(500);
  }
  else if ((linetracker == 0b00111111 || linetracker == 0b00011111) && vorige_afslag == RECHTS) {
    richtingKiezen(500);
  }
  
  else if (linetracker == 0b11111111) { //Bij obstakel
    richtingKiezen(150);
    driveMotors(MOTOR_BACKWARDS, drivingSpeed, MOTOR_BACKWARDS, drivingSpeed);
    delay(500);
  }
  else if (linetracker & (1 << 1)) {
    driveMotors(MOTOR_FORWARD, drivingSpeed / 2, MOTOR_FORWARD, drivingSpeed * 2); //Links draaien
    Serial.println("Links draaien");
    delay(150);
  }
  else if (linetracker & (1 << 6)){
    driveMotors(MOTOR_FORWARD, drivingSpeed * 2, MOTOR_FORWARD, drivingSpeed / 2); //Rechts draaien
    Serial.println("Rechts draaien");
    delay(150);
  }

  else {
    driveMotors(MOTOR_FORWARD, drivingSpeed, MOTOR_FORWARD, drivingSpeed); //Rechtdoor rijden
    Serial.println("Rechtdoor");
  }
  delay(50);
}


void richtingKiezen(int pauze) {
  if (vorige_afslag == LINKS) {
    driveMotors(MOTOR_BACKWARDS, drivingSpeed * 2, MOTOR_FORWARD, int(drivingSpeed * 1.5)); //Rechts draaien
    Serial.println("Rechts draaien");
    delay(pauze);
  }
  else if (vorige_afslag == RECHTS) {
    driveMotors(MOTOR_FORWARD, int(drivingSpeed * 1.5), MOTOR_BACKWARDS, drivingSpeed * 2); //Links draaien
    Serial.println("Links draaien");
    delay(pauze);
  }
  byte linetracker_bocht;
  Wire.write(LINETRACKER);
  while (Wire.available()) {
    linetracker_bocht = Wire.read();
  }
  if (linetracker_bocht & (1 << 3) && linetracker_bocht & (1 << 4) || linetracker_bocht & (1 << 2) && linetracker_bocht & (1 << 3) || linetracker_bocht & (1 << 4) && linetracker_bocht & (1 << 5)) {
    if (pauze <= 50) {
      richtingKiezen(pauze);
    }
    else {
      richtingKiezen(pauze / 2);
    }
  }
  else {
    vorige_afslag = !vorige_afslag;
  }
}

void voorbestemdProgramma(){
  //Voorwaarts rijden, links draaien, voorwaarts rijden, rechts draaien, achteruit rijden, links curved draaien, voorwaarts rijden, rechts curved, stoppen
//  lcd.print("Voorbestemd programma aan het rijden");
  drivingSpeed=250;
  
  driveMotors(MOTOR_FORWARD, drivingSpeed/2, MOTOR_FORWARD, drivingSpeed); // Curved turn forward to the right
  delay(1000);
  driveMotors(MOTOR_FORWARD, drivingSpeed, MOTOR_FORWARD, drivingSpeed); // Drive forward
  delay(1000);
  driveMotors(MOTOR_FORWARD, drivingSpeed, MOTOR_FORWARD, drivingSpeed/2); // Curved turn forward to the left
  delay(1000);
  driveMotors(MOTOR_STOP, 0, MOTOR_STOP, 0); // Stop driving
  delay(1000);
  driveMotors(MOTOR_BACKWARDS, drivingSpeed, MOTOR_BACKWARDS, drivingSpeed); // Drive backwards
  delay(1000);
  driveMotors(MOTOR_BACKWARDS, drivingSpeed, MOTOR_FORWARD, drivingSpeed); // Turn right around center point chassis
  delay(1000);
  driveMotors(MOTOR_STOP, 0, MOTOR_STOP, 0); // Stop driving
  delay(1000);
  driveMotors(MOTOR_BACKWARDS, drivingSpeed, MOTOR_BACKWARDS, drivingSpeed/2); // Curved turn backwards to the left
  delay(1000);
  driveMotors(MOTOR_STOP, 0, MOTOR_STOP, 0); // Stop driving
  delay(1000);
//  lcd.print("Voorbestemd programma voltooid");
  client.publish(TOPIC, "Voorbestemd programma voltooid");
}

byte usSensor(){
  Wire.beginTransmission(ADRES_SENSOR);
  Wire.write(USSENSOR);
  Wire.endTransmission();
  Wire.requestFrom(ADRES_SENSOR, 1);
  while (Wire.available()) {
    us_afstand_cm = Wire.read();
  }
  return byte(us_afstand_cm);
}

byte irSensor(){
  Wire.beginTransmission(ADRES_SENSOR);
  Wire.write(IRSENSOR);
  Wire.endTransmission();
  Wire.requestFrom(ADRES_SENSOR, 1);
  while (Wire.available()) {
    ir_afstand_cm = Wire.read();
  }
  return byte(ir_afstand_cm);
}

void driveMotors(int leftMotorDirection, int leftMotorSpeed, int rightMotorDirection, int rightMotorSpeed) {
//    lcd.clear(); // scherm leegmaken bij nieuw commando
//    lcd.setCursor(0, 0); // Cursor links bovenaan zetten

  switch (leftMotorDirection)
  {
    case MOTOR_BACKWARDS:
      Serial.println("Linker motor achteruit");
//      lcd.print("Linker motor achteruit"); // Tekst op het scherm zetten
      ledcWrite(MOTOR_CHANNELS[1], rightMotorSpeed); // Motor doet de rupsbanden naar achter draaien
      ledcWrite(MOTOR_CHANNELS[0], LOW); // Correcte PWM signaal sturen naar linker motor
      break;
    case MOTOR_STOP:
      Serial.println("Linker motor stop");
//      lcd.print("Linker motor stop");
      ledcWrite(MOTOR_CHANNELS[0], LOW);
      ledcWrite(MOTOR_CHANNELS[1], LOW); // Motorsnelheid wordt op 0 gezet
      break;
    case MOTOR_FORWARD:
      Serial.println("Linker motor vooruit");
//      lcd.print("Linker motor vooruit");
      ledcWrite(MOTOR_CHANNELS[1], HIGH); // Correcte PWM signaal sturen naar linker motor
      ledcWrite(MOTOR_CHANNELS[0], rightMotorSpeed); // Motor doet de rupsbanden naar voren draaien
      break;
    default:
      break;
  }

  switch (rightMotorDirection)
  {
    case MOTOR_BACKWARDS:
      Serial.println("Rechter motor achteruit");
//      lcd.print("Rechter motor achteruit");
      ledcWrite(MOTOR_CHANNELS[3], leftMotorSpeed); // Motor doet de rupsbanden naar achter draaien
      ledcWrite(MOTOR_CHANNELS[2], LOW);// Correcte PWM signaal sturen naar rechter motor
      break;
    case MOTOR_STOP:
      Serial.println("Rechter motor stop");
//      lcd.print("Rechter motor stop");
      ledcWrite(MOTOR_CHANNELS[2], LOW);
      ledcWrite(MOTOR_CHANNELS[3], LOW);// Motorsnelheid wordt op 0 gezet
      break;
    case MOTOR_FORWARD:
      Serial.println("Rechter motor vooruit");
//      lcd.print("Rechter motor vooruit");
      ledcWrite(MOTOR_CHANNELS[3], HIGH);// Correcte PWM signaal sturen naar rechter motor
      ledcWrite(MOTOR_CHANNELS[2], leftMotorSpeed); // Motor doet de rupsbanden naar voren draaien
      break;
    default:
      break;
  }
}
