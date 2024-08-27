#include <Keypad.h>
#include <ESP32Servo.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Arduino.h>
#include <SD.h>
#include <WiFi.h>
#include <PubSubClient.h>
#include <Update.h>
#include <WiFiClientSecure.h> // For SSL/TLS


#define PASSWORD "1234"  // Set your password

#define SERVO_PIN_FOR_DOOR 4 // PWM pin for the door servo motor
#define ledPinDoor 23   // Define the LED pin for door control
#define BUZZER_PIN 15    // Digital pin for the buzzer

#define soundSensorPin 35  // Pin connected to the sound sensor's digital output
#define ledPinSound 16   // Pin connected to the LED

#define irSensorPin 34   // Analog pin for IR sensor
#define ledPinIR 17      // LED pin to turn on when distance is 10 units

#define pirSensorPin 18  // Digital pin for PIR sensor
#define ledPinPIR 19     // LED pin to turn on when motion is detected by PIR

#define ldrPin 36        // Analog pin for LDR (A0)
#define ledPinLDR 5      // LED pin to turn on when it's dark

#define SDA_PIN 21       // Custom I2C SDA pin
#define SCL_PIN 22       // Custom I2C SCL pin

#define buttonPin 2      // Pin connected to the pushbutton
#define ledPinbutton 1  // LED pin to turn on when the button is pressed

// Function prototypes
void activateBuzzer();

// Keypad configuration
const byte ROWS = 4; // Four rows
const byte COLS = 4; // Four columns
char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte rowPins[ROWS] = {13, 12, 14, 27}; // ESP32 pins connected to the row pins
byte colPins[COLS] = {26, 25, 33, 32}; // ESP32 pins connected to the column pins

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);
LiquidCrystal_I2C lcd(0x27, 16, 2); // LCD address 0x27, 16 columns, 2 rows

Servo doorServo;
int wrongPasswordAttempts = 0; // Counter for failed attempts
int buttonState = 0; // Variable for reading the pushbutton status
String inputPassword = "";

// MQTT Configuration
const char* mqtt_server = "e6c8bd5084724567a770aa56ecaa09e3.s1.eu.hivemq.cloud";
const int mqtt_port = 8883; // Secure port for MQTT
const char* mqtt_user = "Salsabil Mohamed";
const char* mqtt_password = "SalsabilMohamed12";

// Root CA Certificate for SSL/TLS
static const char* ca_cert PROGMEM = R"EOF(
-----BEGIN CERTIFICATE-----
MIIFazCCA1OgAwIBAgIRAIIQz7DSQONZRGPgu2OCiwAwDQYJKoZIhvcNAQELBQAw
TzELMAkGA1UEBhMCVVMxKTAnBgNVBAoTIEludGVybmV0IFNlY3VyaXR5IFJlc2Vh
cmNoIEdyb3VwMRUwEwYDVQQDEwxJU1JHIFJvb3QgWDEwHhcNMTUwNjA0MTEwNDM4
WhcNMzUwNjA0MTEwNDM4WjBPMQswCQYDVQQGEwJVUzEpMCcGA1UEChMgSW50ZXJu
ZXQgU2VjdXJpdHkgUmVzZWFyY2ggR3JvdXAxFTATBgNVBAMTDElTUkcgUm9vdCBY
MTCCAiIwDQYJKoZIhvcNAQEBBQADggIPADCCAgoCggIBAK3oJHP0FDfzm54rVygc
h77ct984kIxuPOZXoHj3dcKi/vVqbvYATyjb3miGbESTtrFj/RQSa78f0uoxmyF+
0TM8ukj13Xnfs7j/EvEhmkvBioZxaUpmZmyPfjxwv60pIgbz5MDmgK7iS4+3mX6U
A5/TR5d8mUgjU+g4rk8Kb4Mu0UlXjIB0ttov0DiNewNwIRt18jA8+o+u3dpjq+sW
T8KOEUt+zwvo/7V3LvSye0rgTBIlDHCNAymg4VMk7BPZ7hm/ELNKjD+Jo2FR3qyH
B5T0Y3HsLuJvW5iB4YlcNHlsdu87kGJ55tukmi8mxdAQ4Q7e2RCOFvu396j3x+UC
B5iPNgiV5+I3lg02dZ77DnKxHZu8A/lJBdiB3QW0KtZB6awBdpUKD9jf1b0SHzUv
KBds0pjBqAlkd25HN7rOrFleaJ1/ctaJxQZBKT5ZPt0m9STJEadao0xAH0ahmbWn
OlFuhjuefXKnEgV4We0+UXgVCwOPjdAvBbI+e0ocS3MFEvzG6uBQE3xDk3SzynTn
jh8BCNAw1FtxNrQHusEwMFxIt4I7mKZ9YIqioymCzLq9gwQbooMDQaHWBfEbwrbw
qHyGO0aoSCqI3Haadr8faqU9GY/rOPNk3sgrDQoo//fb4hVC1CLQJ13hef4Y53CI
rU7m2Ys6xt0nUW7/vGT1M0NPAgMBAAGjQjBAMA4GA1UdDwEB/wQEAwIBBjAPBgNV
HRMBAf8EBTADAQH/MB0GA1UdDgQWBBR5tFnme7bl5AFzgAiIyBpY9umbbjANBgkq
hkiG9w0BAQsFAAOCAgEAVR9YqbyyqFDQDLHYGmkgJykIrGF1XIpu+ILlaS/V9lZL
ubhzEFnTIZd+50xx+7LSYK05qAvqFyFWhfFQDlnrzuBZ6brJFe+GnY+EgPbk6ZGQ
3BebYhtF8GaV0nxvwuo77x/Py9auJ/GpsMiu/X1+mvoiBOv/2X/qkSsisRcOj/KK
NFtY2PwByVS5uCbMiogziUwthDyC3+6WVwW6LLv3xLfHTjuCvjHIInNzktHCgKQ5
ORAzI4JMPJ+GslWYHb4phowim57iaztXOoJwTdwJx4nLCgdNbOhdjsnvzqvHu7Ur
TkXWStAmzOVyyghqpZXjFaH3pO3JLF+l+/+sKAIuvtd7u+Nxe5AW0wdeRlN8NwdC
jNPElpzVmbUq4JUagEiuTDkHzsxHpFKVK7q4+63SM1N95R1NbdWhscdCb+ZAJzVc
oyi3B43njTOQ5yOf+1CceWxG1bQVs5ZufpsMljq4Ui0/1lvh+wjChP4kqKOJ2qxq
4RgqsahDYVvTH9w7jXbyLeiNdd8XM2w9U/t7y0Ff/9yi0GE44Za4rF2LN9d11TPA
mRGunUHBcnWEvgJBQl9nJEiU0Zsnvgc/ubhPgXRR4Xq37Z0j4r7g1SgEEzwxA57d
emyPxgcYxn/eR44/KJ4EBs+lVDR3veyJm+kXQ99b21/+jh5Xos1AnX5iItreGCc=
-----END CERTIFICATE-----
)EOF";

WiFiClientSecure espClient; // Use WiFiClientSecure for SSL/TLS
PubSubClient client(espClient);

void callback(char* topic, byte* payload, unsigned int length) {
  String message;
  for (unsigned int i = 0; i < length; i++) {
    message += (char)payload[i];
  }
  
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  Serial.println(message);

  if (String(topic) == "home/control/door") {
    if (message == "OPEN") {
      doorServo.write(180); // Open the door
      client.publish("home/control/door/status", "OPEN"); // Publish door status
    } else if (message == "CLOSE") {
      doorServo.write(90); // Close the door
      client.publish("home/control/door/status", "CLOSE"); // Publish door status
    }
  } else if (String(topic) == "home/control/ledDoor") {
    if (message == "ON") {
      digitalWrite(ledPinDoor, HIGH);
      client.publish("home/control/ledDoor/status", "ON"); // Publish LED status
    } else if (message == "OFF") {
      digitalWrite(ledPinDoor, LOW);
      client.publish("home/control/ledDoor/status", "OFF"); // Publish LED status
    }
  }else if (String(topic) == "home/control/ledSound") {
    if (message == "ON") {
      digitalWrite(ledPinSound, HIGH);
      client.publish("home/control/ledSound/status", "ON"); // Publish LED status
    } else if (message == "OFF") {
      digitalWrite(ledPinSound, LOW);
      client.publish("home/control/ledsound/status", "OFF"); // Publish LED status
    }
  } else if (String(topic) == "home/control/ledIR") {
    if (message == "ON") {
      digitalWrite(ledPinIR, HIGH);
      client.publish("home/control/ledIR/status", "ON"); // Publish LED status
    } else if (message == "OFF") {
      digitalWrite(ledPinIR, LOW);
      client.publish("home/control/ledIR/status", "OFF"); // Publish LED status
    }
  }  else if (String(topic) == "home/control/ledPIR") {
    if (message == "ON") {
      digitalWrite(ledPinPIR, HIGH);
      client.publish("home/control/ledPIR/status", "ON"); // Publish LED status
    } else if (message == "OFF") {
      digitalWrite(ledPinPIR, LOW);
      client.publish("home/control/ledPIR/status", "OFF"); // Publish LED status
    }
  } else if (String(topic) == "home/control/ledLDR") {
    if (message == "ON") {
      digitalWrite(ledPinLDR, HIGH);
      client.publish("home/control/ledLDR/status", "ON"); // Publish LED status
    } else if (message == "OFF") {
      digitalWrite(ledPinLDR, LOW);
      client.publish("home/control/ledLDR/status", "OFF"); // Publish LED status
    }
  } else if (String(topic) == "home/control/ledButton") {
    if (message == "ON") {
      digitalWrite(ledPinbutton, HIGH);
      client.publish("home/control/ledLDR/status", "ON"); // Publish LED status
    } else if (message == "OFF") {
      digitalWrite(ledPinbutton, LOW);
      client.publish("home/control/ledButton/status", "OFF"); // Publish LED status
    }
  }else if (String(topic) == "home/control/buzzer") {
    if (message == "ON") {
      activateBuzzer();
      client.publish("home/control/buzzer/status", "ON"); // Publish buzzer status
    } else if (message == "OFF") {
      client.publish("home/control/buzzer/status", "OFF"); // Publish buzzer status
    }
  }
}

void setup_wifi() {
  WiFi.begin("realme7Pro", "123456789"); // Replace with your Wi-Fi credentials
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("Connected to WiFi");
}

void setup() {
  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback);
  espClient.setCACert(ca_cert);


 // Initialize LCD with custom I2C pins
  Wire.begin(SDA_PIN, SCL_PIN);  // Initialize I2C communication with custom pins
  lcd.init();
  lcd.backlight();

  // Initialize Servos
  doorServo.attach(SERVO_PIN_FOR_DOOR);  // Attach the door servo to pin 4
  doorServo.write(90); // Start with door servo in the middle position (90 degrees)
  
  // Set up the LED pins
  pinMode(ledPinDoor, OUTPUT);  // LED for door
  pinMode(ledPinSound, OUTPUT); // LED for sound sensor
  pinMode(ledPinIR, OUTPUT);  // LED for ir
  pinMode(ledPinPIR, OUTPUT); // LED for pir
  pinMode(ledPinLDR, OUTPUT);  // LED for LDR
  pinMode(BUZZER_PIN, OUTPUT); // Buzzer pin
  pinMode(ledPinbutton, OUTPUT);  // LED for button
  pinMode(ldrPin, INPUT); // Changed from OUTPUT to INPUT
  pinMode(buttonPin, INPUT);

  
  pinMode(soundSensorPin, INPUT);  // Set sound sensor pin as input
  pinMode(irSensorPin, INPUT);     // Set IR sensor pin as input
  pinMode(pirSensorPin, INPUT);    // Set PIR sensor pin as input

  
  // Turn off LEDs initially
  digitalWrite(ledPinDoor, LOW);  
  digitalWrite(ledPinSound, LOW);
  digitalWrite(ledPinIR, LOW);
  digitalWrite(ledPinPIR, LOW);
  digitalWrite(ledPinLDR, LOW);
  digitalWrite(ledPinbutton, LOW); 
  digitalWrite(BUZZER_PIN, LOW);

  // Display initial message on LCD
  lcd.clear();
  lcd.print("Enter Password:");
  
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    String clientId = "ESP32Client-";
    clientId += String(random(0xffff), HEX);
    if (client.connect(clientId.c_str(), mqtt_user, mqtt_password)) {
      Serial.println("connected");
      // Subscribe to the topic for controlling devices
      client.subscribe("home/control/#");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
}

void activateBuzzer() {
  digitalWrite(BUZZER_PIN, HIGH);
  delay(1000);
  digitalWrite(BUZZER_PIN, LOW);
}


void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

// Keypad Input for Door Control
  char key = keypad.getKey();
  if (key) {
    if (key == '#') {
      if (inputPassword == PASSWORD) {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Access Granted");
        lcd.print("HALLO IN HOME");
        doorServo.write(180); // Open the door
        digitalWrite(ledPinDoor, HIGH);  // Turn on the LED
        client.publish("home/control/door", "OPEN"); // Publish door status
        client.publish("home/control/ledDoor", "ON"); // Publish led sound status
        delay(2000); // Keep door open for 2 seconds]
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Enter Password:");
        doorServo.write(90);           // Rotate back to 90 degrees (closed)
        digitalWrite(ledPinDoor, LOW); // Turn off the LED
        client.publish("home/control/door", "CLOSE"); // Publish door status
        client.publish("home/control/ledDoor", "OFF"); // Publish led sound status
        wrongPasswordAttempts = 0; // Reset wrong attempts
      } else {
        wrongPasswordAttempts++;
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Access Denied");
        delay(2000);
        if (wrongPasswordAttempts >= 3) {
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("Alert! Locked Out");
          activateBuzzer();
          client.publish("home/control/buzzer", "ON"); // Publish buzzer status
          delay(3000); // Keep buzzer active for 3 seconds
          client.publish("home/control/buzzer", "OFF"); // Publish buzzer status
          wrongPasswordAttempts = 0; // Reset wrong attempts
        } else {
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("Enter Password:");
        }
      }
      inputPassword = ""; // Clear input
    } else if (key == '*') {
      inputPassword = ""; // Clear input
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Enter Password:");
    } else {
      inputPassword += key;
      lcd.setCursor(0, 1);
      lcd.print(inputPassword);  // Print the actual input
    }
  }

      //sound
  int analogValue = analogRead(soundSensorPin); // Read analog value from AO pin
  Serial.println(analogValue); // Print the analog value (optional)
  //client.publish("home/sensors/sound", String(analogValue).c_str());
  // Check if the analog value is within the range
  if (analogValue >= 3000) {
    digitalWrite(ledPinSound, HIGH);
    client.publish("home/control/ledSound", "ON"); // Publish led sound status
  }else{
    digitalWrite(ledPinSound, LOW);
    client.publish("home/control/ledSound", "OFF"); // Publish led sound status
    }

// PIR

  int pirState = digitalRead(pirSensorPin); // Read the state of the PIR sensor
 // client.publish("home/sensors/PIR", String(pirState).c_str());
  if (pirState == HIGH) {
    digitalWrite(ledPinPIR, HIGH);  // Turn on the LED if motion is detected
    Serial.println("Motion Detected, LED ON");
    client.publish("home/control/ledPIR", "ON"); // Publish led sound status
   
  } else {
    digitalWrite(ledPinPIR, LOW);   // Turn off the LED if no motion is detected
    Serial.println("No Motion, LED OFF");
    client.publish("home/control/ledPIR", "OFF"); // Publish led sound status
  }

  //IR 
  
   int irValue = analogRead(irSensorPin); // Read the analog value from IR sensor
  float voltage = irValue * (3.3 / 4095.0); // Convert to voltage (assuming 3.3V ADC)
  float distance = 12.3 * pow(voltage, -1); // Convert voltage to distance (example formula)
  //client.publish("home/sensors/IR", String(irValue).c_str());
  Serial.print("Distance: ");
  Serial.println(distance);

  if (distance >= 6 ) {  // Turn on LED if distance is 10 units or less
    digitalWrite(ledPinIR, HIGH);
    Serial.println("Distance 10 or less, LED ON");
    client.publish("home/control/ledSound", "ON"); // Publish led sound status
  } else {
    digitalWrite(ledPinIR, LOW);
    Serial.println("Distance more than 10, LED OFF");
    client.publish("home/control/ledSound", "OFF"); // Publish led sound status
  }

  //Button
  // Read the state of the pushbutton value
  buttonState = digitalRead(buttonPin);
  Serial.println(buttonState);
 // client.publish("home/button", String(buttonState).c_str());

  // Check if the pushbutton is pressed.
  if (buttonState == HIGH) {
    // Turn LED on
    digitalWrite(ledPinbutton, HIGH);
    client.publish("home/control/ledButton", "ON"); // Publish led sound status
  } else {
    // Turn LED off
    digitalWrite(ledPinbutton, LOW);
    client.publish("home/control/ledButton", "OFF"); // Publish led sound status
  }

//LDR
  int ldrValue = analogRead(ldrPin);
  Serial.print("LDR Value: ");
  Serial.println(ldrValue);
 // client.publish("home/sensors/ldr", String(ldrValue).c_str());

  if (ldrValue < 500) {
    digitalWrite(ledPinLDR, HIGH); // Turn on LED if it's dark
    client.publish("home/control/ledLDR", "ON"); // Publish led sound status
  } else {
    digitalWrite(ledPinLDR, LOW);  // Turn off LED if it's bright
    client.publish("home/control/ledLDR", "OFF"); // Publish led sound status
  }

  delay(100); // Small delay to prevent excessive MQTT traffic
}